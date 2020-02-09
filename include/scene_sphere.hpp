/**
 * @file scene_sphere.hpp
 * @author Julien Lin
 * @brief This file contains the declaration of the SceneSphere class.
 * @version 0.1
 * @date 2020-02-09
 *
 *
 */
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
  /**
   * @brief Construct a new Scene Sphere object which center is (0,0,0) and radius is equal to 1.
   *
   */
  SceneSphere() : m_center(POSITION_T_NULL), m_radius(1) {}

  /**
   * @brief Construct a new Scene Sphere object.
   *
   * @param surface Object that give the surface characteristic.
   * @param center The center of the sphere.
   * @param radius The radius of the sphere.
   * @param refflect The coefficent of reflection of the object.
   * @param spec_reflect The coefficient of specular reflection that determines the intensity of white dots.
   * @param diff_reflect The coefficient of diffuse reflection.
   * @param amb_reflect The ambient reflection coefficient that determine the intensity of the ambient light on the object.
   * @param shine The shininess coefficient that determine the shininess of the object.
   */
  SceneSphere(ObjectBaseSurface *surface, position_t center, double radius, double refflect = 0, double spec_reflect = 0.5, double diff_reflect = 0.5, double amb_reflect = 0.5, double shine = 10.);

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

  /**
   * @brief Get the Color object.
   *
   * @param pos
   * @return RGBColor
   */
  RGBColor getColor(position_t &pos) const;
};

#endif // __SCENE_SPHERE_H_
