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
    CgSceneGraphEntity* m_parent;
    std::vector<CgBaseRenderableObject*> m_objects;
    std::vector<CgSceneGraphEntity*> m_children;

    glm::mat4 m_current_transformation = glm::mat4(1.0f);
    CgAppearance* m_appearance;

    bool renderObjects = true;
    bool colorChangeable = true;

public:
    CgSceneGraphEntity();
    CgSceneGraphEntity(CgSceneGraphEntity* parent);
    ~CgSceneGraphEntity();

    void addObject(CgBaseRenderableObject* obj);
    void clearObjects();
    void addChild(CgSceneGraphEntity* child);
    void clearChildren();

    void addTransformation(glm::mat4 transformation);

    CgSceneGraphEntity *parent() const;
    void setParent(CgSceneGraphEntity *parent);
    glm::mat4 current_transformation() const;
    void setCurrentTransformation(const glm::mat4 &current_transformation);
    glm::mat4 getCurrentTransformation() const;
    CgAppearance* appearance() const;
    void setAppearance(CgAppearance* appearance);

    std::vector<CgBaseRenderableObject *> getObjects() const;
    std::vector<CgSceneGraphEntity *> getChildren() const;

    bool* renderObject();
    void setRenderObjects(bool value);
    bool getIsColorChangeable() const;
    void setIsColorChangeable(bool value);
};

#endif // CGSCENEGRAPHENTITY_H
