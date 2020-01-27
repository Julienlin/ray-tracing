#include "ray.hpp"

Ray& Ray::operator=(const Ray& ray){
    m_pos = ray.m_pos;
    m_direction = ray.m_direction;
    m_intensity = ray.m_intensity;
    m_color = ray.m_color;
    return *this;
}
