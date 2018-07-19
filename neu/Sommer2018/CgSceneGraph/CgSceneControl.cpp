#include "CgSceneControl.h"
#include "CgBase/CgEnums.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgEvents/CgLoadObjFileEvent.h"
#include "CgEvents/CgTrackballEvent.h"
#include "CgBase/CgBaseRenderer.h"
#include "CgExampleTriangle.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <CgEvents/CgColorChangeEvent.h>
#include <CgEvents/CgObjectSelectionChangedEvent.h>
#include "CgUtils/ObjLoader.h"
#include <string>

CgSceneControl::CgSceneControl()
{
    m_current_transformation=glm::mat4(1.);
    m_lookAt_matrix= glm::lookAt(glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    m_proj_matrix= glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
    m_trackball_rotation=glm::mat4(1.);

    idGen = IdSingleton::instance();


    initCoordinateSystem();
    m_triangle= new CgExampleTriangle(idGen->getNextId());
    m_cube = new CgCube(idGen->getNextId());
    m_cube_normals = m_cube->getPolylineNormals();
}


CgSceneControl::~CgSceneControl()
{
    m_coordinate_system.clear();
    delete m_triangle;
    delete m_cube;
    m_cube_normals->clear();
}

void CgSceneControl::setRenderer(CgBaseRenderer* r)
{
    m_renderer = r;
    m_renderer->setSceneControl(this);

    for(CgPolyline* poly : m_coordinate_system){
        m_renderer->init(poly);
    }

    m_renderer->init(m_triangle);

    m_renderer->init(m_cube);

    for(CgPolyline* poly : *m_cube_normals){
        m_renderer->init(poly);
    }
}


void CgSceneControl::renderObjects()
{

    // Materialeigenschaften setzen
    // sollte ja eigentlich pro Objekt unterschiedlich sein können, naja bekommen sie schon hin....

    m_renderer->setUniformValue("mycolor",glm::vec4(1.0,0.0,0.0,1.0));

    m_renderer->setUniformValue("matDiffuseColor",glm::vec4(0.35,0.31,0.09,1.0));
    m_renderer->setUniformValue("lightDiffuseColor",glm::vec4(1.0,1.0,1.0,1.0));

    m_renderer->setUniformValue("matAmbientColor",glm::vec4(0.25,0.22,0.06,1.0));
    m_renderer->setUniformValue("lightAmbientColor",glm::vec4(1.0,1.0,1.0,1.0));

    m_renderer->setUniformValue("matSpecularColor",glm::vec4(0.8,0.72,0.21,1.0));
    m_renderer->setUniformValue("lightSpecularColor",glm::vec4(1.0,1.0,1.0,1.0));


    glm::mat4 mv_matrix = m_lookAt_matrix * m_trackball_rotation* m_current_transformation ;
    glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(mv_matrix)));

    m_renderer->setUniformValue("projMatrix",m_proj_matrix);
    m_renderer->setUniformValue("modelviewMatrix",mv_matrix);
    m_renderer->setUniformValue("normalMatrix",normal_matrix);


    if(renderCoordinateSystem){
        for(CgPolyline* poly : m_coordinate_system){
            m_renderer->setUniformValue("mycolor",glm::vec4(poly->getColor(),0.5f));
            m_renderer->render(poly);
        }
    }

    if(renderTriangle) {
        m_renderer->setUniformValue("mycolor",glm::vec4(m_triangle->getColor(),0.5f));
        m_renderer->render(m_triangle);
    }

    if(renderCube){

        m_renderer->setUniformValue("mycolor",glm::vec4(m_cube->getColor(),1.0f));
        m_renderer->render(m_cube);
    }

    if(renderCubeNormals){
        for(CgPolyline* poly : *m_cube_normals){
            m_renderer->render(poly);
        }
    }


}

