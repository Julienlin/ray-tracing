#ifndef __LIGHT_SOURCE_H_
#define __LIGHT_SOURCE_H_

#include "types.hpp"

class LightSource  {
private:
  position_t m_pos;
        // TODO: add color with sfml.
public:
  LightSource();
  virtual ~LightSource();
};

#endif // __LIGHT_SOURCE_H_
