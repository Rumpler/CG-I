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
    glm::mat4 transformMat = glm::mat4(1.0f);


    //ENTITYS
    CgSceneGraphEntity* chairE = new CgSceneGraphEntity(m_scene);

    CgSceneGraphEntity* chairLeg1E = new CgSceneGraphEntity(chairE);
    CgSceneGraphEntity* chairLeg2E = new CgSceneGraphEntity(chairE);
    CgSceneGraphEntity* chairLeg3E = new CgSceneGraphEntity(chairE);
    CgSceneGraphEntity* chairLeg4E = new CgSceneGraphEntity(chairE);

    CgSceneGraphEntity* chairSeatE = new CgSceneGraphEntity(chairE);
    CgSceneGraphEntity* chairBackE = new CgSceneGraphEntity(chairE);

    CgSceneGraphEntity* personE = new CgSceneGraphEntity(chairE);

    //ADDING OBJECTS
    chairLeg1E->addObject(m_cylinder);
//    chairLeg2E->addObject(m_cylinder);
//    chairLeg3E->addObject(m_cylinder);
//    chairLeg4E->addObject(m_cylinder);

//    chairSeatE->addObject(m_cube);
//    chairBackE->addObject(m_cube);

    personE->addObject(m_sitting_person);

    //ADDING TRANSFORMATIONS
    transformMat = /*CgU::tScaleMat(glm::vec3(0.15f)) **/ CgU::tTranslateMat(glm::vec3(0,0,-0.5f));
    chairLeg1E->setCurrentTransformation(transformMat);




    transformMat = CgU::tScaleMat(glm::vec3(0.01f));
    personE->setCurrentTransformation(transformMat);


}

CgSceneGraphEntity *CgScene::getScene()
{
    return m_scene;
}
