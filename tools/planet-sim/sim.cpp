#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include "Arduino.h"
SerialStub Serial;
#ifndef PLANET_HEADER
#define PLANET_HEADER "../../firmware/movement-sequences.h"
#endif
#include PLANET_HEADER
int frameDelay = 100;
int walkCycles = 10;
int motorCurrentDelay = 20;
String currentCommand = "";
struct Ev { long t; char kind; int ch; int val; };  
static long simNow = 0;
static int angles[8];
static std::vector<Ev> trace;
static long interruptAt = -1;
static String interruptTo = "";
static int rawMin[8], rawMax[8];
static int minDelaySeen = 1 << 30, maxDelaySeen = 0;
static std::vector<std::string> facesUsed;
static void tick(long ms) {
  for (long i = 0; i < ms; i++) {
    simNow++;
    if (interruptAt >= 0 && simNow >= interruptAt) { currentCommand = interruptTo; interruptAt = -1; }
  }
}
void delayWithFace(unsigned long ms) { tick((long)ms); }
void setServoAngle(uint8_t channel, int angle) {
  if (channel < 8) {
    rawMin[channel] = std::min(rawMin[channel], angle);
    rawMax[channel] = std::max(rawMax[channel], angle);
    angles[channel] = constrain(angle, 0, 180);
    trace.push_back({simNow, 'w', channel, angle});
    minDelaySeen = std::min(minDelaySeen, motorCurrentDelay);
    maxDelaySeen = std::max(maxDelaySeen, motorCurrentDelay);
    delayWithFace(motorCurrentDelay);
  }
}
bool pressingCheck(String cmd, int ms) {
  trace.push_back({simNow, 'p', -1, ms});
  long start = simNow;
  while (simNow - start < ms) {
    if (currentCommand != cmd) { runStandPose(1); return false; }
    tick(1);
  }
  return true;
}
void setFace(const String& n) { facesUsed.push_back(n.c_str()); }
void setFaceMode(FaceAnimMode) {}
void setFaceWithMode(const String& n, FaceAnimMode) { setFace(n); }
void enterIdle() {}
bool planetDisplayStart(const char*) { return true; }   
void planetDisplayStop() {}
static int failures = 0;
#define CHECK(cond, ...) do { if (!(cond)) { failures++; std::printf("  FAIL: "); std::printf(__VA_ARGS__); std::printf("\n"); } } while (0)
static const int STAND[8] = {135, 45, 45, 135, 0, 180, 0, 180};  
static const char* FACES_WITH_BITMAPS[] = {
  "walk", "rest", "swim", "dance", "wave", "point", "stand", "cute", "pushup", "freaky", "bow", "worm",
  "shake", "shrug", "dead", "crab", "idle", "idle_blink", "happy", "sad", "angry", "surprised", "sleepy",
  "love", "excited", "confused", "thinking"};
