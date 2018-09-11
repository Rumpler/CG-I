#ifndef CGSHADEREVENT_H
#define CGSHADEREVENT_H

#include <CgBase/CgBaseEvent.h>



class CgShaderEvent  : public CgBaseEvent
{
public:
    CgShaderEvent();

    // CgBaseEvent interface
public:
    Cg::EventType getType();
    CgBaseEvent *clone();

    bool getPhong() const;
    void setPhong(bool value);

    bool getGouraud() const;
    void setGouraud(bool value);

    bool getFlat() const;
    void setFlat(bool value);

    bool getSmooth() const;
    void setSmooth(bool value);

    int getMaterialIndex() const;
    void setMaterialIndex(int value);

    bool getNoneShader() const;
    void setNoneShader(bool value);

private:
    Cg::EventType m_type;

    bool noneShader;
    bool phong;
    bool gouraud;

    bool flat;
    bool smooth;

    int materialIndex;
};

#endif // CGSHADEREVENT_H
