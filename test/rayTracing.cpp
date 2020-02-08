#include "rayTracing.hpp"

int main(int argc, char const *argv[])
{

  // create color multi threaded logger
  auto console = spdlog::stdout_color_mt("console");
  auto err_logger = spdlog::stderr_color_mt("stderr");
  spdlog::get("console")->info("Starting the ray Tracing !");

  spdlog::get("console")->info("Creating objects...");
  std::vector<SceneBaseObject *> objects;
  SurfaceUniformedColor surf_red(RGB_RED);
  SurfaceUniformedColor surf_green(RGB_GREEN);
  SurfaceUniformedColor surf_blue(RGB_BLUE);
  SurfaceUniformedColor surf_cyan(RGB_BLUE + RGB_GREEN);
  SceneSphere sphere(&surf_red, position_t(50, 190, -100), 25);
  SceneSphere sphere2(&surf_green, position_t(100, 190, 0), 80);
  SceneSphere sphere3(&surf_blue, position_t(-100, 190, 0), 60);
  SceneSphere sphere4(&surf_blue, position_t(-100, 160, 100), 50);
  ScenePlane plane(&surf_cyan, position_t(0, 300, 0), E1, E3 + 10 * E2);
  objects.push_back(&sphere);
  objects.push_back(&sphere2);
  objects.push_back(&sphere3);
  objects.push_back(&sphere4);
  objects.push_back(&plane);

  spdlog::get("console")->info("Creating sources...");
  std::vector<LightSource> sources;
  // position_t src_pos(100, -10, -100);
  // LightSource source(src_pos, 1., 1.);
  // sources.push_back(LightSource(position_t(100, 50, 0), 10., 10.));
  // sources.push_back(LightSource(position_t(-100, -10, 100), 10., 10.));
  // sources.push_back(LightSource(position_t(0, 50, -100), 10., 10.));
  sources.push_back(LightSource(position_t(0, 0, 1000), 10., 10.));
  sources.push_back(LightSource(position_t(0, 0, -1000), 10., 2.));
  position_t observer_pos(0, -1000, 0);
  // sources.push_back(LightSource(observer_pos, 1., 2.));

  double size_pix = 0.25;
  int nb_pix = 1000;
  int size_screen = nb_pix * size_pix, top_left = size_screen / 2;
  // std::cout << "size of the screen : " << size_screen << "\ttop left : " << top_left << std::endl;
  position_t screen_pos(-top_left, 0, top_left);
  Screen screen(nb_pix, nb_pix, size_pix, E1, -E3, screen_pos);
  RayCastingEngine casting_engine(objects, sources, screen, observer_pos, RGB_BLACK, 1.);
  RayEngine *engine = &casting_engine;

  engine->compute();

  spdlog::get("console")->info("Writing image...");

  std::string filename("test.tga");
  if (argc > 1)
  {
    filename = std::string(argv[1]);
  }

  engine->get_screen().write(filename);

  std::stringstream ss;

  ss << "Wrinting image in " << filename << " done!" << std::ends;

  spdlog::get("console")->info(ss.str());

  Screen screen_test = engine->get_screen();

  // std::cout << "screen_test.H() * screen_test.W() : " << screen_test.H() * screen_test.W() << std::endl;
  // std::cout << "screen.H() * screen.W() : " << screen.H() * screen.W() << std::endl;

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
