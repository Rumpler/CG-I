#include "kamera.h"
#include <iostream>

glm::vec3 Camera::getEye() const
{
    return eye;
}

void Camera::setEye(const glm::vec3 &value)
{
    eye = value;
}

glm::vec3 Camera::getCenter() const
{
    return center;
}

void Camera::setCenter(const glm::vec3 &value)
{
    center = value;
}

glm::vec3 Camera::getUp() const
{
    return up;
}

void Camera::setUp(const glm::vec3 &value)
{
    up = value;
}

glm::mat4 Camera::getProjectionMatParallel() const
{
    return projectionMatParallel;
}

void Camera::setProjectionMatParallel(const glm::mat4 &value)
{
    projectionMatParallel = value;
}

glm::mat4 Camera::getLookAt() const
{
    return lookAt;
}

void Camera::setLookAt(const glm::mat4 &value)
{
    lookAt = value;
}

glm::mat4 Camera::getProjectionMatCentral() const
{
    return projektionMatCentral;
}

void Camera::setProjectionMatCentral(const glm::mat4 &value)
{
    projektionMatCentral = value;
}

glm::vec2 Camera::getWindow() const
{
    return window;
}

void Camera::setWindow(const glm::vec2 &value)
{
    window = value;
}

float Camera::getX() const
{
    return x;
}

void Camera::setX(float value)
{
    x = value;
}

float Camera::getY() const
{
    return y;
}

void Camera::setY(float value)
{
    y = value;
}

float Camera::getZ() const
{
    return z;
}

void Camera::setZ(float value)
{
    z = value;
}

float Camera::getR() const
{
    return r;
}

void Camera::setR(float value)
{
    r = value;
}

float Camera::getL() const
{
    return l;
}

void Camera::setL(float value)
{
    l = value;
}

float Camera::getB() const
{
    return b;
}

void Camera::setB(float value)
{
    b = value;
}

float Camera::getT() const
{
    return t;
}

void Camera::setT(float value)
{
    t = value;
}

float Camera::getF() const
{
    return f;
}

void Camera::setF(float value)
{
    f = value;
}

float Camera::getN() const
{
    return n;
}

void Camera::setN(float value)
{
    n = value;
}

void Camera::renew(){

    //--------------------------------------------------
    //paralelprojektion? matrix, normalized device coordinates ?
    projectionMatParallel = glm::mat4(glm::vec4(2/(r-l),0,0,-((r+l)/(r-l))),
                                  glm::vec4(0,2/(t-b),0,-((t+b)/(t-b))),
                                  glm::vec4(0,0,-2/(f-n),-((f+n)/(f-n))),
                                  glm::vec4(0,0,0,1));
    projektionMatCentral = glm::mat4(glm::vec4((2*n)/(r-l),0,(r+l)/(r-l),0),
                                          glm::vec4(0,(2*n)/(t-b),(t+b)/(t-b),0),
                                          glm::vec4(0,0,-((f+n)/(f-n)),-((2*f*n)/(f-n))),
                                          glm::vec4(0,0,-1,0));
    //--------------------------------------------------

}

Camera::Camera()
{
    x = 0;
    y = 0;
    z = -1.0;
    rotation = 0;
    r = 5;
    l = -5;
    t = 5;
    b = -5;
    n = 5;
    f = -5;
    setWindow(glm::vec2(400,400));
    //--------------------------------------------------
    //paralelprojektion? matrix, normalized device coordinates ?
    projectionMatParallel = glm::mat4(glm::vec4(2/(r-l),0,0,-((r+l)/(r-l))),
                                  glm::vec4(0,2/(t-b),0,-((t+b)/(t-b))),
                                  glm::vec4(0,0,-2/(f-n),-((f+n)/(f-n))),
                                  glm::vec4(0,0,0,1));
    projektionMatCentral = glm::mat4(glm::vec4((2*n)/(r-l),0,(r+l)/(r-l),0),
                                          glm::vec4(0,(2*n)/(t-b),(t+b)/(t-b),0),
                                          glm::vec4(0,0,-((f+n)/(f-n)),-((2*f*n)/(f-n))),
                                          glm::vec4(0,0,-1,0));
    //--------------------------------------------------

    eye = glm::vec3(0,0,1.0);
    center = glm::vec3(0,0,0);
    up = glm::vec3(0,1.0,0);

    w = (center - eye);
    w = glm::normalize(w);

    v = up;
    v = glm::normalize(v);

    u = glm::cross(v,w);

    v = glm::cross(w,u);
    u = glm::normalize(u);
    v = glm::normalize(v);

lookAt = constructLookAt();

}

