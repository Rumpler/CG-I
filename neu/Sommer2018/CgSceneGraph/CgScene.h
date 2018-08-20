#ifndef CGSCENE_H
#define CGSCENE_H

#include "CgCube.h"
#include "CgCylinder.h"
#include "CgSceneGraphEntity.h"
#include "CgTriangles.h"

#include <CgUtils/IdSingleton.h>

#include <CgBase/CgBaseRenderer.h>



class CgScene
{
private:
    CgBaseRenderer *m_renderer;
    CgSceneGraphEntity* m_scene;
    IdSingleton* idGen;


    //Objects
    CgCube *m_cube;
    CgCylinder *m_cylinder;
    CgTriangles *m_sitting_person;

    //Entitys
    CgSceneGraphEntity *m_chair_E;



    //Methodes
    void initObjects();
    void initChairWithPerson();



    void setEntityRelationship(CgSceneGraphEntity* parent, CgSceneGraphEntity* child);

public:
    CgScene(CgBaseRenderer *renderer);
    ~CgScene();

    CgSceneGraphEntity *getScene();
};

#endif // CGSCENE_H
