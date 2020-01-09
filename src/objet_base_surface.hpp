#ifndef __OBJECT_BASE_SURFACE_H_
#define __OBJECT_BASE_SURFACE_H_

#include "types.hpp"

class ObjectBaseSurface {
public:
  ObjectBaseSurface();
  virtual ~ObjectBaseSurface(){};
  virtual RGBColor getColor(position_t &pos) = 0;
};

class SurfaceTransparancy : public ObjectBaseSurface {
private:
  double m_transparancy;

public:
  SurfaceTransparancy(double transparancy)
      : ObjectBaseSurface(), m_transparancy(transparancy){};
  virtual ~SurfaceTransparancy(){};
  virtual double getTransparancy(position_t pos){ return m_transparancy; };
};

class SurfaceUniformedColor : public ObjectBaseSurface {
private:
  RGBColor color;

public:
  SurfaceUniformedColor(RGBColor color) : color(color){};
  SurfaceUniformedColor(const SurfaceUniformedColor &surface) = default;
  SurfaceUniformedColor(SurfaceUniformedColor &&surface) = default;
  virtual ~SurfaceUniformedColor(){};
  RGBColor getColor(position_t pos) { return color; }
};

#endif // __OBJECT_BASE_SURFACE_H_
