#include "CgSceneControl.h"
#include "CgBase/CgEnums.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgEvents/CgLoadObjFileEvent.h"
#include "CgEvents/CgTrackballEvent.h"
#include "CgBase/CgBaseRenderer.h"
#include "CgTriangles.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <CgEvents/CgColorChangeEvent.h>
#include <CgEvents/CgObjectSelectionChangedEvent.h>
#include <CgUtils/CgUtils.h>
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

    m_cube = new CgCube(idGen->getNextId());
    colorObjects.push_back(m_cube);

    m_cube_normals = m_cube->getPolylineNormals();

    m_loaded_object= new CgTriangles(idGen->getNextId());
    colorObjects.push_back(m_loaded_object);
}


CgSceneControl::~CgSceneControl()
{
    m_coordinate_system.clear();
    delete m_cube;
    m_cube_normals->clear();
    delete m_loaded_object;
}

void CgSceneControl::setRenderer(CgBaseRenderer* r)
{
    m_renderer = r;
    m_renderer->setSceneControl(this);

    for(CgLine* poly : m_coordinate_system){
        m_renderer->init(poly);
    }

    m_renderer->init(m_cube);

    for(CgLine* poly : *m_cube_normals){
        m_renderer->init(poly);
    }

    m_renderer->init(m_loaded_object);
}


void CgSceneControl::renderObjects()
{

    // Materialeigenschaften setzen
    // sollte ja eigentlich pro Objekt unterschiedlich sein können, naja bekommen sie schon hin....

    //    m_renderer->setUniformValue("mycolor",glm::vec4(1.0,0.0,0.0,1.0));
    m_renderer->setUniformValue("mycolor",glm::vec4(1.0f,1.0f,1.0f,1.0f));

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


    /* coordinatesystem  */
    for(CgLine* poly : m_coordinate_system){
        if(poly->getDisplay()){
            m_renderer->setUniformValue("mycolor",glm::vec4(poly->getColor(),0.5f));
            m_renderer->render(poly);
        }
    }

    /* cube  */
    if(m_cube->getDisplay()){
        m_renderer->setUniformValue("mycolor",glm::vec4(m_cube->getColor(),1.0f));
        m_renderer->render(m_cube);
    }

    /* cubeNormals  */
    for(CgLine* poly : *m_cube_normals){
        if(poly->getDisplay()){
            m_renderer->setUniformValue("mycolor",glm::vec4(poly->getColor(),1.0f));
            m_renderer->render(poly);
        }
    }

    /* loadedObject  */
    if(m_loaded_object->getDisplay()) {
        m_renderer->setUniformValue("mycolor",glm::vec4(m_loaded_object->getColor(),0.5f));
        m_renderer->render(m_loaded_object);
    }
}

void CgSceneControl::initCoordinateSystem()
{
    //X
    CgLine* axis = new CgLine(idGen->getNextId());
    axis->addVertice(glm::vec3(0.0f,0.0f,0.0f));
    axis->addVertice(glm::vec3(1.0f,0.0f,0.0f));
    axis->setColor(glm::vec3(1.0f,0.0f,0.0f));
    axis->setDisplay(true);
    m_coordinate_system.push_back(axis);
    //Y
    axis = new CgLine(idGen->getNextId());
    axis->addVertice(glm::vec3(0.0f,0.0f,0.0f));
    axis->addVertice(glm::vec3(0.0f,1.0f,0.0f));
    axis->setColor(glm::vec3(0.0f,1.0f,0.0f));
    axis->setDisplay(true);
    m_coordinate_system.push_back(axis);
    //Z
    axis = new CgLine(idGen->getNextId());
    axis->addVertice(glm::vec3(0.0f,0.0f,0.0f));
    axis->addVertice(glm::vec3(0.0f,0.0f,1.0f));
    axis->setColor(glm::vec3(0.0f,0.0f,1.0f));
    axis->setDisplay(true);
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
        m_loaded_object->init(ev->FileName());
        m_renderer->init(m_loaded_object);
        m_renderer->redraw();
    }

    if(e->getType() == Cg::CgColorChangeEvent){
        CgColorChangeEvent* ev = (CgColorChangeEvent*) e;
        glm::vec3 customColor = glm::vec3((float)(ev->getRed() * 0.01f), (float)(ev->getGreen() * 0.01f), (float)(ev->getBlue() * 0.01f));

        for(CgBaseRenderableObject* obj : colorObjects){
            std::cout <<  "Loop entered" << std::endl;
            if(obj->getType() == Cg::TriangleMesh){
                std::cout <<  "triangleMesh entered" << std::endl;
                CgTriangleMesh* o = (CgTriangleMesh*) obj;
                o->setColor(customColor);
            }else if(obj->getType() == Cg::Polyline){
                std::cout <<  "Polyline entered" << std::endl;
                CgPolyline* o = (CgPolyline*) obj;
                o->setColor(customColor);
            }
        }
        m_renderer->redraw();
    }

    if(e->getType() == Cg::CgObjectSelectionChangeEvent){
        CgObjectSelectionChangeEvent *ev = (CgObjectSelectionChangeEvent*) e;

        for(CgLine* poly : m_coordinate_system){
            poly->setDisplay(ev->getRenderCoordinateSystem());
        }

        m_cube->setDisplay(ev->getRenderCube());

        for(CgLine* poly : *m_cube_normals){
            poly->setDisplay(ev->getRenderCubeNormals());
        }

        m_loaded_object->setDisplay(ev->getRenderLoadedObject());

        m_renderer->redraw();
    }
    delete e;


}
