#include "CgCube.h"
#include "CgScene.h"

#include <CgUtils/CgUtils.h>



CgScene::CgScene(CgBaseRenderer *renderer, std::vector<CgSceneGraphEntity*>* selectableEntitys):
    m_renderer(renderer),
    m_scene(new CgSceneGraphEntity),
    idGen(IdSingleton::instance()),
    selectableEntitys(selectableEntitys)
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
    selectableEntitys->push_back(chairE);

    CgSceneGraphEntity* chairLeg1E = new CgSceneGraphEntity(chairE);
    CgSceneGraphEntity* chairLeg2E = new CgSceneGraphEntity(chairE);
    CgSceneGraphEntity* chairLeg3E = new CgSceneGraphEntity(chairE);
    CgSceneGraphEntity* chairLeg4E = new CgSceneGraphEntity(chairE);

    CgSceneGraphEntity* chairSeatE = new CgSceneGraphEntity(chairE);
    CgSceneGraphEntity* chairBackE = new CgSceneGraphEntity(chairE);

    CgSceneGraphEntity* personE = new CgSceneGraphEntity(chairE);

    //ADDING OBJECTS
    chairLeg1E->addObject(m_cylinder);
    chairLeg2E->addObject(m_cylinder);
    chairLeg3E->addObject(m_cylinder);
    chairLeg4E->addObject(m_cylinder);

    chairSeatE->addObject(m_cube);
    chairBackE->addObject(m_cube);

    personE->addObject(m_sitting_person);

    //ADDING TRANSFORMATIONS
    chairLeg1E->addTransformation(CgU::tScaleMat(glm::vec3(0.15f,0.17f,0.15f)));
    chairLeg1E->addTransformation(CgU::tTranslateMat(glm::vec3(-0.1,0,-0.1)));
    chairLeg2E->addTransformation(CgU::tScaleMat(glm::vec3(0.15f,0.17f,0.15f)));
    chairLeg2E->addTransformation(CgU::tTranslateMat(glm::vec3(0.1,0,-0.1)));
    chairLeg3E->addTransformation(CgU::tScaleMat(glm::vec3(0.15f,0.17f,0.15f)));
    chairLeg3E->addTransformation(CgU::tTranslateMat(glm::vec3(-0.1,0,-0.275)));
    chairLeg4E->addTransformation(CgU::tScaleMat(glm::vec3(0.15f,0.17f,0.15f)));
    chairLeg4E->addTransformation(CgU::tTranslateMat(glm::vec3(0.1,0,-0.275)));

    chairSeatE->addTransformation(CgU::tScaleMat(glm::vec3(0.24f, 0.015f,0.2f)));
    chairSeatE->addTransformation(CgU::tTranslateMat(glm::vec3(0,0.17,-0.19)));

    chairBackE->addTransformation(CgU::tScaleMat(glm::vec3(0.24f, 0.24f, 0.015f)));
    chairBackE->addTransformation(CgU::tRotateMatX(-10));
    chairBackE->addTransformation(CgU::tTranslateMat(glm::vec3(0,0.29,-0.3)));

    personE->addTransformation(CgU::tScaleMat(glm::vec3(0.01f)));
}

CgSceneGraphEntity *CgScene::getScene()
{
    return m_scene;
}
