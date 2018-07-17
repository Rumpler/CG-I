#ifndef CGCOLORCHANGEEVENT_H
#define CGCOLORCHANGEEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"

#include <iostream>

class CgColorChangeEvent : public CgBaseEvent
{
public:
    CgColorChangeEvent();
    CgColorChangeEvent(int r, int g, int b);
    ~CgColorChangeEvent(){}

    // CgBaseEvent interface
public:

    //inherited
    Cg::EventType getType();
    CgBaseEvent *clone();

    friend std::ostream& operator <<(std::ostream& os, const CgColorChangeEvent& e);

    unsigned int getRed() const;
    void setRed(unsigned int value);

    unsigned int getGreen() const;
    void setGreen(unsigned int value);

    unsigned int getBlue() const;
    void setBlue(unsigned int value);

private:
    Cg::EventType m_type;
    unsigned int red;
    unsigned int green;
    unsigned int blue;
};

#endif // CGCOLORCHANGEEVENT_H
