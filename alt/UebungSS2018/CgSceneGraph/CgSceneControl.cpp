#include "CgSceneControl.h"
#include "CgBase/CgEnums.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgEvents/CgColorChangeEvent.h"
#include "CgEvents/CgObjectSelectionChangeEvent.h"
#include "CgEvents/CgValueChangedEvent.h"
#include "CgBase/CgBaseRenderer.h"
#include "CgTriangles.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <CgEvents/CgResetEvent.h>
#include <CgEvents/CgSubdivisionEvent.h>

CgSceneControl::CgSceneControl()
{
    idGen = IdSingleton::instance();

    //Coordinatesystem
    x_Axis = new CgPolyline(idGen->getNextId());
    x_Axis->addVertice(glm::vec3(0.0,0.0,0.0));
    x_Axis->addVertice(glm::vec3(1.0,0.0,0.0));

    y_Axis = new CgPolyline(idGen->getNextId());
    y_Axis->addVertice(glm::vec3(0.0,0.0,0.0));
    y_Axis->addVertice(glm::vec3(0.0,1.0,0.0));

    z_Axis = new CgPolyline(idGen->getNextId());
    z_Axis->addVertice(glm::vec3(0.0,0.0,0.0));
    z_Axis->addVertice(glm::vec3(0.0,0.0,1.0));

    //Objects displayed
    renderCoordinateSystem = true;
    renderCube = false;
    renderCubeNormals = false;
    renderCylinder = false;
    renderCylinderNormals = false;
    renderRotationCurve = true;

    //Objects for rendering
    m_cube = new CgCube(idGen->getNextId());
    m_cube_normals = m_cube->getPolylineNormals();
    m_cylinder = new CgCylinder(idGen->getNextId(), 50, 0.5);
    m_cylinder_normals = m_cylinder->getPolylineNormals();

    m_rotationCurve = new CgPolyline(idGen->getNextId());
    m_rotationCurve->setRotationCurveExample1();


    //Matrix
    m_current_transformation=glm::mat4(1.);
    m_proj_matrix= glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));

    color= glm::vec3(100,40,1);
}


CgSceneControl::~CgSceneControl()
{
    delete x_Axis;
    delete y_Axis;
    delete z_Axis;

    delete m_cube;
    m_cube_normals->clear();
    delete m_cylinder;
    m_cylinder_normals->clear();

    delete m_rotationCurve;
}

void CgSceneControl::setRenderer(CgBaseRenderer* r)
{
    m_renderer=r;
    m_renderer->setSceneControl(this);

    //Coordinate-System
    m_renderer->init(x_Axis);
    m_renderer->init(y_Axis);
    m_renderer->init(z_Axis);

    //Cube
    m_renderer->init(m_cube);

    //CubeNormals
    for(CgPolyline* poly : *(m_cube_normals)){
        m_renderer->init(poly);
    }

    //Cylinder
    m_renderer->init(m_cylinder);

    //CylinderNormals
    for(CgPolyline* poly : *(m_cylinder_normals)){
        m_renderer->init(poly);
    }

    m_renderer->init(m_rotationCurve);
}


void CgSceneControl::renderObjects()
{
    m_renderer->setProjectionMatrix(m_proj_matrix);
    m_renderer->setLookAtMatrix(glm::mat4x4(glm::vec4(1.0, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.0, 0.0, 0.0), glm::vec4(0.0, 0.0, 1.0, -1.0), glm::vec4(0.0, 0.0, -1.0, 1.0)));

    //Coordinate-System
    if(renderCoordinateSystem){
        m_renderer->setUniformValue("mycolor", glm::vec4(1.0,0.0,0.0,0.5));
        m_renderer->render(x_Axis,m_current_transformation);
        m_renderer->setUniformValue("mycolor", glm::vec4(0.0,1.0,0.0,0.5));
        m_renderer->render(y_Axis,m_current_transformation);
        m_renderer->setUniformValue("mycolor", glm::vec4(0.0,0.0,1.0,0.5));
        m_renderer->render(z_Axis,m_current_transformation);
    }


    //Color for all objects
    m_renderer->setUniformValue("mycolor", glm::vec4(color.x * 0.01, color.y * 0.01, color.z * 0.01 ,1.0));

    //Cube
    if(renderCube){
        m_renderer->render(m_cube,m_current_transformation);
    }

    //CubeNormals
    if(renderCubeNormals){
        //Color for cube normals
        m_renderer->setUniformValue("mycolor", glm::vec4(1,0.01,0.5,1.0));
        for(CgPolyline* poly : *(m_cube_normals)){
            m_renderer->render(poly,m_current_transformation);
        }
        m_renderer->setUniformValue("mycolor", glm::vec4(color.x * 0.01, color.y * 0.01, color.z * 0.01 ,1.0));
    }

    //Cylinder
    if(renderCylinder){
        m_renderer->render(m_cylinder, m_current_transformation);
    }

    //CylinderNormals
    if(renderCylinderNormals){
        //Color for cylinder normals
        m_renderer->setUniformValue("mycolor", glm::vec4(1,0.01,0.5,1.0));
        for(CgPolyline* poly : *(m_cylinder_normals)){
            m_renderer->render(poly,m_current_transformation);
        }
        m_renderer->setUniformValue("mycolor", glm::vec4(color.x * 0.01, color.y * 0.01, color.z * 0.01 ,1.0));
    }

    if(renderRotationCurve){
        m_renderer->render(m_rotationCurve, m_current_transformation);
    }


}



