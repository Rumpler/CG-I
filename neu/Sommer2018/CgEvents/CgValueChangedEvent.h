#ifndef CGVALUECHANGEDEVENT_H
#define CGVALUECHANGEDEVENT_H

#include <CgBase/CgBaseEvent.h>
#include <iostream>

/*!
 * \brief The CgValueChangedEvent class contains bools wich objects are changed and special params for each object
 *
 * It is neccessary to set the specifc params for each object when the bool for the object is true
 *
 * \author Gerrit Harmes
 */

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

    bool getRotationCurveChanged() const;
    void setRotationCurveChanged(bool value);

    double getValueRadiusCylinder() const;
    void setValueRadiusCylinder(double value);

    bool getSdForPointScheme() const;
    void setSdForPointScheme(bool value);

    bool getResetRotationCurve() const;
    void setResetRotationCurve(bool value);

private:
    Cg::EventType m_type;

    bool cylinderChanged = false;
    int valueAmountOfSegmentsCylinder;
    double valueHeightCylinder;
    double valueRadiusCylinder;

    bool rotationCurveChanged = false;
    bool sdForPointScheme = false;
    bool resetRotationCurve = false;

    bool rotationBodyChanged = false;
    int valueAmountOfSegmentsRotationBody;
};

#endif // CGVALUECHANGEDEVENT_H
