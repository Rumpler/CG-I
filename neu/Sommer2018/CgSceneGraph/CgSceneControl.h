#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include "CgCube.h"
#include "CgCylinder.h"
#include "CgRotationBody.h"
#include "CgSceneGraph.h"
#include "CgTriangles.h"
#include <glm/glm.hpp>

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
    CgSceneGraph *m_scene_graph;

    //default helper vars
    glm::vec3 transVec = glm::vec3(0.1f,0.0f,0.0f);
    glm::vec3 rotateVec = glm::vec3(1.0f,1.0f,1.0f);
};

#endif // CGSCENECONTROL_H
