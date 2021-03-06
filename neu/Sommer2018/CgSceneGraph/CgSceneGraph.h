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
#include <CgEvents/CgMaterialChangeEvent.h>
#include "CgUtils/IdSingleton.h"
#include <CgClasses/kamera.h>
#include <CgClasses/CgLightsource.h>

class CgSceneGraph
{
private:

    //Basics
    IdSingleton* idGen;
    CgBaseRenderer *m_renderer;
    glm::mat4 m_trackball_rotation;
    glm::mat4 m_lookAt_matrix;
    glm::mat4 m_proj_matrix;
    std::stack<glm::mat4> m_mat_stack;
    CgScene* scene;

    //Shading
    bool noneShading = true ;
    bool phong = false;
    bool gouraud = false;
    bool flat = true;
    bool smooth = false;
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    float shininess;
    CgLightsource* light;
    Camera* cam;
    int projektionstype;

    //Colors
    glm::vec4 defaultColor = glm::vec4(0.0f, 0.45f, 0.5f, 1.0f);
    glm::vec4 defaultColorNormals = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec4 selectedColor = glm::vec4(0.0f,1.0f,0.5f, 1.0f);
    glm::vec4 currentColor = defaultColor;
    glm::vec4 lastColorOfSelectedEntity = defaultColor;

    //Entitys
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

    //Helper for selecting next entity
    int selectedEntityPosition = 0;
    std::vector<CgSceneGraphEntity*> selectableEntitys;

    //Helper for matrix stack
    void pushMatrix(){m_mat_stack.push(m_mat_stack.top());}
    void popMatrix(){m_mat_stack.pop();}
    void applyTransform(glm::mat4 arg){m_mat_stack.top() *= arg;}

    //Recursiv helper methodes to apply changes to all children of entity
    void changeColorRecursiv(CgSceneGraphEntity* currentEntity, glm::vec4 color);
    void renderRecursive(CgSceneGraphEntity* currentEntity);
    void destructRecursive(CgSceneGraphEntity* currentEntity);

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

    //Interaction
    void render();
    void selectNextEnitiy();
    void loadObject(std::string str);

    //Color
    void changeColorOfAllObjects(glm::vec4 color);
    void changeColorOfSelectedObjects(glm::vec4 color);

    //Shader
    void setMaterialPropertiesForSelectedEntity();
    void setMaterialPropertiesRecursiv(CgSceneGraphEntity* currentEntity);
    void setShader();

    //Cylinder
    void changeCylinder(int amountOfSegments, double height, double radius);
    //Rotation Body
    void changeRotationBody(int amountOfSegments);
    void changeRotationBody();
    void changeRotationCurveForPointScheme();
    void changeRotationCurveReset();

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
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void rotateLeft();
    void rotateRight();
    void reset();
    void setLookAtAfterMove();
    void setProjection(int i);
    void setFrustum(int i, float wert);
    glm::vec4 getAmb() const;
    void setAmb(const glm::vec4 &value);
    glm::vec4 getDef() const;
    void setDef(const glm::vec4 &value);
    glm::vec4 getSpec() const;
    void setSpec(const glm::vec4 &value);
    float getShininess() const;
    void setShininess(float value);
    bool getNone() const;
    void setNone(bool value);
    bool getPhong() const;
    void setPhong(bool value);
    bool getGouraud() const;
    void setGouraud(bool value);
    bool getFlat() const;
    void setFlat(bool value);
    bool getSmooth() const;
    void setSmooth(bool value);
};

#endif // CGSCENEGRAPH_H
