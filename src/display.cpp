#include <GL/glew.h>
#include <iostream>
#include "display.h"

Display::Display(int width, int height, const std::string& title) {

    this->width = width;
    this->height = height;

    SDL_Init(SDL_INIT_EVERYTHING);
    
    SDL_GL_SetSwapInterval(1);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


    this->m_window = SDL_CreateWindow(title.c_str(), 
                                SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED, 
                                width, 
                                height, 
                                SDL_WINDOW_OPENGL);

    this->m_glContext = SDL_GL_CreateContext(this->m_window);

    GLenum status = glewInit();
    if(status != GLEW_OK)
        std::cerr << "Window failed to initialize!\n";

    this->m_isClosed = false;

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    this->camera = new Camera(glm::vec3(0, -21, -28), 70.0f, (float)this->width/this->height, 0.01f, 200.0f);

}

void Display::clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {

    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

}

void Display::update(Transform &transform) {
    
    SDL_GL_SwapWindow(this->m_window);

    SDL_Event e;

    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT)
            this->m_isClosed = true;

        switch(e.type) {
            case SDL_QUIT:
                this->m_isClosed = true;
                break;
            case SDL_KEYDOWN:
                if(e.key.keysym.sym == SDLK_d) {
                    transform.getRot().y -= 0.015f;
                }
                if(e.key.keysym.sym == SDLK_a) {
                    transform.getRot().y += 0.015f;
                }
                if(e.key.keysym.sym == SDLK_w) {
                    transform.getScale() += glm::vec3(0.015f, 0.015f, 0.015f);
                }
                if(e.key.keysym.sym == SDLK_s) {
                    transform.getScale() -= glm::vec3(0.015f, 0.015f, 0.015f);
                }
        }
    }

}

bool Display::isClosed() {
    return this->m_isClosed;
}

Display::~Display() {

    SDL_GL_DeleteContext(this->m_glContext);
    SDL_DestroyWindow(this->m_window);
    SDL_Quit();

}