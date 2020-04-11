#include <iostream>
#include <scene_base_object.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>


class SceneTriangle : public SceneBaseObject {
private:
  position_t m_A;
  position_t m_B;
  position_t m_C;
  vector_t m_normal;

public:
  SceneTriangle(ObjectBaseSurface *surface, position_t A, position_t B,
                position_t C, double reflect = 0, double spec_reflect = 0.5,
                double diff_reflect = 0.5, double amb_reflect = 0.5,
                double shine = 10.);

  virtual double intersecDist(const Ray &ray);
  virtual vector_t getNormal(const position_t &pos);
  virtual RGBColor getColor(position_t &pos) const;
};
