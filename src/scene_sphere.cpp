#include "scene_sphere.hpp"

double SceneSphere::intersecDist(const Ray &ray)
{
  position_t v = ray.getPos() - m_center;
  auto normal_direc = ray.getDirection().normalize();
  double s_v_d = (v * normal_direc);
  // s_v_d *= s_v_d;
  double s_v = v * v, discriminant = s_v_d * s_v_d - s_v + m_radius * m_radius;
  if (discriminant < 0)
    return -1;
  double res = -s_v_d - std::sqrt(discriminant) > 0 ? -s_v_d - std::sqrt(discriminant) : -s_v_d + std::sqrt(discriminant);
  return res;
}

vector_t SceneSphere::getNormal(const position_t &pos)
{
  auto position = pos;
  return vector_t(position - m_center).normalize();
}

Ray SceneSphere::generateReflectionRay(const Ray &incident)
{
  return Ray();
}

Ray SceneSphere::generateRefractionRay(const Ray &incident)
{
  return Ray();
}

genRays_t SceneSphere::generateRays(const Ray &incident)
{
  return genRays_t(generateRefractionRay(incident), generateReflectionRay(incident));
}
