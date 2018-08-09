#include "CgCube.h"
#include "CgCylinder.h"
#include "CgRotationBody.h"
#include "CgSceneGraph.h"
#include "CgTriangles.h"

#include <CgUtils/CgUtils.h>



CgSceneGraph::CgSceneGraph(CgBaseRenderer *renderer):
    m_renderer(renderer)
{
    m_mat_stack.push(glm::mat4(1.));

    m_lookAt_matrix= glm::lookAt(glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    m_proj_matrix= glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
    m_trackball_rotation=glm::mat4(1.);
    idGen = IdSingleton::instance();

    m_root_node = new CgSceneGraphEntity();
    m_root_node->setRenderObjects(true);


    initCoordinateSystem();
    initVariousObjects();
    initSceneObjects();




}

CgSceneGraph::~CgSceneGraph()
{
  //TODO
}

void CgSceneGraph::render()
{
    selectItemsToDisplay();
    m_renderer->setUniformValue("projMatrix",m_proj_matrix);
    recursiveRender(m_root_node);
}

void CgSceneGraph::recursiveRender(CgSceneGraphEntity *currentEntity)
{
    if(*(currentEntity->getRenderObject())){
        glm::mat4 mv_matrix = m_lookAt_matrix * m_trackball_rotation * currentEntity->getCurrentTransformation();
        glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(mv_matrix)));

        m_renderer->setUniformValue("modelviewMatrix",mv_matrix);
        m_renderer->setUniformValue("normalMatrix",normal_matrix);

        m_renderer->setUniformValue("mycolor",glm::vec4(currentEntity->appearance()->getObjectColor(), 1.0f));

        for(CgBaseRenderableObject* obj : currentEntity->getObjects()){
            m_renderer->render(obj);
        }

        for(CgSceneGraphEntity* entity : currentEntity->getChildren()){
            recursiveRender(entity);
        }
    }
}



void CgSceneGraph::initCoordinateSystem()
{
    //Objects
    CgLine* axis = new CgLine(idGen->getNextId());
    axis->addVertice(glm::vec3(0.0f,0.0f,0.0f));
    axis->addVertice(glm::vec3(1.0f,0.0f,0.0f));
    m_renderer->init(axis);


    /*********** coordinate system ***********/

    coordinateSystem = new CgSceneGraphEntity;
    coordinateSystem->setParent(m_root_node);
    m_root_node->addChild(coordinateSystem);
    renderCoordinateSystem = coordinateSystem->getRenderObject();
    setRenderCoordinateSystem(true);

        m_mat_stack.push(m_mat_stack.top());

            CgSceneGraphEntity* xAxis = new CgSceneGraphEntity();
            xAxis->setRenderObjects(true);
            xAxis->setParent(coordinateSystem);
            coordinateSystem->addChild(xAxis);
            xAxis->appearance()->setObjectColor(glm::vec3(1.0f, 0.0f, 0.0f));
            xAxis->addObject(axis);
            xAxis->setCurrentTransformation(m_mat_stack.top());

        m_mat_stack.pop();
        m_mat_stack.push(m_mat_stack.top() * CgU::rotateMatZ(90.0f));

            CgSceneGraphEntity* yAxis = new CgSceneGraphEntity();
            yAxis->setRenderObjects(true);
            yAxis->setParent(coordinateSystem);
            coordinateSystem->addChild(yAxis);
            yAxis->appearance()->setObjectColor(glm::vec3(0.0f, 1.0f, 0.0f));
            yAxis->addObject(axis);
            yAxis->setCurrentTransformation(m_mat_stack.top());

        m_mat_stack.pop();
        m_mat_stack.push(m_mat_stack.top() * CgU::rotateMatY(-90.0f));

            CgSceneGraphEntity* zAxis = new CgSceneGraphEntity();
            zAxis->setRenderObjects(true);
            zAxis->setParent(coordinateSystem);
            coordinateSystem->addChild(zAxis);
            zAxis->appearance()->setObjectColor(glm::vec3(0.0f, 0.0f, 1.0f));
            zAxis->addObject(axis);
            zAxis->setCurrentTransformation(m_mat_stack.top());

        m_mat_stack.pop();

        /*********** END coordinate system ***********/
}

