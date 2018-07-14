#ifndef CGLOADEVENT_H
#define CGLOADEVENT_H

#include <CgBase/CgBaseEvent.h>
#include <string>



class CgLoadEvent : public CgBaseEvent
{
public:
    CgLoadEvent();

    // CgBaseEvent interface
    Cg::EventType getType();
    CgBaseEvent *clone();

    std::string getFilename() const;
    void setFilename(const std::string &value);

private:
    Cg::EventType m_type;
    std::string filename;
};

#endif // CGLOADEVENT_H
