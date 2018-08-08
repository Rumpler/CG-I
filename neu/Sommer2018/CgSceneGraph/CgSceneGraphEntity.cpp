#include "CgSceneGraphEntity.h"

CgSceneGraphEntity::CgSceneGraphEntity()
{
    m_current_transformation = glm::mat4(1.0f);
    m_appearance = new CgAppearance();
}

CgSceneGraphEntity::~CgSceneGraphEntity()
{
    delete m_appearance;
}


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

void CgSceneGraphEntity::setCurrentTransformation(const glm::mat4 &current_transformation)
{
    m_current_transformation = current_transformation;
}

void CgSceneGraphEntity::addObject(CgBaseRenderableObject * obj)
{
    m_objects.push_back(obj);
}

void CgSceneGraphEntity::addChild(CgSceneGraphEntity *child)
{
    m_children.push_back(child);
}

CgAppearance* CgSceneGraphEntity::appearance() const
{
    return m_appearance;
}

void CgSceneGraphEntity::setAppearance(CgAppearance* appearance)
{
    m_appearance = appearance;
}

std::vector<CgBaseRenderableObject *> CgSceneGraphEntity::getObjects() const
{
    return m_objects;
}


std::vector<CgSceneGraphEntity *> CgSceneGraphEntity::getChildren() const
{
    return m_children;
}

glm::mat4 CgSceneGraphEntity::getCurrentTransformation() const
{
    return m_current_transformation;
}


