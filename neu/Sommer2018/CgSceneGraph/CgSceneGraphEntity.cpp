#include "CgSceneGraphEntity.h"

bool* CgSceneGraphEntity::renderObject()
{
    return &renderObjects;
}

void CgSceneGraphEntity::setRenderObjects(bool value)
{
    renderObjects = value;
}

bool CgSceneGraphEntity::getIsColorChangeable() const
{
    return colorChangeable;
}

void CgSceneGraphEntity::setIsColorChangeable(bool value)
{
    colorChangeable = value;
}

CgSceneGraphEntity::CgSceneGraphEntity()
{
    m_current_transformation = glm::mat4(1.0f);
    m_appearance = new CgAppearance();
}

CgSceneGraphEntity::CgSceneGraphEntity(CgSceneGraphEntity *parent)
{
    m_current_transformation = glm::mat4(1.0f);
    m_appearance = new CgAppearance();

    parent->addChild(this);
    this->setParent(parent);
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

void CgSceneGraphEntity::clearObjects()
{
    m_objects.clear();
}

void CgSceneGraphEntity::addChild(CgSceneGraphEntity *child)
{
    m_children.push_back(child);
}

void CgSceneGraphEntity::clearChildren()
{
    m_children.clear();
}

void CgSceneGraphEntity::addTransformation(glm::mat4 transformation)
{
    glm::mat4 mat = this->getCurrentTransformation();
    glm::vec3 translationVec =glm::vec3(mat[3].x, mat[3].y, mat[3].z);
    mat[3] = glm::vec4(glm::vec3(0.0f), mat[3].w);
    mat = mat * glm::inverse(mat) * transformation * mat;
    mat[3] = mat[3] + glm::vec4(translationVec, 0);
    this->setCurrentTransformation(mat);
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


