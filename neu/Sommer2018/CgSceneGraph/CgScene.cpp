#include "CgCube.h"
#include "CgScene.h"

#include <CgUtils/CgUtils.h>



CgScene::CgScene(CgBaseRenderer *renderer):
    m_renderer(renderer),
    m_scene(new CgSceneGraphEntity),
    idGen(IdSingleton::instance())
{
    initObjects();

    initChairWithPerson();
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
    //objects
    m_cube = new CgCube(idGen->getNextId());
    m_cylinder = new CgCylinder(idGen->getNextId(),50,1.0,0.1);
    m_sitting_person = new CgTriangles(idGen->getNextId());

    //init loaded objects
    std::string pathSittingPerson = CgU::getParentDirectory();
    pathSittingPerson.append("/Sommer2018/CgData/Man_sitting.obj");
    m_sitting_person->init(pathSittingPerson);


    //init at renderer
    m_renderer->init(m_cube);
    m_renderer->init(m_cylinder);
    m_renderer->init(m_sitting_person);
}

void CgScene::initChairWithPerson()
{
    CgSceneGraphEntity* personE = new CgSceneGraphEntity();
    setEntityRelationship(m_scene, personE);

    personE->addObject(m_sitting_person);


}

void CgScene::setEntityRelationship(CgSceneGraphEntity *parent, CgSceneGraphEntity *child)
{
    parent->addChild(child);
    child->setParent(parent);
}

CgSceneGraphEntity *CgScene::getScene()
{
    return m_scene;
}
