#include "main.hpp"

int main()
{

  std::vector<SceneBaseObject *> objects;
  SurfaceUniformedColor surf_red(RGB_RED);
  SceneSphere sphere(&surf_red, position_t(0, 50, 0), 80);
  SurfaceUniformedColor surf_green(RGB_GREEN);
  SceneSphere sphere2(&surf_green, position_t(100, 50, 0), 80);
  objects.push_back(&sphere);
  // objects.push_back(&sphere2);

  std::vector<LightSource> sources;
  // position_t src_pos(100, -10, -100);
  // LightSource source(src_pos, 1., 1.);
  sources.push_back(LightSource(position_t(100, -100, 100), 10., 10.));
  // sources.push_back(LightSource(position_t(-100, -10, 100), 10., 10.));
  // sources.push_back(LightSource(position_t(0, 0, 100), 1., 1.));
  double size_pix = 0.5;
  int nb_pix = 900;
  int size_screen = nb_pix * size_pix, top_left = size_screen / 2;
  std::cout << "size of the screen : " << size_screen << "\ttop left : " << top_left << std::endl;
  position_t screen_pos(-top_left, 0, top_left);
  Screen screen(nb_pix, nb_pix, size_pix, E1, -E3, screen_pos);
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
