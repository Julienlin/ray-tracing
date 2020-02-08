#include "scene_sphere.hpp"

SceneSphere::SceneSphere(ObjectBaseSurface *surface, position_t center, double radius, double spec_reflect, double diff_reflect, double amb_reflect, double shine)
    : SceneBaseObject(surface, spec_reflect, diff_reflect, amb_reflect, shine), m_center(center), m_radius(radius) {}

double SceneSphere::intersecDist(const Ray &ray)
{
  position_t v = ray.getPos() - m_center;
  auto normal_direc = ray.getDirection().normalize();
  double s_v_d = (v * normal_direc);
  // s_v_d *= s_v_d;
  double s_v = v * v, discriminant = s_v_d * s_v_d - s_v + m_radius * m_radius;
  // std::cout << "ray.getPos() : " << ray.getPos() << "\tm_center : " << m_center << "\tv : " << v << "\tnormal_direc : " << normal_direc << "\ts_v_d : " << s_v_d << "\ts_v : " << s_v << "\tdiscriminant : " << discriminant << std::endl;
  double res = -1;
  if (-s_v_d - std::sqrt(discriminant) > MIN_PROXIMITY)
  {
    res = -s_v_d - std::sqrt(discriminant);
  }
  else if (-s_v_d + std::sqrt(discriminant) > MIN_PROXIMITY)
  {
    res = -s_v_d + std::sqrt(discriminant);
  }

  return res;
}

vector_t SceneSphere::getNormal(const position_t &pos)
{
  return vector_t(pos - m_center).normalize();
}

RGBColor SceneSphere::getColor(position_t &pos) const
{
  return m_surface->getColor(pos);
}
