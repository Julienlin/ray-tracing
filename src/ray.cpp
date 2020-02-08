#include "ray.hpp"

Ray::Ray()
    : m_pos(POSITION_T_NULL), m_direction(POSITION_T_NULL),
      m_color()
{
    m_fundamental = nullptr;
}

Ray::Ray(position_t pos, vector_t direction, RGBColor color,
         Ray *fondamental)
    : m_pos(pos), m_direction(direction),
      m_color(color)
{
    m_fundamental = fondamental;
}

Ray::Ray(position_t pos, vector_t direction)
    : m_pos(pos), m_direction(direction), m_color()
{
    m_fundamental = nullptr;
}

Ray &Ray::operator=(const Ray &ray)
{
    m_pos = ray.m_pos;
    m_direction = ray.m_direction;
    m_color = ray.m_color;
    m_fundamental = ray.m_fundamental;
    return *this;
}

Ray *Ray::get_fundamental()
{
    return m_fundamental;
}

void Ray::setPos(const position_t &pos)
{
    m_pos = pos;
}
void Ray::setDirection(const vector_t &direction)
{
    m_direction = direction;
}