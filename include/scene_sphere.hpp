#ifndef __SCENE_SPHERE_H_
#define __SCENE_SPHERE_H_

#include "light_source.hpp"
#include "scene_base_object.hpp"
#include "types.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class SceneSphere : public SceneBaseObject
{
private:
  position_t m_center;
  double m_radius;

public:
  SceneSphere() : m_center(POSITION_T_NULL), m_radius(0) {}
  SceneSphere(ObjectBaseSurface *surface, position_t center, double radius, double spec_reflect = 0.5, double diff_reflect = 0.5, double amb_reflect = 0.5, double shine = 10.);

  /**
   * @brief Test whether the ray is intersecting the object.
   *
   * @param ray
   *
   * @return true if the ray is intersecting the object if not false.
   */
  double intersecDist(const Ray &ray);

  /**
   * @brief get the normal to the surface passing by POS.
   *
   * @param pos
   *
   * @return the normal to the surface passing by POS.
   */
  vector_t getNormal(const position_t &pos);
};

#endif // __SCENE_SPHERE_H_
