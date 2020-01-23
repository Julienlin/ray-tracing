#include "ray_engine.hpp"


void RayCastingEngine::compute(){
    int nb_rays = m_rays.size();
    for (int i = 0; i < nb_rays; i++) {
        vector_t direction = m_screen[i] - m_obs_pos;
    }
}
