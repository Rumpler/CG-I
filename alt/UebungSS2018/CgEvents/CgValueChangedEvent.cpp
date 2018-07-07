#include "CgValueChangedEvent.h"

CgValueChangedEvent::CgValueChangedEvent():
    m_type(Cg::CgValueChangedEvent)
{

}

Cg::EventType CgValueChangedEvent::getType()
{
    return m_type;
}

CgBaseEvent* CgValueChangedEvent::clone()
{
    CgValueChangedEvent* e = new CgValueChangedEvent();
    e->setValueAmountOfSegments(valueAmountOfSegments);
    e->setValueHeight(valueHeight);
    return e;
}

int CgValueChangedEvent::getValueAmountOfSegments() const
{
    return valueAmountOfSegments;
}

void CgValueChangedEvent::setValueAmountOfSegments(int value)
{
    valueAmountOfSegments = value;
}

double CgValueChangedEvent::getValueHeight() const
{
    return valueHeight;
}

void CgValueChangedEvent::setValueHeight(double value)
{
    valueHeight = value;
}

std::ostream& operator<<(std::ostream& os,const CgValueChangedEvent& e)
{
    os << "ValueChanged-Event of Type: "<< e.m_type <<", height:" << e.getValueHeight()  <<", AmountOfSegments:" << e.getValueAmountOfSegments()  << std::endl;
    return os;
}
