#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include "CgPolyline.h"
#include "CgCube.h"
#include <glm/glm.hpp>

class CgBaseEvent;
class CgBaseRenderer;
class CgTriangles;
class CgCube;

class CgSceneControl : public CgObserver, public CgBaseSceneControl
{
public:
    CgSceneControl();
    ~CgSceneControl();
    void handleEvent(CgBaseEvent* e);
    void setRenderer(CgBaseRenderer* r);

    void renderObjects();

private:

    CgBaseRenderer* m_renderer;
    glm::vec3 color;

    //Objects for rendering
    CgTriangles* m_triangle;
    CgCube* m_cube;

    //Objects do display
    bool renderCoordinateSystem;
    bool renderTriangle;
    bool renderCube;

    //Coordinatesystem
    CgPolyline* x_Axis;
    CgPolyline* y_Axis;
    CgPolyline* z_Axis;



    //Matrix
    glm::mat4 m_current_transformation;
    glm::mat4 m_proj_matrix;

};

#endif // CGSCENECONTROL_H