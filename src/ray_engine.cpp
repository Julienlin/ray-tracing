#include <ray_engine.hpp>

RayEngine::RayEngine(std::vector<Ray> &rays,
                     std::vector<SceneBaseObject *> &objects,
                     std::vector<LightSource> &sources, Screen &screen,
                     position_t &observer_pos, RGBColor background_color,
                     double amb_lighting, int deepth)
    : m_rays(rays), m_objects(objects), m_sources(sources), m_screen(screen),
      m_obs_pos(observer_pos), m_background_color(background_color),
      m_amb_lighting(amb_lighting), m_deepth(deepth) {}

RayEngine::RayEngine(std::vector<SceneBaseObject *> &objects,
                     std::vector<LightSource> &sources, Screen &screen,
                     position_t &obs_pos, RGBColor background_color,
                     double amb_lighting, int deepth)
    : m_rays(), m_objects(objects), m_sources(sources), m_screen(screen),
      m_obs_pos(obs_pos), m_background_color(background_color),
      m_amb_lighting(amb_lighting), m_deepth(deepth) {}

void RayEngine::generate_fundamental_rays() {
  int nb_rays = m_rays.size();
  // Create fondamental rays
  for (int i = 0; i < nb_rays; i++) {
    vector_t direction = m_screen(i) - m_obs_pos;
    direction.normalize();
    // std::cout << " direction : " << direction << "\tm_obs_pos : " <<
    // m_obs_pos << "\tm_screen(" << i << "): " << m_screen(i) << std::endl;
    m_rays[i] = Ray(m_screen(i), direction, m_background_color);
    m_screen.add_crossing_ray(i, m_rays[i]);
  }
}

/************************************************************************************************
 *
 * Ray Casting
 *
 ************************************************************************************************/

RayCastingEngine::RayCastingEngine(std::vector<SceneBaseObject *> &objects,
                                   std::vector<LightSource> &sources,
                                   Screen &screen, position_t &observer_pos,
                                   RGBColor background_color,
                                   double amb_lighting)
    : RayEngine(objects, sources, screen, observer_pos, background_color,
                amb_lighting) {
  m_rays.resize(m_screen.H() * m_screen.W());
}

void RayCastingEngine::compute() {
  int nb_rays = m_rays.size();

  spdlog::get("console")->info("Generate fundamental rays...");
  spdlog::get("rayEngine")->info("Generate fundamental rays...");
  auto timer_beg = std::chrono::duration_cast<std::chrono::milliseconds>(
                       std::chrono::system_clock::now().time_since_epoch())
                       .count();
  generate_fundamental_rays();
  auto timer_end = std::chrono::duration_cast<std::chrono::milliseconds>(
                       std::chrono::system_clock::now().time_since_epoch())
                       .count();
  spdlog::get("console")->info(
      " Fundamental rays generation time to process : {} s",
      (timer_end - timer_beg) / 1000);
  spdlog::get("rayEngine")
      ->info(" Fundamental rays generation time to process : {} s",
             (timer_end - timer_beg) / 1000);
  spdlog::get("console")->info("Rendering scene...");
  spdlog::get("rayEngine")->info("Rendering scene...");

  // Foreach ray check wether it hits something. We store the element and the
  // distance of the object.

  std::vector<ray_obj_dist_t> distances;

  timer_beg = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::system_clock::now().time_since_epoch())
                  .count();
  // TODO: why nb_t_rays = nb_rays * 2 * m_deepth;
  int nb_tt_rays = nb_rays * 2 * m_deepth;
  distances.reserve(nb_tt_rays);
  for (int i = 0; i < nb_rays; i++) {
    auto ray = m_rays[i];
    ray_obj_dist_t buf = get_intersection(&m_rays[i]);
    if (std::get<2>(buf) > HORIZON) {
      std::get<2>(buf) = std::numeric_limits<double>::infinity();
    }
    distances.push_back(buf);
  }
  timer_end = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::system_clock::now().time_since_epoch())
                  .count();
  spdlog::get("console")->info(
      " First intersection generation time toprocess : {} s",
      (timer_end - timer_beg) / 1000);
  spdlog::get("rayEngine")
      ->info(" First intersection generation time toprocess : {} s",
             (timer_end - timer_beg) / 1000);

  int nb_intersec = 0;
  timer_beg = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::system_clock::now().time_since_epoch())
                  .count();

  for (int i = 0; i < nb_tt_rays; i++) {
    // Determing the color of rays
    // testing if > 0 in the case of when the image is split by a plan  some ray
    // can be on the plane so we don't want to compute the color first.

    ray_obj_dist_t dist = distances[i];

    if (std::get<2>(dist) < std::numeric_limits<double>::infinity() &&
        std::get<2>(dist) > 0) {
      nb_intersec++;

      RGBColor color = intermediairy_step(dist, m_deepth);
    }
  }

  timer_end = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::system_clock::now().time_since_epoch())
                  .count();
  spdlog::get("rayEngine")
      ->info(" Ray simulation time to process : {} s",
             (timer_end - timer_beg) / 1000);
  spdlog::get("console")->info(" Ray simulation time to process : {} s",
                               (timer_end - timer_beg) / 1000);
  spdlog::get("console")->info("nb_intersec : {}", nb_intersec);
  spdlog::get("rayEngine")->info("nb_intersec : {}", nb_intersec);
  timer_beg = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::system_clock::now().time_since_epoch())
                  .count();

  // Determine the color for each pixel
  for (unsigned i = 0; i < m_rays.size(); i++) {
    m_screen[i] = m_rays[i].getColor();
  }

  spdlog::get("console")->info("Computing done!");
  timer_end = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::system_clock::now().time_since_epoch())
                  .count();
  spdlog::get("rayEngine")
      ->info(" Image generation time to process : {} s",
             (timer_end - timer_beg) / 1000);
  spdlog::get("console")->info(" Image generation time to process : {}s",
                               (timer_end - timer_beg) / 1000);
}

