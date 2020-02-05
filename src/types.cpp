#include "types.hpp"

position_t position_t::operator+(const position_t &pos)
{
  return position_t(x + pos.x, y + pos.y, z + pos.z);
}
position_t position_t::operator-(const position_t &pos)
{
  return position_t(x - pos.x, y - pos.y, z - pos.z);
}

position_t &position_t::operator=(const position_t &pos)
{
  x = pos.x;
  y = pos.y;
  z = pos.z;
  return *this;
}

position_t &position_t::operator+=(const position_t &pos)
{
  x += pos.x;
  y += pos.y;
  z += pos.z;
  return *this;
}
position_t &position_t::operator-=(const position_t &pos)
{
  x -= pos.x;
  y -= pos.y;
  z -= pos.z;
  return *this;
}
position_t &position_t::operator*=(const double coef)
{
  x *= coef;
  y *= coef;
  z *= coef;
  return *this;
}

double position_t::operator*(const position_t pos)
{
  return x * pos.x + y * pos.y + z * pos.z;
}

position_t position_t::operator*(const double c)
{
  return position_t(x * c, y * c, z * c);
}

position_t position_t::operator/(const double c)
{
  return position_t(x / c, y / c, z / c);
}

double position_t::norm() { return std::sqrt(x * x + y * y + z * z); }

double position_t::norm(const position_t &pos)
{
  return std::sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
}

position_t &position_t::normalize()
{
  double norm = this->norm();
  x /= norm;
  y /= norm;
  z /= norm;
  return *this;
}

position_t position_t::operator^(const position_t &pos)
{
  return position_t(y * pos.z - z * pos.y, z * pos.x - x * pos.z, x * pos.y - y * pos.x).normalize();
}

position_t position_t::operator-() const
{
  return position_t(-x, -y, -z);
}

position_t position_t::operator-()
{
  return position_t(-x, -y, -z);
}

bool position_t::operator==(const position_t &pos)
{
  return x == pos.x && y == pos.y && z == pos.z;
}

position_t operator*(double coef, const position_t &pos)
{
  return position_t(pos.x * coef, pos.y * coef, pos.z * coef);
}

position_t operator*(double c, position_t pos)
{
  return position_t(c * pos.x, c * pos.y, c * pos.z);
}

/***********************************************************
 *  RGBColor function definitions.
 ***********************************************************/

std::ostream &
operator<<(std::ostream &os, const position_t &pos)
{
  os << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")";
  return os;
}

void RGBColor::swap(RGBColor &other)
{
  uint8_t buf = m_red;
  m_red = other.m_red;
  other.m_red = buf;

  buf = m_green;
  m_green = other.m_green;
  other.m_green = buf;

  buf = m_blue;
  m_blue = other.m_blue;
  other.m_blue = buf;
}

RGBColor &RGBColor::operator=(const RGBColor &color)
{
  m_red = color.m_red;
  m_blue = color.m_blue;
  m_green = color.m_green;
  return *this;
}

RGBColor RGBColor::operator*(const double &d) const
{
  return RGBColor(cap(m_red * d), cap(m_green * d), cap(m_blue * d));
}

RGBColor operator*(double d, const RGBColor &color)
{
  return color * d;
}

RGBColor RGBColor::operator+(const RGBColor &c) const
{
  return RGBColor(cap(m_red + c.m_red), cap(m_green + c.m_green), cap(m_blue + c.m_blue));
}

RGBColor &RGBColor::operator+=(const RGBColor &c)
{
  m_red += c.m_red;
  m_green += c.m_green;
  m_blue += c.m_blue;
  return *this;
}

void swap(RGBColor &color1, RGBColor &color2) { color1.swap(color2); }

unsigned char RGBColor::cap(unsigned c) const
{
  return c > threshold ? threshold : c;
}

std::ostream &operator<<(std::ostream &os, const RGBColor &color)
{
  os << color.m_red << color.m_green << color.m_blue;
  return os;
}
