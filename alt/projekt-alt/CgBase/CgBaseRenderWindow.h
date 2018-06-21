#ifndef CGBASERENDERWINDOW
#define CGBASERENDERWINDOW

class CgBaseRenderer;

class CgBaseRenderWindow
{


    public:

        virtual CgBaseRenderer* getRenderer()=0;
};


#endif // CGBASERENDERWINDOW

