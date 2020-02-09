/**
 * @file ray_engine.hpp
 * @author Julien Lin
 * @brief This file contains the declarations of RayEngine class and RayCastingEngine class.
 * @version 0.1
 * @date 2020-02-09
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __RAY_CASTING_H_
#define __RAY_CASTING_H_

#include "light_source.hpp"
#include "ray.hpp"
#include "scene_base_object.hpp"
#include "screen.hpp"
#include "types.hpp"
// #include <deque>
#include <iostream>
#include <limits>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <sstream>
#include <tuple>
#include <vector>

/**
 * @brief This class is the motherclass of ray engine class. This class can be used as an interface for ray engines.
 * @class RayEngine.
 */
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
  // using ray_dist_t = std::pair<Ray, double>;
  // using obj_dist_t = std::pair<SceneBaseObject *, double>;

  /**
   * @brief This type define the relation between a light source and the direction where it is.
   *
   */
  using source_vect_t = std::pair<LightSource *, vector_t>;

  /**
   * @brief This type define the relation between a incident ray, an object and the inetsection point.
   *
   */
  using ray_obj_dist_t = std::tuple<Ray *, SceneBaseObject *, double>;

  RayEngine(std::vector<Ray> &rays, std::vector<SceneBaseObject *> &objects,
            std::vector<LightSource> &sources, Screen &screen,
            position_t &observer_pos, RGBColor background_color = RGB_BLACK, double amb_lighting = 1, int deepth = 1);

  /**
   * @brief Construct a new Ray Engine object.
   *
   * @param objects a vector of object that are in the scene.
   * @param sources  a vector of light source that are in the scene.
   * @param screen the screen where the image will be taken.
   * @param obs_pos the position of the observer.
   * @param background_color The background color.
   * @param amb_lighting the ambient light.
   * @param deepth the deepth of ray generation.
   */
  RayEngine(std::vector<SceneBaseObject *> &objects,
            std::vector<LightSource> &sources, Screen &screen,
            position_t &obs_pos, RGBColor background_color = RGB_BLACK, double amb_lighting = 1, int deepth = 1);

  /**
   * @brief Construct a new Ray Engine object. This constructor is generated by the compiler.
   *
   * @param engine
   */
  RayEngine(const RayEngine &engine) = default;

  /**
   * @brief Construct a new Ray Engine object. This constructor is generated by the compiler.
   *
   * @param engine
   */
  RayEngine(RayEngine &&engine) = default;

  /**
   * @brief Destroy the Ray Engine object.
   *
   */
  virtual ~RayEngine() {}

  /**
   * @brief This function launch the rendering of the image. This function is the interface from which we can launch every ray engine.
   *
   */
  virtual void compute() = 0;

  /**
   * @brief Get the screen object.
   *
   * @return Screen
   */
  Screen get_screen() { return m_screen; }

  /**
   * @brief This function generate every fundamental rays.
   *
   */
  void generate_fundamental_rays();
};

/**
 * @brief This class implements the ray casting engine.
 * @class RayCastingEngine
 */
class RayCastingEngine : public RayEngine
{
public:
  /**
   * @brief Construct a new Ray Casting Engine object
   *
   * @param objects a vector of object that are in the scene.
   * @param sources  a vector of light source that are in the scene.
   * @param screen the screen where the image will be taken.
   * @param obs_pos the position of the observer.
   * @param background_color The background color.
   * @param amb_lighting the ambient light.
   */
  RayCastingEngine(std::vector<SceneBaseObject *> &objects,
                   std::vector<LightSource> &sources, Screen &screen,
                   position_t &observer_pos, RGBColor background_color = RGB_BLACK, double amb_lighting = 1);

  /**
   * @brief Construct a new Ray Casting Engine object. This constructor is generated by the compiler.
   *
   * @param engine
   */
  RayCastingEngine(const RayCastingEngine &engine) = default;

  /**
   * @brief Construct a new Ray Casting Engine object. This constructor is generated by the compiler.
   *
   * @param engine
   */
  RayCastingEngine(RayCastingEngine &&engine) = default;

  /**
   * @brief This function implements the compute function of RayEngine.
   *
   */
  void compute();

  /**
   * @brief Get the object and the distance to it from the ray.
   *
   * @return ray_obj_dist_t
   */
  ray_obj_dist_t get_intersection(Ray *);

  /**
   * @brief Get the reachable sources from a intersection.
   *
   */
  void get_reachable_sources(Ray &, SceneBaseObject *, position_t, std::vector<source_vect_t> &);

  /**
   * @brief Generate the reflected ray from an intersection and a source.
   *
   * @return Ray
   */
  Ray generate_reflection_ray(ray_obj_dist_t &, source_vect_t &);

  /**
   * @brief Generate the reflected ray from intersection.
   *
   * @param dist
   * @return Ray
   */
  Ray generate_reflection_ray(ray_obj_dist_t &dist);

  /**
   * @brief Compute the color seen given an intersection a source and a reflected ray.
   *
   * @param dist a intersection point.
   * @param source the source.
   * @param reflected the reflected ray.
   * @return RGBColor
   */
  RGBColor compute_color(ray_obj_dist_t &dist, source_vect_t &source, Ray &reflected);

  /**
   * @brief this function compute
   *
   * @return RGBColor
   */
  RGBColor step(ray_obj_dist_t &);
  RGBColor intermediairy_step(ray_obj_dist_t, int);
};

#endif // __RAY_CASTING_H_