static void resetRun() {
  for (int i = 0; i < 8; i++) { angles[i] = STAND[i]; rawMin[i] = 999; rawMax[i] = -999; }
  trace.clear();
  facesUsed.clear();
  simNow = 0;
  interruptAt = -1;
  minDelaySeen = 1 << 30; maxDelaySeen = 0;
}
static bool atStand() {
  for (int i = 0; i < 8; i++) if (angles[i] != STAND[i]) return false;
  return true;
}
static int stockMin[8], stockMax[8];
static void collectStockRanges() {
  for (int i = 0; i < 8; i++) { stockMin[i] = 999; stockMax[i] = -999; }
  struct { const char* cmd; void (*fn)(); } stock[] = {
    {"rest", runRestPose}, {"wave", runWavePose}, {"dance", runDancePose}, {"swim", runSwimPose},
    {"point", runPointPose}, {"pushup", runPushupPose}, {"bow", runBowPose}, {"cute", runCutePose},
    {"freaky", runFreakyPose}, {"worm", runWormPose}, {"shake", runShakePose}, {"shrug", runShrugPose},
    {"dead", runDeadPose}, {"crab", runCrabPose}, {"forward", runWalkPose}, {"backward", runWalkBackward},
    {"left", runTurnLeft}, {"right", runTurnRight}};
  int savedCycles = walkCycles; walkCycles = 2;
  for (auto& s : stock) {
    resetRun();
    currentCommand = s.cmd;
    s.fn();
    for (int i = 0; i < 8; i++) {
      stockMin[i] = std::min(stockMin[i], rawMin[i]);
      stockMax[i] = std::max(stockMax[i], rawMax[i]);
    }
  }
  walkCycles = savedCycles;
  currentCommand = "";
}
static std::vector<Ev> stripTimes(const std::vector<Ev>& v) {
  std::vector<Ev> out;
  for (auto e : v) { e.t = 0; out.push_back(e); }
  return out;
}
static void checkWalkCopy() {
  std::printf("[walk copy] planet walk keyframes vs runWalkPose()\n");
  const int cycles = 3, dwell = 100;
  resetRun();
  frameDelay = dwell; walkCycles = cycles; currentCommand = "forward";
  runWalkPose();
  std::vector<Ev> ref = stripTimes(trace);
  ref.resize(ref.size() - 8);  
  PlanetProfile p = PLANET_PROFILES[2];
  p.cmd = "forward"; p.tempo = 1.0f; p.walkCycles = cycles;
  resetRun();
  currentCommand = "forward";
  bool ok = planetWalk(p, 0);
  std::vector<Ev> got = stripTimes(trace);
  CHECK(ok, "planet walk was interrupted");
  bool same = ref.size() == got.size();
  for (size_t i = 0; same && i < ref.size(); i++)
    same = ref[i].kind == got[i].kind && ref[i].ch == got[i].ch && ref[i].val == got[i].val;
  CHECK(same, "planet walk trace differs from runWalkPose() (%zu vs %zu events)", got.size(), ref.size());
  if (same) std::printf("  ok: %zu identical events\n", ref.size());
  frameDelay = 100; walkCycles = 10; currentCommand = "";
}
struct RunResult { long duration; bool stand; };
static RunResult runPlanet(int idx, long interruptMs, const char* interruptCmd) {
  const PlanetProfile& p = PLANET_PROFILES[idx];
  resetRun();
  frameDelay = 100; walkCycles = 10;
  currentCommand = p.cmd;  
  if (interruptMs >= 0) { interruptAt = interruptMs; interruptTo = interruptCmd; }
  void (*fns[])() = {runMoonPose, runMarsPose, runEarthPose, runJupiterPose};
  fns[idx]();
  return {simNow, atStand()};
}
static void checkAnglesAndFaces(const char* name) {
  for (int i = 0; i < 8; i++) {
    if (rawMax[i] < 0) continue;  
    CHECK(rawMin[i] >= 0 && rawMax[i] <= 180, "%s: %s requested %d..%d (outside 0..180)",
          name, ServoNames[i].c_str(), rawMin[i], rawMax[i]);
    CHECK(rawMin[i] >= stockMin[i] && rawMax[i] <= stockMax[i],
          "%s: %s used %d..%d, stock poses only use %d..%d",
          name, ServoNames[i].c_str(), rawMin[i], rawMax[i], stockMin[i], stockMax[i]);
  }
  for (auto& f : facesUsed) {
    bool known = false;
    for (auto k : FACES_WITH_BITMAPS) known |= (f == k);
    CHECK(known, "%s: face '%s' has no bitmap", name, f.c_str());
  }
}
int main() {
  std::printf("PLANET_INTENSITY=%.2f  CROUCH_WALK=%d  STORM_SWAY=%d\n",
              PLANET_INTENSITY, (int)PLANET_CROUCH_WALK, (int)PLANET_STORM_SWAY);
  CHECK(PLANET_MAX_DEPTH <= 0.5f, "PLANET_MAX_DEPTH %.2f is deeper than the 0.5 safety limit", PLANET_MAX_DEPTH);
  collectStockRanges();
  checkWalkCopy();
  const int n = sizeof(PLANET_PROFILES) / sizeof(PLANET_PROFILES[0]);
  std::printf("\n%-8s %6s %6s %7s  %-31s %s\n", "planet", "delay", "writes", "total s",
              "knee deg bounce/crouch/strain", "faces");
  for (int i = 0; i < n; i++) {
    const PlanetProfile& p = PLANET_PROFILES[i];
    motorCurrentDelay = 20;
    RunResult r = runPlanet(i, -1, "");
    int writes = 0;
    for (auto& e : trace) writes += (e.kind == 'w');
    int bDeg = planetKneeAngle(R4, planetDepth(p.bounceDepth));
    int cDeg = planetKneeAngle(R4, planetDepth(p.crouch));
    int sDeg = p.strainCount ? planetKneeAngle(R4, planetDepth(p.strainDepth)) : 0;
    std::string faces;
    for (auto& f : facesUsed) if (faces.find(f) == std::string::npos) faces += f + " ";
    std::printf("%-8s %6d %6d %7.2f  %3d / %3d / %3d                  %s\n", p.cmd, maxDelaySeen, writes,
                r.duration / 1000.0, bDeg, cDeg, sDeg, faces.c_str());
    CHECK(r.stand, "%s: did not end in stand pose", p.cmd);
    CHECK(currentCommand == "", "%s: currentCommand not cleared", p.cmd);
    CHECK(motorCurrentDelay == 20 && frameDelay == 100 && walkCycles == 10, "%s: settings not restored", p.cmd);
    CHECK(minDelaySeen >= 20, "%s: motor delay dropped below 20", p.cmd);
    CHECK(r.duration > 3000, "%s: finished in %ld ms, looks aborted", p.cmd, r.duration);
    if (r.duration < 5000 || r.duration > 15000)
      std::printf("  WARN: %s duration %.1f s outside 5-15 s\n", p.cmd, r.duration / 1000.0);
    checkAnglesAndFaces(p.cmd);
    long full = r.duration;
    for (double frac : {0.05, 0.25, 0.50, 0.85}) {
      long at = (long)(full * frac);
      motorCurrentDelay = 20;
      RunResult ir = runPlanet(i, at, "");
      CHECK(ir.stand, "%s: STOP at %ld ms did not end in stand", p.cmd, at);
      CHECK(ir.duration - at < 1000, "%s: STOP at %ld ms took %ld ms to stop", p.cmd, at, ir.duration - at);
      CHECK(motorCurrentDelay == 20, "%s: motor delay not restored after STOP", p.cmd);
      CHECK(currentCommand == "", "%s: STOP left currentCommand set", p.cmd);
      checkAnglesAndFaces(p.cmd);
    }
    motorCurrentDelay = 20;
    RunResult wr = runPlanet(i, full / 2, "wave");
    CHECK(wr.stand && currentCommand == "wave", "%s: new command mid-way not handed over cleanly", p.cmd);
    motorCurrentDelay = 60;
    runPlanet(i, -1, "");
    CHECK(minDelaySeen >= 60 && motorCurrentDelay == 60, "%s: user motor delay 60 not respected", p.cmd);
    motorCurrentDelay = 20;
    resetRun();
    currentCommand = "";
    void (*fns[])() = {runMoonPose, runMarsPose, runEarthPose, runJupiterPose};
    fns[i]();
    CHECK(simNow < 1500 && atStand(), "%s: did not abort when currentCommand was empty", p.cmd);
  }
  std::printf("\n%s (%d failure%s)\n", failures ? "FAILED" : "ALL CHECKS PASSED", failures, failures == 1 ? "" : "s");
  return failures ? 1 : 0;
}