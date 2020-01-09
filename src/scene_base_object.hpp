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
  virtual genRays_t generateRays(const Ray &incident_ray) = 0;
  virtual bool isIntersecting(const Ray &ray) = 0;
  virtual Ray generateReflectionRay(const Ray &incident) = 0;
  virtual Ray generateRefractionRay(const Ray &incident) = 0;
  virtual vector_t getNormal(position_t &pos) = 0;
  virtual double getLightSourceDirection(position_t &pos) = 0;
};

#endif // __SCENE_BASE_OBJECT_H_
