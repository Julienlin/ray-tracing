/**
 * @file ray.hpp
 * @author Julien Lin
 * @brief This contains the implementation of the Ray class.
 * @version 0.1
 * @date 2020-02-09
 *
 */
#ifndef __RAY_H_
#define __RAY_H_

#include "types.hpp"
#include <utility>
/**
 * @brief This class represent a ray in the scene.
 * @class Ray
 */
class Ray
{
private:
  position_t m_pos;
  vector_t m_direction;
  RGBColor m_color;
  /**
   * We have to record which pixels we come from so we can update the color. Instead of keeping the pixels,
   * we keep the ray come out from the pixels.
   */
  Ray *m_fundamental;

public:
  /**
   * @brief Construct a new Ray object. This constructor a ray that come from (0,0,0) with (0,0,0) direction,
   *  black color and no fundamental.
   *
   */
  Ray();

  /**
   * @brief Construct a new Ray object.
   *
   * @param pos origin of the ray.
   * @param direction direction of the ray.
   * @param color color of the ray.
   * @param fondamental fundamental ray that this ray come from. If the ray is a fundamental ray the attribute is equal to nullptr.
   */
  Ray(position_t pos, vector_t direction, RGBColor color,
      Ray *fondamental = nullptr);

  /**
   * @brief Construct a new Ray object. The color is initialize to black and fundamental to nullptr.
   *
   * @param pos  origin of the ray.
   * @param direction direction of the ray.
   */
  Ray(position_t pos, vector_t direction);

  /**
   * @brief Get the Pos object
   *
   * @return position_t
   */
  position_t getPos() const { return m_pos; };

  /**
   * @brief Get the Direction object
   *
   * @return vector_t
   */
  vector_t getDirection() const { return m_direction; }

  /**
   * @brief Get the Color object
   *
   * @return RGBColor
   */
  RGBColor getColor() const { return m_color; }

  /**
   * @brief Set the Pos object
   *
   * @param pos
   */
  void setPos(const position_t &pos);

  /**
   * @brief Set the Direction object
   *
   * @param direction
   */
  void setDirection(const vector_t &direction);

  /**
   * @brief Set the Color object
   *
   * @param color
   */
  void setColor(RGBColor color) { swap(color, m_color); }

  /**
   * @brief Overload the operator equal.
   *
   * @return Ray&
   */
  Ray &operator=(const Ray &);

  /**
   * @brief Get the fundamental object.
   *
   * @return Ray*
   */
  Ray *get_fundamental();
  ~Ray(){};
};

using genRays_t = std::tuple<Ray, Ray>;

#endif // __RAY_H_
