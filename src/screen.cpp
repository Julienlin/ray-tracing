#include <screen.hpp>

Screen::Screen(int H, int W, double pix_size, vector_t v_W, vector_t v_H,
               position_t screen_pos)
    : m_H(H), m_W(W), m_pix_size(pix_size), m_v_H(v_H), m_v_W(v_W),
      m_screen_pos(screen_pos), m_pixels(m_H * m_W), m_pix_pos(m_H * m_W),
      m_crossing_rays(m_H * m_W), m_normal(v_W ^ v_W)
{
  // int n = m_H * m_W;
  m_pix_pos[0] = position_t(m_screen_pos);
  // std::cout << "m_pix_pos[0] : " << m_pix_pos[0] << std::endl;
  // double half_px_size = m_pix_size / 2;
  vector_t cur_v_H = m_v_H;
  vector_t cur_v_W = m_v_W;
  for (int i = 0; i < m_H; i++)
  {
    cur_v_W = m_v_W;
    for (int j = 0; j < m_W; j++)
    {
      // calcul des futurs position centrale ( il faut sauvegarder ou utilisé le
      // tableau existant )
      if (!(i == 0 && j == 0))
      {
        m_pix_pos[i * m_W + j] =
            m_screen_pos + m_pix_size * cur_v_H + m_pix_size * cur_v_W;
        // std::cout << "m_pix_pos[" << i * m_W + j << "] : " << m_pix_pos[i * m_W + j] << std::endl;
        cur_v_W += m_v_W;
      }
    }
    cur_v_H += m_v_H;
  }
}

RGBColor &Screen::operator[](int i) { return m_pixels[i]; }

position_t &Screen::operator()(int i) { return m_pix_pos[i]; }

void Screen::add_crossing_ray(int i, Ray &ray)
{
  m_crossing_rays[i].push_back(ray);
}

bool Screen::write(const std::string &filename)
{
  std::ofstream ofs;
  ofs.open(filename, std::ios::out | std::ios::binary);
  ofs << "P6\n"
      << m_W << " " << m_H << "\n255\n";
  int n = m_H * m_W;
  for (int i = 0; i < n; i++)
  {
    ofs << m_pixels[i];
  }
  ofs.close();
  return true;
}

bool Screen::is_intersecting(Ray &ray)
{
  // determine wether the ray is intersecting the plane

  // determine wether the intersection point belong to the screen
  auto ray_pos = ray.getPos();
  auto ray_direction = ray.getDirection();

  if (ray_direction * m_normal == 0)
  {
    if ((ray_pos - m_screen_pos) * m_normal == 0)
    { // the line is in the plane the screen. We now
      // do nothing.
      return false;
    }
    return false;
  }

  double t = (m_normal * (ray_pos - m_screen_pos)) / ((-ray_direction) * m_normal);
  double u = ((m_v_W ^ (-ray_direction)) * (ray_pos - m_screen_pos)) / ((-ray_direction) * m_normal);
  double v = (((-ray_direction) ^ m_v_H) * (ray_pos - m_screen_pos)) / ((-ray_direction) * m_normal);

  if (v < 0 || u < 0)
  {
    return false;
  }
  else
  {
    auto top = m_screen_pos - m_v_H - m_v_W;
    ///MERDE c'est en 3D
    auto v_w_max = top.x + m_W * m_pix_size * m_v_W.x;
    auto v_h_max = top.y + m_H * m_pix_size * m_v_W.y;
  }

  // auto intersct_pt = ray_pos + (t * ray_direction);
  return t > 0;
}

position_t Screen::intersect_pt(Ray &ray)
{
  auto ray_pos = ray.getPos();
  auto ray_direction = ray.getDirection();

  double t = (m_normal * (ray_pos - m_screen_pos)) / ((-ray_direction) * m_normal);
  double u = ((m_v_W ^ (-ray_direction)) * (ray_pos - m_screen_pos)) / ((-ray_direction) * m_normal);
  double v = (((-ray_direction) ^ m_v_H) * (ray_pos - m_screen_pos)) / ((-ray_direction) * m_normal);

  auto pt = ray_pos + (t * ray_direction);
  return pt;
}
