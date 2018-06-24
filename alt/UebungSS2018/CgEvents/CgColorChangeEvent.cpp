#include "CgColorChangeEvent.h"

CgColorChangeEvent::CgColorChangeEvent():
    m_type(Cg::CgColorChangeEvent),
    red(1),
    green(1),
    blue(1)
{

}

CgColorChangeEvent::CgColorChangeEvent(int r, int g, int b):
    m_type(Cg::CgColorChangeEvent),
    red(r),
    green(g),
    blue(b)
{

}

Cg::EventType CgColorChangeEvent::getType()
{
    return m_type;
}

CgBaseEvent *CgColorChangeEvent::clone()
{
    return new CgColorChangeEvent(red, green, blue);
}




//Getter and Setter
unsigned int CgColorChangeEvent::getRed() const
{
    return red;
}

void CgColorChangeEvent::setRed(unsigned int value)
{
    red = value;
}

unsigned int CgColorChangeEvent::getGreen() const
{
    return green;
}

void CgColorChangeEvent::setGreen(unsigned int value)
{
    green = value;
}

unsigned int CgColorChangeEvent::getBlue() const
{
    return blue;
}

void CgColorChangeEvent::setBlue(unsigned int value)
{
    blue = value;
}








std::ostream& operator<<(std::ostream& os,const CgColorChangeEvent& e)
{
    os << "ColorChangeEvent of Type: "<< e.m_type <<", r:" << e.red  <<", g:" << e.green<<", b:" << e.blue  << std::endl;
    return os;
}
