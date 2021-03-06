#include "rayTracing.hpp"

int main(int argc, char const *argv[])
{

  // create color multi threaded logger
  auto console = spdlog::stdout_color_mt("console");
  auto err_logger = spdlog::stderr_color_mt("stderr");
  auto file_logger = spdlog::basic_logger_mt("rayEngine", "logs/rayEngine_justplane.txt");
  spdlog::get("console")->info("Starting the ray Tracing !");

  spdlog::get("console")->info("Creating objects...");
  std::vector<SceneBaseObject *> objects;
  SurfaceUniformedColor surf_red(RGB_RED);
  SurfaceUniformedColor surf_green(RGB_GREEN);
  SurfaceUniformedColor surf_blue(RGB_BLUE);
  SurfaceUniformedColor surf_yellow(RGB_GREEN + RGB_RED);
  ScenePlane plan(&surf_yellow, position_t(0, 190, -1000), E1, 10 * E2 + E3, 0, 0.05, 0.5, 1., 100);
  SceneSphere sphere(&surf_red, position_t(50, 190, -100), 25, 0.7, 0.05);
  SceneSphere sphere2(&surf_green, position_t(100, 190, 0), 80, 0, 0.05);
  SceneSphere sphere3(&surf_blue, position_t(-100, 190, 0), 60, 0, 0.05);
  SceneSphere sphere4(&surf_blue, position_t(-100, 160, 100), 50, 0, 0.05);
  objects.push_back(&sphere);
  objects.push_back(&sphere2);
  objects.push_back(&sphere3);
  objects.push_back(&sphere4);

  objects.push_back(&plan);

  spdlog::get("console")->info("Creating sources...");
  std::vector<LightSource> sources;

  sources.push_back(LightSource(position_t(0, 100, 1000), 10., 1.));
  // sources.push_back(LightSource(position_t(0, 0, -1000), 10., 2.));
  // sources.push_back(LightSource(position_t(0, -10, 100), 10., 2.));

  double size_pix = 0.25;
  int nb_pix = 1000;
  int size_screen = nb_pix * size_pix, top_left = size_screen / 2;
  position_t screen_pos(-top_left, 0, top_left);
  Screen screen(nb_pix, nb_pix, size_pix, E1, -E3, screen_pos);
  position_t observer_pos(0, -1000, 0);
  RayCastingEngine casting_engine(objects, sources, screen, observer_pos);
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

  return 0;
}
