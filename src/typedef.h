// Copyright (c) 2017 shoarai

#define _USE_MATH_DEFINES // π用

#include <math.h>
#include <string>

typedef unsigned int UINT;
typedef const int CINT;
typedef const unsigned int CUINT;
typedef const float CFLT;
typedef const double CDBL;

CDBL PI = M_PI;                   // π
CDBL GRAVITY_m = 9.80665;         // 重力加速度[m/s2]
CDBL GRAVITY_mm = 9.80665 * 1000; // 重力加速度[mm/s2]

//------------------------------------------//
//				インライン //
//------------------------------------------//
template <class T> inline T square(const T &x) { // ２乗
  return ((x) * (x));
}

inline double rad2deg(CDBL &x) { // [rad]→[deg]
  return ((x)*180 / PI);
}

inline double deg2rad(CDBL &x) { // [deg]→[rad]
  return ((x) / 180 * PI);
}

inline double sinDeg(CDBL &x) { // °のsin計算
  return sin(deg2rad(x));
}

inline double cosDeg(CDBL &x) { // °のcos計算
  return cos(deg2rad(x));
}

inline double tanDeg(CDBL &x) { // °のtan計算
  return tan(deg2rad(x));
}

inline double msec2sec(CDBL &x) { // [ms]→[s]
  return ((x) / 1000);
}

template <class T> inline T sec2msec(const T &x) { // [s]→[ms]
  return ((x)*1000);
}

inline double mm2meter(CDBL &x) { // [mm]→[m]
  return ((x) / 1000);
}

template <class T> inline T meter2mm(const T &x) { // [m]→[mm]
  return ((x)*1000);
}

// template<class T>
// inline std::string val2str(const T& x)	// 値→文字列
// {
// 	std::ostringstream os;
// 	os << x;
//
// 	return os.str();
// }
