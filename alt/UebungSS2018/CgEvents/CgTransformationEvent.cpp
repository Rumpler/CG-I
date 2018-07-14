#include "CgTransformationEvent.h"

CgTransformationEvent::CgTransformationEvent(glm::vec3 scaleVec):
    m_type(Cg::CgTransformationEvent),
    scaleVec(scaleVec)
{

}

Cg::EventType CgTransformationEvent::getType()
{
    return m_type;
}

CgBaseEvent *CgTransformationEvent::clone()
{
    CgTransformationEvent* e = new CgTransformationEvent(scaleVec);

    return e;
}

glm::vec3 CgTransformationEvent::getScaleVec() const
{
    return scaleVec;
}

void CgTransformationEvent::setScaleVec(const glm::vec3 &value)
{
    scaleVec = value;
}


