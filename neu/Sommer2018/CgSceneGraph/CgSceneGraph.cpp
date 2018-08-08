#include "CgCube.h"
#include "CgSceneGraph.h"


glm::mat4 CgSceneGraph::proj_matrix() const
{
    return m_proj_matrix;
}

void CgSceneGraph::setProj_matrix(const glm::mat4 &proj_matrix)
{
    m_proj_matrix = proj_matrix;
}

glm::mat4 CgSceneGraph::trackball_rotation() const
{
    return m_trackball_rotation;
}

void CgSceneGraph::setTrackball_rotation(const glm::mat4 &trackball_rotation)
{
    m_trackball_rotation = trackball_rotation;
}

CgSceneGraph::CgSceneGraph(CgBaseRenderer *renderer):
    m_renderer(renderer)
{
    m_current_transformation=glm::mat4(1.);
    m_lookAt_matrix= glm::lookAt(glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    m_proj_matrix= glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
    m_trackball_rotation=glm::mat4(1.);

    idGen = IdSingleton::instance();

    cube = new CgCube(idGen->getNextId());

    m_renderer->init(cube);

}

void CgSceneGraph::render()
{

    m_renderer->setUniformValue("mycolor",glm::vec4(1.0f,1.0f,1.0f,1.0f));

    m_renderer->setUniformValue("matDiffuseColor",glm::vec4(0.35,0.31,0.09,1.0));
    m_renderer->setUniformValue("lightDiffuseColor",glm::vec4(1.0,1.0,1.0,1.0));

    m_renderer->setUniformValue("matAmbientColor",glm::vec4(0.25,0.22,0.06,1.0));
    m_renderer->setUniformValue("lightAmbientColor",glm::vec4(1.0,1.0,1.0,1.0));

    m_renderer->setUniformValue("matSpecularColor",glm::vec4(0.8,0.72,0.21,1.0));
    m_renderer->setUniformValue("lightSpecularColor",glm::vec4(1.0,1.0,1.0,1.0));



    glm::mat4 mv_matrix = m_lookAt_matrix * m_trackball_rotation * m_current_transformation ;
    glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(mv_matrix)));

    m_renderer->setUniformValue("projMatrix",m_proj_matrix);
    m_renderer->setUniformValue("modelviewMatrix",mv_matrix);
    m_renderer->setUniformValue("normalMatrix",normal_matrix);


    m_renderer->render(cube);
}
