#ifndef CGMATERIALCHANGEEVENT_H
#define CGMATERIALCHANGEEVENT_H

#include <CgBase/CgBaseEvent.h>
#include <glm/common.hpp>
#include "CgBase/CgEnums.h"
class CgMaterialChangeEvent :public CgBaseEvent
{
public:
    CgMaterialChangeEvent();
    CgMaterialChangeEvent(glm::vec4 mat,glm::vec4 amb, glm::vec4 diffuse, float scalar, enum Cg::EventType type,int shadingmode);
    CgMaterialChangeEvent(glm::vec4 mat, int shadingmode);
    enum Cg::EventType type;
    glm::vec4 mat;
    glm::vec4 amb;
    glm::vec4 diffuse;
    float scalar;
    int shadingmode;

    // CgBaseEvent interface
public:

    Cg::EventType getType();
    CgBaseEvent *clone();
    glm::vec4 getMat() const;
    void setMat(const glm::vec4 &value);
    glm::vec4 getAmb() const;
    void setAmb(const glm::vec4 &value);
    glm::vec4 getDiffuse() const;
    void setDiffuse(const glm::vec4 &value);
    float getScalar() const;
    void setScalar(float value);
    int getShadingmode() const;
    void setShadingmode(int value);
};

#endif // CGMATERIALCHANGEEVENT_H
