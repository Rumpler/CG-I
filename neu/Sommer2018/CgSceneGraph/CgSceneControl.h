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
    CgSceneGraph *m_scene_graph;

};

#endif // CGSCENECONTROL_H
