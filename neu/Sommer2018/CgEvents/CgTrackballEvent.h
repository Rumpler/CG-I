#ifndef CGTRACKBALLEVENT_H
#define CGTRACKBALLEVENT_H


#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"


#include <iostream>
#include <string>
#include <glm/glm.hpp>

class CgTrackballEvent : public CgBaseEvent
{
public:
    CgTrackballEvent();
    CgTrackballEvent(Cg::EventType type, glm::mat4 rot);
    ~CgTrackballEvent(){};

    //inherited
    Cg::EventType  getType();
    CgBaseEvent* clone();

    glm::mat4 getRotationMatrix(){return m_rotation;}


    friend std::ostream& operator <<(std::ostream& os, const CgTrackballEvent& e);

private:
     Cg::EventType m_type;
     glm::mat4 m_rotation;



};
#endif // CGTRACKBALLEVENT_H
