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
    e->setCylinderChanged(cylinderChanged);
    e->setRotationCurveChanged(rotationCurveChanged);
    e->setRotationBodyChanged(rotationBodyChanged);

    e->setValueAmountOfSegmentsCylinder(valueAmountOfSegmentsCylinder);
    e->setValueHeightCylinder(valueHeightCylinder);
    e->setValueRadiusCylinder(valueRadiusCylinder);

    e->setValueAmountOfSegmentsRotationBody(valueAmountOfSegmentsRotationBody);
    e->setSdForPointScheme(sdForPointScheme);
    e->setResetRotationCurve(resetRotationCurve);

    return e;
}

int CgValueChangedEvent::getValueAmountOfSegmentsCylinder() const
{
    return valueAmountOfSegmentsCylinder;
}

void CgValueChangedEvent::setValueAmountOfSegmentsCylinder(int value)
{
    if(value >= 2){
        valueAmountOfSegmentsCylinder = value;
    }else{
        valueAmountOfSegmentsCylinder = 2;
    }

}

double CgValueChangedEvent::getValueHeightCylinder() const
{
    return valueHeightCylinder;
}

void CgValueChangedEvent::setValueHeightCylinder(double value)
{
    valueHeightCylinder = value;
}

bool CgValueChangedEvent::getCylinderChanged() const
{
    return cylinderChanged;
}

void CgValueChangedEvent::setCylinderChanged(bool value)
{
    cylinderChanged = value;
}

bool CgValueChangedEvent::getRotationBodyChanged() const
{
    return rotationBodyChanged;
}

void CgValueChangedEvent::setRotationBodyChanged(bool value)
{
    rotationBodyChanged = value;
}

int CgValueChangedEvent::getValueAmountOfSegmentsRotationBody() const
{
    return valueAmountOfSegmentsRotationBody;
}

void CgValueChangedEvent::setValueAmountOfSegmentsRotationBody(int value)
{
    valueAmountOfSegmentsRotationBody = value;
}

bool CgValueChangedEvent::getRotationCurveChanged() const
{
    return rotationCurveChanged;
}

void CgValueChangedEvent::setRotationCurveChanged(bool value)
{
    rotationCurveChanged = value;
}

double CgValueChangedEvent::getValueRadiusCylinder() const
{
    return valueRadiusCylinder;
}

void CgValueChangedEvent::setValueRadiusCylinder(double value)
{
    valueRadiusCylinder = value;
}

bool CgValueChangedEvent::getSdForPointScheme() const
{
    return sdForPointScheme;
}

void CgValueChangedEvent::setSdForPointScheme(bool value)
{
    sdForPointScheme = value;
}

bool CgValueChangedEvent::getResetRotationCurve() const
{
    return resetRotationCurve;
}

void CgValueChangedEvent::setResetRotationCurve(bool value)
{
    resetRotationCurve = value;
}

std::ostream& operator<<(std::ostream& os,const CgValueChangedEvent& e)
{
    os << "ValueChanged-Event of Type: "<< e.m_type <<", height:" << e.getValueHeightCylinder()  <<", AmountOfSegments:" << e.getValueAmountOfSegmentsCylinder()  << std::endl;
    return os;
}
