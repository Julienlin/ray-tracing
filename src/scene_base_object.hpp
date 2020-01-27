#ifndef __SCENE_BASE_OBJECT_H_
#define __SCENE_BASE_OBJECT_H_

#include "objet_base_surface.hpp"
#include "ray.hpp"
#include "types.hpp"

class SceneBaseObject {
protected:
  ObjectBaseSurface *m_surface;

public:
  SceneBaseObject() : m_surface(nullptr){};
  SceneBaseObject(ObjectBaseSurface *surface) : m_surface(surface) {}
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
  virtual vector_t getNormal(position_t &pos) = 0;

  ObjectBaseSurface* getSurface();
};

#endif // __SCENE_BASE_OBJECT_H_