void CgSceneGraph::initVariousObjects()
{
    variousObjects = new CgSceneGraphEntity();
    variousObjects->setParent(m_root_node);
    m_root_node->addChild(variousObjects);
    renderVariousObjects = variousObjects->getRenderObject();

    initCube();
    initCylinder();
    initRotationObjects();
    initLoadedObject();
}

void CgSceneGraph::initSceneObjects()
{
    sceneObjects = new CgSceneGraphEntity();
    sceneObjects->setParent(m_root_node);
    m_root_node->addChild(sceneObjects);
    renderScene = sceneObjects->getRenderObject();
}

void CgSceneGraph::initCube()
{
    //Object cube
    CgCube* cube = new CgCube(idGen->getNextId());
    m_renderer->init(cube);

    // entity cube
    cubeEntity = new CgSceneGraphEntity();
    cubeEntity->setParent(variousObjects);
    variousObjects->addChild(cubeEntity);
    cubeEntity->appearance()->setObjectColor(defaultColor);
    cubeEntity->addObject(cube);
    cubeEntity->setCurrentTransformation(m_mat_stack.top());
    renderCube = cubeEntity->getRenderObject();

        // entity cube normals
        cubeNormalsEntity = new CgSceneGraphEntity();
        cubeNormalsEntity->setParent(cubeEntity);
        cubeEntity->addChild(cubeNormalsEntity);
        cubeNormalsEntity->appearance()->setObjectColor(defaultColorNormals);
        cubeNormalsEntity->setCurrentTransformation(m_mat_stack.top());
        renderCubeNormals = cubeNormalsEntity->getRenderObject();

        std::vector<CgLine*>* cubeNormals = cube->getPolylineNormals();
        for(CgLine* line : *cubeNormals){
            m_renderer->init(line);
            cubeNormalsEntity->addObject(line);
        }


}

void CgSceneGraph::initCylinder()
{
    CgCylinder* cylinder = new CgCylinder(idGen->getNextId(), 50, 0.5f, 0.2);
    m_renderer->init(cylinder);


        // entity cylinder
        cylinderEntity = new CgSceneGraphEntity();
        cylinderEntity->setParent(variousObjects);
        variousObjects->addChild(cylinderEntity);
        cylinderEntity->appearance()->setObjectColor(defaultColor);
        cylinderEntity->addObject(cylinder);
        cylinderEntity->setCurrentTransformation(m_mat_stack.top());
        renderCylinder = cylinderEntity->getRenderObject();

            // entity cylinder normals
            cylinderNormalsEntity = new CgSceneGraphEntity();
            cylinderNormalsEntity->setParent(cylinderEntity);
            cylinderEntity->addChild(cylinderNormalsEntity);
            cylinderNormalsEntity->appearance()->setObjectColor(defaultColorNormals);
            cylinderNormalsEntity->setCurrentTransformation(m_mat_stack.top());
            renderCylinderNormals = cylinderNormalsEntity->getRenderObject();

            std::vector<CgLine*>* cylinderNormals = cylinder->getPolylineNormals();
            for(CgLine* line : *cylinderNormals){
                m_renderer->init(line);
                cylinderNormalsEntity->addObject(line);
            }
}