void RayCastingEngine::get_reachable_sources(
    Ray &ray_incident, SceneBaseObject *obj, position_t pos,
    std::vector<source_vect_t> &reachables) {
  reachables.clear();
  vector_t normal = obj->getNormal(pos);
  // foreach source see that they
  for (unsigned i = 0; i < m_sources.size(); i++) {
    vector_t direction = m_sources[i].get_pos() - pos;
    direction.normalize();
    Ray ray(pos, direction);
    ray_obj_dist_t obstacle = get_intersection(&ray);
    std::stringstream ss;

    if (std::get<2>(obstacle) == std::numeric_limits<double>::infinity()) {
      if ((ray_incident.getDirection() * normal) * (normal * (-direction)) >
          0) {
        source_vect_t new_el(&m_sources[i], direction);
        reachables.push_back(new_el);
      }
    }
  }
}

RayCastingEngine::ray_obj_dist_t RayCastingEngine::get_intersection(Ray *ray) {
  ray_obj_dist_t obstacle(ray, nullptr,
                          std::numeric_limits<double>::infinity());
  for (auto obj : m_objects) {
    ray_obj_dist_t new_dist(ray, obj, obj->intersecDist(*ray));

    if (std::get<2>(new_dist) >= obj->MIN_PROXIMITY &&
        std::get<2>(new_dist) < std::get<2>(obstacle)) {
      obstacle.swap(new_dist);
    }
  }
  return obstacle;
}

Ray RayCastingEngine::generate_reflection_ray(ray_obj_dist_t &dist,
                                              source_vect_t &source) {
  Ray *ray = std::get<0>(dist);
  double t = std::get<2>(dist);
  position_t pos = ray->getPos() + t * ray->getDirection();
  auto normal = std::get<1>(dist)->getNormal(pos);
  auto L = source.second;
  auto x = L * normal;
  auto direction = 2 * x * normal - L;
  direction.normalize();
  Ray new_ray(pos, direction, std::get<1>(dist)->getSurface()->getColor(pos),
              ray->get_fundamental());
  return new_ray;
}

