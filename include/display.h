#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include "camera.h"
#include "transform.h"

class Display {

    public:
        Display(int width, int height, const std::string& title);
        void clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
        void update(Transform &transform);
        bool isClosed();

        inline int getWidth() { return this->width; }
        inline int getHeight() { return this->height; }
        inline SDL_Window* getWindow() { return this->m_window; }
        inline Camera* getCamera() { return this->camera; }

        virtual ~Display(); 

    private:
        Display(const Display& other) {}
        void operator=(const Display& other) {}

        int width;
        int height;

        Camera* camera;

        SDL_Window* m_window;
        SDL_GLContext m_glContext;
        bool m_isClosed;

};

#endif // DISPLAY_H