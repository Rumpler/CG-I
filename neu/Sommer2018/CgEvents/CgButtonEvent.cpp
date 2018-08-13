#include "CgButtonEvent.h"

bool CgButtonEvent::getBtSelectNextObject() const
{
    return btSelectNextObject;
}

void CgButtonEvent::setBtSelectNextObject(bool value)
{
    btSelectNextObject = value;
}

bool CgButtonEvent::getBtScalePlus() const
{
    return btScalePlus;
}

void CgButtonEvent::setBtScalePlus(bool value)
{
    btScalePlus = value;
}

bool CgButtonEvent::getBtScaleMinus() const
{
    return btScaleMinus;
}

void CgButtonEvent::setBtScaleMinus(bool value)
{
    btScaleMinus = value;
}

bool CgButtonEvent::getBtRotateX() const
{
    return btRotateX;
}

void CgButtonEvent::setBtRotateX(bool value)
{
    btRotateX = value;
}

bool CgButtonEvent::getBtRotateY() const
{
    return btRotateY;
}

void CgButtonEvent::setBtRotateY(bool value)
{
    btRotateY = value;
}

bool CgButtonEvent::getBtRotateZ() const
{
    return btRotateZ;
}

void CgButtonEvent::setBtRotateZ(bool value)
{
    btRotateZ = value;
}

bool CgButtonEvent::getBtTranslate() const
{
    return btTranslate;
}

void CgButtonEvent::setBtTranslate(bool value, glm::vec3 translateVec)
{
    btTranslate = value;
}

glm::vec3 CgButtonEvent::getTranslateVec() const
{
    return translateVec;
}

void CgButtonEvent::setTranslateVec(const glm::vec3 &value)
{
    translateVec = value;
}

CgButtonEvent::CgButtonEvent() :
    m_type(Cg::CgButtonEvent)
{

}

Cg::EventType CgButtonEvent::getType()
{
    return m_type;
}

CgBaseEvent *CgButtonEvent::clone()
{
    CgButtonEvent* e = new CgButtonEvent();
    e->setBtSelectNextObject(btSelectNextObject);

    e->setBtScalePlus(btScalePlus);
    e->setBtScaleMinus(btScaleMinus);

    e->setBtRotateX(btRotateX);
    e->setBtRotateY(btRotateY);
    e->setBtRotateZ(btRotateZ);

    e->setBtTranslate(btTranslate, translateVec);
    return e;
}
