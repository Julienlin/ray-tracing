#include "types.hpp"

position_t position_t::operator+(const position_t &pos) {
  return position_t(x + pos.x, y + pos.y, z + pos.z);
}
position_t position_t::operator-(const position_t &pos) {
  return position_t(x - pos.x, y - pos.y, z - pos.z);
}
position_t &position_t::operator+=(const position_t &pos) {
  x += pos.x;
  y += pos.y;
  z += pos.z;
  return *this;
}
position_t &position_t::operator-=(const position_t &pos) {
  x -= pos.x;
  y -= pos.y;
  z -= pos.z;
  return *this;
}
position_t &position_t::operator*=(const double coef) {
  x *= coef;
  y *= coef;
  z *= coef;
  return *this;
}

double position_t::operator*(const position_t pos) {
  return x * pos.x + y * pos.y + z * pos.z;
}

position_t position_t::operator*(const double c) {
  return position_t(x * c, y * c, z * c);
}

void RGBColor::swap(RGBColor &other){
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
