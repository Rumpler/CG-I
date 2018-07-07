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

    int getValueAmountOfSegments() const;
    void setValueAmountOfSegments(int value);

    double getValueHeight() const;
    void setValueHeight(double value);

    friend std::ostream& operator <<(std::ostream& os, const CgValueChangedEvent& e);

private:
    Cg::EventType m_type;

    int valueAmountOfSegments;
    double valueHeight;
};

#endif // CGVALUECHANGEDEVENT_H
