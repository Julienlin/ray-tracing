#ifndef __SURFACE_REFLECTION_HPP_
#define __SURFACE_REFLECTION_HPP_

#include <objet_base_surface.hpp>
#include <ray.hpp>

class Surface_reflection : public ObjectBaseSurface
{
private:
    /**
     * @brief compris dans [0,1]; détermine la réfexivité de l'objet
     */
    double m_reflect_intensity;

public:
    Surface_reflection(double reflect_intensity);
    virtual ~Surface_reflection(){};
};

Surface_reflection::Surface_reflection(double reflect_intensity) : m_reflect_intensity(reflect_intensity) {}

#endif