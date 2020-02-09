#include<scene_triangle.hpp>

SceneTriangle::SceneTriangle(ObjectBaseSurface *surface, position_t A,position_t B, position_t C, double reflect , double spec_reflect , double diff_reflect , double amb_reflect , double shine ) : SceneBaseObject(surface, reflect,spec_reflect,diff_reflect,amb_reflect,shine), m_A(A), m_B(B), m_C(C), m_normal((B-A)^(C-A)){}


     double SceneTriangle::intersecDist(const Ray &ray){
         if (ray.getDirection() * m_normal == 0)
         {
             if ((ray.getPos() - m_A) * m_normal == 0)
             {
                 return 0;
             }
             return -1;
         }
         else
         {
            auto direction = -ray.getDirection();
            double d = m_normal * direction;
            double t = (m_normal * (ray.getPos()-m_A)) / d;
            if (t < MIN_PROXIMITY)
            {
                return -1;
            }

            vector_t AC= m_C-m_A;
            AC.normalize();
            vector_t AB = m_B-m_A;
            AB.normalize();
            vector_t proj = (AC*AB)*AB;
            vector_t to_C = AC-proj;
            to_C.normalize();
            proj = (AB*AC)*AC;
            vector_t to_B = AB-proj;
            to_B.normalize();
            vector_t CB = m_B - m_C;
            proj=((-AC) *CB)*CB;
            vector_t to_A = -AC - proj;
            to_A.normalize();

            position_t inter = ray.getPos() + t * ray.getDirection();

            if ((inter - m_A) * to_C >0 && (inter - m_A)* to_B > 0 && (inter - m_C)*to_A >0 )
            {
                return t;
            }
            else
            {
                return -1;
            }

         }


     }


vector_t SceneTriangle::getNormal(const position_t &pos){
    if (pos * m_normal > 0)
    {
        return m_normal;
    }

    return -m_normal;
}

RGBColor SceneTriangle::getColor(position_t &pos) const{
    return m_surface->getColor(pos);
}
