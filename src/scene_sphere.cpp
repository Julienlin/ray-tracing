#include "scene_sphere.hpp"

double SceneSphere::intersecDist(const Ray &ray) {
  position_t v = ray.getPos() - m_center;
  double s_v_d = (v * ray.getDirection());
  s_v_d *= s_v_d;
  double s_v = v * v, discriminant = s_v_d - s_v + m_radius * m_radius;
  if(discriminant < 0 )
     return -1;
  double res = -s_v_d + std::max(- std::sqrt(discriminant), std::sqrt(discriminant)) ;
  return res;
}

vector_t SceneSphere::getNormal(const position_t &pos) {
  auto position = pos;
  return vector_t(position - m_center).normalize();
}
