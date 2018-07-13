#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include "CgPolyline.h"
#include "CgCube.h"
#include "CgCylinder.h"
#include "CgRotationBody.h"
#include "CgUtils/IdSingleton.h"
#include <glm/glm.hpp>
#include <vector>

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

    //Id generator
    IdSingleton* idGen;

    //Objects for rendering
    CgCube* m_cube;
    std::vector<CgPolyline*>* m_cube_normals;
    CgCylinder* m_cylinder;
    std::vector<CgPolyline*>* m_cylinder_normals;
    CgPolyline* m_rotation_curve;
    CgRotationBody* m_rotation_body;

    CgPolyline* tempPoly;


    //Objects do display
    bool renderCoordinateSystem;
    bool renderCube;
    bool renderCubeNormals;
    bool renderCylinder;
    bool renderCylinderNormals;
    bool renderRotationCurve;
    bool renderRotationBody;

    //Coordinatesystem
    CgPolyline* x_Axis;
    CgPolyline* y_Axis;
    CgPolyline* z_Axis;



    //Matrix
    glm::mat4 m_current_transformation;
    glm::mat4 m_proj_matrix;

};

#endif // CGSCENECONTROL_H
