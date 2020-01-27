#ifndef __LIGHT_SOURCE_H_
#define __LIGHT_SOURCE_H_

#include "types.hpp"

class LightSource {
private:
  position_t m_pos;
  double m_intensity;
  double m_diffusion;

public:
  LightSource(position_t &pos, double &intensity, double &diffusion);
  virtual ~LightSource();
  double get_intensity();
  double get_diffusion();
};

#endif // __LIGHT_SOURCE_H_
