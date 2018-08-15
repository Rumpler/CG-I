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
#include <CgEvents/CgButtonEvent.h>
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

        if(ev->key() == Cg::Key_N){
            m_scene_graph->selectNextEnitiy();
        }
        if(ev->key() == Cg::Key_Minus){
            m_scene_graph->tScaleSelectedEntity(glm::vec3(0.9f,0.9f,0.9f));
        }
        if(ev->key() == Cg::Key_Plus){
            m_scene_graph->tScaleSelectedEntity(glm::vec3(1.1f,1.1f,1.1f));
        }
        if(ev->key() == Cg::Key_X){
            m_scene_graph->tRotateSelectedEntity(45.0, 'x');
        }
        if(ev->key() == Cg::Key_Y){
            m_scene_graph->tRotateSelectedEntity(45.0, 'y');
        }
        if(ev->key() == Cg::Key_Z){
            m_scene_graph->tRotateSelectedEntity(45.0, 'z');
        }
        if(ev->key() == Cg::Key_C){
            m_scene_graph->tRotateSelectedEntity(45.0, rotateVec);
        }
        if(ev->key() == Cg::Key_T){
            m_scene_graph->tTranslateSelectedEntity(transVec);
        }
    }

    if(e->getType() == Cg::CgWindowResizeEvent)
    {
        CgWindowResizeEvent* ev = (CgWindowResizeEvent*)e;
        m_scene_graph->setProjectionMatrix(glm::perspective(45.0f, (float)(ev->w()) / ev->h(), 0.01f, 100.0f));
    }

    if(e->getType() == Cg::CgButtonEvent){
        CgButtonEvent* ev = (CgButtonEvent*) e;

        if(ev->getBtSelectNextObject()){
            m_scene_graph->selectNextEnitiy();
        }
        if(ev->getBtScalePlus()){
            m_scene_graph->tScaleSelectedEntity(glm::vec3(1.1f,1.1f,1.1f));
        }
        if(ev->getBtScaleMinus()){
            m_scene_graph->tScaleSelectedEntity(glm::vec3(0.9f,0.9f,0.9f));
        }
        if(ev->getBtRotateX()){
            m_scene_graph->tRotateSelectedEntity(45.0, 'x');
        }
        if(ev->getBtRotateY()){
            m_scene_graph->tRotateSelectedEntity(45.0, 'y');
        }
        if(ev->getBtRotateZ()){
            m_scene_graph->tRotateSelectedEntity(45.0, 'z');
        }
        if(ev->getBtRotateCustom()){
            rotateVec = ev->getRotateVec();
            m_scene_graph->tRotateSelectedEntity(45.0f, rotateVec);
        }
        if(ev->getBtTranslate()){
            transVec = ev->getTranslateVec();
            m_scene_graph->tTranslateSelectedEntity(transVec);
        }
    }

    if(e->getType() == Cg::CgLoadObjFileEvent)
    {
        CgLoadObjFileEvent* ev = (CgLoadObjFileEvent*)e;
        m_scene_graph->loadObject(ev->fileName());
        m_renderer->redraw();
    }

    if(e->getType() == Cg::CgColorChangeEvent)
    {
        CgColorChangeEvent* ev = (CgColorChangeEvent*) e;
        glm::vec3 customColor = glm::vec3((float)(ev->getRed() * 0.01f), (float)(ev->getGreen() * 0.01f), (float)(ev->getBlue() * 0.01f));
        m_scene_graph->changeColorOfVariousObjects(customColor);
        m_renderer->redraw();
    }

    if(e->getType() == Cg::CgObjectSelectionChangeEvent)
    {
        CgObjectSelectionChangeEvent *ev = (CgObjectSelectionChangeEvent*) e;

        m_scene_graph->setRenderCoordinateSystem(ev->getRenderCoordinateSystem());

        m_scene_graph->setRenderVariousObjects(true);
            m_scene_graph->setRenderCube(ev->getRenderCube());
            m_scene_graph->setRenderCubeNormals(ev->getRenderCubeNormals());
            m_scene_graph->setRenderCylinder(ev->getRenderCylinder());
            m_scene_graph->setRenderCylinderNormals(ev->getRenderCylinderNormals());
            m_scene_graph->setRenderRotationCurve(ev->getRenderRotationCurve());
            m_scene_graph->setRenderRotationBody(ev->getRenderRotationBody());
            m_scene_graph->setRenderRotationBodyNormals(ev->getRenderRotationBodyNormals());
            m_scene_graph->setRenderLoadedObject(ev->getRenderLoadedObject());
            m_scene_graph->setRenderLoadedObjectNormals(ev->getRenderLoadedObjectNormals());
            m_scene_graph->setRenderCustomRotationAxis(ev->getRenderCustomRotationAxis());

        m_renderer->redraw();
    }

    if(e->getType() == Cg::CgValueChangedEvent)
    {
        CgValueChangedEvent* ev = (CgValueChangedEvent*) e;

        if(ev->getCylinderChanged()){
            if(ev->getValueAmountOfSegmentsCylinder() >= 2 && ev->getValueHeightCylinder() >= 0 && ev->getValueRadiusCylinder() >= 0){
                m_scene_graph->changeCylinder(ev->getValueAmountOfSegmentsCylinder(), ev->getValueHeightCylinder(), ev->getValueRadiusCylinder());
            }else{
                std::cout << "bad values for cylinder" << std::endl;
            }
        }

        if(ev->getRotationCurveChanged()){
            if(ev->getSdForPointScheme()){
                m_scene_graph->changeRotationCurveForPointScheme();
            }
            if(ev->getResetRotationCurve()){
                m_scene_graph->changeRotationCurveReset();
            }
        }

        if(ev->getRotationBodyChanged()){
            if(ev->getValueAmountOfSegmentsRotationBody() > 1){
                m_scene_graph->changeRotationBody(ev->getValueAmountOfSegmentsRotationBody());
            }else{
                std::cout << "bad values for rotationBody" << std::endl;
            }
        }

        m_renderer->redraw();
    }

    delete e;


}