void Camera::reset()
{
    x = 0;
    y = 0;
    z = -1;
    rotation = -3.13;
    eye = glm::vec3(0,0,1.0);
    center = glm::vec3(0,0,0);
    up = glm::vec3(0,1.0,0);

    w = (center - eye);
    w = glm::normalize(w);

    v = up;
    v = glm::normalize(v);

    u = glm::cross(v,w);

    v = glm::cross(w,u);
    u = glm::normalize(u);
    v = glm::normalize(v);

lookAt = constructLookAt();

}

glm::mat4 Camera::constructLookAt(){
    glm::mat4 temp = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                               glm::vec4(v.x,v.y,v.z,0),
                               glm::vec4(w.x,w.y,w.z,0),
                               glm::vec4(x,y,z,1));
    std::cout<<"const look at "<< w.x<<w.y<<w.z<<std::endl;
    return temp;
}

void Camera::moveCamW(){
    z = z +0.1;
    lookAt = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                       glm::vec4(v.x,v.y,v.z,0),
                       glm::vec4(w.x,w.y,w.z,0),
                       glm::vec4(x,y,z,1));
}

void Camera::moveCamA()
{
    x = x -0.1;
    lookAt = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                       glm::vec4(v.x,v.y,v.z,0),
                       glm::vec4(w.x,w.y,w.z,0),
                       glm::vec4(x,y,z,1));
}

void Camera::moveCamS()
{
    z = z -0.1;
    lookAt = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                       glm::vec4(v.x,v.y,v.z,0),
                       glm::vec4(w.x,w.y,w.z,0),
                       glm::vec4(x,y,z,1));
}

void Camera::moveCamD()
{
    x = x +0.1;
    lookAt = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                       glm::vec4(v.x,v.y,v.z,0),
                       glm::vec4(w.x,w.y,w.z,0),
                       glm::vec4(x,y,z,1));
}

void Camera::moveCamUpY()
{
    y = y +0.1;
    lookAt = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                       glm::vec4(v.x,v.y,v.z,0),
                       glm::vec4(w.x,w.y,w.z,0),
                       glm::vec4(x,y,z,1));
}

void Camera::moveCamDownX()
{
    y = y -0.1;
    lookAt = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                       glm::vec4(v.x,v.y,v.z,0),
                       glm::vec4(w.x,w.y,w.z,0),
                       glm::vec4(x,y,z,1));
}
/**
 *
 *
 *
**/
void Camera::RotateCamLeft()
{
    rotation = rotation - 1;
    eye = glm::vec3(0,0,0);
       center = glm::vec3(glm::cos(glm::radians(rotation)),0,glm::sin(glm::radians(rotation)));
    up = glm::vec3(0,1.0,0);

    w = (center -eye);
    w = glm::normalize(w);

    v = up;
    v = glm::normalize(v);

    u = glm::cross(v,w);

    v = glm::cross(w,u);
    u = glm::normalize(u);
    v = glm::normalize(v);

    lookAt = constructLookAt();
}

void Camera::RotateCamRight()
{
    rotation = rotation + 1;
    eye = glm::vec3(0,0,0);
    center = glm::vec3(glm::cos(glm::radians(rotation)),0,glm::sin(glm::radians(rotation)));
    up = glm::vec3(0,1.0,0);

    w = (center -eye);
    w = glm::normalize(w);

    v = up;
    v = glm::normalize(v);

    u = glm::cross(v,w);

    v = glm::cross(w,u);
    u = glm::normalize(u);
    v = glm::normalize(v);

    lookAt = constructLookAt();
}

// rotation der Kamera um ein punkt, mit blick auf diesen punkt
//    rotation = rotation - 0.02;

//    eye = glm::vec3(0,0,1.0);
//    center = glm::vec3(glm::sin(rotation),0,glm::cos(rotation));
//    up = glm::vec3(0,1.0,0);

//    w = (center - eye);
//    w = glm::normalize(w);

//    v = up;
//    v = glm::normalize(v);

//u = glm::cross(v,w);

//v = glm::cross(w,u);
//u = glm::normalize(u);
//v = glm::normalize(v);

//lookAt = constructLookAt();
