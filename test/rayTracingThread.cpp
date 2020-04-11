#include <rayTracing.hpp>

int main(int argc, char const *argv[])
{

  // create color multi threaded logger
  auto console = spdlog::stdout_color_mt("console");
  auto err_logger = spdlog::stderr_color_mt("stderr");

  // Set the default logger to file logger
  auto file_logger = spdlog::basic_logger_mt("thread", "logs/threads_logs.txt");
  // spdlog::set_level(spdlog::level::debug); // Set global log level to debug
  spdlog::set_pattern("[thread %t] %+");

  spdlog::get("console")
      ->info("Starting the ray Tracing !");

  spdlog::get("console")->info("Creating objects...");
  std::vector<SceneBaseObject *> objects;
  SurfaceUniformedColor surf_red(RGB_RED);
  SurfaceUniformedColor surf_green(RGB_GREEN);
  SurfaceUniformedColor surf_blue(RGB_BLUE);
  SurfaceUniformedColor surf_cyan(RGB_BLUE + RGB_GREEN);
  SurfaceUniformedColor surf_magenta(RGB_RED + RGB_BLUE);
  SurfaceUniformedColor surf_gray(RGB_SILVER_GREY);
  SurfaceUniformedColor surf_left(RGBColor(130, 7, 5));
  SurfaceUniformedColor surf_right(0.5 * RGB_GREEN + 0.2 * RGB_BLUE + 0.7 * RGB_RED);
  SurfaceUniformedColor surf_violet(RGBColor(173, 19, 143));
  SceneSphere sphere(&surf_red, position_t(50, 190, -100), 25, 0, 0.1);
  SceneSphere sphere2(&surf_green, position_t(100, 190, 0), 80, 0.5, 0.09);
  SceneSphere sphere3(&surf_blue, position_t(-100, 190, 0), 60, 0.7, 0.09);
  SceneSphere sphere4(&surf_blue, position_t(-100, 160, 100), 50, 1, 0.09);
  SceneSphere sphere5(&surf_magenta, position_t(-800, 500, 600), 50, 1, 0.09);
  ScenePlane plane(&surf_cyan, position_t(0, 300, 0), E1, E3, 0, 0.01, 0.5, 1, 100);
  ScenePlane plane_left(&surf_left, position_t(-500, 0, 0), E2 + 0.2 * E1, E3, 0, 0.1);
  ScenePlane plane_right(&surf_right, position_t(500, 0, 0), E2 - 0.2 * E1, -E3, 0, 0.1);
  ScenePlane plane_under(&surf_green, position_t(0, 0, -500), 5 * E2 + E3, E1, 0, 0.05, 0.3);
  ScenePlane plane_upper(&surf_violet, position_t(0, 0, 500), 5 * E2 - E3, E1, 0, 0.05, 0.3);
  objects.push_back(&sphere);
  objects.push_back(&sphere2);
  objects.push_back(&sphere3);
  objects.push_back(&sphere4);
  objects.push_back(&sphere5);
  // objects.push_back(&plane);
  objects.push_back(&plane_under);
  objects.push_back(&plane_left);
  objects.push_back(&plane_right);
  objects.push_back(&plane_upper);

  spdlog::get("console")->info("Creating sources...");
  std::vector<LightSource> sources;
  // position_t src_pos(100, -10, -100);
  // LightSource source(src_pos, 1., 1.);
  // sources.push_back(LightSource(position_t(100, 50, 0), 10., 10.));
  // sources.push_back(LightSource(position_t(-100, -10, 100), 10., 10.));
  // sources.push_back(LightSource(position_t(0, 50, -100), 10., 10.));
  // sources.push_back(LightSource(position_t(0, 0, 1000), 10., 10.));
  sources.push_back(LightSource(position_t(0, -1000, 0), 10., 2.));
  position_t observer_pos(0, -1000, 0);
  // sources.push_back(LightSource(observer_pos , 10., 2.));
  // sources.push_back(LightSource(observer_pos, 1., 2.));

  double size_pix = 0.25;
  int nb_pix = 2000;
  int size_screen = nb_pix * size_pix, top_left = size_screen / 2;
  // std::cout << "size of the screen : " << size_screen << "\ttop left : " << top_left << std::endl;
  position_t screen_pos(-top_left, 0, top_left);
  Screen screen(nb_pix, nb_pix, size_pix, E1, -E3, screen_pos);
  RayCastingEngine casting_engine(objects, sources, screen, observer_pos, RGB_BLACK, 1.);
  RayEngineThread thread_engine(objects, sources, screen, observer_pos, RGB_BLACK, 1.);

  RayEngine *engine = &thread_engine;

  engine->compute();

  spdlog::get("console")->info("Writing image...");

  std::string filename("test.tga");
  if (argc > 1)
  {
    filename = std::string(argv[1]);
  }

  engine->get_screen().write(filename);

  std::stringstream ss;

  ss << "Wrinting image in " << filename << " done!";

  spdlog::get("console")->info(ss.str());

  Screen screen_test = engine->get_screen();

  return 0;
}
