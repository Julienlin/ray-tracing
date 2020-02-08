#ifndef __RAY_CASTING_H_
#define __RAY_CASTING_H_

#include "light_source.hpp"
#include "ray.hpp"
#include "scene_base_object.hpp"
#include "screen.hpp"
#include "types.hpp"
#include <deque>
#include <iostream>
#include <limits>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <sstream>
#include <tuple>
#include <vector>

class RayEngine
{
protected:
  std::vector<Ray> m_rays;
  std::vector<SceneBaseObject *> m_objects;
  std::vector<LightSource> m_sources;
  Screen m_screen;
  position_t m_obs_pos;
  RGBColor m_background_color;
  double m_amb_lighting;
  int m_deepth;
  static constexpr double HORIZON = 1e18;

public:
  using ray_dist_t = std::pair<Ray, double>;
  using obj_dist_t = std::pair<SceneBaseObject *, double>;
  using source_vect_t = std::pair<LightSource *, vector_t>;
  using ray_obj_dist_t = std::tuple<Ray *, SceneBaseObject *, double>;
  RayEngine(std::vector<Ray> &rays, std::vector<SceneBaseObject *> &objects,
            std::vector<LightSource> &sources, Screen &screen,
            position_t &observer_pos, RGBColor background_color = RGB_BLACK, double amb_lighting = 1, int deepth = 1);

  RayEngine(std::vector<SceneBaseObject *> &objects,
            std::vector<LightSource> &sources, Screen &screen,
            position_t &obs_pos, RGBColor background_color = RGB_BLACK, double amb_lighting = 1, int deepth = 1);

  RayEngine(const RayEngine &engine) = default;
  RayEngine(RayEngine &&engine) = default;
  virtual ~RayEngine() {}
  virtual void compute() = 0;
  Screen get_screen() { return m_screen; }
  void generate_fundamental_rays();
};

class RayCastingEngine : public RayEngine
{
public:
  RayCastingEngine(std::vector<SceneBaseObject *> &objects,
                   std::vector<LightSource> &sources, Screen &screen,
                   position_t &observer_pos, RGBColor background_color = RGB_BLACK, double amb_lighting = 1);
  RayCastingEngine(const RayCastingEngine &engine) = default;
  RayCastingEngine(RayCastingEngine &&engine) = default;
  void compute();
  ray_obj_dist_t get_intersection(Ray *);
  void get_reachable_sources(Ray &, SceneBaseObject *, position_t, std::vector<source_vect_t> &);
  Ray generate_reflection_ray(const position_t &, SceneBaseObject *, source_vect_t &);
};

#endif // __RAY_CASTING_H_
