#include <scene_triangle.hpp>

SceneTriangle::SceneTriangle(ObjectBaseSurface *surface, position_t A, position_t B, position_t C, double reflect, double spec_reflect, double diff_reflect, double amb_reflect, double shine) : SceneBaseObject(surface, reflect, spec_reflect, diff_reflect, amb_reflect, shine), m_A(A), m_B(B), m_C(C), m_normal((B - A) ^ (C - A)) {}

// double SceneTriangle::intersecDist(const Ray &ray)
// {
//     if (ray.getDirection() * m_normal == 0)
//     {
//         if ((ray.getPos() - m_A) * m_normal == 0)
//         {
//             return 0;
//         }
//         return -1;
//     }
//     else
//     {
//         auto direction = -ray.getDirection();
//         double d = m_normal * direction;
//         double tA = (m_normal * (ray.getPos() - m_A)) / d;
//         double tC = (m_normal * (ray.getPos() - m_C)) / d;
//         if (tA < MIN_PROXIMITY)
//         {
//             return -1;
//         }

//         vector_t AC = m_C - m_A;
//         AC.normalize();
//         vector_t AB = m_B - m_A;
//         AB.normalize();
//         vector_t proj = (AC * AB) * AB;
//         proj.normalize();
//         vector_t to_C = AC - proj;
//         to_C.normalize();
//         proj = (AB * AC) * AC;
//         proj.normalize();
//         vector_t to_B = AB - proj;
//         to_B.normalize();
//         vector_t CB = m_B - m_C;
//         CB.normalize();
//         proj = ((-AC) * CB) * CB;
//         proj.normalize();
//         vector_t to_A = (-AC) - proj;
//         to_A.normalize();

//         position_t interA = ray.getPos() + tA * ray.getDirection();
//         position_t interC = ray.getPos() + tC * ray.getDirection();

//         std::cout << "interA : " << interA << "\tinterC : " << interC << "\n(interA - m_A) * to_C : " << (interA - m_A) * to_C
//                   << "\t(interA - m_A)* to_B : " << (interA - m_C) * to_B
//                   << "\t(interC - m_C)*to_A : " << (interC - m_C) * to_A << std::endl;

//         std::cout << "ray pos : " << ray.getPos() << "\tray direction : " << ray.getDirection() << std::endl;

//         if ((interA - m_A) * to_C > 0 && (interA - m_A) * to_B > 0 && (interC - m_C) * to_A > 0)
//         {
//             return tA;
//         }
//         else
//         {
//             return -1;
//         }
//     }
// }

vector_t SceneTriangle::getNormal(const position_t &pos)
{
    if (pos * m_normal > 0)
    {
        return m_normal;
    }

    return -m_normal;
}

RGBColor SceneTriangle::getColor(position_t &pos) const
{
    return m_surface->getColor(pos);
}

double SceneTriangle::intersecDist(const Ray &ray)
{
    vector_t e1 = m_B - m_A;
    vector_t e2 = m_C - m_A;
    vector_t normal = e1 ^ e2;
    double det = -(ray.getDirection() * normal);
    vector_t orig_to_pos = ray.getPos() - m_A;
    vector_t DAO = orig_to_pos ^ ray.getDirection();
    double u = (e2 * DAO) / det;
    double v = -(e1 * DAO) / det;
    double t = (DAO * normal) / det;
    if (det >= 1e-6 && t >= MIN_PROXIMITY && u >= 0.0 && v >= 0.0 && (u + v) <= 1.0)
    {
        return t;
    }
    else
    {
        return -1;
    }
}
