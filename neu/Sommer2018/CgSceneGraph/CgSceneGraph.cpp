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


    initCoordinateSystem(false);
    initVariousObjects();
    initSceneObjects();

    selectedEntity = cubeEntity;
}

CgSceneGraph::~CgSceneGraph()
{
    //TODO
}

void CgSceneGraph::changeColorOfVariousObjects(glm::vec3 color)
{
    if(color.x < 0 || color.x > 1.0 || color.y < 0 || color.y > 1.0 || color.z < 0 || color.z > 1.0){
        std::cout << "bad color values" << std::endl;
        return;
    }else{
//        selectedEntity->appearance()->setObjectColor(color);
        changeColorOfAllChildrenRecursiv(variousObjectsEntity, color);
        currentColor = color;
    }
}

void CgSceneGraph::changeCylinder(int amountOfSegments, double height, double radius)
{
    if(amountOfSegments >= 2 && height >= 0 && radius >= 0){
        CgCylinder* cylinder = (CgCylinder*) cylinderEntity->getObjects().at(0);
        cylinder->makeCylinder(amountOfSegments, height, radius);
        m_renderer->init(cylinder);


        std::vector<CgLine*>* cylinderNormals = cylinder->getPolylineNormals();
        cylinderNormalsEntity->clearObjects();
        for(CgLine* line : *cylinderNormals){
            m_renderer->init(line);
            cylinderNormalsEntity->addObject(line);
        }
    }
}

void CgSceneGraph::changeRotationBody(int amountOfSegments)
{
    CgRotationBody* rotationBody = (CgRotationBody*) rotationBodyEntity->getObjects().at(0);
    rotationBody->makeRotationBody((CgLine*)rotationCurveEntity->getObjects().at(0), amountOfSegments);
    m_renderer->init(rotationBody);

    std::vector<CgLine*>* rotationBodyNormals = rotationBody->getPolylineNormals();
    rotationBodyNormalsEntity->clearObjects();
    for(CgLine* line : *rotationBodyNormals){
        m_renderer->init(line);
        rotationBodyNormalsEntity->addObject(line);
    }
}

void CgSceneGraph::changeRotationBody()
{
    CgRotationBody* rotationBody = (CgRotationBody*) rotationBodyEntity->getObjects().at(0);
    int amountOfSegments = rotationBody->getAmountOfSegments();
    changeRotationBody(amountOfSegments);
}

void CgSceneGraph::changeRotationCurveForPointScheme()
{
    CgLine* rotationCurve = (CgLine*) rotationCurveEntity->getObjects().at(0);
    rotationCurve->sdForPointScheme();
    m_renderer->init(rotationCurve);
}

void CgSceneGraph::changeRotationCurveReset()
{
    CgLine* rotationCurve = (CgLine*) rotationCurveEntity->getObjects().at(0);
    rotationCurve->setRotationCurveExample1();
    m_renderer->init(rotationCurve);
}

void CgSceneGraph::selectNextEnitiy()
{
    if(selectableEntitys.size() > 1){
        selectedEntity->appearance()->setObjectColor(currentColor);

        int startPos = selectedEntityPosition;
        do{
            selectedEntityPosition = (selectedEntityPosition + 1) % selectableEntitys.size();
            selectedEntity = selectableEntitys.at(selectedEntityPosition);
            if(*(selectedEntity->renderObject())){
                break;
            }
        }while(selectedEntityPosition != startPos);

        selectedEntity->appearance()->setObjectColor(selectedColor);
    }









    m_renderer->redraw();
}

void CgSceneGraph::tScaleSelectedEntity(glm::vec3 factor)
{
    selectedEntity->setCurrentTransformation(selectedEntity->getCurrentTransformation() * CgU::tScaleMat(factor));
    m_renderer->redraw();
}

