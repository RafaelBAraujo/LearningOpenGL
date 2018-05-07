#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {

    public:
        Camera(const glm::vec3 &pos, float fov, float aspect, float zNear, float zFar) {
            this->perspective = glm::perspective(fov, aspect, zNear, zFar);
            this->position = pos;
            this->forward = glm::vec3(0, 0, 1);
            this->up = glm::vec3(0, 1, 0);
        }

        inline glm::mat4 getViewProjection() const {
            return (this->perspective * glm::lookAt(this->position, this->position + this->forward, this->up));
        }

        inline void setPosition(const glm::vec3 &position) {
            this->position = position;
        }

        inline void setForward(const glm::vec3 &forward) {
            this->forward = forward;
        }

        inline glm::vec3 getPosition() { return this->position; }
        inline glm::vec3 getForward() { return this->forward; }

    private:
        glm::mat4 perspective;
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 up;
};

#endif // CAMERA_H