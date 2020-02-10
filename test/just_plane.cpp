#include "rayTracing.hpp"

int main(int argc, char const *argv[])
{

  // create color multi threaded logger
  auto console = spdlog::stdout_color_mt("console");
  auto err_logger = spdlog::stderr_color_mt("stderr");
  // Set the default logger to file logger
  auto file_logger = spdlog::basic_logger_mt("rayEngine", "logs/rayEngine_justplane.txt");
  // spdlog::set_level(spdlog::level::debug); // Set global log level to debug
  spdlog::set_default_logger(file_logger);
  std::stringstream ss;

  spdlog::get("console")->info("Starting the ray Tracing !");

  spdlog::get("console")->info("Creating objects...");
  std::vector<SceneBaseObject *> objects;
  SurfaceUniformedColor surf_red(RGB_RED);
  SurfaceUniformedColor surf_green(RGB_GREEN);
  SurfaceUniformedColor surf_blue(RGB_BLUE);
  SurfaceUniformedColor surf_yellow(RGB_GREEN + RGB_RED);
  ScenePlane plan(&surf_blue, position_t(0, 50, 0), E1, E3);
  ScenePlane plan_left(&surf_yellow, position_t(-250, 0, 0), E3, E2 + 0.5 * E1);
  ScenePlane plan_right(&surf_red, position_t(250, 0, 0), E2 - 0.2 * E1, -E3);
  ScenePlane plan_under(&surf_red, position_t(0, 0, -200), E1, 10 * E2 + E3);
  SceneSphere sphere(&surf_blue, position_t(0, 40, 0), 10, 0.4, 0.05);
  objects.push_back(&plan_left);
  objects.push_back(&plan_right);
  objects.push_back(&plan_under);
  objects.push_back(&sphere);

  spdlog::get("console")->info("Creating sources...");
  std::vector<LightSource> sources;
  // position_t src_pos(100, -10, -100);
  // LightSource source(src_pos, 1., 1.);
  // sources.push_back(LightSource(position_t(100, 50, 0), 10., 10.));
  // sources.push_back(LightSource(position_t(-100, -10, 100), 10., 10.));
  // sources.push_back(LightSource(position_t(0, 50, -100), 10., 10.));
  // sources.push_back(LightSource(position_t(0, 1000, 10000), 1., 1.));
  sources.push_back(LightSource(position_t(0, -1000, 100), 10., 2.));
  // sources.push_back(LightSource(position_t(0, -10, 100), 10., 2.));
  // sources.push_back(LightSource(position_t(0, -1000, 0), 10., 2.));

  position_t observer_pos(0, -1000, 0);
  // sources.push_back(LightSource(observer_pos, 10., 2.));

  double size_pix = 0.25;
  int nb_pix = 1000;
  int size_screen = nb_pix * size_pix, top_left = size_screen / 2;
  // std::cout << "size of the screen : " << size_screen << "\ttop left : " << top_left << std::endl;
  ss << "size of the screen : " << size_screen << "\ttop left : " << top_left;
  spdlog::get("console")->info(ss.str());

  position_t screen_pos(-top_left, 0, top_left);
  Screen screen(nb_pix, nb_pix, size_pix, E1, -E3, screen_pos);
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

  ss.str("");
  ss.clear();
  ss << "Wrinting image in " << filename << " done!" << std::ends;

  spdlog::get("console")->info(ss.str());

  Screen screen_test = engine->get_screen();

  return 0;
}
