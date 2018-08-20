#ifndef CGSCENEGRAPH_H
#define CGSCENEGRAPH_H

#include "CgCube.h"
#include "CgScene.h"
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
    //Basic vars
    IdSingleton* idGen;
    CgBaseRenderer *m_renderer;
    glm::mat4 m_trackball_rotation;
    glm::mat4 m_lookAt_matrix;
    glm::mat4 m_proj_matrix;
    std::stack<glm::mat4> m_mat_stack;

    //Colors
    glm::vec3 defaultColor = glm::vec3(0.0f, 0.45f, 0.5f);
    glm::vec3 defaultColorNormals = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 currentColor = defaultColor;
    glm::vec3 selectedColor = glm::vec3(0.0f,1.0f,0.5f);

    //Helper for chosing next selected entity
    int selectedEntityPosition = 0;
    std::vector<CgSceneGraphEntity*> selectableEntitys;

    //Scene
    CgScene* scene;

    //Entitys*
    CgSceneGraphEntity* selectedEntity;
    CgSceneGraphEntity* m_root_node;
        CgSceneGraphEntity* coordinateSystemEntity;
        CgSceneGraphEntity* variousObjectsEntity;
            CgSceneGraphEntity* cubeEntity;
                CgSceneGraphEntity* cubeNormalsEntity;
            CgSceneGraphEntity* cylinderEntity;
                CgSceneGraphEntity* cylinderNormalsEntity;
            CgSceneGraphEntity* rotationCurveEntity;
            CgSceneGraphEntity* rotationBodyEntity;
                CgSceneGraphEntity* rotationBodyNormalsEntity;
            CgSceneGraphEntity* loadedObjectEntity;
                CgSceneGraphEntity* loadedObjectNormalsEntity;
            CgSceneGraphEntity* customRotationAxisEntity;
        CgSceneGraphEntity* sceneEntity;

    //Bools* for rendering
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
        bool* renderCustomRotationAxis;
    bool* renderScene;


    //Private helper methodes for matrix stack
    void pushMatrix(){m_mat_stack.push(m_mat_stack.top());}
    void popMatrix(){m_mat_stack.pop();}
    void applyTransform(glm::mat4 arg){m_mat_stack.top() *= arg;}

    //Recursiv helper methodes to apply changes to all children of entity
    void changeColorRecursiv(CgSceneGraphEntity* currentEntity, glm::vec3 color);
    void renderRecursive(CgSceneGraphEntity* currentEntity);

    //Helper methods for initialization
    void initCoordinateSystem();
    void initVariousObjects();
        void initCube();
        void initCylinder();
        void initRotationObjects();
        void initLoadedObject();
        void initCustomRotationAxis();
    void initSceneObjects();

public:
    CgSceneGraph(CgBaseRenderer *renderer);
    ~CgSceneGraph();

    //Public methodes for interacton with Scenegraph
    void render();

    void changeColorOfVariousObjects(glm::vec3 color);
    void changeCylinder(int amountOfSegments, double height, double radius);
    void changeRotationBody(int amountOfSegments);
    void changeRotationBody();
    void changeRotationCurveForPointScheme();
    void changeRotationCurveReset();

    void selectNextEnitiy();
    void loadObject(std::string str);

    //Transformation methodes
    void tScaleSelectedEntity(glm::vec3 factor);
    void tRotateSelectedEntity(float angle, char c);
    void tRotateSelectedEntity(float angle, glm::vec3 axis);
    void tTranslateSelectedEntity(glm::vec3 transVec);

    //Getter and Setter
    glm::mat4 projectionMatrix() const;
    void setProjectionMatrix(const glm::mat4 &projectionMatrix);
    glm::mat4 trackballRotation() const;
    void setTrackballRotation(const glm::mat4 &trackballRotation);
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
    bool getRenderCustomRotationAxis() const;
    void setRenderCustomRotationAxis(bool value);
};

#endif // CGSCENEGRAPH_H
