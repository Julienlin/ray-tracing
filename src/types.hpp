#ifndef __TYPES_H_
#define __TYPES_H_

#include <cmath>
#include <cstdint>
#include <tuple>
#include <ostream>

class position_t {
public:
  position_t() : x(0), y(0), z(0) {}
  double x, y, z;
  position_t(double x, double y, double z) : x(x), y(y), z(y) {}
  position_t(const position_t &pos) = default;
  position_t(position_t &&pos) = default;

  position_t operator/(const double c);
  double operator*(const position_t pos);
  position_t operator*(const double c);
  position_t operator+(const position_t &pos);
  position_t operator-(const position_t &pos);
  position_t& operator=(const position_t &pos);
  position_t &operator+=(const position_t &pos);
  position_t &operator-=(const position_t &pos);
  position_t &operator*=(const double coef);
  double norm();
  static double norm(const position_t &pos);
  position_t &normalize();

  // double norm(){ return  }
  // double getX(){ return x; }
  // double getY(){ return y; }
  // double getZ(){ return z; }
  // void setX(double i){ x = i; }
  // void setY(double i){ y = i; }
  // void setZ(double i){ z = i; }
};

position_t operator*(const double , const position_t );
position_t operator*( double ,  position_t );

using vector_t = position_t;

class RGBColor {
private:
  unsigned char m_red, m_green, m_blue;

public:
  RGBColor() : m_red(0), m_green(0), m_blue(0) {}
  RGBColor(unsigned char red, unsigned char green, unsigned char blue)
      : m_red(red), m_green(green), m_blue(blue) {}
  RGBColor(const RGBColor &color) = default;
  RGBColor(RGBColor &&color) = default;
  void swap(RGBColor &other);
  RGBColor& operator=(const RGBColor&);
  RGBColor operator*(const double&) const;
  friend std::ostream& operator<<( std::ostream& os, const RGBColor& color);
};


void swap(RGBColor &, RGBColor &);
RGBColor operator*(double , const RGBColor& );

const position_t POSITION_T_NULL = position_t(0, 0, 0);
const vector_t E1 = vector_t(1,0,0);
const vector_t E2 = vector_t(0,1,0);
const vector_t E3 = vector_t(0,0,1);
const RGBColor RGB_WHITE = RGBColor(255,255,255);
const RGBColor RGB_BLACK = RGBColor(0,0,0);
#endif // __TYPES_H_
