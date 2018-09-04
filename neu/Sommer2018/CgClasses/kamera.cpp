#include "kamera.h"
#include <iostream>

glm::vec3 Kamera::getEye() const
{
    return eye;
}

void Kamera::setEye(const glm::vec3 &value)
{
    eye = value;
}

glm::vec3 Kamera::getCenter() const
{
    return center;
}

void Kamera::setCenter(const glm::vec3 &value)
{
    center = value;
}

glm::vec3 Kamera::getUp() const
{
    return up;
}

void Kamera::setUp(const glm::vec3 &value)
{
    up = value;
}

glm::mat4 Kamera::getProjektionsMatrix() const
{
    return projektionsMatrix;
}

void Kamera::setProjektionsMatrix(const glm::mat4 &value)
{
    projektionsMatrix = value;
}

glm::mat4 Kamera::getLookAt() const
{
    return lookAt;
}

void Kamera::setLookAt(const glm::mat4 &value)
{
    lookAt = value;
}

glm::mat4 Kamera::getProjektionsMatrixZentrall() const
{
    return projektionsMatrixZentrall;
}

void Kamera::setProjektionsMatrixZentrall(const glm::mat4 &value)
{
    projektionsMatrixZentrall = value;
}

glm::vec2 Kamera::getFenster() const
{
    return fenster;
}

void Kamera::setFenster(const glm::vec2 &value)
{
    fenster = value;
}

float Kamera::getX() const
{
    return x;
}

void Kamera::setX(float value)
{
    x = value;
}

float Kamera::getY() const
{
    return y;
}

void Kamera::setY(float value)
{
    y = value;
}

float Kamera::getZ() const
{
    return z;
}

void Kamera::setZ(float value)
{
    z = value;
}

float Kamera::getR() const
{
    return r;
}

void Kamera::setR(float value)
{
    r = value;
}

float Kamera::getL() const
{
    return l;
}

void Kamera::setL(float value)
{
    l = value;
}

float Kamera::getB() const
{
    return b;
}

void Kamera::setB(float value)
{
    b = value;
}

float Kamera::getT() const
{
    return t;
}

void Kamera::setT(float value)
{
    t = value;
}

float Kamera::getF() const
{
    return f;
}

void Kamera::setF(float value)
{
    f = value;
}

float Kamera::getN() const
{
    return n;
}

void Kamera::setN(float value)
{
    n = value;
}

void Kamera::renew(){

    //--------------------------------------------------
    //paralelprojektion? matrix, normalized device coordinates ?
    projektionsMatrix = glm::mat4(glm::vec4(2/(r-l),0,0,-((r+l)/(r-l))),
                                  glm::vec4(0,2/(t-b),0,-((t+b)/(t-b))),
                                  glm::vec4(0,0,-2/(f-n),-((f+n)/(f-n))),
                                  glm::vec4(0,0,0,1));
    projektionsMatrixZentrall = glm::mat4(glm::vec4((2*n)/(r-l),0,(r+l)/(r-l),0),
                                          glm::vec4(0,(2*n)/(t-b),(t+b)/(t-b),0),
                                          glm::vec4(0,0,-((f+n)/(f-n)),-((2*f*n)/(f-n))),
                                          glm::vec4(0,0,-1,0));
    //--------------------------------------------------

}

Kamera::Kamera()
{
    x = 0;
    y = 0;
    z = -1.0;
    rotation = 0;
    r = 1;
    l = -1;
    t = 1;
    b = -1;
    n = 1;
    f = -1;
    setFenster(glm::vec2(400,400));
    //--------------------------------------------------
    //paralelprojektion? matrix, normalized device coordinates ?
    projektionsMatrix = glm::mat4(glm::vec4(2/(r-l),0,0,-((r+l)/(r-l))),
                                  glm::vec4(0,2/(t-b),0,-((t+b)/(t-b))),
                                  glm::vec4(0,0,-2/(f-n),-((f+n)/(f-n))),
                                  glm::vec4(0,0,0,1));
    projektionsMatrixZentrall = glm::mat4(glm::vec4((2*n)/(r-l),0,(r+l)/(r-l),0),
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

void Kamera::reset()
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

glm::mat4 Kamera::constructLookAt(){
    glm::mat4 temp = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                               glm::vec4(v.x,v.y,v.z,0),
                               glm::vec4(w.x,w.y,w.z,0),
                               glm::vec4(x,y,z,1));
    std::cout<<"const look at "<< w.x<<w.y<<w.z<<std::endl;
    return temp;
}

void Kamera::moveKammW(){
    z = z +0.1;
    lookAt = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                       glm::vec4(v.x,v.y,v.z,0),
                       glm::vec4(w.x,w.y,w.z,0),
                       glm::vec4(x,y,z,1));
}

void Kamera::moveKammA()
{
    x = x -0.1;
    lookAt = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                       glm::vec4(v.x,v.y,v.z,0),
                       glm::vec4(w.x,w.y,w.z,0),
                       glm::vec4(x,y,z,1));
}

void Kamera::moveKammS()
{
    z = z -0.1;
    lookAt = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                       glm::vec4(v.x,v.y,v.z,0),
                       glm::vec4(w.x,w.y,w.z,0),
                       glm::vec4(x,y,z,1));
}

void Kamera::moveKammD()
{
    x = x +0.1;
    lookAt = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                       glm::vec4(v.x,v.y,v.z,0),
                       glm::vec4(w.x,w.y,w.z,0),
                       glm::vec4(x,y,z,1));
}

void Kamera::moveKammUpY()
{
    y = y +0.1;
    lookAt = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                       glm::vec4(v.x,v.y,v.z,0),
                       glm::vec4(w.x,w.y,w.z,0),
                       glm::vec4(x,y,z,1));
}

void Kamera::moveKammDownX()
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
void Kamera::RotateKammLeft()
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

void Kamera::RotateKammRight()
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
