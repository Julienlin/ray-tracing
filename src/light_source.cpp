#include "light_source.hpp"

LightSource::LightSource(position_t &pos, double &intensity,
                         double &diffusion) :
    m_pos(pos), m_intensity(intensity), m_diffusion(diffusion){}

double LightSource::get_intensity(){ return m_intensity; }
double LightSource::get_diffusion(){ return m_diffusion; }
