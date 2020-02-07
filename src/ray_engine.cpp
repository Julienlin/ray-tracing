#include <ray_engine.hpp>

RayEngine::RayEngine(std::vector<Ray> &rays, std::vector<SceneBaseObject *> &objects,
                     std::vector<LightSource> &sources, Screen &screen,
                     position_t &observer_pos, int deepth)
    : m_rays(rays), m_objects(objects), m_sources(sources), m_screen(screen),
      m_obs_pos(observer_pos), m_deepth(deepth) {}

RayEngine::RayEngine(std::vector<SceneBaseObject *> &objects,
                     std::vector<LightSource> &sources, Screen &screen,
                     position_t &obs_pos, int deepth)
    : m_rays(), m_objects(objects), m_sources(sources), m_screen(screen),
      m_obs_pos(obs_pos), m_deepth(deepth) {}

RayCastingEngine::RayCastingEngine(std::vector<SceneBaseObject *> &objects,
                                   std::vector<LightSource> &sources, Screen &screen,
                                   position_t &observer_pos)
    : RayEngine(objects, sources, screen, observer_pos)
{
  m_rays.resize(m_screen.H() * m_screen.W());
}

void RayCastingEngine::compute()
{
  int nb_rays = m_rays.size();
  // Create fondamental rays
  for (int i = 0; i < nb_rays; i++)
  {
    vector_t direction = m_screen(i) - m_obs_pos;
    direction.normalize();
    // std::cout << " direction : " << direction << "\tm_obs_pos : " << m_obs_pos << "\tm_screen(" << i << "): " << m_screen(i) << std::endl;
    m_rays[i] = Ray(m_screen(i), direction, RGB_BLACK);
    m_screen.add_crossing_ray(i, m_rays[i]);
  }

  spdlog::get("console")->info("Computing...");

  // Foreach ray check wether it hits something. Wi store the element and the distance of the object.
  std::vector<obj_dist_t> distances;
  distances.reserve(nb_rays);
  for (unsigned i = 0; i < distances.capacity(); i++)
  {
    auto ray = m_rays[i];
    distances[i] = get_intersection(ray);
    // if (distances[i].second != std::numeric_limits<double>::infinity())
    // {
    //   std::cout << "i : " << i << "\tintesection point : " << ray.getPos() + distances[i].second * ray.getDirection() << std::endl;
    // }
  }

  int nb_intersec = 0;
  for (int i = 0; i < nb_rays; i++)
  {
    // Determing the color of rays
    // testing if > 0 in the case of when the image is split by a plan  some ray can be on the plane so we don't want to compute the color first.
    if (distances[i].second < std::numeric_limits<double>::infinity() && distances[i].second > 0)
    {
      nb_intersec++;

      // pt_pos is the position of the intersection.
      position_t pt_pos =
          m_rays[i].getPos() + distances[i].second * m_rays[i].getDirection();
      m_rays[i].setColor(distances[i].first->getSurface()->getColor(pt_pos));

      // determining all light sources reachable from this point
      std::vector<source_vect_t> reachables;
      get_reachable_sources(pt_pos, reachables);
      // std ::cout << "i : " << i << "\tsize of reachables : " << reachables.size() << std::endl;

      unsigned nb_reachables_R = reachables.size();
      // Determining the perfect reflected ray foreach sources
      if (nb_reachables_R > 0)
      {
        std::vector<Ray> R;
        R.reserve(nb_reachables_R);
        for (unsigned j = 0; j < nb_reachables_R; j++)
        {
          R[j] = generate_reflection_ray(pt_pos, distances[i].first, reachables[j]);
          // std::cout << "R[" << j << "] direction : " << R[j].getDirection() << std::endl;
        }

        // Determining the illumination of the point / ray
        vector_t V = m_obs_pos - pt_pos;
        V.normalize();
        auto ray_color = m_rays[i].getColor();
        auto new_color = RGB_BLACK;

        for (unsigned j = 0; j < nb_reachables_R; j++)
        {
          auto N = distances[i].first->getNormal(pt_pos);
          // auto k_a = distances[i].first->get_amb_reflect();
          auto L = reachables[j].second;
          auto k_s = distances[i].first->get_spec_reflect();
          auto k_d = distances[i].first->get_diff_reflect();
          // double k_d = 300;
          auto alpha = distances[i].first->get_shine();
          // int alpha = 10;
          auto i_d = reachables[j].first->get_diffusion();
          auto i_s = reachables[j].first->get_intensity();
          auto RV = R[j].getDirection() * V;
          // RV = RV > 0 ? RV : -RV;
          auto LN = (L * N);
          // LN = LN > 0 ? LN : -LN;

          // std ::cout << "i : " << i << "\tL : " << L << "\tk_s : " << k_s << "\tk_d : " << k_d
          //  << "\talpha : " << alpha << "\tRV : " << RV << "\tV : " << V << "\tN :" << N << "\t L * N : " << L * N * k_d * i_d << std::endl;

          new_color +=
              k_d * LN * i_d * ray_color + k_s * power<double>(RV, alpha) * i_s * RGB_WHITE;
        }
        m_rays[i].setColor(new_color);
      }
      else
      {
        m_rays[i].setColor(RGB_BLACK);
      }
    }
  }
  std::stringstream ss;
  ss << "nb_intersec : " << nb_intersec << std::ends;
  spdlog::info(ss.str());

  // Determine the color for each pixel
  for (unsigned i = 0; i < m_rays.size(); i++)
  {
    m_screen[i] = m_rays[i].getColor();
  }

  spdlog::get("console")->info("Computing done!");
}

void RayCastingEngine::get_reachable_sources(
    position_t pos, std::vector<source_vect_t> &reachables)
{
  reachables.clear();
  // foreach source see that they
  for (unsigned i = 0; i < m_sources.size(); i++)
  {
    vector_t direction = m_sources[i].get_pos() - pos;
    direction.normalize();
    // std::cout << "direction pos to source : " << direction << std::endl;
    Ray ray(pos, direction);
    obj_dist_t obstacle = get_intersection(ray);
    if (obstacle.second == std::numeric_limits<double>::infinity())
    {
      source_vect_t new_el(&m_sources[i], direction);
      reachables.push_back(new_el);
    }
  }
}

RayCastingEngine::obj_dist_t RayCastingEngine::get_intersection(Ray &ray)
{
  obj_dist_t obstacle(nullptr, std::numeric_limits<double>::infinity());
  for (auto obj : m_objects)
  {
    obj_dist_t new_dist(obj, obj->intersecDist(ray));
    // std::cout << "Ray pos : " << ray.getPos() << "\tdist : " << new_dist.second << std::endl;
    if (new_dist.second >= 0 && new_dist.second < obstacle.second)
    {
      obstacle.swap(new_dist);
    }
  }
  return obstacle;
}

Ray RayCastingEngine::generate_reflection_ray(const position_t &pos,
                                              SceneBaseObject *obj,
                                              source_vect_t &source)
{
  auto normal = obj->getNormal(pos);
  auto L = source.second;
  auto x = L * normal;
  auto direction = 2 * x * normal - L;
  direction.normalize();
  return Ray(pos, direction);
}
