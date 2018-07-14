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
#include <CgEvents/CgLoadEvent.h>
#include <CgEvents/CgResetEvent.h>
#include <CgEvents/CgSubdivisionEvent.h>
#include <CgEvents/CgTransformationEvent.h>
#include <CgUtils/ObjLoader.h>

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
    renderRotationCurve = false;
    renderRotationBody = false;
    renderLoadedObj = false;


    //Objects for rendering
    m_cube = new CgCube(idGen->getNextId());
    m_cube_normals = m_cube->getPolylineNormals();
    m_cylinder = new CgCylinder(idGen->getNextId(), 50, 0.5);
    m_cylinder_normals = m_cylinder->getPolylineNormals();

    m_rotation_curve = new CgPolyline(idGen->getNextId());
    m_rotation_curve->setRotationCurveExample1();

    m_rotation_body = new CgRotationBody(idGen->getNextId(), m_rotation_curve, 50);

    m_loaded_obj = new CgTriangles(idGen->getNextId());

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

    delete m_rotation_curve;
    delete m_rotation_body;
    delete m_loaded_obj;
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

    m_renderer->init(m_rotation_curve);

    m_renderer->init(m_rotation_body);

    m_renderer->init(m_loaded_obj);
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
        m_renderer->render(m_rotation_curve, m_current_transformation);
    }

    if(renderRotationBody){
        m_renderer->render(m_rotation_body, m_current_transformation);
    }

    if(renderLoadedObj){
        m_renderer->render(m_loaded_obj, m_current_transformation);
    }


}

void CgSceneControl::loadMeshObject(std::string file)
{
    /********************** OBJ Loader **********************/

    ObjLoader loader;
    loader.load(file);
    std::vector<glm::vec3> pos;
    loader.getPositionData(pos);
    std::vector<unsigned int> index;
    loader.getFaceIndexData(index);

    delete m_loaded_obj;
    m_loaded_obj = new CgTriangles(idGen->getNextId(), &pos, &index);
    m_renderer->init(m_loaded_obj);
    m_renderer->redraw();
}

void CgSceneControl::scale(glm::vec3 scale)
{
    m_current_transformation[0].x = m_current_transformation[0].x * scale.x;
    m_current_transformation[1].y = m_current_transformation[1].y * scale.y;
    m_current_transformation[2].z = m_current_transformation[2].z * scale.z;
}



void CgSceneControl::handleEvent(CgBaseEvent* e)
{


    if(e->getType() == Cg::CgMouseEvent)
    {
        //CgMouseEvent* ev = (CgMouseEvent*)e;
        //std::cout << *ev << std::endl;
    }

    if(e->getType() == Cg::CgKeyEvent || e->getType() == Cg::CgKeyPressEvent)
    {
        CgKeyEvent* ev = (CgKeyEvent*) e;
//        std::cout << *ev <<std::endl;

        if(ev->key() & Cg::Key_Escape){
            exit(0);
        }

        if(ev->key() == Cg::Key_Minus){
            scale(glm::vec3(0.9f));
            m_renderer->redraw();
        }

        if(ev->key() == Cg::Key_Plus){
            scale(glm::vec3(1.1f));
            m_renderer->redraw();
        }

    }


    if(e->getType() == Cg::WindowResizeEvent)
    {
        CgWindowResizeEvent* ev = (CgWindowResizeEvent*)e;
        m_proj_matrix=glm::perspective(45.0f, (float)(ev->w()) / ev->h(), 0.01f, 100.0f);
    }

    if(e->getType() == Cg::CgColorChangeEvent)
    {
        CgColorChangeEvent* ev = (CgColorChangeEvent*)e;
        color = glm::vec3(ev->getRed(),ev->getGreen(),ev->getBlue());
        m_renderer->redraw();
    }


    if(e->getType() == Cg::CgObjectSelectionChangeEvent)
    {

        CgObjectSelectionChangeEvent* ev = (CgObjectSelectionChangeEvent*)e;
        renderCoordinateSystem = ev->getRenderCoordinateSystem();
        renderCube = ev->getRenderCube();
        renderCubeNormals = ev->getRenderCubeNormals();
        renderCylinder = ev->getRenderCylinder();
        renderCylinderNormals = ev->getRenderCylinderNormals();
        renderRotationCurve = ev->getRenderRotationCurve();
        renderRotationBody = ev->getRenderRotationBody();
        renderLoadedObj = ev->getRenderLoadedObject();
        m_renderer->redraw();
    }

    if(e->getType() == Cg::CgValueChangedEvent)
    {
        CgValueChangedEvent* ev = (CgValueChangedEvent*) e;

        if(ev->getCylinderChanged()){
            m_cylinder_normals->clear();
            delete m_cylinder;
            m_cylinder = new CgCylinder(IdSingleton::instance()->getNextId(), ev->getValueAmountOfSegmentsCylinder(), ev->getValueHeightCylinder());
            m_renderer->init(m_cylinder);
            m_cylinder_normals = m_cylinder->getPolylineNormals();
            for(CgPolyline* poly : *(m_cylinder_normals)){
                m_renderer->init(poly);
            }
        }

        if(ev->getResetRotationCurve()){
            m_rotation_curve->setRotationCurveExample1();
            m_renderer->init(m_rotation_curve);
        }

        if(ev->getRotationBodyChanged()){
            delete m_rotation_body;
            m_rotation_body = new CgRotationBody(idGen->getNextId(), m_rotation_curve, ev->getValueAmountOfSegmentsRotationBody());
            m_renderer->init(m_rotation_body);
        }

        m_renderer->redraw();
    }


    if(e->getType() == Cg::CgResetEvent)
    {
        std::cout << "Empty Reset-Event called" << std::endl;
    }

    if(e->getType() == Cg::CgSubdivisionEvent){

        m_rotation_curve->sdForPointScheme();
        m_renderer->init(m_rotation_curve);
        m_renderer->redraw();


    }

    if(e->getType() == Cg::CgLoadEvent){
        CgLoadEvent *ev = (CgLoadEvent*) e;
        loadMeshObject(ev->getFilename());
    }

    if(e->getType() == Cg::CgTransformationEvent){
        std::cout << "CgTransformationEvent reached" << std::endl;

        CgTransformationEvent *ev = (CgTransformationEvent*) e;
        scale(ev->getScaleVec());
        m_renderer->redraw();
    }

    delete e;
}