void CgSceneControl::initCoordinateSystem()
{
    //X
    CgPolyline* axis = new CgPolyline(idGen->getNextId());
    axis->addVertice(glm::vec3(0.0f,0.0f,0.0f));
    axis->addVertice(glm::vec3(1.0f,0.0f,0.0f));
    axis->setColor(glm::vec3(1.0f,0.0f,0.0f));
    m_coordinate_system.push_back(axis);
    //Y
    axis = new CgPolyline(idGen->getNextId());
    axis->addVertice(glm::vec3(0.0f,0.0f,0.0f));
    axis->addVertice(glm::vec3(0.0f,1.0f,0.0f));
    axis->setColor(glm::vec3(0.0f,1.0f,0.0f));
    m_coordinate_system.push_back(axis);
    //Z
    axis = new CgPolyline(idGen->getNextId());
    axis->addVertice(glm::vec3(0.0f,0.0f,0.0f));
    axis->addVertice(glm::vec3(0.0f,0.0f,1.0f));
    axis->setColor(glm::vec3(0.0f,0.0f,1.0f));
    m_coordinate_system.push_back(axis);
}



void CgSceneControl::handleEvent(CgBaseEvent* e)
{
//    std::cout << e->getType() << " reached" << std::endl;
//    std::cout << Cg::CgObjectSelectionChangeEvent << " estimated" << std::endl;

    if(e->getType() == Cg::CgMouseButtonPress || e->getType() == Cg::CgMouseMove)
    {
        CgMouseEvent* ev = (CgMouseEvent*)e;
        //        std::cout << *ev<< "called" << std::endl;
    }

    if(e->getType() == Cg::CgTrackballEvent)
    {
        CgTrackballEvent* ev = (CgTrackballEvent*)e;
        //        std::cout << *ev << std::endl;
        m_trackball_rotation=ev->getRotationMatrix();
        m_renderer->redraw();

    }

    if(e->getType() == Cg::CgKeyPressEvent)
    {
        CgKeyEvent* ev = (CgKeyEvent*)e;
//        std::cout << *ev <<std::endl;

        if(ev->text()=="+")
        {
            glm::mat4 scalemat;
            scalemat= glm::scale(scalemat,glm::vec3(1.2,1.2,1.2));
            m_current_transformation=m_current_transformation*scalemat;
            m_renderer->redraw();
        }
        if(ev->text()=="-")
        {
            glm::mat4 scalemat;
            scalemat= glm::scale(scalemat,glm::vec3(0.8,0.8,0.8));
            m_current_transformation=m_current_transformation*scalemat;
            m_renderer->redraw();
        }
    }

    if(e->getType() == Cg::CgWindowResizeEvent)
    {
        CgWindowResizeEvent* ev = (CgWindowResizeEvent*)e;
//        std::cout << *ev <<std::endl;
        m_proj_matrix=glm::perspective(45.0f, (float)(ev->w()) / ev->h(), 0.01f, 100.0f);
    }

    if(e->getType() == Cg::CgLoadObjFileEvent)
    {
        CgLoadObjFileEvent* ev = (CgLoadObjFileEvent*)e;
        ObjLoader* loader= new ObjLoader();
        loader->load(ev->FileName());
        std::cout << ev->FileName() << std::endl;
        std::vector<glm::vec3> pos;
        loader->getPositionData(pos);
        std::vector<glm::vec3> norm;
        loader->getNormalData(norm);
        std::vector<unsigned int> indx;
        loader->getFaceIndexData(indx);
        m_triangle->init(pos,norm,indx);
        m_renderer->init(m_triangle);
        m_renderer->redraw();
    }

    if(e->getType() == Cg::CgColorChangeEvent){
        CgColorChangeEvent* ev = (CgColorChangeEvent*) e;
        std::cout << *ev << std::endl;
        m_cube->setColor(glm::vec3(ev->getRed(), ev->getGreen(), ev->getBlue()));
        m_renderer->redraw();
    }

    if(e->getType() == Cg::CgObjectSelectionChangeEvent){
        CgObjectSelectionChangeEvent *ev = (CgObjectSelectionChangeEvent*) e;

        renderCoordinateSystem = ev->getRenderCoordinateSystem();
        renderCube = ev->getRenderCube();
        renderCubeNormals = ev->getRenderCubeNormals();

        m_renderer->redraw();
    }
    delete e;


}
