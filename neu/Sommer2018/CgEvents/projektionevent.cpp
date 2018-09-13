#include "projektionevent.h"

glm::vec3 ProjektionEvent::getValue() const
{
    return value;
}

void ProjektionEvent::setValue(const glm::vec3 &value)
{
    this->value = value;
}

ProjektionEvent::ProjektionEvent(enum Cg::EventType type,const glm::vec3& value):type(type),value(value)

{

}

ProjektionEvent::~ProjektionEvent()
{

}

Cg::EventType ProjektionEvent::getType()
{
    return this->type;
}

ProjektionEvent::ProjektionEvent(Cg::EventType type)
{
    this->type=type;
}

CgBaseEvent *ProjektionEvent::clone()
{
    return new ProjektionEvent(type,value);
}
