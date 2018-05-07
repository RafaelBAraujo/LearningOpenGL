#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "texture.h"

class Vertex {

    public:
        Vertex(const glm::vec3 &pos, const glm::vec2 &texCoord,
                const glm::vec3 &normal = glm::vec3(0.0, 0.0, 0.0),
                const glm::vec3 &color = glm::vec3(1.0, 1.0, 1.0)) :
            pos(pos),
            texCoord(texCoord),
            normal(normal),
            color(color)
            {}

    private:
        glm::vec3 pos;
        glm::vec2 texCoord;
        glm::vec3 normal;
        glm::vec3 color;

};

class Mesh {

    public:
        Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, int i);
        Mesh(std::vector<Vertex> &data, std::vector<unsigned int> &indices, std::vector<Texture*> &textures);

        void draw();

        ~Mesh();

    private:

        enum {
            POSITION_VB,
            NUM_BUFFERS
        };

        GLuint vertexArrayObject;
        GLuint vertexArrayBuffer[NUM_BUFFERS];
        GLuint indicesBuffer;

        std::vector<Vertex> data;
        std::vector<unsigned int> indices;
        std::vector<Texture*> textures;

        unsigned int drawCount;

};

#endif