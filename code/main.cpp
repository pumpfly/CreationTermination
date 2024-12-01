
#include <iostream>
#include <Window.h>

int main() {
  try {
  brew::Window win = brew::Window(800, 600, "Hello World");
  brew::Color color = brew::Color(200, 255, 150, 255);
  brew::Color recColor = brew::Color(100, 200, 50, 255);


    while(!win.ShouldClose()) {
      win.BeginDrawing();
      win.ClearBackground(color);

      win.DrawRectangle(0, 0, 800, 600, recColor);
      if(win.IsKeyPressed(brew::Window::KEY_SPACE)) {
        std::cout << "pressed space" << std::endl;
      }
      if(win.IsKeyDown(brew::Window::KEY_SPACE)) {
        std::cout << "hold space" << std::endl;
      }
      if(win.IsKeyReleased(brew::Window::KEY_SPACE)) {
        std::cout << "released space" << std::endl;
      }

      win.EndDrawing();
    }
  } catch (const std::exception& e) {
    std::cout << "Exception " << e.what() << std::endl;
  }
  return 0;
}
