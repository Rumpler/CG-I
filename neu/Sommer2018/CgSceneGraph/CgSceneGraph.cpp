#include "CgCube.h"
#include "CgCylinder.h"
#include "CgSceneGraph.h"

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
    if(currentEntity->getRenderObjects()){
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
    CgLine* axis = new CgLine(idGen->getNextId()); // Needs to be deleted?
    axis->addVertice(glm::vec3(0.0f,0.0f,0.0f));
    axis->addVertice(glm::vec3(1.0f,0.0f,0.0f));
    m_renderer->init(axis);


    /*********** coordinate system ***********/

    coordinateSystem = new CgSceneGraphEntity;
    coordinateSystem->setRenderObjects(true);
    coordinateSystem->setParent(m_root_node);
    m_root_node->addChild(coordinateSystem);

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

    initCube();
    initCylinder();
}

void CgSceneGraph::initSceneObjects()
{
    sceneObjects = new CgSceneGraphEntity();
    sceneObjects->setParent(m_root_node);
    m_root_node->addChild(sceneObjects);
}

void CgSceneGraph::initCube()
{
    //Object cube
    CgCube* cube = new CgCube(idGen->getNextId());
    m_renderer->init(cube);

    // entity cube
    cubeEntity = new CgSceneGraphEntity();
    //cubeEntity->getRenderObjects() = true;
    cubeEntity->setParent(variousObjects);
    variousObjects->addChild(cubeEntity);
    cubeEntity->appearance()->setObjectColor(glm::vec3(0.0f, 1.0f, 0.0f));
    cubeEntity->addObject(cube);
    cubeEntity->setCurrentTransformation(m_mat_stack.top());

        // entity cube normals
        cubeNormalsEntity = new CgSceneGraphEntity();
        cubeNormalsEntity->setParent(cubeEntity);
        cubeEntity->addChild(cubeNormalsEntity);
        cubeNormalsEntity->appearance()->setObjectColor(glm::vec3(1.0f, 1.0f, 1.0f));
        cubeNormalsEntity->setCurrentTransformation(m_mat_stack.top());

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
    //cubeEntity->getRenderObjects() = true;
    cylinderEntity->setParent(variousObjects);
    variousObjects->addChild(cylinderEntity);
    cylinderEntity->appearance()->setObjectColor(glm::vec3(0.0f, 1.0f, 0.0f));
    cylinderEntity->addObject(cylinder);
    cylinderEntity->setCurrentTransformation(m_mat_stack.top());

        // entity cube normals
        cylinderNormalsEntity = new CgSceneGraphEntity();
        cylinderNormalsEntity->setRenderObjects(true);
        cylinderNormalsEntity->setParent(cylinderEntity);
        cylinderEntity->addChild(cylinderNormalsEntity);
        cylinderNormalsEntity->appearance()->setObjectColor(glm::vec3(1.0f, 1.0f, 1.0f));
        cylinderNormalsEntity->setCurrentTransformation(m_mat_stack.top());

        std::vector<CgLine*>* cylinderNormals = cylinder->getPolylineNormals();
        for(CgLine* line : *cylinderNormals){
            m_renderer->init(line);
            cubeNormalsEntity->addObject(line);
        }
}

void CgSceneGraph::selectItemsToDisplay()
{
    coordinateSystem->setRenderObjects(false);
    variousObjects->setRenderObjects(true);
    sceneObjects->setRenderObjects(true);

    cubeEntity->setRenderObjects(true);
    cubeNormalsEntity->setRenderObjects(false);

    cylinderEntity->setRenderObjects(true);
    cylinderNormalsEntity->setRenderObjects(true);
}

glm::mat4 CgSceneGraph::projectionMatrix() const
{
    return m_proj_matrix;
}

void CgSceneGraph::setProjectionMatrix(const glm::mat4 &proj_matrix)
{
    m_proj_matrix = proj_matrix;
}

glm::mat4 CgSceneGraph::trackballRotation() const
{
    return m_trackball_rotation;
}

void CgSceneGraph::setTrackballRotation(const glm::mat4 &trackball_rotation)
{
    m_trackball_rotation = trackball_rotation;
}
