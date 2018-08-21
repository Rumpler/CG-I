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
    initTable();
    initChessBoard();
    initBox();

    m_scene->addTransformation(CgU::tTranslateMat(0,0,-1)); //TODO DELETE
    selectableEntitys->push_back(m_scene);
}

CgScene::~CgScene()
{
    delete m_scene;
    delete m_cube;
    delete m_cylinder;
    delete m_sitting_person;
    delete m_pawn;
    delete m_king;
    delete m_queen;
    delete m_knight;
    delete m_bishop;
    delete m_rook;
}

void CgScene::initObjects()
{
    //rotationCurve for rotationBody
    CgLine* curvePawn = new CgLine(idGen->getNextId());
    curvePawn->setPawnContour();
    for(int i = 0; i < 4; i++){ curvePawn->sdForPointScheme();  }

    //objects
    m_cube = new CgCube(idGen->getNextId());
    m_cylinder = new CgCylinder(idGen->getNextId(),50,1.0,0.1);
    m_sitting_person = new CgTriangles(idGen->getNextId());
    m_pawn = new CgRotationBody(idGen->getNextId(), curvePawn, 50);
    m_king = new CgTriangles(idGen->getNextId());
    m_queen = new CgTriangles(idGen->getNextId());
    m_knight = new CgTriangles(idGen->getNextId());
    m_bishop = new CgTriangles(idGen->getNextId());
    m_rook = new CgTriangles(idGen->getNextId());

    //init loaded objects
    std::string pathSittingPerson = CgU::getParentDirectory();
    pathSittingPerson.append("/Sommer2018/CgData/Man_sitting.obj");
    m_sitting_person->init(pathSittingPerson);

    std::string pathKing = CgU::getParentDirectory();
    pathKing.append("/Sommer2018/CgData/King.obj");
    m_king->init(pathKing);

    std::string pathQueen = CgU::getParentDirectory();
    pathQueen.append("/Sommer2018/CgData/Queen.obj");
    m_queen->init(pathQueen);

    std::string pathKnight = CgU::getParentDirectory();
    pathKnight.append("/Sommer2018/CgData/Knight.obj");
    m_knight->init(pathKnight);

    std::string pathBishop = CgU::getParentDirectory();
    pathBishop.append("/Sommer2018/CgData/Bishop.obj");
    m_bishop->init(pathBishop);

    std::string pathRook = CgU::getParentDirectory();
    pathRook.append("/Sommer2018/CgData/Rook.obj");
    m_rook->init(pathRook);

    //init at renderer
    m_renderer->init(m_cube);
    m_renderer->init(m_cylinder);
    m_renderer->init(m_sitting_person);
    m_renderer->init(m_pawn);
    m_renderer->init(m_king);
    m_renderer->init(m_queen);
    m_renderer->init(m_knight);
    m_renderer->init(m_king);
    m_renderer->init(m_bishop);
    m_renderer->init(m_rook);

    delete curvePawn;
}

void CgScene::initChairWithPerson()
{
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

    chairE->addTransformation(CgU::tTranslateMat(glm::vec3(0,0,-0.15)));
    selectableEntitys->push_back(chairE);
}

