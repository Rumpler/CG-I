#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include "CgCube.h"
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

    //Display objects?
    bool renderCube;
    bool renderCubeNormals;

    //Objects
    CgCube* m_cube;
    std::vector<CgPolyline*>* m_cube_normals;



};

#endif // CGSCENECONTROL_H
