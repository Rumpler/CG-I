#ifndef CGBASERENDERABLEOBJECT
#define CGBASERENDERABLEOBJECT


#include "CgBase/CgEnums.h"


class CgBaseRenderableObject
{

    public:

    virtual ~CgBaseRenderableObject(){};


    virtual Cg::ObjectType getType() const  =0;
    virtual unsigned int getID() const  =0;


protected:


};




#endif // CGBASERENDERABLEOBJECT

