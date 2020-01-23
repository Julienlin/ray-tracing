#ifndef __SCENE_CUBE_H_
#define __SCENE_CUBE_H_

#include "scene_base_object.hpp"

using cubeVertex_t = std::tuple<double,double,double,double,double,double,double,double,double>;

class SceneCube : public SceneBaseObject {
    private:
        cubeVertex_t m_vertexes;

    public:
        SceneCube(cubeVertex_t vertexes): m_vertexes(vertexes){}
        SceneCube( const SceneCube& cube ) = default;
        SceneCube( SceneCube&& cube ) = default;
        ~SceneCube() {}

};

#endif // __SCENE_CUBE_H_
