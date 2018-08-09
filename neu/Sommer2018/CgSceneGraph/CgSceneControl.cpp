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

}


CgSceneControl::~CgSceneControl()
{

}

void CgSceneControl::setRenderer(CgBaseRenderer* r)
{
    m_renderer = r;
    m_renderer->setSceneControl(this);
    m_scene_graph = new CgSceneGraph(m_renderer);
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

    m_scene_graph->render();
}

void CgSceneControl::handleEvent(CgBaseEvent* e)
{
    if(e->getType() == Cg::CgMouseButtonPress || e->getType() == Cg::CgMouseMove)
    {
        CgMouseEvent* ev = (CgMouseEvent*)e;
    }

    if(e->getType() == Cg::CgTrackballEvent)
    {
        CgTrackballEvent* ev = (CgTrackballEvent*)e;
        m_scene_graph->setTrackballRotation(ev->getRotationMatrix());
        m_renderer->redraw();

    }

    if(e->getType() == Cg::CgKeyPressEvent)
    {
        CgKeyEvent* ev = (CgKeyEvent*)e;
    }

    if(e->getType() == Cg::CgWindowResizeEvent)
    {
        CgWindowResizeEvent* ev = (CgWindowResizeEvent*)e;
        m_scene_graph->setProjectionMatrix(glm::perspective(45.0f, (float)(ev->w()) / ev->h(), 0.01f, 100.0f));
    }

    if(e->getType() == Cg::CgLoadObjFileEvent)
    {
        std::cout << "currently not implemented" << std::endl;
        CgLoadObjFileEvent* ev = (CgLoadObjFileEvent*)e;
//        m_loaded_object->init(ev->fileName());
//        m_renderer->init(m_loaded_object);

//        m_loaded_object_normals = m_loaded_object->getPolylineNormals();
//        for(CgLine* poly : *m_loaded_object_normals){
//            m_renderer->init(poly);
//        }
//        m_renderer->redraw();
    }

    if(e->getType() == Cg::CgColorChangeEvent)
    {
        std::cout << "currently not implemented" << std::endl;
        CgColorChangeEvent* ev = (CgColorChangeEvent*) e;
//        glm::vec3 customColor = glm::vec3((float)(ev->getRed() * 0.01f), (float)(ev->getGreen() * 0.01f), (float)(ev->getBlue() * 0.01f));

//        for(CgBaseRenderableObject* obj : colorObjects){
//            if(obj->getType() == Cg::TriangleMesh){
//                CgTriangleMesh* o = (CgTriangleMesh*) obj;
//                o->setColor(customColor);
//            }else if(obj->getType() == Cg::Polyline){
//                CgPolyline* o = (CgPolyline*) obj;
//                o->setColor(customColor);
//            }
//        }
//        m_renderer->redraw();
    }

    if(e->getType() == Cg::CgObjectSelectionChangeEvent)
    {
        std::cout << "currently not implemented" << std::endl;
        CgObjectSelectionChangeEvent *ev = (CgObjectSelectionChangeEvent*) e;

//        for(CgLine* poly : m_coordinate_system){                    //coordinateSystem
//            poly->setDisplay(ev->getRenderCoordinateSystem());
//        }
//        m_cube->setDisplay(ev->getRenderCube());                    //cube
//        for(CgLine* poly : *m_cube_normals){                        //cubeNormals
//            poly->setDisplay(ev->getRenderCubeNormals());
//        }
//        m_cylinder->setDisplay(ev->getRenderCylinder());            //cylinder
//        for(CgLine* poly : *m_cylinder_normals){                    //cylinderNormals
//            poly->setDisplay(ev->getRenderCylinderNormals());
//        }
//        m_rotation_curve->setDisplay(ev->getRenderRotationCurve()); //rotationCurve
//        m_rotation_body->setDisplay(ev->getRenderRotationBody());   //rotationBody

//        for(CgLine* poly : *m_rotation_body_normals){               //rotationBodyNormals
//            poly->setDisplay(ev->getRenderRotationBodyNormals());
//        }

//        m_loaded_object->setDisplay(ev->getRenderLoadedObject());   //loadedObject

//        renderLoadedObjectNormals = ev->getRenderLoadedObjectNormals();
        m_renderer->redraw();
    }

    if(e->getType() == Cg::CgValueChangedEvent)
    {
        std::cout << "currently not implemented" << std::endl;
        CgValueChangedEvent* ev = (CgValueChangedEvent*) e;

//        if(ev->getCylinderChanged()){
//            if(ev->getValueAmountOfSegmentsCylinder() >= 2 && ev->getValueHeightCylinder() >= 0 && ev->getValueRadiusCylinder() >= 0){
//                m_cylinder->makeCylinder(ev->getValueAmountOfSegmentsCylinder(), ev->getValueHeightCylinder(), ev->getValueRadiusCylinder());
//                m_renderer->init(m_cylinder);
//                m_cylinder_normals = m_cylinder->getPolylineNormals();
//                for(CgLine* poly : *m_cylinder_normals){
//                    m_renderer->init(poly);
//                }
//            }
//        }

//        if(ev->getResetRotationCurve()){
//            m_rotation_curve->setRotationCurveExample1();
//            m_renderer->init(m_rotation_curve);
//        }

//        if(ev->getRotationBodyChanged()){
//            m_rotation_body_normals->clear();
//            m_rotation_body->makeRotationBody(m_rotation_curve, ev->getValueAmountOfSegmentsRotationBody());
//            m_renderer->init(m_rotation_body);
//            for(CgLine* poly : *m_rotation_body_normals){
//                m_renderer->init(poly);
//            }
//        }

        m_renderer->redraw();
    }

    if(e->getType() == Cg::CgSubdivisionEvent){
        std::cout << "currently not implemented" << std::endl;
        CgSubdivisionEvent* ev = (CgSubdivisionEvent*) e;

//        if(ev->getForPointScheme()){
//            m_rotation_curve->sdForPointScheme();
//            m_renderer->init(m_rotation_curve);
//        }
        m_renderer->redraw();
    }

    delete e;


}