void CgSceneGraph::tRotateSelectedEntity(float angle, char c)
{
    glm::mat4 rotateMat;
    if(c == 'x'){
        rotateMat = CgU::tRotateMatX(angle);
    }else if(c == 'y'){
        rotateMat = CgU::tRotateMatY(angle);
    }else if(c == 'z'){
        rotateMat = CgU::tRotateMatZ(angle);
    }
    selectedEntity->setCurrentTransformation(selectedEntity->getCurrentTransformation()* rotateMat);
    m_renderer->redraw();
}



void CgSceneGraph::render()
{
    selectItemsToDisplay();
    m_renderer->setUniformValue("projMatrix",m_proj_matrix);
    renderRecursive(m_root_node);
}

void CgSceneGraph::renderRecursive(CgSceneGraphEntity *currentEntity)
{
    if(*(currentEntity->renderObject())){
        glm::mat4 mv_matrix = m_lookAt_matrix * m_trackball_rotation * currentEntity->getCurrentTransformation();
        glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(mv_matrix)));

        m_renderer->setUniformValue("modelviewMatrix",mv_matrix);
        m_renderer->setUniformValue("normalMatrix",normal_matrix);

        m_renderer->setUniformValue("mycolor",glm::vec4(currentEntity->appearance()->getObjectColor(), 1.0f));

        for(CgBaseRenderableObject* obj : currentEntity->getObjects()){
            m_renderer->render(obj);
        }

        for(CgSceneGraphEntity* entity : currentEntity->getChildren()){
            renderRecursive(entity);
        }
    }
}



void CgSceneGraph::initCoordinateSystem(bool cylinder)
{
        CgCylinder* axis = new CgCylinder(idGen->getNextId(), 5, 1.0f, 0.0001);

//        CgLine* axis = new CgLine(idGen->getNextId());
//        axis->addVertice(glm::vec3(0.0f,0.0f,0.0f));
//        axis->addVertice(glm::vec3(1.0f,0.0f,0.0f));

        m_renderer->init(axis);

    /*********** coordinate system ***********/

    coordinateSystemEntity = new CgSceneGraphEntity;
    coordinateSystemEntity->setParent(m_root_node);
    m_root_node->addChild(coordinateSystemEntity);
    coordinateSystemEntity->setIsColorChangeable(false);
    renderCoordinateSystem = coordinateSystemEntity->renderObject();
    setRenderCoordinateSystem(true);

        m_mat_stack.push(m_mat_stack.top() * CgU::tRotateMatZ(-90.0f));

            CgSceneGraphEntity* xAxis = new CgSceneGraphEntity();
            xAxis->setRenderObjects(true);
            xAxis->setParent(coordinateSystemEntity);
            coordinateSystemEntity->addChild(xAxis);
            xAxis->appearance()->setObjectColor(glm::vec3(1.0f, 0.0f, 0.0f));
            xAxis->addObject(axis);
            xAxis->setCurrentTransformation(m_mat_stack.top());

        m_mat_stack.pop();
        m_mat_stack.push(m_mat_stack.top());

            CgSceneGraphEntity* yAxis = new CgSceneGraphEntity();
            yAxis->setRenderObjects(true);
            yAxis->setParent(coordinateSystemEntity);
            coordinateSystemEntity->addChild(yAxis);
            yAxis->appearance()->setObjectColor(glm::vec3(0.0f, 1.0f, 0.0f));
            yAxis->addObject(axis);
            yAxis->setCurrentTransformation(m_mat_stack.top());

        m_mat_stack.pop();
        m_mat_stack.push(m_mat_stack.top() * CgU::tRotateMatX(90.0f));

            CgSceneGraphEntity* zAxis = new CgSceneGraphEntity();
            zAxis->setRenderObjects(true);
            zAxis->setParent(coordinateSystemEntity);
            coordinateSystemEntity->addChild(zAxis);
            zAxis->appearance()->setObjectColor(glm::vec3(0.0f, 0.0f, 1.0f));
            zAxis->addObject(axis);
            zAxis->setCurrentTransformation(m_mat_stack.top());

        m_mat_stack.pop();

        /*********** END coordinate system ***********/
}

