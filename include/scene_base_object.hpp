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

  double m_reflect;
  double m_refract;
  double m_spec_reflect;
  double m_diff_reflect;
  double m_amb_reflect;
  double m_shine;
  static constexpr double MIN_PROXIMITY = 1e-10;

public:
  SceneBaseObject() : m_surface(nullptr){};
  SceneBaseObject(ObjectBaseSurface *surface, double refflect = 0, double spec_reflect = 0.5, double diff_reflect = 0.5, double amb_reflect = 0.5, double shine = 10.);
  SceneBaseObject(const SceneBaseObject &obj) = default;
  SceneBaseObject(SceneBaseObject &&obj) = default;
  virtual ~SceneBaseObject(){};
  virtual double intersecDist(const Ray &ray) = 0;

  /**
   * @brief get the normal to the surface passing by POS.
   *
   * @param pos is Either the position of the intersection or the position to where the normal has to go trhough.
   *
   * @return the normal to the surface passing by POS.
   */
  virtual vector_t getNormal(const position_t &pos) = 0;

  ObjectBaseSurface *getSurface() const;
  virtual RGBColor getColor(position_t &pos) const = 0;

  RGBColor getColor() const;
  double get_spec_reflect() const { return m_spec_reflect; }
  double get_diff_reflect() const { return m_diff_reflect; }
  double get_amb_reflect() const { return m_amb_reflect; }
  double get_shine() const { return m_shine; }
  double get_reflect() const { return m_reflect; }
};

#endif // __SCENE_BASE_OBJECT_H_
