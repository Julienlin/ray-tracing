#ifndef __TYPES_H_
#define __TYPES_H_

#include <cmath>
#include <cstdint>
#include <tuple>

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

using vector_t = position_t;

class RGBColor {
private:
  std::uint8_t m_red, m_green, m_blue;

public:
  RGBColor() : m_red(0), m_green(0), m_blue(0) {}
  RGBColor(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
      : m_red(red), m_green(green), m_blue(blue) {}
  RGBColor(const RGBColor &color) = default;
  RGBColor(RGBColor &&color) = default;
  void swap(RGBColor &other);
  RGBColor& operator=(const RGBColor&);
  RGBColor operator*(const double&) const;
};


void swap(RGBColor &, RGBColor &);
RGBColor operator*(const double d, const RGBColor& color );

const position_t POSITION_T_NULL = position_t(0, 0, 0);
#endif // __TYPES_H_
