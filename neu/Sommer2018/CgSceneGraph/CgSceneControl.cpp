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
#include <CgEvents/CgSubdivisionEvent.h>
#include <CgEvents/CgValueChangedEvent.h>
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

    m_cylinder = new CgCylinder(idGen->getNextId(), 50, 0.3, 0.2);
    colorObjects.push_back(m_cylinder);

    m_cylinder_normals = m_cylinder->getPolylineNormals();

    m_rotation_curve = new CgLine(idGen->getNextId());
    m_rotation_curve->setRotationCurveExample1();
    colorObjects.push_back(m_rotation_curve);

    m_rotation_body = new CgRotationBody(idGen->getNextId(), m_rotation_curve, 50);
    colorObjects.push_back(m_rotation_body);

    m_loaded_object= new CgTriangles(idGen->getNextId());
    colorObjects.push_back(m_loaded_object);

    m_loaded_object_normals = m_loaded_object->getPolylineNormals();
}


CgSceneControl::~CgSceneControl()
{
    m_coordinate_system.clear();
    delete m_cube;
    m_cube_normals->clear();
    delete m_cylinder;
    m_cylinder_normals->clear();
    delete m_rotation_curve;
    delete m_rotation_body;
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

    m_renderer->init(m_cylinder);

    for(CgLine* poly : *m_cylinder_normals){
        m_renderer->init(poly);
    }

    m_renderer->init(m_rotation_curve);

    m_renderer->init(m_rotation_body);

    m_renderer->init(m_loaded_object);
}


void CgSceneControl::renderObjects()
{
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

    /* cylinder  */
    if(m_cylinder->getDisplay()){
        m_renderer->setUniformValue("mycolor",glm::vec4(m_cylinder->getColor(),0.5f));
        m_renderer->render(m_cylinder);
    }


    /* cylinderNormals  */
    for(CgLine* poly : *m_cylinder_normals){
        if(poly->getDisplay()){
            m_renderer->setUniformValue("mycolor",glm::vec4(poly->getColor(),0.5f));
            m_renderer->render(poly);
        }

    }

    if(m_rotation_curve->getDisplay()){
        m_renderer->setUniformValue("mycolor",glm::vec4(m_rotation_curve->getColor(),0.5f));
        m_renderer->render(m_rotation_curve);
    }

    //m_rotation_body->setDisplay(true); //TODO delete

    if(m_rotation_body->getDisplay()){
        m_renderer->setUniformValue("mycolor",glm::vec4(m_rotation_body->getColor(),0.5f));
        m_renderer->render(m_rotation_body);
    }

    /* loadedObject  */
    if(m_loaded_object->getDisplay()) {
        m_renderer->setUniformValue("mycolor",glm::vec4(m_loaded_object->getColor(),0.5f));
        m_renderer->render(m_loaded_object);
    }

    if(renderLoadedObjectNormals){
        for(CgLine* poly : *m_loaded_object_normals){
            m_renderer->setUniformValue("mycolor",glm::vec4(poly->getColor(),0.5f));
            m_renderer->render(poly);
        }
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
        m_proj_matrix=glm::perspective(45.0f, (float)(ev->w()) / ev->h(), 0.01f, 100.0f);
    }

    if(e->getType() == Cg::CgLoadObjFileEvent)
    {
        CgLoadObjFileEvent* ev = (CgLoadObjFileEvent*)e;
        m_loaded_object->init(ev->FileName());
        m_renderer->init(m_loaded_object);

        m_loaded_object_normals = m_loaded_object->getPolylineNormals();
        for(CgLine* poly : *m_loaded_object_normals){
            m_renderer->init(poly);
        }
        m_renderer->redraw();
    }

    if(e->getType() == Cg::CgColorChangeEvent){
        CgColorChangeEvent* ev = (CgColorChangeEvent*) e;
        glm::vec3 customColor = glm::vec3((float)(ev->getRed() * 0.01f), (float)(ev->getGreen() * 0.01f), (float)(ev->getBlue() * 0.01f));

        for(CgBaseRenderableObject* obj : colorObjects){
            if(obj->getType() == Cg::TriangleMesh){
                CgTriangleMesh* o = (CgTriangleMesh*) obj;
                o->setColor(customColor);
            }else if(obj->getType() == Cg::Polyline){
                CgPolyline* o = (CgPolyline*) obj;
                o->setColor(customColor);
            }
        }
        m_renderer->redraw();
    }

    if(e->getType() == Cg::CgObjectSelectionChangeEvent){
        CgObjectSelectionChangeEvent *ev = (CgObjectSelectionChangeEvent*) e;

        for(CgLine* poly : m_coordinate_system){                    //coordinateSystem
            poly->setDisplay(ev->getRenderCoordinateSystem());
        }
        m_cube->setDisplay(ev->getRenderCube());                    //cube
        for(CgLine* poly : *m_cube_normals){                        //cubeNormals
            poly->setDisplay(ev->getRenderCubeNormals());
        }
        m_cylinder->setDisplay(ev->getRenderCylinder());            //cylinder
        for(CgLine* poly : *m_cylinder_normals){                    //cylinderNormals
            poly->setDisplay(ev->getRenderCylinderNormals());
        }
        m_rotation_curve->setDisplay(ev->getRenderRotationCurve()); //rotationCurve
        m_rotation_body->setDisplay(ev->getRenderRotationBody());   //rotationBody

        m_loaded_object->setDisplay(ev->getRenderLoadedObject());   //loadedObject

        renderLoadedObjectNormals = ev->getRenderLoadedObjectNormals();
        m_renderer->redraw();
    }

    if(e->getType() == Cg::CgValueChangedEvent){
        CgValueChangedEvent* ev = (CgValueChangedEvent*) e;

        if(ev->getCylinderChanged()){
            if(ev->getValueAmountOfSegmentsCylinder() >= 2 && ev->getValueHeightCylinder() >= 0 && ev->getValueRadiusCylinder() >= 0){
                m_cylinder->makeCylinder(ev->getValueAmountOfSegmentsCylinder(), ev->getValueHeightCylinder(), ev->getValueRadiusCylinder());
                m_renderer->init(m_cylinder);
                m_cylinder_normals = m_cylinder->getPolylineNormals();
                for(CgLine* poly : *m_cylinder_normals){
                    m_renderer->init(poly);
                }
            }
        }

        if(ev->getResetRotationCurve()){
            m_rotation_curve->setRotationCurveExample1();
            m_renderer->init(m_rotation_curve);
        }

        if(ev->getRotationBodyChanged()){
            m_rotation_body->makeRotationBody(m_rotation_curve, ev->getValueAmountOfSegmentsRotationBody());
            m_renderer->init(m_rotation_body);
        }

        m_renderer->redraw();
    }

    if(e->getType() == Cg::CgSubdivisionEvent){
        CgSubdivisionEvent* ev = (CgSubdivisionEvent*) e;

        if(ev->getForPointScheme()){
            m_rotation_curve->sdForPointScheme();
            m_renderer->init(m_rotation_curve);
        }
        m_renderer->redraw();
    }

    delete e;


}
