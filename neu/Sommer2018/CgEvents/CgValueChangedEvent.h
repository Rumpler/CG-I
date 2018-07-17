#ifndef CGVALUECHANGEDEVENT_H
#define CGVALUECHANGEDEVENT_H

#include <CgBase/CgBaseEvent.h>
#include <iostream>



class CgValueChangedEvent : public CgBaseEvent
{
public:
    CgValueChangedEvent();

    // CgBaseEvent interface
    Cg::EventType getType();
    CgBaseEvent *clone();

    int getValueAmountOfSegmentsCylinder() const;
    void setValueAmountOfSegmentsCylinder(int value);

    double getValueHeightCylinder() const;
    void setValueHeightCylinder(double value);

    friend std::ostream& operator <<(std::ostream& os, const CgValueChangedEvent& e);

    bool getCylinderChanged() const;
    void setCylinderChanged(bool value);

    bool getRotationBodyChanged() const;
    void setRotationBodyChanged(bool value);

    int getValueAmountOfSegmentsRotationBody() const;
    void setValueAmountOfSegmentsRotationBody(int value);

    bool getResetRotationCurve() const;
    void setResetRotationCurve(bool value);

private:
    Cg::EventType m_type;

    bool cylinderChanged = false;
    bool resetRotationCurve = false;
    bool rotationBodyChanged = false;

    int valueAmountOfSegmentsCylinder;
    double valueHeightCylinder;

    int valueAmountOfSegmentsRotationBody;
};

#endif // CGVALUECHANGEDEVENT_H
