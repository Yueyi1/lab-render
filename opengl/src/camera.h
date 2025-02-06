#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
private:
    glm::vec3 mPosition;
    glm::vec3 mFront;
    glm::vec3 mUp;
    glm::vec3 mRight;
    glm::vec3 mWorldUp;
    float mYaw;
    float mPitch;

    void updateCameraVectors();

public:
    Camera(const glm::vec3 &position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3 &up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = -90.0f, float pitch = 0.0f)
        : mPosition(position), mWorldUp(up), mYaw(yaw), mPitch(pitch)
    {
        updateCameraVectors();
    }
    ~Camera(){};
    glm::mat4 getViewMatrix() const;
    void moveForward(float distance);
    void moveBackward(float distance);
    void moveLeft(float distance);
    void moveRight(float distance);
    void rotate(float xoffset, float yoffset, float sensitivity = 0.1f);
};

#endif // CAMERA_H