void CgSceneControl::handleEvent(CgBaseEvent* e)
{


    if(e->getType() & Cg::CgMouseEvent)
    {
        //CgMouseEvent* ev = (CgMouseEvent*)e;
        //std::cout << *ev << std::endl;
    }

    if(e->getType() & Cg::CgKeyEvent)
    {
        /*CgKeyEvent* ev = (CgKeyEvent*) e;
        std::cout << *(ev) << std::endl;*/
        CgKeyEvent* ev = (CgKeyEvent*)e;
        //std::cout << *ev <<std::endl;

        if(ev->key() & Cg::Key_Escape){
            exit(0);
        }
    }

    if(e->getType() & Cg::WindowResizeEvent)
    {
        /*WindowResizeEvent* ev = (WindowResizeEvent*) e;
        std::cout << *(ev) << std::endl;*/
        CgWindowResizeEvent* ev = (CgWindowResizeEvent*)e;
        std::cout << *ev <<std::endl;
        m_proj_matrix=glm::perspective(45.0f, (float)(ev->w()) / ev->h(), 0.01f, 100.0f);
    }

    if(e->getType() & Cg::CgColorChangeEvent)
    {
        /*CgColorChangeEvent* ev = (CgColorChangeEvent*) e;
        std::cout << *(ev) << std::endl;*/
        CgColorChangeEvent* ev = (CgColorChangeEvent*)e;
        color = glm::vec3(ev->getRed(),ev->getGreen(),ev->getBlue());
        m_renderer->redraw();
    }

    if(e->getType() & Cg::CgObjectSelectionChangeEvent)
    {

        CgObjectSelectionChangeEvent* ev = (CgObjectSelectionChangeEvent*)e;
        /*std::cout << *(ev) << std::endl;*/
        renderCoordinateSystem = ev->getRenderCoordinateSystem();
        renderCube = ev->getRenderCube();
        renderCubeNormals = ev->getRenderCubeNormals();
        renderCylinder = ev->getRenderCylinder();
        renderCylinderNormals = ev->getRenderCylinderNormals();
        renderRotationCurve = ev->getRenderRotationCurve();
        m_renderer->redraw();
    }

    if(e->getType() & Cg::CgValueChangedEvent)
    {
        CgValueChangedEvent* ev = (CgValueChangedEvent*) e;
        /*std::cout << *(ev) << std::endl;*/
        m_cylinder_normals->clear();
        delete m_cylinder;
        m_cylinder = new CgCylinder(IdSingleton::instance()->getNextId(), ev->getValueAmountOfSegments(), ev->getValueHeight());
        m_renderer->init(m_cylinder);
        m_cylinder_normals = m_cylinder->getPolylineNormals();
        for(CgPolyline* poly : *(m_cylinder_normals)){
            m_renderer->init(poly);
        }
        m_renderer->redraw();
    }

    if(e->getType() & Cg::CgResetEvent)
    {
        /*CgResetEvent* ev = (CgResetEvent*) e;
        std::cout << *(ev) << std::endl;*/
        m_cylinder_normals->clear();
        delete m_cylinder;
        m_cylinder = new CgCylinder(IdSingleton::instance()->getNextId(), 50, 0.5);
        m_renderer->init(m_cylinder);
        m_cylinder_normals = m_cylinder->getPolylineNormals();
        for(CgPolyline* poly : *(m_cylinder_normals)){
            m_renderer->init(poly);
        }

        m_rotationCurve->setRotationCurveExample1();
        m_renderer->init(m_rotationCurve);

        m_renderer->redraw();
    }

    if(e->getType() & Cg::CgSubdivisionEvent){
        /*CgSubdivisionEvent* ev = (CgSubdivisionEvent*) e;
        std::cout << *(ev) << std::endl;*/

        m_rotationCurve->sdForPointScheme();
        m_renderer->init(m_rotationCurve);
        m_renderer->redraw();


    }
    delete e;
}
