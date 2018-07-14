#ifndef CGTRANSFORMATIONEVENT_H
#define CGTRANSFORMATIONEVENT_H

#include <CgBase/CgBaseEvent.h>
#include <glm/glm.hpp>



class CgTransformationEvent : public CgBaseEvent
{
public:
    CgTransformationEvent(glm::vec3 scaleVec);

    // CgBaseEvent interface
    Cg::EventType getType();
    CgBaseEvent *clone();

    glm::vec3 getScaleVec() const;
    void setScaleVec(const glm::vec3 &value);

private:
    Cg::EventType m_type;

    glm::vec3 scaleVec = glm::vec3(1.0f);
};

#endif // CGTRANSFORMATIONEVENT_H