void CgSceneGraph::initVariousObjects()
{
    variousObjectsEntity = new CgSceneGraphEntity();
    variousObjectsEntity->setParent(m_root_node);
    m_root_node->addChild(variousObjectsEntity);
    renderVariousObjects = variousObjectsEntity->renderObject();

    initCube();
    initCylinder();
    initRotationObjects();
    initLoadedObject();
}

void CgSceneGraph::initSceneObjects()
{
    sceneObjectsEntity = new CgSceneGraphEntity();
    sceneObjectsEntity->setParent(m_root_node);
    m_root_node->addChild(sceneObjectsEntity);
    renderScene = sceneObjectsEntity->renderObject();
}

void CgSceneGraph::initCube()
{
    //Object cube
    CgCube* cube = new CgCube(idGen->getNextId());
    m_renderer->init(cube);

    // entity cube
    cubeEntity = new CgSceneGraphEntity();
    cubeEntity->setParent(variousObjectsEntity);
    variousObjectsEntity->addChild(cubeEntity);
    cubeEntity->appearance()->setObjectColor(defaultColor);
    cubeEntity->addObject(cube);
    renderCube = cubeEntity->renderObject();
    selectableEntitys.push_back(cubeEntity);

        // entity cube normals
        cubeNormalsEntity = new CgSceneGraphEntity();
        cubeNormalsEntity->setParent(cubeEntity);
        cubeEntity->addChild(cubeNormalsEntity);
        cubeNormalsEntity->setIsColorChangeable(false);
        cubeNormalsEntity->appearance()->setObjectColor(defaultColorNormals);
        renderCubeNormals = cubeNormalsEntity->renderObject();

        std::vector<CgLine*>* cubeNormals = cube->getPolylineNormals();
        for(CgLine* line : *cubeNormals){
            m_renderer->init(line);
            cubeNormalsEntity->addObject(line);
        }
}

void CgSceneGraph::initCylinder()
{
    CgCylinder* cylinder = new CgCylinder(idGen->getNextId(), 50, 0.3f, 0.2);
    m_renderer->init(cylinder);


        // entity cylinder
        cylinderEntity = new CgSceneGraphEntity();
        cylinderEntity->setParent(variousObjectsEntity);
        variousObjectsEntity->addChild(cylinderEntity);
        cylinderEntity->appearance()->setObjectColor(defaultColor);
        cylinderEntity->addObject(cylinder);
        renderCylinder = cylinderEntity->renderObject();
        selectableEntitys.push_back(cylinderEntity);

            // entity cylinder normals
            cylinderNormalsEntity = new CgSceneGraphEntity();
            cylinderNormalsEntity->setParent(cylinderEntity);
            cylinderEntity->addChild(cylinderNormalsEntity);
            cylinderNormalsEntity->setIsColorChangeable(false);
            cylinderNormalsEntity->appearance()->setObjectColor(defaultColorNormals);
            renderCylinderNormals = cylinderNormalsEntity->renderObject();

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
        rotationCurveEntity->setParent(variousObjectsEntity);
        variousObjectsEntity->addChild(rotationCurveEntity);
        rotationCurveEntity->appearance()->setObjectColor(defaultColor);
        rotationCurveEntity->addObject(rotationCurve);
        renderRotationCurve = rotationCurveEntity->renderObject();
        selectableEntitys.push_back(rotationCurveEntity);

        rotationBodyEntity = new CgSceneGraphEntity();
        rotationBodyEntity->setParent(variousObjectsEntity);
        variousObjectsEntity->addChild(rotationBodyEntity);
        rotationBodyEntity->appearance()->setObjectColor(defaultColor);
        rotationBodyEntity->addObject(rotationBody);
        renderRotationBody = rotationBodyEntity->renderObject();
        selectableEntitys.push_back(rotationBodyEntity);

            rotationBodyNormalsEntity = new CgSceneGraphEntity();
            rotationBodyNormalsEntity->setParent(rotationBodyEntity);
            rotationBodyEntity->addChild(rotationBodyNormalsEntity);
            rotationBodyNormalsEntity->setIsColorChangeable(false);
            rotationBodyNormalsEntity->appearance()->setObjectColor(defaultColorNormals);
            renderRotationBodyNormals = rotationBodyNormalsEntity->renderObject();

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
        loadedObjectEntity->setParent(variousObjectsEntity);
        variousObjectsEntity->addChild(loadedObjectEntity);
        loadedObjectEntity->appearance()->setObjectColor(defaultColor);
        loadedObjectEntity->addObject(loadedObject);
        selectableEntitys.push_back(loadedObjectEntity);

        renderLoadedObject = loadedObjectEntity->renderObject();

            loadedObjectNormalsEntity = new CgSceneGraphEntity();
            loadedObjectNormalsEntity->setParent(loadedObjectEntity);
            loadedObjectEntity->addChild(loadedObjectNormalsEntity);
            loadedObjectNormalsEntity->setIsColorChangeable(false);
            loadedObjectNormalsEntity->appearance()->setObjectColor(defaultColorNormals);

            renderLoadedObjectNormals = loadedObjectNormalsEntity->renderObject();

            std::vector<CgLine*>* loadedObjectNormals = loadedObject->getPolylineNormals();
            for(CgLine* line : *loadedObjectNormals){
                m_renderer->init(line);
                loadedObjectNormalsEntity->addObject(line);
            }


}

