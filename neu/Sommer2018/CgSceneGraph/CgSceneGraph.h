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
    glm::mat4 m_current_transformation;
    glm::mat4 m_trackball_rotation;
    glm::mat4 m_lookAt_matrix;
    glm::mat4 m_proj_matrix;

    CgSceneGraphEntity* m_root_node;
    std::stack<glm::mat4> m_modelview_matrix_stack;

    void pushMatrix(){m_modelview_matrix_stack.push(m_modelview_matrix_stack.top());}
    void popMatrix(){m_modelview_matrix_stack.pop();}
    void applyTransform(glm::mat4 arg){m_modelview_matrix_stack.top() *= arg;}

    CgCube* cube;





public:
    CgSceneGraph(CgBaseRenderer *renderer);

    void render();

    glm::mat4 proj_matrix() const;
    void setProj_matrix(const glm::mat4 &proj_matrix);
    glm::mat4 trackball_rotation() const;
    void setTrackball_rotation(const glm::mat4 &trackball_rotation);
};

#endif // CGSCENEGRAPH_H
