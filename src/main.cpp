#include <core/application.hpp>

int main(int argc, const char* argv[]) {
  try {
    Application app;
    app.run();
  } catch (const std::exception& e) {
    std::cerr << "Fatal error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}