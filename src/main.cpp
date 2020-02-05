#include "main.hpp"

int main()
{

  std::vector<SceneBaseObject *> objects;
  SurfaceUniformedColor surface(RGB_RED);
  SceneSphere sphere(&surface, position_t(-50, 100, 0), 80);
  objects.push_back(&sphere);

  std::vector<LightSource> sources;
  // position_t src_pos(100, -10, -100);
  // LightSource source(src_pos, 1., 1.);
  sources.push_back(LightSource(position_t(100, 0, 0), 10., 10.));
  // sources.push_back(LightSource(position_t(-100, -10, 100), 1., 1.));
  // sources.push_back(LightSource(position_t(0, 0, 100), 1., 1.));
  position_t screen_pos(-15, 0, 15);
  Screen screen(300, 300, 0.1, E1, -E3, screen_pos);
  position_t observer_pos(0, -10, 0);
  RayCastingEngine casting_engine(objects, sources, screen, observer_pos);
  RayEngine *engine = &casting_engine;
  engine->compute();
  engine->get_screen().write("test.tga");

  auto screen_test = engine->get_screen();

  // int damn = -1;
  // for (unsigned i = 0; i < screen.H() * screen.W(); i++)
  // {
  //   if (screen_test(i) == screen_test(i + 1))
  //   {
  //     damn = i;
  //     break;
  //   }
  // }
  // std::cout << "damn : " << damn << std::endl;
  return 0;
}
