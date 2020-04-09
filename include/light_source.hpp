#ifndef __LIGHT_SOURCE_H_
#define __LIGHT_SOURCE_H_

#include <types.hpp>
/**
 * @brief This class describe a light source in the scene.
 * @class LightSource
 */
class LightSource
{
private:
  /**
   * m_pos describe the position of the light source.
   */
  position_t m_pos;
  double m_intensity;
  double m_diffusion;

public:
  /**
   * @brief Construct a new Light Source object
   * @param pos is the position in the scene of the light.
   * @param intensity is the coefficent of intensity of the light.
   * @param diffusion is the diffusion coefficent of the light.
   */
  LightSource(position_t &, double &, double &);
  /**
   * @brief Construct a new Light Source object
   * @param pos is the position in the scene of the light.
   * @param intensity is the coefficent of intensity of the light.
   * @param diffusion is the diffusion coefficent of the light.
   */
  LightSource(position_t, double, double);
  // virtual ~LightSource() {}
  /**
   * @brief Get the intensity object.
   *
   * @return double
   */
  double get_intensity();
  /**
   * @brief Get the diffusion object.
   *
   * @return double
   */
  double get_diffusion();
  /**
   * @brief Get the pos object.
   *
   * @return position_t
   */
  position_t get_pos();
};

#endif // __LIGHT_SOURCE_H_
