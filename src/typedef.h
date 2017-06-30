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
CDBL GRAVITY_m = 9.80665;         // Gravity[m/s2]
CDBL GRAVITY_mm = 9.80665 * 1000; // Gravity[mm/s2]

template <class T>
inline T square(const T &x)
{
  return ((x) * (x));
}

inline double rad2deg(CDBL &x)
{
  return ((x)*180 / PI);
}

inline double deg2rad(CDBL &x)
{
  return ((x) / 180 * PI);
}

inline double sinDeg(CDBL &x)
{
  return sin(deg2rad(x));
}

inline double cosDeg(CDBL &x)
{
  return cos(deg2rad(x));
}

inline double tanDeg(CDBL &x)
{
  return tan(deg2rad(x));
}

inline double msec2sec(CDBL &x)
{
  return ((x) / 1000);
}

template <class T>
inline T sec2msec(const T &x)
{
  return ((x)*1000);
}

inline double mm2meter(CDBL &x)
{
  return ((x) / 1000);
}

template <class T>
inline T meter2mm(const T &x)
{
  return ((x)*1000);
}