#ifndef CGSCENE_H
#define CGSCENE_H

#include "CgCube.h"
#include "CgCylinder.h"
#include "CgRotationBody.h"
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

    std::vector<CgSceneGraphEntity*>* selectableEntitys;


    //Objects
    CgCube *m_cube;
    CgCylinder *m_cylinder;
    CgTriangles *m_sitting_person;
    CgRotationBody* m_pawn;
    CgTriangles* m_king;
    CgTriangles* m_queen;
    CgTriangles* m_knight;
    CgTriangles* m_bishop;

    //Entitys
    CgSceneGraphEntity *m_chair_E;



    //Methodes
    void initObjects();
    void initChairWithPerson();
    void initTable();
    void initChessBoard();

public:
    CgScene(CgBaseRenderer *renderer, std::vector<CgSceneGraphEntity*>* selectableEntitys);
    ~CgScene();

    CgSceneGraphEntity *getScene();
};

#endif // CGSCENE_H
