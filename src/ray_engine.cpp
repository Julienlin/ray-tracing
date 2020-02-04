#include "ray_engine.hpp"

void RayCastingEngine::compute() {
  int nb_rays = m_rays.size();
  // Create fondamental rays
  for (int i = 0; i < nb_rays; i++) {
    vector_t direction = m_screen(i) - m_obs_pos;
    direction.normalize();
    m_rays[i] = Ray(m_screen(i), direction);
    m_screen.add_crossing_ray(i, m_rays[i]);
  }

  // Foreach ray check wether it hits something.
  std::vector<obj_dist_t> distances;
  distances.reserve(m_rays.size());
  for (int i = 0; i < distances.capacity(); i++) {
    Ray ray = m_rays[i];
    distances[i] = get_intersection(ray);
  }

  for (unsigned i = 0; i < distances.size(); i++) {
    // Determing the color of rays
    if (distances[i].second != std::numeric_limits<double>::infinity()) {
      position_t pt_pos =
          m_rays[i].getPos() + distances[i].second * m_rays[i].getDirection();
      m_rays[i].setColor(distances[i].first->getSurface()->getColor(pt_pos));

      // determining all light sources reachable from this point
      std::vector<source_vect_t> reachables;
      get_reachable_sources(pt_pos, reachables);

      // Determining the the perfect reflected ray foreach sources
      std::vector<Ray> R;
      R.reserve(reachables.size());
      for (unsigned j = 0; j < reachables.size(); j++) {
        R[j] = make_reflect_ray(pt_pos, distances[i].first, reachables[j]);
      }

      // Determining the illumination of the point / ray
      vector_t N = distances[i].first->getNormal(pt_pos);
      vector_t V = m_rays[i].getDirection();
      double illumination = 0;

      for (unsigned j = 0; j < R.size(); j++) {
        // auto k_a = distances[i].first->get_amb_reflect();
        auto L = reachables[i].second;
        auto k_s = distances[i].first->get_spec_reflect();
        auto k_d = distances[i].first->get_diff_reflect();
        auto alpha = distances[i].first->get_shine();
        auto RV = R[j].getDirection() * V;
        illumination += k_d * (L * N) * reachables[j].first->get_diffusion() +
                        k_s * power<double>(RV, alpha) *
                            reachables[j].first->get_intensity();
      }
      m_rays[i].setIntensity(illumination);
    }
  }
  // Determine the color for each pixel
  for (unsigned i = 0; i < m_rays.size(); i++) {
    m_screen[i] = m_rays[i].getIntensity() * m_rays[i].getColor();
  }
}

void RayCastingEngine::get_reachable_sources(
    position_t pos, std::vector<source_vect_t> &reachables) {
  // foreach source see that they
  for (unsigned i = 0; i < m_sources.size(); i++) {
    vector_t direction = m_sources[i].get_pos() - pos;
    direction.normalize();
    Ray ray(pos, direction);
    auto obstacle = get_intersection(ray);
    if (obstacle.second == std::numeric_limits<double>::infinity()) {
      source_vect_t new_el(&m_sources[i], direction);
      reachables.push_back(new_el);
    }
  }
}

RayCastingEngine::obj_dist_t RayCastingEngine::get_intersection(Ray &ray) {
  obj_dist_t obstacle(nullptr, std::numeric_limits<double>::infinity());
  for (auto obj : m_objects) {
    obj_dist_t new_dist(obj, obj->intersecDist(ray));
    if (new_dist.second < obstacle.second) {
      obstacle.swap(new_dist);
    }
  }
  return obstacle;
}

Ray RayCastingEngine::make_reflect_ray(const position_t &pos,
                                       SceneBaseObject *obj,
                                       source_vect_t &source) {
  auto normal = obj->getNormal(pos);
  auto L = source.second;
  auto x = L * normal;
  auto direction = 2 * x * normal - L;
  direction.normalize();
  return Ray(pos, direction);
}
