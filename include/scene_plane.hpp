#ifndef SCENE_PLANE_HPP
#define SCENE_PLANE_HPP

#include <cmath>
#include <iostream>
#include <scene_base_object.hpp>
#include <types.hpp>

class ScenePlane : public SceneBaseObject
{
private:
    position_t m_origin;
    vector_t m_e1, m_e2;
    vector_t m_normal;

public:
    ScenePlane(ObjectBaseSurface *surface, double spec_reflect, double diff_reflect, double amb_reflect, double shine, position_t origin, vector_t e1, vector_t e2);
    ScenePlane(ObjectBaseSurface *surface, position_t origin, vector_t e1, vector_t e2);
    vector_t getNormal(const position_t &pos);
    double intersecDist(const Ray &ray);
    RGBColor getColor(position_t &pos) const;
};

#endif