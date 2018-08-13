#ifndef CGBUTTONEVENT_H
#define CGBUTTONEVENT_H

#include <CgBase/CgBaseEvent.h>
#include <glm/gtc/matrix_transform.hpp>



class CgButtonEvent : public CgBaseEvent
{
private:
    Cg::EventType m_type;

    bool btSelectNextObject = false;

    bool btScalePlus = false;
    bool btScaleMinus = false;

    bool btRotateX = false;
    bool btRotateY = false;
    bool btRotateZ = false;

    bool btTranslate = false;
        glm::vec3 translateVec = glm::vec3(0.0f);

public:
    CgButtonEvent();

    Cg::EventType getType();
    CgBaseEvent *clone();

    bool getBtSelectNextObject() const;
    void setBtSelectNextObject(bool value);
    bool getBtScalePlus() const;
    void setBtScalePlus(bool value);
    bool getBtScaleMinus() const;
    void setBtScaleMinus(bool value);
    bool getBtRotateX() const;
    void setBtRotateX(bool value);
    bool getBtRotateY() const;
    void setBtRotateY(bool value);
    bool getBtRotateZ() const;
    void setBtRotateZ(bool value);
    bool getBtTranslate() const;
    void setBtTranslate(bool value, glm::vec3 translateVec);
    glm::vec3 getTranslateVec() const;
    void setTranslateVec(const glm::vec3 &value);
};

#endif // CGBUTTONEVENT_H
