#include <scene_triangle.hpp>

SceneTriangle::SceneTriangle(ObjectBaseSurface *surface, position_t A,
                             position_t B, position_t C, double reflect,
                             double spec_reflect, double diff_reflect,
                             double amb_reflect, double shine)
    : SceneBaseObject(surface, reflect, spec_reflect, diff_reflect, amb_reflect,
                      shine),
      m_A(A), m_B(B), m_C(C), m_normal(((B - A) ^ (C - A)).normalize()) {}

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
//         // AC.normalize();
//         vector_t AB = m_B - m_A;
//         // AB.normalize();
//         vector_t proj_C_AB = (AC * AB) * AB;
//         // proj.normalize();
//         vector_t to_C = AC - proj;
//         // to_C.normalize();
//         vector_t proj_B_AC = (AB * AC) * AC;
//         // proj.normalize();
//         vector_t to_B = AB - proj;
//         // to_B.normalize();
//         vector_t CB = m_B - m_C;
//         // CB.normalize();
//         vector_t proj_A_CB = ((-AC) * CB) * CB;
//         // proj.normalize();
//         vector_t to_A = (-AC) - proj;
//         // to_A.normalize();

//         position_t interA = ray.getPos() + tA * ray.getDirection();
//         position_t interC = ray.getPos() + tC * ray.getDirection();

//         std::cout << "interA : " << interA << "\tinterC : " << interC <<
//         "\n(interA - m_A) * to_C : " << (interA - m_A) * to_C
//                   << "\t(interA - m_A)* to_B : " << (interA - m_C) * to_B
//                   << "\t(interC - m_C)*to_A : " << (interC - m_C) * to_A <<
//                   std::endl;

//         std::cout << "ray pos : " << ray.getPos() << "\tray direction : " <<
//         ray.getDirection() << std::endl;

//         if ((interA - proj_C_AB) * to_C > 0 && (interA - m_A) * to_B > 0 &&
//         (interC - m_C) * to_A > 0)
//         {
//             return tA;
//         }
//         else
//         {
//             return -1;
//         }
//     }
// }

vector_t SceneTriangle::getNormal(const position_t &pos) {
  // if (pos * m_normal < 0) {
  //   return m_normal;
  // }

  // return -m_normal;
  return m_normal;
}

RGBColor SceneTriangle::getColor(position_t &pos) const {
  return m_surface->getColor(pos);
}

// double SceneTriangle::intersecDist(const Ray &ray) {
//   vector_t e1 = m_B - m_A;
//   e1.normalize();
//   vector_t e2 = m_C - m_A;
//   e2.normalize();
//   vector_t normal = e1 ^ e2;
//   normal.normalize();
//   double det = -(ray.getDirection() * normal);
//   vector_t orig_to_pos = ray.getPos() - m_A;
//   orig_to_pos.normalize();
//   vector_t DAO = orig_to_pos ^ ray.getDirection();
//   DAO.normalize();
//   double u = (e2 * DAO) / det;
//   double v = -(e1 * DAO) / det;
//   double t = (DAO * normal) / det;
//   // std::cout << "det : " << det << "\tt : " << t << "\tu: " << u << "\tv :
//   " << v
//   //           << std::endl;
//   if (det >= 1e-6 && t >= MIN_PROXIMITY && u >= 0.0 && v >= 0.0 &&
//       (u + v) <= 1.0) {
//     return t;
//   } else {
//     return -1;
//   }
// }

// double SceneTriangle::intersecDist(const Ray &ray) {
//   position_t pos = ray.getPos();
//   vector_t dir = ray.getDirection();
//   vector_t normal = m_normal;

//   if (dir * normal == 0) {
//     position_t C = (m_A + m_B + m_C) / 3;
//     double p = ((C - pos) * normal) / (dir * normal);
//     position_t inter = pos + p * dir;
//     double a, b, c;
//     a = ((m_B - m_A) ^ (inter - m_A)) * ((inter - m_B) ^ (m_C - m_A));
//     b = ((m_A - m_B) ^ (inter - m_B)) * ((inter - m_B) ^ (m_C - m_B));
//     c = ((m_A - m_C) ^ (inter - m_C)) * ((inter - m_C) ^ (m_B - m_C));
//     if (a >= 0 && b >= 0 && c >= 0) {
//       return p;
//     } else {
//       return -1;
//     }
//   } else {
//     return -1;
//   }
// }

/**
 * Intesection function using Möller–Trumbore algorithm
 *
 * @param ray
 *
 * @return
 */
double SceneTriangle::intersecDist(const Ray &ray) {

  position_t ray_origin = ray.getPos();
  vector_t ray_vector = ray.getDirection();
  vector_t edge1 = m_B - m_A, edge2 = m_C - m_A, tvec, pvec, qvec;
  double det, inv_det, t, u, v;

  pvec = ray_vector ^ edge2;
  det = edge1 * pvec;

  if (det > -MIN_PROXIMITY && det < MIN_PROXIMITY) {
    return -1;
  }

  inv_det = 1.0 / det;
  tvec = ray_origin - m_A;
  u = (tvec * pvec) * inv_det;

  if (u < 0.0 || u > 1.0) {
    return -1;
  }

  qvec = tvec ^ edge1;

  v = (ray_vector * qvec) * inv_det;

  if (v < -MIN_PROXIMITY || u + v > 1.0) {
    return -1;
  }
  t = (edge2 * qvec) * inv_det;

  if (t < MIN_PROXIMITY) {
    return -1;
  }

  return t;
}

// double SceneTriangle::intersecDist(const Ray &ray) {
//   position_t ray_origin = ray.getPos();
//   vector_t ray_vector = ray.getDirection();
//   vector_t edge1 = m_B - m_A, edge2 = m_C - m_A, tvec, pvec, qvec;
//   double det, u, v,t;
//   pvec = ray_vector ^ edge2;
//   det = edge1 * pvec;
//   if ( det < MIN_PROXIMITY )
//   {
//     return -1;
//   }

//   tvec = ray_origin - m_A;

//   u = tvec * pvec;
//   if( u < 0.0 || u > det )
//   {
//     return -1;
//   }

//   qvec = tvec ^ edge1;
//   v = ray_vector * qvec;
//   if ( v < 0.0 || u+v > det ){
//     return -1;
//   }
//   t = edge2 * qvec;
//   t /=det;
//   return t;
// }
