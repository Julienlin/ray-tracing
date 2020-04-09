#ifndef __RAY_ENGINE_THREAD_HPP_
#define __RAY_ENGINE_THREAD_HPP_

#include <omp.h>
#include <ray_engine.hpp>
#include <chrono>

/**
 * @brief This class implements the ray casting engine.
 * @class RayEngineThread
 */
class RayEngineThread : public RayEngine
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
    RayEngineThread(std::vector<SceneBaseObject *> &objects,
                    std::vector<LightSource> &sources, Screen &screen,
                    position_t &observer_pos, RGBColor background_color = RGB_BLACK, double amb_lighting = 1);

    /**
   * @brief Construct a new Ray Casting Engine object. This constructor is generated by the compiler.
   *
   * @param engine
   */
    RayEngineThread(const RayEngineThread &engine) = default;

    /**
   * @brief Construct a new Ray Casting Engine object. This constructor is generated by the compiler.
   *
   * @param engine
   */
    RayEngineThread(RayEngineThread &&engine) = default;

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

#endif