void CgScene::initTable()
{
    //ENTITYS
    CgSceneGraphEntity* tableE = new CgSceneGraphEntity(m_scene);

    CgSceneGraphEntity* tableBaseE = new CgSceneGraphEntity(tableE);
        CgSceneGraphEntity* tableLeg1E = new CgSceneGraphEntity(tableBaseE);
        CgSceneGraphEntity* tableLeg2E = new CgSceneGraphEntity(tableBaseE);
        CgSceneGraphEntity* tableLeg3E = new CgSceneGraphEntity(tableBaseE);
        CgSceneGraphEntity* tableLeg4E = new CgSceneGraphEntity(tableBaseE);

        CgSceneGraphEntity* tableBaseFrontE = new CgSceneGraphEntity(tableBaseE);
        CgSceneGraphEntity* tableBaseBacktE = new CgSceneGraphEntity(tableBaseE);
        CgSceneGraphEntity* tableBaseLeftE = new CgSceneGraphEntity(tableBaseE);
        CgSceneGraphEntity* tableBaseRightE = new CgSceneGraphEntity(tableBaseE);

    CgSceneGraphEntity* tableSurfaceE = new CgSceneGraphEntity(tableE);
        CgSceneGraphEntity* tableBoard1E = new CgSceneGraphEntity(tableSurfaceE);
        CgSceneGraphEntity* tableBoard2E = new CgSceneGraphEntity(tableSurfaceE);
        CgSceneGraphEntity* tableBoard3E = new CgSceneGraphEntity(tableSurfaceE);
        CgSceneGraphEntity* tableBoard4E = new CgSceneGraphEntity(tableSurfaceE);
        CgSceneGraphEntity* tableBoard5E = new CgSceneGraphEntity(tableSurfaceE);
        CgSceneGraphEntity* tableBoard6E = new CgSceneGraphEntity(tableSurfaceE);

    //ADDING OBJECTS
    tableLeg1E->addObject(m_cylinder);
    tableLeg2E->addObject(m_cylinder);
    tableLeg3E->addObject(m_cylinder);
    tableLeg4E->addObject(m_cylinder);

    tableBaseFrontE->addObject(m_cube);
    tableBaseBacktE->addObject(m_cube);
    tableBaseLeftE->addObject(m_cube);
    tableBaseRightE->addObject(m_cube);

    tableBoard1E->addObject(m_cube);
    tableBoard2E->addObject(m_cube);
    tableBoard3E->addObject(m_cube);
    tableBoard4E->addObject(m_cube);
    tableBoard5E->addObject(m_cube);
    tableBoard6E->addObject(m_cube);


    //ADDING TRANSFORMATIONS

    //legs
    tableLeg1E->addTransformation(CgU::tScaleMat(0.1,0.28,0.1));
    tableLeg1E->addTransformation(CgU::tTranslateMat(glm::vec3(0.2,0,0.2)));
    tableLeg2E->addTransformation(CgU::tScaleMat(0.1,0.28,0.1));
    tableLeg2E->addTransformation(CgU::tTranslateMat(glm::vec3(-0.2,0,0.2)));
    tableLeg3E->addTransformation(CgU::tScaleMat(0.1,0.28,0.1));
    tableLeg3E->addTransformation(CgU::tTranslateMat(glm::vec3(0.2,0,-0.2)));
    tableLeg4E->addTransformation(CgU::tScaleMat(0.1,0.28,0.1));
    tableLeg4E->addTransformation(CgU::tTranslateMat(glm::vec3(-0.2,0,-0.2)));

    //base
    tableBaseFrontE->addTransformation(CgU::tScaleMat(0.42,0.01,0.01));
    tableBaseFrontE->addTransformation(CgU::tTranslateMat(glm::vec3(0,0.28,0.2)));
    tableBaseBacktE->addTransformation(CgU::tScaleMat(0.42,0.01,0.01));
    tableBaseBacktE->addTransformation(CgU::tTranslateMat(glm::vec3(0,0.28,-0.2)));
    tableBaseLeftE->addTransformation(CgU::tScaleMat(0.01,0.01,0.42));
    tableBaseLeftE->addTransformation(CgU::tTranslateMat(glm::vec3(0.2,0.28,0)));
    tableBaseRightE->addTransformation(CgU::tScaleMat(0.01,0.01,0.42));
    tableBaseRightE->addTransformation(CgU::tTranslateMat(glm::vec3(-0.2,0.28,0)));

    //surface
    tableBoard1E->addTransformation(CgU::tScaleMat(0.5,0.01,0.06));
    tableBoard1E->addTransformation(CgU::tTranslateMat(glm::vec3(0,0,0.17)));
    tableBoard2E->addTransformation(CgU::tScaleMat(0.5,0.01,0.06));
    tableBoard2E->addTransformation(CgU::tTranslateMat(glm::vec3(0,0,0.1)));
    tableBoard3E->addTransformation(CgU::tScaleMat(0.5,0.01,0.06));
    tableBoard3E->addTransformation(CgU::tTranslateMat(glm::vec3(0,0,0.03)));
    tableBoard4E->addTransformation(CgU::tScaleMat(0.5,0.01,0.06));
    tableBoard4E->addTransformation(CgU::tTranslateMat(glm::vec3(0,0,-0.04)));
    tableBoard5E->addTransformation(CgU::tScaleMat(0.5,0.01,0.06));
    tableBoard5E->addTransformation(CgU::tTranslateMat(glm::vec3(0,0,-0.11)));
    tableBoard6E->addTransformation(CgU::tScaleMat(0.5,0.01,0.06));
    tableBoard6E->addTransformation(CgU::tTranslateMat(glm::vec3(0,0,-0.18)));

    tableSurfaceE->addTransformation(CgU::tTranslateMat(0,0.29,0));

    selectableEntitys->push_back(tableE);
}

