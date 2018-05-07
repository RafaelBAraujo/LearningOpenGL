#include "mesh.h"
#include <iostream>

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, int i) {

    this->drawCount = indices.size();

    glGenVertexArrays(1, &this->vertexArrayObject);
    glBindVertexArray(this->vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, this->vertexArrayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexArrayBuffer[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GL_FLOAT)));

    glGenBuffers(1, &this->indicesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indicesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->drawCount * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);

}

Mesh::Mesh(std::vector<Vertex> &data, std::vector<unsigned int> &indices, std::vector<Texture*> &textures) {

    this->data = data;
    this->indices = indices;
    this->textures = textures;

    glGenVertexArrays(1, &this->vertexArrayObject);
    glBindVertexArray(this->vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, this->vertexArrayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexArrayBuffer[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, this->data.size() * sizeof(Vertex), &this->data[0], GL_STATIC_DRAW);

    glGenBuffers(1, &this->indicesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indicesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(this->indices[0]), &this->indices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &this->vertexArrayObject);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &this->vertexArrayBuffer[POSITION_VB]);
    glDeleteBuffers(1, &this->indicesBuffer);
}

void Mesh::draw() {

    if(this->data.empty()) {

        glBindVertexArray(this->vertexArrayObject);

        //glDrawArrays(GL_TRIANGLES, 0, this->drawCount);
        glDrawElements(GL_TRIANGLES, this->drawCount, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

    }

    else {

        for(int i = 0; i < this->textures.size(); i++) {
            this->textures[i]->bind(i);
        }

        glBindVertexArray(this->vertexArrayObject);

        glBindBuffer(GL_ARRAY_BUFFER, this->vertexArrayBuffer[POSITION_VB]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indicesBuffer);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GL_FLOAT)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5 * sizeof(GL_FLOAT)));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GL_FLOAT)));

        glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

    }


}