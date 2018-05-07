#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include "transform.h"
#include "camera.h"

class Shader {

    public:
        Shader(const std::string &filename);

        void bind();
        void update(const Transform &transform, const Camera &camera);

        ~Shader();

    private:
        GLuint program;

        enum {
            VERTEX_SHADER,
            FRAGMENT_SHADER,
            NUM_SHADERS
        };

        enum {
            TRANSFORM_U,
            VIEWPROJECTION_U,
            NUM_UNIFORMS
        };

        GLuint shaders[NUM_SHADERS];
        GLuint uniforms[NUM_UNIFORMS];

};

#endif // SHADER_H