void CgSceneGraph::initRotationObjects()
{
    CgLine* rotationCurve = new CgLine(idGen->getNextId());
    rotationCurve->setRotationCurveExample1();
    m_renderer->init(rotationCurve);

    CgRotationBody* rotationBody = new CgRotationBody(idGen->getNextId(), rotationCurve, 50);
    m_renderer->init(rotationBody);

        rotationCurveEntity = new CgSceneGraphEntity();
        rotationCurveEntity->setParent(variousObjects);
        variousObjects->addChild(rotationCurveEntity);
        rotationCurveEntity->appearance()->setObjectColor(defaultColor);
        rotationCurveEntity->addObject(rotationCurve);
        rotationCurveEntity->setCurrentTransformation(m_mat_stack.top());
        renderRotationCurve = rotationCurveEntity->getRenderObject();

        rotationBodyEntity = new CgSceneGraphEntity();
        rotationBodyEntity->setParent(variousObjects);
        variousObjects->addChild(rotationBodyEntity);
        rotationBodyEntity->appearance()->setObjectColor(defaultColor);
        rotationBodyEntity->addObject(rotationBody);
        rotationBodyEntity->setCurrentTransformation(m_mat_stack.top());
        renderRotationBody = rotationBodyEntity->getRenderObject();

            rotationBodyNormalsEntity = new CgSceneGraphEntity();
            rotationBodyNormalsEntity->setParent(rotationBodyEntity);
            rotationBodyEntity->addChild(rotationBodyNormalsEntity);
            rotationBodyNormalsEntity->appearance()->setObjectColor(defaultColorNormals);
            rotationBodyNormalsEntity->setCurrentTransformation(m_mat_stack.top());
            renderRotationBodyNormals = rotationBodyNormalsEntity->getRenderObject();

            std::vector<CgLine*>* rotationBodyNormals = rotationBody->getPolylineNormals();
            for(CgLine* line : *rotationBodyNormals){
                m_renderer->init(line);
                rotationBodyNormalsEntity->addObject(line);
            }

}

void CgSceneGraph::initLoadedObject()   //Keep in mind not to change the order of objects! Method loadObject(std::string str) will be affected.
{
    CgTriangles* loadedObject = new CgTriangles(idGen->getNextId());
    loadedObject->init("/home/gerrit/git/CG-I/neu/Sommer2018/CgData/porsche.obj");
    m_renderer->init(loadedObject);

        loadedObjectEntity = new CgSceneGraphEntity();
        loadedObjectEntity->setParent(variousObjects);
        variousObjects->addChild(loadedObjectEntity);
        loadedObjectEntity->appearance()->setObjectColor(defaultColor);
        loadedObjectEntity->addObject(loadedObject);
        loadedObjectEntity->setCurrentTransformation(m_mat_stack.top());

        renderLoadedObject = loadedObjectEntity->getRenderObject();

            loadedObjectNormalsEntity = new CgSceneGraphEntity();
            loadedObjectNormalsEntity->setParent(loadedObjectEntity);
            loadedObjectEntity->addChild(loadedObjectNormalsEntity);
            loadedObjectNormalsEntity->appearance()->setObjectColor(defaultColorNormals);
            loadedObjectNormalsEntity->setCurrentTransformation(m_mat_stack.top());

            renderLoadedObjectNormals = loadedObjectNormalsEntity->getRenderObject();

            std::vector<CgLine*>* loadedObjectNormals = loadedObject->getPolylineNormals();
            for(CgLine* line : *loadedObjectNormals){
                m_renderer->init(line);
                loadedObjectNormalsEntity->addObject(line);
            }


}

void CgSceneGraph::selectItemsToDisplay()
{
    coordinateSystem->setRenderObjects(*renderCoordinateSystem);

    variousObjects->setRenderObjects(*renderVariousObjects);
        cubeEntity->setRenderObjects(*renderCube);
        cubeNormalsEntity->setRenderObjects(*renderCubeNormals);

        cylinderEntity->setRenderObjects(*renderCylinder);
        cylinderNormalsEntity->setRenderObjects(*renderCylinderNormals);

        rotationCurveEntity->setRenderObjects(*renderRotationCurve);
        rotationBodyEntity->setRenderObjects(*renderRotationBody);
        rotationBodyNormalsEntity->setRenderObjects(*renderRotationBodyNormals);

        loadedObjectEntity->setRenderObjects(*renderLoadedObject);
        loadedObjectNormalsEntity->setRenderObjects(*renderLoadedObjectNormals);

    sceneObjects->setRenderObjects(*renderScene);

}


