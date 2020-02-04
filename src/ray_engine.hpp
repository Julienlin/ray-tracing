#ifndef __RAY_CASTING_H_
#define __RAY_CASTING_H_

#include "light_source.hpp"
#include "ray.hpp"
#include "scene_base_object.hpp"
#include "screen.hpp"
#include "types.hpp"
#include <limits>
#include <vector>

class RayEngine {
protected:
  std::vector<Ray> m_rays;
  std::vector<SceneBaseObject *> m_objects;
  std::vector<LightSource> m_sources;
  Screen m_screen;
  position_t m_obs_pos;
  int m_deepth;

public:
  using ray_dist_t = std::pair<Ray, double>;
  using obj_dist_t = std::pair<SceneBaseObject *, double>;
  using source_vect_t = std::pair<LightSource *, vector_t>;
  RayEngine(std::vector<Ray> &rays, std::vector<SceneBaseObject *> &objects,
            std::vector<LightSource> &sources, Screen &screen,
            position_t &observer_pos, int deepth = 0)
      : m_rays(rays), m_objects(objects), m_sources(sources), m_screen(screen),
        m_obs_pos(observer_pos), m_deepth(deepth) {}
  RayEngine(std::vector<SceneBaseObject *> &objects,
            std::vector<LightSource> &sources, Screen &screen,
            position_t &obs_pos, int deepth = 0)
      : m_rays(), m_objects(objects), m_sources(sources), m_screen(screen),
        m_obs_pos(obs_pos), m_deepth(deepth) {}
  RayEngine(const RayEngine &engine) = default;
  RayEngine(RayEngine &&engine) = default;
  virtual ~RayEngine() {}
  virtual void compute()=0;
  Screen get_screen() { return m_screen; }
};

class RayCastingEngine : public RayEngine {
public:
  RayCastingEngine(std::vector<SceneBaseObject *> &objects,
                   std::vector<LightSource> &sources, Screen &screen,
                   position_t &observer_pos)
      : RayEngine(objects, sources, screen, observer_pos) {
    m_rays.resize(m_screen.H() * m_screen.W());
  }
  RayCastingEngine(const RayCastingEngine &engine) = default;
  RayCastingEngine(RayCastingEngine &&engine) = default;
  void compute();
  obj_dist_t get_intersection(Ray &);
  void get_reachable_sources(position_t, std::vector<source_vect_t> &);
  Ray make_reflect_ray(const position_t &,SceneBaseObject*, source_vect_t&);
};

#endif // __RAY_CASTING_H_
