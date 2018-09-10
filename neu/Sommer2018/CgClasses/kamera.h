#ifndef KAMERA_H
#define KAMERA_H

#include "glm/glm.hpp"
#include "vector"
class Camera
{
private:
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;
    glm::vec3 u;
    glm::vec3 v;
    glm::vec3 w;
    glm::mat4 projectionMatParallel;
    glm::mat4 projektionMatCentral;
    glm::mat4 lookAt;
    float x;
    float y;
    float z;
    float rotation;

    float r;
    float l;
    float b;
    float t;
    float f;
    float n;

    glm::vec2 window;
public:
    Camera();
    void renew();
    void reset();
    glm::mat4 constructLookAt();
    glm::vec3 getEye() const;
    void setEye(const glm::vec3 &value);
    glm::vec3 getCenter() const;
    void setCenter(const glm::vec3 &value);
    glm::vec3 getUp() const;
    void setUp(const glm::vec3 &value);
    glm::mat4 getProjectionMatParallel() const;
    void setProjectionMatParallel(const glm::mat4 &value);
    glm::mat4 getLookAt() const;
    void setLookAt(const glm::mat4 &value);
    void moveCamW();
    void moveCamA();
    void moveCamS();
    void moveCamD();
    void moveCamUpY();
    void moveCamDownX();
    void RotateCamLeft();
    void RotateCamRight();

    glm::mat4 getProjectionMatCentral() const;
    void setProjectionMatCentral(const glm::mat4 &value);
    glm::vec2 getWindow() const;
    void setWindow(const glm::vec2 &value);
    float getX() const;
    void setX(float value);
    float getY() const;
    void setY(float value);
    float getZ() const;
    void setZ(float value);
    float getR() const;
    void setR(float value);
    float getL() const;
    void setL(float value);
    float getB() const;
    void setB(float value);
    float getT() const;
    void setT(float value);
    float getF() const;
    void setF(float value);
    float getN() const;
    void setN(float value);
};
#endif
