#include <iostream>
#include <SDL.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <Gl/gl.h>
#endif

int main () {
  std::cout << "hello world\n";

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  auto win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (win == nullptr) {
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  auto ren = SDL_CreateRenderer(win, -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == nullptr) {
    SDL_DestroyWindow(win);
    std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  auto imagePath = std::string { "../hello.bmp" };
  auto bmp = SDL_LoadBMP(imagePath.c_str());
  if (bmp == nullptr) {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  auto tex = SDL_CreateTextureFromSurface(ren, bmp);
  SDL_FreeSurface(bmp);
  if (tex == nullptr) {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() <<
      std::endl;
    SDL_Quit();
    return 1;
  }

  auto gl = SDL_GL_CreateContext(win);
  if (gl == nullptr) {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    std::cout << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_GL_SetSwapInterval(1);
  glClearColor ( 1.0, 0.0, 0.0, 1.0 );
  glClear ( GL_COLOR_BUFFER_BIT );
  SDL_GL_SwapWindow(win);
  SDL_Delay(2000);

  /* Same as above, but green */
  glClearColor ( 0.0, 1.0, 0.0, 1.0 );
  glClear ( GL_COLOR_BUFFER_BIT );
  SDL_GL_SwapWindow(win);
  SDL_Delay(2000);

  /* Same as above, but blue */
  glClearColor ( 0.0, 0.0, 1.0, 1.0 );
  glClear ( GL_COLOR_BUFFER_BIT );
  SDL_GL_SwapWindow(win);
  SDL_Delay(2000);

  /* Delete our opengl context, destroy our window, and shutdown SDL */
  SDL_GL_DeleteContext(gl);

  //SDL_RenderClear(ren);
  //SDL_RenderCopy(ren, tex, nullptr, nullptr);
  //SDL_RenderPresent(ren);

  //SDL_Delay(2000);

  SDL_DestroyTexture(tex);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
}

