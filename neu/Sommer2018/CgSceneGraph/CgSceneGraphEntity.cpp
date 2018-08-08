#include "CgSceneGraphEntity.h"

CgSceneGraphEntity *CgSceneGraphEntity::parent() const
{
    return m_parent;
}

void CgSceneGraphEntity::setParent(CgSceneGraphEntity *parent)
{
    m_parent = parent;
}

glm::mat4 CgSceneGraphEntity::current_transformation() const
{
    return m_current_transformation;
}

void CgSceneGraphEntity::setCurrent_transformation(const glm::mat4 &current_transformation)
{
    m_current_transformation = current_transformation;
}

void CgSceneGraphEntity::addObject(CgBaseRenderableObject * arg)
{
    list_of_objects.push_back(arg);
}

CgAppearance CgSceneGraphEntity::appearance() const
{
    return m_appearance;
}

void CgSceneGraphEntity::setAppearance(const CgAppearance &appearance)
{
    m_appearance = appearance;
}

std::vector<CgBaseRenderableObject *> CgSceneGraphEntity::getList_of_objects() const
{
    return list_of_objects;
}


CgSceneGraphEntity::CgSceneGraphEntity()
{

}
