/**
 * @file screen.hpp
 * @author Julien Lin
 * @brief
 * @version 0.1
 * @date 2020-02-09
 *
 *
 */
#ifndef __SCREEN_H_
#define __SCREEN_H_

#include "ray.hpp"
#include "types.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Screen
{
private:
  int m_H;
  int m_W;
  double
      m_pix_size; /**< Size of a pixel in the model. The pixel is a square. */

  vector_t m_v_H; /**<  Vector that define the direction and orientation of the
                     screen in Height. Since M_POS is the position of top left
                     most pixel. */
  vector_t m_v_W; /**<  Same as m_v_H but in the width direction.*/

  position_t m_screen_pos; /**< position of the top left most pixel. It
                              define the center of the pixel.*/
  std::vector<RGBColor> m_pixels;

  std::vector<position_t>
      m_pix_pos; /**<  Vector of position that refers to the center of pixel
                (i,j) (W,H) by [ j * m_W + i ] */

  std::vector<std::vector<Ray>> m_crossing_rays;

  /**
   * contains the normal of the screen plane.
   */
  vector_t m_normal;

public:
  /**
   * @brief Construct a new Screen object.
   *
   * @param H height in pixels of the screen.
   * @param W width in pixels of the screen.
   * @param pix_size size a pixel.
   * @param v_W the vector on which the width is in the scene.
   * @param v_H the vector on which the height is in the scene.
   * @param screen_pos the position of the center of the top left most pixel.
   */
  Screen(int H, int W, double pix_size, vector_t v_W, vector_t v_H,
         position_t screen_pos);

  /**
   * Get the heigth of the screen.
   *
   * @return int
   */
  int H() { return m_H; }

  /**
   * @brief Get the width of the screen.
   *
   * @return int
   */
  int W() { return m_W; }

  /**
   * Get the color of the pixel i.
   *
   * @param i linearize index of the pixel.
   *
   * @return color of the pixel i.
   */
  RGBColor &operator[](int i);

  /**
   * Get the position_t of the center of the pixel i.
   *
   * @param i linearize index of the pixel.
   *
   * @return position_t of the center of the pixel i.
   */
  position_t &operator()(int i);

  void add_crossing_ray(int i, Ray &ray);

  /**
   * @brief Save the screen in a given filename.
   *
   * @return true if everthing went well.
   * @return false if there was an error.
   */
  bool write(const std::string &);

  bool is_intersecting(Ray &ray);

  position_t intersect_pt(Ray &ray);
};

#endif // __SCREEN_H_
