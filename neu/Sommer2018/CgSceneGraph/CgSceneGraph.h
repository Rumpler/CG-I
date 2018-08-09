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


    glm::vec3 defaultColor = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 defaultColorNormals = glm::vec3(1.0f, 1.0f, 1.0f);


    void pushMatrix(){m_mat_stack.push(m_mat_stack.top());}
    void popMatrix(){m_mat_stack.pop();}
    void applyTransform(glm::mat4 arg){m_mat_stack.top() *= arg;}

    void initCoordinateSystem();
    void initVariousObjects();
    void initSceneObjects();


    void initCube();
    void initCylinder();
    void initRotationObjects();


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
};

#endif // CGSCENEGRAPH_H
