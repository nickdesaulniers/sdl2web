#include <iostream>
#include <SDL.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#elif __EMSCRIPTEN__
#include <GLES2/gl2.h>
#include "emscripten.h"
#else
#include <Gl/gl.h>
#endif


GLuint load_shader (GLenum type, const char* shader_src) {
  auto shader = glCreateShader(type);
  GLint compiled;

  if (shader == 0) {
    return 0;
  }

  glShaderSource(shader, 1, &shader_src, nullptr);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

  if (!compiled) {
    GLint info_length = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_length);
    if (info_length > 1) {
      auto info_log = static_cast<char*>(malloc(sizeof(char) * info_length));
      glGetShaderInfoLog(shader, info_length, nullptr, info_log);
      std::cerr << "Error compiling shader:\n" << shader_src << "\n" <<
        info_log << std::endl;
      free(info_log);
    }
  }

  return shader;
}

GLuint load_program () {
  const char* vShaderStr =
    "attribute vec4 aPosition;\n"
    "void main () {\n"
    "  gl_Position = aPosition;\n"
    "}";
  const char* fShaderStr =
#ifdef __EMSCRIPTEN__
    "precision mediump float;\n"
#endif
    "void main () {\n"
    "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}";
  // TODO: error handling
  GLuint vertexShader = load_shader(GL_VERTEX_SHADER, vShaderStr);
  GLuint fragmentShader = load_shader(GL_FRAGMENT_SHADER, fShaderStr);
  GLuint program = glCreateProgram();
  if (program == 0) {
    return 0;
  }

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  glBindAttribLocation(program, 0, "aPosition");
  glLinkProgram(program);

  GLint linked;
  glGetProgramiv(program, GL_LINK_STATUS, &linked);
  if (!linked) {
    GLint info_length = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_length);
    if (info_length > 1) {
      auto info_log = static_cast<char*>(malloc(sizeof(char*) * info_length));
      glGetProgramInfoLog(program, info_length, nullptr, info_log);
      std::cerr << "Error linking program: " << info_log << std::endl;
      free(info_log);
    }
    glDeleteProgram(program);
    return GL_FALSE;
  }
  glUseProgram(program);
  glViewport(0, 0, 640, 480);

  return GL_TRUE;
}

void load_buffers () {
  GLfloat vertices [] = {
     0.0f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
  };

  GLuint vertexPosObj;
  glGenBuffers(1, &vertexPosObj);
  glBindBuffer(GL_ARRAY_BUFFER, vertexPosObj);
  glBufferData(GL_ARRAY_BUFFER, 9 * 4, vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
}

void draw () {
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void loop () {
  draw();
}

int main () {
  std::cout << "hello world\n";

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
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

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  auto gl = SDL_GL_CreateContext(win);
  if (gl == nullptr) {
    SDL_DestroyWindow(win);
    std::cout << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_GL_SetSwapInterval(1);

  // TODO: Error handling
  load_program();
  load_buffers();

  glClearColor ( 0.0, 1.0, 0.0, 1.0 );

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop, 0, 0);
#else
  bool run = true;
  SDL_Event e;
  while (run) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        run = false;
      }
    }
    loop();
    SDL_GL_SwapWindow(win);
  }
#endif

  /* Delete our opengl context, destroy our window, and shutdown SDL */
  SDL_GL_DeleteContext(gl);
  SDL_DestroyWindow(win);
  SDL_Quit();
}