void CgSceneGraph::selectItemsToDisplay()
{
    coordinateSystemEntity->setRenderObjects(*renderCoordinateSystem);

    variousObjectsEntity->setRenderObjects(*renderVariousObjects);
        cubeEntity->setRenderObjects(*renderCube);
        cubeNormalsEntity->setRenderObjects(*renderCubeNormals);

        cylinderEntity->setRenderObjects(*renderCylinder);
        cylinderNormalsEntity->setRenderObjects(*renderCylinderNormals);

        rotationCurveEntity->setRenderObjects(*renderRotationCurve);
        rotationBodyEntity->setRenderObjects(*renderRotationBody);
        rotationBodyNormalsEntity->setRenderObjects(*renderRotationBodyNormals);

        loadedObjectEntity->setRenderObjects(*renderLoadedObject);
        loadedObjectNormalsEntity->setRenderObjects(*renderLoadedObjectNormals);

    sceneObjectsEntity->setRenderObjects(*renderScene);

}

void CgSceneGraph::changeColorOfAllChildrenRecursiv(CgSceneGraphEntity *currentEntity, glm::vec3 color)
{
    if(currentEntity->getIsColorChangeable()){
        currentEntity->appearance()->setObjectColor(color);
        for(CgSceneGraphEntity* entity : currentEntity->getChildren()){
            changeColorOfAllChildrenRecursiv(entity, color);
        }
    }







    if(*(currentEntity->renderObject())){
        glm::mat4 mv_matrix = m_lookAt_matrix * m_trackball_rotation * currentEntity->getCurrentTransformation();
        glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(mv_matrix)));

        m_renderer->setUniformValue("modelviewMatrix",mv_matrix);
        m_renderer->setUniformValue("normalMatrix",normal_matrix);

        m_renderer->setUniformValue("mycolor",glm::vec4(currentEntity->appearance()->getObjectColor(), 1.0f));

        for(CgBaseRenderableObject* obj : currentEntity->getObjects()){
            m_renderer->render(obj);
        }

        for(CgSceneGraphEntity* entity : currentEntity->getChildren()){
            renderRecursive(entity);
        }
    }
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
