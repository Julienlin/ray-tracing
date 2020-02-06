#include "scene_base_object.hpp"

SceneBaseObject::SceneBaseObject(ObjectBaseSurface *surface, double spec_reflect, double diff_reflect, double amb_reflect, double shine)
    : m_surface(surface), m_spec_reflect(spec_reflect),
      m_diff_reflect(diff_reflect), m_amb_reflect(amb_reflect),
      m_shine(shine) {}

ObjectBaseSurface *SceneBaseObject::getSurface() { return m_surface; }