void CgScene::initChessBoard()
{
    //ENTITYS
    CgSceneGraphEntity* chessBoardE = new CgSceneGraphEntity(m_scene);

    CgSceneGraphEntity* boardE = new CgSceneGraphEntity(chessBoardE);

    CgSceneGraphEntity* pawn1E = new CgSceneGraphEntity(chessBoardE);
    CgSceneGraphEntity* pawn2E = new CgSceneGraphEntity(chessBoardE);
    CgSceneGraphEntity* pawn3E = new CgSceneGraphEntity(chessBoardE);
    CgSceneGraphEntity* pawn4E = new CgSceneGraphEntity(chessBoardE);
    CgSceneGraphEntity* pawn5E = new CgSceneGraphEntity(chessBoardE);
    CgSceneGraphEntity* pawn6E = new CgSceneGraphEntity(chessBoardE);

    CgSceneGraphEntity* king1E = new CgSceneGraphEntity(chessBoardE);
    CgSceneGraphEntity* king2E = new CgSceneGraphEntity(chessBoardE);

    CgSceneGraphEntity* bishop1E = new CgSceneGraphEntity(chessBoardE);
    CgSceneGraphEntity* bishop2E = new CgSceneGraphEntity(chessBoardE);

    CgSceneGraphEntity* queen1E = new CgSceneGraphEntity(chessBoardE);
    CgSceneGraphEntity* knight1E = new CgSceneGraphEntity(chessBoardE);
    CgSceneGraphEntity* rook1E = new CgSceneGraphEntity(chessBoardE);

    //ADDING OBJECTS
    boardE->addObject(m_cube);
    pawn1E->addObject(m_pawn);
    pawn2E->addObject(m_pawn);
    pawn3E->addObject(m_pawn);
    pawn4E->addObject(m_pawn);
    pawn5E->addObject(m_pawn);
    pawn6E->addObject(m_pawn);
    king1E->addObject(m_king);
    king2E->addObject(m_king);
    bishop1E->addObject(m_bishop);
    bishop2E->addObject(m_bishop);
    queen1E->addObject(m_queen);
    knight1E->addObject(m_knight);
    rook1E->addObject(m_rook);

    //ADDING TRANSFORMATIONS
    boardE->addTransformation(CgU::tScaleMat(0.4, 0.01, 0.4));
    boardE->addTransformation(CgU::tTranslateMat(0,-0.005,0));
    pawn1E->addTransformation(CgU::tScaleMat(0.1,0.1,0.1));
    pawn1E->addTransformation(CgU::tTranslateMat(0.15,0,0.1));
    pawn2E->addTransformation(CgU::tScaleMat(0.1,0.1,0.1));
    pawn2E->addTransformation(CgU::tTranslateMat(0.08,0,0.1));
    pawn3E->addTransformation(CgU::tScaleMat(0.1,0.1,0.1));
    pawn3E->addTransformation(CgU::tTranslateMat(0.01,0,0.1));
    pawn4E->addTransformation(CgU::tScaleMat(0.1,0.1,0.1));
    pawn4E->addTransformation(CgU::tTranslateMat(-0.06,0,0.03));
    pawn5E->addTransformation(CgU::tScaleMat(0.1,0.1,0.1));
    pawn5E->addTransformation(CgU::tTranslateMat(-0.06,0,-0.11));
    pawn6E->addTransformation(CgU::tScaleMat(0.1,0.1,0.1));
    pawn6E->addTransformation(CgU::tTranslateMat(-0.13,0,-0.11));
    king1E->addTransformation(CgU::tScaleMat(0.05,0.05,0.05));
    king1E->addTransformation(CgU::tRotateMatX(-98));
    king1E->addTransformation(CgU::tRotateMatY(20));
    king1E->addTransformation(CgU::tTranslateMat(0.08,0,0.05));
    king2E->addTransformation(CgU::tScaleMat(0.05,0.05,0.05));
    king2E->addTransformation(CgU::tTranslateMat(-0.013,0,0.14));
    bishop1E->addTransformation(CgU::tScaleMat(0.05,0.05,0.05));
    bishop1E->addTransformation(CgU::tTranslateMat(-0.025,0,-0.18));
    bishop2E->addTransformation(CgU::tScaleMat(0.05,0.05,0.05));
    bishop2E->addTransformation(CgU::tTranslateMat(0.13,0,-0.07));
    queen1E->addTransformation(CgU::tScaleMat(0.05,0.05,0.05));
    queen1E->addTransformation(CgU::tTranslateMat(-0.15,0,0));
    knight1E->addTransformation(CgU::tScaleMat(0.05,0.05,0.05));
    knight1E->addTransformation(CgU::tTranslateMat(0.13,0,-0.18));

    rook1E->addTransformation(CgU::tScaleMat(0.05,0.05,0.05));
    rook1E->addTransformation(CgU::tTranslateMat(-0.15,0,0.14));

    chessBoardE->addTransformation(CgU::tTranslateMat(0,0.3,0));
    chessBoardE->addTransformation(CgU::tScaleMat(0.6,0.6,0.6));
    selectableEntitys->push_back(chessBoardE);
}

