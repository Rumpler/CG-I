#include "CgBoxEvent.h"

#include "CgBoxEvent.h"

float CgBoxEvent::getSelected() const
{
    return selected;
}

void CgBoxEvent::setSelected(float value)
{
    selected = value;
}

CgBoxEvent::CgBoxEvent()
{

}

CgBoxEvent::CgBoxEvent(const Cg::EventType type, const float selected):type(type),selected(selected)
{
}

Cg::EventType CgBoxEvent::getType()
{
    return this->type;
}

CgBaseEvent *CgBoxEvent::clone()
{
    return new CgBoxEvent(type,selected);
}
