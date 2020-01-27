
#ifndef __RAY_H_
#define __RAY_H_

#include "types.hpp"
#include <utility>

class Ray {
private:
  position_t m_pos;
  vector_t m_direction;
  double m_intensity;
  RGBColor m_color;

public:
  Ray()
      : m_pos(POSITION_T_NULL), m_direction(POSITION_T_NULL), m_intensity(0),
        m_color() {}
  Ray(position_t pos, vector_t direction, double intensity, RGBColor color)
      : m_pos(pos), m_direction(direction), m_intensity(intensity),
        m_color(color) {}
 Ray(position_t pos, vector_t direction)
      : m_pos(pos), m_direction(direction), m_intensity(0),
        m_color() {}

  position_t getPos() const { return m_pos; };
  vector_t getDirection() const { return m_direction; }
  double getIntensity() const { return m_intensity; }
  RGBColor getColor() const { return m_color; };
  void setPos(const position_t &pos);
  void setDirection(const vector_t &direction);
  void setIntensity(double intensity) { m_intensity = intensity; }
  void setColor(RGBColor color) { swap(color, m_color); }
  Ray& operator=(const Ray& );
};

using genRays_t = std::tuple<Ray, Ray, Ray>;

#endif // __RAY_H_
