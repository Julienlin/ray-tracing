#include "ray.hpp"

Ray::Ray()
    : m_pos(POSITION_T_NULL), m_direction(POSITION_T_NULL),
      m_color() {}

Ray::Ray(position_t pos, vector_t direction, RGBColor color,
         Ray *fondamental)
    : m_pos(pos), m_direction(direction),
      m_color(color) {}

Ray::Ray(position_t pos, vector_t direction)
    : m_pos(pos), m_direction(direction), m_color() {}

Ray &Ray::operator=(const Ray &ray)
{
    m_pos = ray.m_pos;
    m_direction = ray.m_direction;
    m_color = ray.m_color;
    return *this;
}
