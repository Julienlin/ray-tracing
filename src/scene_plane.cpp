#include <scene_plane.hpp>

ScenePlane::ScenePlane(ObjectBaseSurface *surface, double spec_reflect, double diff_reflect, double amb_reflect, double shine, position_t origin, vector_t e1, vector_t e2) : SceneBaseObject(surface, spec_reflect, diff_reflect, amb_reflect, shine), m_origin(origin), m_e1(e1), m_e2(e2), m_normal(m_e1 ^ m_e2)
{
    m_e1.normalize();
    m_e2.normalize();
    m_normal.normalize();
}

ScenePlane::ScenePlane(ObjectBaseSurface *surface, position_t origin, vector_t e1, vector_t e2) : SceneBaseObject(surface), m_origin(origin), m_e1(e1), m_e2(e2), m_normal(m_e1 ^ m_e2) {}

vector_t ScenePlane::getNormal(const position_t &pos)
{
    return m_normal;
}

double ScenePlane::intersecDist(const Ray &ray)
{
    auto pos = ray.getPos();
    auto direction = -ray.getDirection();
    auto origin_to_pos = pos - m_origin;
    double d = direction * m_normal;
    double t = -1;
    if (d == 0)
    {
        if (origin_to_pos * m_normal == 0)
        {
            return 0;
        }
        return t;
    }

    // TODO: finding a way to determine the "good side" of the plane

    t = (m_normal * origin_to_pos) / d;
    // double u = ((m_e2 ^ direction) * origin_to_pos) / d;
    // double v = ((direction ^ m_e1) * origin_to_pos) / d;
    return t > 0 ? t : -1;
}