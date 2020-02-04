#include "screen.hpp"

Screen::Screen(int H, int W, double pix_size, vector_t v_H, vector_t v_W,
               position_t screen_pos)
    : m_H(H), m_W(W), m_pix_size(pix_size), m_v_H(v_H), m_v_W(v_H),
      m_screen_pos(screen_pos), m_pixels(m_H * m_W), m_pix_pos(m_H * m_W),
      m_crossing_rays(m_H * m_W)
{
  // int n = m_H * m_W;
  m_pix_pos[0] = position_t(m_screen_pos);
  double half_px_size = m_pix_size / 2;
  vector_t cur_v_H = m_v_H;
  vector_t cur_v_W = m_v_W;
  for (int i = 0; i < m_H; i++)
  {
    cur_v_W = m_v_W;
    for (int j = 0; j < m_W; j++)
    {
      // calcul des futurs position centrale ( il faut sauvegarder ou utilisé le
      // tableau existant )
      m_pix_pos[i * m_W + j] =
          m_screen_pos + half_px_size * cur_v_H + half_px_size * cur_v_W;
      cur_v_W += m_v_W;
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

