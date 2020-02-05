#ifndef __SCENE_BASE_OBJECT_H_
#define __SCENE_BASE_OBJECT_H_

#include "objet_base_surface.hpp"
#include "ray.hpp"
#include "types.hpp"
#include "utils.hpp"

class SceneBaseObject
{
protected:
  ObjectBaseSurface *m_surface;
  double m_spec_reflect, m_diff_reflect, m_amb_reflect, m_shine;

public:
  SceneBaseObject() : m_surface(nullptr){};
  SceneBaseObject(ObjectBaseSurface *surface, double spec_reflect = 1.,
                  double diff_reflect = 1., double amb_reflect = 1.,
                  double shine = 10.)
      : m_surface(surface), m_spec_reflect(spec_reflect),
        m_diff_reflect(diff_reflect), m_amb_reflect(amb_reflect),
        m_shine(shine) {}
  SceneBaseObject(const SceneBaseObject &obj) = default;
  SceneBaseObject(SceneBaseObject &&obj) = default;
  virtual ~SceneBaseObject(){};
  virtual double intersecDist(const Ray &ray) = 0;
  /**
   * Generate a set of rays for implementation of several physic phenomenon.
   * This function calls several other virtual functions for the generation of
   * rays.
   *
   * @param incident_ray the incident ray.
   *
   * @return set of generated rays
   */
  virtual genRays_t generateRays(const Ray &incident_ray) = 0;
  virtual Ray generateReflectionRay(const Ray &incident) = 0;
  virtual Ray generateRefractionRay(const Ray &incident) = 0;

  /**
   * @brief get the normal to the surface passing by POS.
   *
   * @param pos
   *
   * @return the normal to the surface passing by POS.
   */
  virtual vector_t getNormal(const position_t &pos) = 0;

  ObjectBaseSurface *getSurface() { return m_surface; }
  double get_spec_reflect() { return m_spec_reflect; }
  double get_diff_reflect() { return m_diff_reflect; }
  double get_amb_reflect() { return m_amb_reflect; }
  double get_shine() { return m_shine; }
};

#endif // __SCENE_BASE_OBJECT_H_
