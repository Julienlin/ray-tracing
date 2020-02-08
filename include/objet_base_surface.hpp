#ifndef __OBJECT_BASE_SURFACE_H_
#define __OBJECT_BASE_SURFACE_H_

#include "types.hpp"

class ObjectBaseSurface
{
public:
  virtual ~ObjectBaseSurface(){};
  virtual RGBColor getColor(position_t &pos) = 0;
};

class SurfaceUniformedColor : public ObjectBaseSurface
{
private:
  RGBColor color;

public:
  SurfaceUniformedColor(RGBColor color) : color(color){};
  SurfaceUniformedColor(const SurfaceUniformedColor &surface) = default;
  SurfaceUniformedColor(SurfaceUniformedColor &&surface) = default;
  virtual ~SurfaceUniformedColor(){};
  virtual RGBColor getColor(position_t &pos) { return color; }
};

#endif // __OBJECT_BASE_SURFACE_H_
