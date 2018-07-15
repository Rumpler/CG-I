#ifndef CGBASESCENECONTROL
#define CGBASESCENECONTROL

class CgBaseRenderer;

class CgBaseSceneControl
{

    public:

     virtual ~CgBaseSceneControl(){};


        virtual void renderObjects()=0;
        virtual void setRenderer(CgBaseRenderer* r)=0;
};


#endif // CGBASESCENECONTROL

