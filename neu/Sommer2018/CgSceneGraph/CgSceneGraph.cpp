#include "CgCube.h"
#include "CgSceneGraph.h"

#include <CgUtils/CgUtils.h>


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

CgSceneGraph::CgSceneGraph(CgBaseRenderer *renderer):
    m_renderer(renderer)
{
    m_mat_stack.push(glm::mat4(1.));

    //    m_current_transformation=glm::mat4(1.);
    m_lookAt_matrix= glm::lookAt(glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    m_proj_matrix= glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
    m_trackball_rotation=glm::mat4(1.);
    idGen = IdSingleton::instance();

    m_root_node = new CgSceneGraphEntity();


    //Objects
    CgLine* axis = new CgLine(idGen->getNextId());
    axis->addVertice(glm::vec3(0.0f,0.0f,0.0f));
    axis->addVertice(glm::vec3(1.0f,0.0f,0.0f));
    m_renderer->init(axis);


    /*********** coordinate system ***********/

    CgSceneGraphEntity* coordinateSystem = new CgSceneGraphEntity;
    coordinateSystem->setParent(m_root_node);
    m_root_node->addChild(coordinateSystem);

        m_mat_stack.push(m_mat_stack.top());

            CgSceneGraphEntity* xAxis = new CgSceneGraphEntity();
            xAxis->setParent(coordinateSystem);
            coordinateSystem->addChild(xAxis);
            xAxis->appearance()->setObjectColor(glm::vec3(1.0f, 0.0f, 0.0f));
            xAxis->addObject(axis);
            xAxis->setCurrentTransformation(m_mat_stack.top());

        m_mat_stack.pop();
        m_mat_stack.push(m_mat_stack.top() * CgU::rotateMatZ(90.0f));

            CgSceneGraphEntity* yAxis = new CgSceneGraphEntity();
            yAxis->setParent(coordinateSystem);
            coordinateSystem->addChild(yAxis);
            yAxis->appearance()->setObjectColor(glm::vec3(0.0f, 1.0f, 0.0f));
            yAxis->addObject(axis);
            yAxis->setCurrentTransformation(m_mat_stack.top());

        m_mat_stack.pop();
        m_mat_stack.push(m_mat_stack.top() * CgU::rotateMatY(-90.0f));

            CgSceneGraphEntity* zAxis = new CgSceneGraphEntity();
            zAxis->setParent(coordinateSystem);
            coordinateSystem->addChild(zAxis);
            zAxis->appearance()->setObjectColor(glm::vec3(0.0f, 0.0f, 1.0f));
            zAxis->addObject(axis);
            zAxis->setCurrentTransformation(m_mat_stack.top());

        m_mat_stack.pop();

    /*********** END coordinate system ***********/

}

void CgSceneGraph::render()
{
    m_renderer->setUniformValue("projMatrix",m_proj_matrix);
    recursiveRender(m_root_node);
}

void CgSceneGraph::recursiveRender(CgSceneGraphEntity *currentEntity)
{

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
