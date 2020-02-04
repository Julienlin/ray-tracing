#include "main.hpp"

int main() {

  std::vector<SceneBaseObject *> objects;
  SurfaceUniformedColor surface(RGB_WHITE);
    SceneSphere sphere(&surface, position_t(0, 100, 0),
    50);
  objects.push_back(&sphere);

  std::vector<LightSource> sources;
  position_t src_pos(0, 0, 1000);
  LightSource source(src_pos, 1., 1.);
  sources.push_back(source);
  position_t screen_pos(-100, 0, 100);
  Screen screen(100, 100, 1, E1, E3, screen_pos);
  position_t observer_pos(0, -100, 0);
  RayCastingEngine casting_engine(objects, sources, screen, observer_pos);
  RayEngine *engine = &casting_engine;
  engine->compute();
  engine->get_screen().write("test.tga");
  return 0;
}
