#ifndef CGKEYEVENT_H
#define CGKEYEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"
#include <string>
#include <iostream>

class CgKeyEvent : public CgBaseEvent
{

public:

    CgKeyEvent();
    CgKeyEvent(Cg::EventType type,Cg::Key key,Cg::KeyboardModifiers mod, std::string text);

    //inherited
    Cg::EventType  getType();
    CgBaseEvent* clone();

    //own specific methods
    Cg::KeyboardModifiers modifiers() const;
    Cg::Key key() const;
    std::string text() const;

    friend std::ostream& operator <<(std::ostream& os, const CgKeyEvent& e);

private:

    Cg::EventType m_type;
    Cg::Key m_key;
    Cg::KeyboardModifiers m_mod;
    std::string m_text;

};

#endif // CGKEYEVENT_H