/************ GETTER AND SETTER ************/

glm::mat4 CgSceneGraph::projectionMatrix() const{
    return m_proj_matrix;
}

void CgSceneGraph::setProjectionMatrix(const glm::mat4 &proj_matrix){
    m_proj_matrix = proj_matrix;
}

glm::mat4 CgSceneGraph::trackballRotation() const{
    return m_trackball_rotation;
}

void CgSceneGraph::setTrackballRotation(const glm::mat4 &trackball_rotation){
    m_trackball_rotation = trackball_rotation;
}

void CgSceneGraph::loadObject(std::string str)
{
    CgTriangles* loadedObject = (CgTriangles*)(loadedObjectEntity->getObjects().at(0));
    loadedObject->init(str);
    m_renderer->init(loadedObject);

    std::vector<CgLine*>* loadedObjectNormals = loadedObject->getPolylineNormals();
    loadedObjectNormalsEntity->clearObjects();
    for(CgLine* line : *loadedObjectNormals){
        m_renderer->init(line);
        loadedObjectNormalsEntity->addObject(line);
    }
}

bool CgSceneGraph::getRenderCoordinateSystem() const{
    return *renderCoordinateSystem;
}

void CgSceneGraph::setRenderCoordinateSystem(bool value){
    *renderCoordinateSystem = value;
}

bool CgSceneGraph::getRenderVariousObjects() const{
    return *renderVariousObjects;
}

void CgSceneGraph::setRenderVariousObjects(bool value){
    *renderVariousObjects = value;
}

bool CgSceneGraph::getRenderCube() const{
    return *renderCube;
}

void CgSceneGraph::setRenderCube(bool value){
    *renderCube = value;
}

bool CgSceneGraph::getRenderCubeNormals() const{
    return *renderCubeNormals;
}

void CgSceneGraph::setRenderCubeNormals(bool value){
    *renderCubeNormals = value;
}

bool CgSceneGraph::getRenderCylinder() const{
    return *renderCylinder;
}

void CgSceneGraph::setRenderCylinder(bool value){
    *renderCylinder = value;
}

bool CgSceneGraph::getRenderCylinderNormals() const{
    return *renderCylinderNormals;
}

void CgSceneGraph::setRenderCylinderNormals(bool value){
    *renderCylinderNormals = value;
}

bool CgSceneGraph::getRenderRotationCurve() const{
    return *renderRotationCurve;
}

void CgSceneGraph::setRenderRotationCurve(bool value){
    *renderRotationCurve = value;
}

bool CgSceneGraph::getRenderRotationBody() const{
    return *renderRotationBody;
}

void CgSceneGraph::setRenderRotationBody(bool value){
    *renderRotationBody = value;
}

bool CgSceneGraph::getRenderRotationBodyNormals() const{
    return *renderRotationBodyNormals;
}

void CgSceneGraph::setRenderRotationBodyNormals(bool value){
    *renderRotationBodyNormals = value;
}

bool CgSceneGraph::getRenderLoadedObject() const{
    return *renderLoadedObject;
}

void CgSceneGraph::setRenderLoadedObject(bool value){
    *renderLoadedObject = value;
}

bool CgSceneGraph::getRenderLoadedObjectNormals() const{
    return *renderLoadedObjectNormals;
}

void CgSceneGraph::setRenderLoadedObjectNormals(bool value){
    *renderLoadedObjectNormals = value;
}

bool CgSceneGraph::getRenderScene() const{
    return *renderScene;
}

void CgSceneGraph::setRenderScene(bool value){
    *renderScene = value;
}
