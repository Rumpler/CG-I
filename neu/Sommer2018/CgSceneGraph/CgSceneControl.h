#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include "CgCube.h"
#include "CgCylinder.h"
#include "CgRotationBody.h"
#include "CgTriangles.h"
#include <glm/glm.hpp>

class CgBaseEvent;
class CgBaseRenderer;
class CgTriangles;

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
    glm::mat4 m_current_transformation;
    glm::mat4 m_trackball_rotation;
    glm::mat4 m_lookAt_matrix;
    glm::mat4 m_proj_matrix;

    IdSingleton* idGen;
    //glm::vec3 customColor = glm::vec3(0.7f,0.0f,1.0f);

    //contains all objects for recoloring
    std::vector<CgBaseRenderableObject*> colorObjects;

    //Objects
    std::vector<CgLine*> m_coordinate_system;
    CgCube* m_cube;
    std::vector<CgLine*>* m_cube_normals;

    CgCylinder* m_cylinder;
    std::vector<CgLine*>* m_cylinder_normals;

    CgLine* m_rotation_curve;

    CgRotationBody* m_rotation_body;

    CgTriangles* m_loaded_object;
    std::vector<CgLine*>* m_loaded_object_normals;
    bool renderLoadedObjectNormals = false;




    void initCoordinateSystem();

};

#endif // CGSCENECONTROL_H
