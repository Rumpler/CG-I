#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include "CgCube.h"
#include "CgTest.h"
#include <glm/glm.hpp>

class CgBaseEvent;
class CgBaseRenderer;
class CgExampleTriangle;

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
    CgExampleTriangle* m_triangle;
    glm::mat4 m_current_transformation;
    glm::mat4 m_trackball_rotation;
    glm::mat4 m_lookAt_matrix;
    glm::mat4 m_proj_matrix;

    IdSingleton* idGen;
    glm::vec3 customColor = glm::vec3(0.7f,0.0f,1.0f);

    //Display objects?
    bool renderCoordinateSystem = true;
    bool renderTriangle = false;
    bool renderCube = false;
    bool renderCubeNormals = false;

    //Objects
    std::vector<CgPolyline*> m_coordinate_system;
    CgCube* m_cube;
    std::vector<CgPolyline*>* m_cube_normals;

    CgTest* m_test;



    void initCoordinateSystem();

};

#endif // CGSCENECONTROL_H