void CgScene::initBox()
{
    //ENTITYS
    CgSceneGraphEntity* boxE = new CgSceneGraphEntity(m_scene);

    CgSceneGraphEntity* boxBoxE = new CgSceneGraphEntity(boxE);
        CgSceneGraphEntity* boxFrontE = new CgSceneGraphEntity(boxBoxE);
        CgSceneGraphEntity* boxBackE = new CgSceneGraphEntity(boxBoxE);
        CgSceneGraphEntity* boxLeftE = new CgSceneGraphEntity(boxBoxE);
        CgSceneGraphEntity* boxRightE = new CgSceneGraphEntity(boxBoxE);
        CgSceneGraphEntity* boxBottomE = new CgSceneGraphEntity(boxBoxE);

    CgSceneGraphEntity* boxFiguresE = new CgSceneGraphEntity(boxE);
        CgSceneGraphEntity* boxQueenE = new CgSceneGraphEntity(boxFiguresE);
        CgSceneGraphEntity* boxPawnE = new CgSceneGraphEntity(boxFiguresE);
        CgSceneGraphEntity* boxRookE = new CgSceneGraphEntity(boxFiguresE);
        CgSceneGraphEntity* boxKnightE = new CgSceneGraphEntity(boxFiguresE);

    //ADDING OBJECTS
    boxFrontE->addObject(m_cube);
    boxBackE->addObject(m_cube);
    boxLeftE->addObject(m_cube);
    boxRightE->addObject(m_cube);
    boxBottomE->addObject(m_cube);

    boxQueenE->addObject(m_queen);
    boxPawnE->addObject(m_pawn);
    boxRookE->addObject(m_rook);
    boxKnightE->addObject(m_knight);


    //ADDING TRANSFORMATIONS

    //box
    boxFrontE->addTransformation(CgU::tScaleMat(0.2,0.1,0.01));
    boxFrontE->addTransformation(CgU::tTranslateMat(0,0.05,0.095));
    boxBackE->addTransformation(CgU::tScaleMat(0.2,0.1,0.01));
    boxBackE->addTransformation(CgU::tTranslateMat(0,0.05,-0.095));
    boxLeftE->addTransformation(CgU::tScaleMat(0.01,0.1,0.2));
    boxLeftE->addTransformation(CgU::tTranslateMat(-0.095,0.05,0));
    boxRightE->addTransformation(CgU::tScaleMat(0.01,0.1,0.2));
    boxRightE->addTransformation(CgU::tTranslateMat(0.095,0.05,0));
    boxBottomE->addTransformation(CgU::tScaleMat(0.2,0.01,0.2));
    boxBoxE->addTransformation(CgU::tTranslateMat(0,0.005,0));

    //figures
    boxFiguresE->addTransformation(CgU::tScaleMat(0.05,0.05,0.05));

    //TODO translate and rotate figures


    boxE->addTransformation(CgU::tTranslateMat(0,0,1)); //TODO delete or change
    selectableEntitys->push_back(boxE);
}

CgSceneGraphEntity *CgScene::getScene()
{
    return m_scene;
}
