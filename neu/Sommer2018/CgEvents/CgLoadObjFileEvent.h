#ifndef CGLOADOBJFILEEVENT
#define CGLOADOBJFILEEVENT



#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"


#include <iostream>
#include <string>

/*!
 * \brief The CgLoadObjFileEvent class transports the filename from the GUI to scenecontroll
 *
 * \author Gerrit Harmes
 */

class CgLoadObjFileEvent : public CgBaseEvent
{
public:
    CgLoadObjFileEvent();
    CgLoadObjFileEvent(Cg::EventType type, std::string filename);
    ~CgLoadObjFileEvent(){};

    //inherited
    Cg::EventType  getType();
    CgBaseEvent* clone();

    std::string fileName(){return m_filename;}


    friend std::ostream& operator <<(std::ostream& os, const CgLoadObjFileEvent& e);

private:
     Cg::EventType m_type;
     std::string m_filename;



};








#endif // CGLOADOBJFILEEVENT

