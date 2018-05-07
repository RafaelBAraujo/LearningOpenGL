#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "meshloader.h"

#include <SDL2/SDL.h>

#define FPS_INTERVAL 1.0 //seconds.

Uint32 fps_lasttime = SDL_GetTicks(); //the last recorded time.
Uint32 fps_current; //the current FPS.
Uint32 fps_frames = 0; //frames passed since the last recorded fps.

int main(int argc, char* argv[]) {

  Display display(800, 600, "Portal de Americana");

  
  MeshLoader *ml = new MeshLoader();
  std::vector<Mesh*> meshes = ml->loadMeshes("./res/obj/Americana/americana.obj");
  Shader shader("./res/shaders/basicShader");
  Transform transform;
  float counter = 0;

  while(!display.isClosed()){

      display.clear(0.0f, 0.15f, 0.3f, 1.0f);

      shader.update(transform, *display.getCamera());
      for(int i = 0; i < meshes.size(); i ++)
        meshes[i]->draw();

      shader.bind();

      display.update(transform);

      fps_frames++;
      if (fps_lasttime < SDL_GetTicks() - FPS_INTERVAL*1000)
      {
          fps_lasttime = SDL_GetTicks();
          fps_current = fps_frames;
          fps_frames = 0;
      }

      //std::cout << fps_current << "FPS\n";

  }

  return 0;
}