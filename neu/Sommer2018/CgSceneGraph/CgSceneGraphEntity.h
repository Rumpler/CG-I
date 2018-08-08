#ifndef CGSCENEGRAPHENTITY_H
#define CGSCENEGRAPHENTITY_H

#include "CgAppearance.h"

#include <vector>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <CgBase/CgBaseRenderableObject.h>


class CgSceneGraphEntity
{
private:
    std::vector<CgBaseRenderableObject*> list_of_objects;
    glm::mat4 m_current_transformation;

    CgAppearance m_appearance;

    CgSceneGraphEntity* m_parent;
    std::vector<CgSceneGraphEntity*> m_children;

public:
    CgSceneGraphEntity();

    void addObject(CgBaseRenderableObject* arg);

    CgSceneGraphEntity *parent() const;
    void setParent(CgSceneGraphEntity *parent);
    glm::mat4 current_transformation() const;
    void setCurrent_transformation(const glm::mat4 &current_transformation);


    CgAppearance appearance() const;
    void setAppearance(const CgAppearance &appearance);
    std::vector<CgBaseRenderableObject *> getList_of_objects() const;
};

#endif // CGSCENEGRAPHENTITY_H
