#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y = sin(glm::radians(mPitch));
    front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mFront  = glm::normalize(front);

    mRight = glm::normalize(glm::cross(mFront, mWorldUp));
    mUp    = glm::normalize(glm::cross(mRight, mFront));
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

void Camera::moveForward(float distance)
{
    mPosition += mFront * distance;
}

void Camera::moveBackward(float distance)
{
    mPosition -= mFront * distance;
}

void Camera::moveLeft(float distance)
{
    mPosition -= mRight * distance;
}

void Camera::moveRight(float distance)
{
    mPosition += mRight * distance;
}

void Camera::rotate(float xoffset, float yoffset, float sensitivity = 0.1f)
{
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    mYaw += xoffset;
    mPitch += yoffset;

    if (mPitch > 89.0f)
    {
        mPitch = 89.0f;
    }
    else if (mPitch < -89.0f)
    {
        mPitch = -89.0f;
    }

    updateCameraVectors();
}