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
  static constexpr double MIN_PROXIMITY = 1e-10;

public:
  SceneBaseObject() : m_surface(nullptr){};
  SceneBaseObject(ObjectBaseSurface *surface, double spec_reflect = 0.5, double diff_reflect = 0.5, double amb_reflect = 0.5, double shine = 10.);
  SceneBaseObject(const SceneBaseObject &obj) = default;
  SceneBaseObject(SceneBaseObject &&obj) = default;
  virtual ~SceneBaseObject(){};
  virtual double intersecDist(const Ray &ray) = 0;

  /**
   * @brief get the normal to the surface passing by POS.
   *
   * @param pos
   *
   * @return the normal to the surface passing by POS.
   */
  virtual vector_t getNormal(const position_t &pos) = 0;

  ObjectBaseSurface *getSurface() const;
  double get_spec_reflect() const { return m_spec_reflect; }
  double get_diff_reflect() const { return m_diff_reflect; }
  double get_amb_reflect() const { return m_amb_reflect; }
  double get_shine() const { return m_shine; }
};

#endif // __SCENE_BASE_OBJECT_H_
