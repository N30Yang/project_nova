#pragma once
#include <cstdint>
#include <cstdio>
#include <string>
#include <algorithm>
using std::max;
using std::min;
#define F(x) (x)
#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))
class String {
 public:
  String() {}
  String(const char* s) : s_(s ? s : "") {}
  String(const std::string& s) : s_(s) {}
  bool operator==(const String& o) const { return s_ == o.s_; }
  bool operator!=(const String& o) const { return s_ != o.s_; }
  bool operator==(const char* o) const { return s_ == o; }
  bool operator!=(const char* o) const { return s_ != o; }
  unsigned int length() const { return (unsigned int)s_.size(); }
  const char* c_str() const { return s_.c_str(); }
 private:
  std::string s_;
};
struct SerialStub {
  bool quiet = true;
  template <typename T> void print(const T&) {}
  template <typename T> void println(const T&) {}
  void print(const String& s) { if (!quiet) std::printf("%s", s.c_str()); }
  void println(const String& s) { if (!quiet) std::printf("%s\n", s.c_str()); }
};
extern SerialStub Serial;