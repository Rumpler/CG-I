#ifndef CGSCENEGRAPH_H
#define CGSCENEGRAPH_H

#include "CgSceneGraphEntity.h"
#include <stack>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <CgBase/CgBaseRenderer.h>


class CgSceneGraph
{
private:
//    CgSceneGraphEntity* m_root_node;
//    std::stack<glm::mat4> m_modelview_matrix_stack;

//    void pushMatrix(){m_modelview_matrix_stack.push(m_modelview_matrix_stack.top());}
//    void popMatrix(){m_modelview_matrix_stack.pop();}
//    void applyTransform(glm::mat4 arg){m_modelview_matrix_stack.top() *= arg;}

public:
    CgSceneGraph();

    //void render(CgBaseRenderer* renderer);
};

#endif // CGSCENEGRAPH_H
