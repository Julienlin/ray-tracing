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

  position_t m_screen_pos; /**< position of the of the most top left pixel. It
                              define the center of the pixel.*/
  std::vector<RGBColor> m_pixels;

  std::vector<position_t>
      m_pix_pos; /**<  Vector of position that refers to the center of pixel
                (i,j) (W,H) by [ j * m_W + i ] */

  std::vector<std::vector<Ray>> m_crossing_rays;

  vector_t m_normal;

public:
  Screen(int H, int W, double pix_size, vector_t v_W, vector_t v_H,
         position_t screen_pos);

  ~Screen() {}
  int H() { return m_H; }
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

  bool write(const std::string &);

  bool is_intersecting(Ray &ray);

  position_t intersect_pt(Ray &ray);
};

#endif // __SCREEN_H_
