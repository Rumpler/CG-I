#ifndef CGSCENEGRAPH_H
#define CGSCENEGRAPH_H

#include "CgCube.h"
#include "CgSceneGraphEntity.h"
#include <stack>
#include <string>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <CgBase/CgBaseRenderer.h>
#include "CgUtils/IdSingleton.h"


class CgSceneGraph
{
private:
    IdSingleton* idGen;
    CgBaseRenderer *m_renderer;
    glm::mat4 m_trackball_rotation;
    glm::mat4 m_lookAt_matrix;
    glm::mat4 m_proj_matrix;

    CgSceneGraphEntity* m_root_node;
    std::stack<glm::mat4> m_mat_stack;

    CgSceneGraphEntity* coordinateSystem;
    CgSceneGraphEntity* variousObjects;
    CgSceneGraphEntity* sceneObjects;

    CgSceneGraphEntity* cubeEntity;
    CgSceneGraphEntity* cubeNormalsEntity;

    CgSceneGraphEntity* cylinderEntity;
    CgSceneGraphEntity* cylinderNormalsEntity;

    CgSceneGraphEntity* rotationCurveEntity;
    CgSceneGraphEntity* rotationBodyEntity;
    CgSceneGraphEntity* rotationBodyNormalsEntity;

    CgSceneGraphEntity* loadedObjectEntity;
    CgSceneGraphEntity* loadedObjectNormalsEntity;


    glm::vec3 defaultColor = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 defaultColorNormals = glm::vec3(1.0f, 1.0f, 1.0f);

    bool* renderCoordinateSystem;
    bool* renderVariousObjects;
        bool* renderCube;
        bool* renderCubeNormals;
        bool* renderCylinder;
        bool* renderCylinderNormals;
        bool* renderRotationCurve;
        bool* renderRotationBody;
        bool* renderRotationBodyNormals;
        bool* renderLoadedObject;
        bool* renderLoadedObjectNormals;
    bool* renderScene;


    void pushMatrix(){m_mat_stack.push(m_mat_stack.top());}
    void popMatrix(){m_mat_stack.pop();}
    void applyTransform(glm::mat4 arg){m_mat_stack.top() *= arg;}

    void initCoordinateSystem();
    void initVariousObjects();
    void initSceneObjects();


    void initCube();
    void initCylinder();
    void initRotationObjects();
    void initLoadedObject();


    void selectItemsToDisplay();




public:
    CgSceneGraph(CgBaseRenderer *renderer);
    ~CgSceneGraph();

    void render();
    void recursiveRender(CgSceneGraphEntity* currentEntity);

    glm::mat4 projectionMatrix() const;
    void setProjectionMatrix(const glm::mat4 &projectionMatrix);
    glm::mat4 trackballRotation() const;
    void setTrackballRotation(const glm::mat4 &trackballRotation);

    void loadObject(std::string str);

    bool getRenderCoordinateSystem() const;
    void setRenderCoordinateSystem(bool value);
    bool getRenderVariousObjects() const;
    void setRenderVariousObjects(bool value);
    bool getRenderCube() const;
    void setRenderCube(bool value);
    bool getRenderCubeNormals() const;
    void setRenderCubeNormals(bool value);
    bool getRenderCylinder() const;
    void setRenderCylinder(bool value);
    bool getRenderCylinderNormals() const;
    void setRenderCylinderNormals(bool value);
    bool getRenderRotationCurve() const;
    void setRenderRotationCurve(bool value);
    bool getRenderRotationBody() const;
    void setRenderRotationBody(bool value);
    bool getRenderRotationBodyNormals() const;
    void setRenderRotationBodyNormals(bool value);
    bool getRenderLoadedObject() const;
    void setRenderLoadedObject(bool value);
    bool getRenderLoadedObjectNormals() const;
    void setRenderLoadedObjectNormals(bool value);
    bool getRenderScene() const;
    void setRenderScene(bool value);
};

#endif // CGSCENEGRAPH_H
