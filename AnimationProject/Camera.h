#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
private:

    float pitch, yaw;
    float targPitch, targYaw;
    glm::vec3 fwd;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 pos;
    float speed = 5.0f;
    float smooth = 0.35f;
    float rotationSpeed = 0.5f;

public:
    Camera();
    Camera(glm::vec3 pos);
    void updateView();
    void smoothUpdateView();
    void translateFwd(float inc);
    void translateRight(float inc);
    void rotateYaw(float inc);
    void rotatePitch(float inc);
    void smoothRotateYaw(float inc);
    void smoothRotatePitch(float inc);
    void setPitchAndYaw(float pitch, float yaw);
    void setPosition(const glm::vec3& pos);
    const glm::mat4& getView();
    const glm::vec3& getFwd();
    const glm::vec3& getRight();
    const glm::vec3& getUp();
    const glm::vec3& getPosition();
    glm::mat4 view;
};

#endif // CAMERA_H