RGBColor RayCastingEngine::compute_color(ray_obj_dist_t &dist,
                                         source_vect_t &source,
                                         Ray &reflected) {

  Ray *ray = std::get<0>(dist);
  double t = std::get<2>(dist);
  position_t pt_pos = ray->getPos() + t * ray->getDirection();

  // Determining the illumination of the point / ray
  vector_t V = m_obs_pos - pt_pos;
  V.normalize();

  auto ray_color = std::get<0>(dist)->getColor();
  auto new_color = RGB_BLACK;

  auto N = std::get<1>(dist)->getNormal(pt_pos);
  auto L = source.second;
  auto k_s = std::get<1>(dist)->get_spec_reflect();
  auto k_d = std::get<1>(dist)->get_diff_reflect();
  auto alpha = std::get<1>(dist)->get_shine();
  auto i_d = source.first->get_diffusion();
  auto i_s = source.first->get_intensity();
  auto RV = reflected.getDirection() * V;
  auto LN = (L * N);

  if (LN > 0) {
    new_color += k_d * LN * i_d * ray_color;
  }

  if (RV > 0) {
    new_color += k_s * power<double>(RV, alpha) * i_s * RGB_WHITE;
  }
  return new_color;
}

RGBColor RayCastingEngine::step(ray_obj_dist_t &dist) {
  // pt_pos is the position of the intersection.
  position_t pt_pos = std::get<0>(dist)->getPos() +
                      std::get<2>(dist) * std::get<0>(dist)->getDirection();
  std::get<0>(dist)->setColor(
      std::get<1>(dist)->getSurface()->getColor(pt_pos));

  // determining all light sources reachable from this point
  std::vector<source_vect_t> reachables;
  get_reachable_sources(*std::get<0>(dist), std::get<1>(dist), pt_pos,
                        reachables);

  unsigned nb_reachables_R = reachables.size();

  // Determining the perfect reflected ray foreach sources

  if (nb_reachables_R > 0) {
    std::vector<Ray> R;
    R.reserve(nb_reachables_R);
    for (unsigned j = 0; j < nb_reachables_R; j++) {
      R[j] = generate_reflection_ray(dist, reachables[j]);
    }

    auto new_color = RGB_BLACK;

    for (unsigned j = 0; j < nb_reachables_R; j++) {
      auto reachable = reachables[j];
      auto r = R[j];
      new_color += compute_color(dist, reachable, r);
    }
    auto k_a = std::get<1>(dist)->get_amb_reflect();
    new_color += m_amb_lighting * k_a * new_color;
    return new_color;
  } else {
    return m_background_color;
  }
}

RGBColor RayCastingEngine::intermediairy_step(ray_obj_dist_t dist, int deepth) {
  if (std::get<2>(dist) == std::numeric_limits<double>::infinity()) {
    return m_background_color;
  }
  if (deepth == 0) {
    return step(dist);
  } else {
    // pt_pos is the position of the intersection.
    position_t pt_pos = std::get<0>(dist)->getPos() +
                        std::get<2>(dist) * std::get<0>(dist)->getDirection();
    std::get<0>(dist)->setColor(
        std::get<1>(dist)->getSurface()->getColor(pt_pos));

    Ray reflec_ray = generate_reflection_ray(dist);
    ray_obj_dist_t refleted = get_intersection(&reflec_ray);
    RGBColor reflect_color = intermediairy_step(refleted, deepth - 1);

    // RGBColor ray_color = std::get<0>(dist)->getColor();
    // auto k_a = std::get<1>(dist)->get_amb_reflect();

    double reflect_coef = std::get<1>(dist)->get_reflect();
    RGBColor new_color = step(dist);
    if (std::get<2>(refleted) < std::numeric_limits<double>::infinity() &&
        reflect_coef > 0) {
      new_color += reflect_coef * reflect_color;
    }

    if (std::get<0>(dist)->get_fundamental() == nullptr) {
      std::get<0>(dist)->setColor(new_color);
    } else {
      std::get<0>(dist)->get_fundamental()->setColor(new_color);
    }
    return new_color;
  }
}

Ray RayCastingEngine::generate_reflection_ray(ray_obj_dist_t &dist) {
  Ray *ray = std::get<0>(dist);
  double t = std::get<2>(dist);
  position_t pos = ray->getPos() + t * ray->getDirection();
  auto normal = std::get<1>(dist)->getNormal(pos);
  vector_t incident = ray->getDirection();
  incident.normalize();
  vector_t reflected = 2 * (incident * normal) * normal - incident;
  RGBColor color = std::get<1>(dist)->getColor(pos);
  return Ray(pos, reflected, color, ray->get_fundamental());
}
