#include "CgCube.h"
#include "CgScene.h"

#include <CgUtils/CgUtils.h>



CgScene::CgScene(CgBaseRenderer *renderer):
    m_renderer(renderer),
    m_scene(new CgSceneGraphEntity),
    idGen(IdSingleton::instance())
{
    std::cout << CgU::getCurrentDirectory() << std::endl;
    std::cout << CgU::getParentDirectory() << std::endl;


    CgCube* cube = new CgCube(idGen->getNextId());
    m_renderer->init(cube);
    m_scene->addObject(cube);

    initObjects();
}

CgScene::~CgScene()
{
    delete m_scene;
    delete m_cube;
    delete m_cylinder;
    delete m_sitting_person;
}

void CgScene::initObjects()
{
    m_cube = new CgCube(idGen->getNextId());
    m_cylinder = new CgCylinder(idGen->getNextId(),50,1.0,0.1);
    m_sitting_person = new CgTriangles(idGen->getNextId());


//    m_sitting_person->init("/home/gerrit/git/CG-I/neu/Sommer2018/CgData/Man_sitting.obj"); //TODO PATH

//    m_renderer->init(m_sitting_person);

//    m_scene->addObject(m_sitting_person);



}

void CgScene::initChairWithPerson()
{

}

CgSceneGraphEntity *CgScene::getScene()
{
    return m_scene;
}
