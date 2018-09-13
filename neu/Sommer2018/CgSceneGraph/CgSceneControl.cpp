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
#include <CgEvents/CgShaderEvent.h>
#include <CgEvents/CgSubdivisionEvent.h>
#include <CgEvents/CgValueChangedEvent.h>
#include <CgUtils/CgUtils.h>
#include "CgUtils/ObjLoader.h"
#include <string>
#include <CgClasses/kamera.h>
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
    m_scene_graph->render();
}

void CgSceneControl::handleEvent(CgBaseEvent* e)
{
    if(e->getType() == Cg::CgMouseButtonPress || e->getType() == Cg::CgMouseMove)
    {
        CgMouseEvent* ev = (CgMouseEvent*)e;
        /*std::cout << *ev << std::endl;
         float lx = ev->getLocalPos().x;
         float ly = ev->getLocalPos().y;
         float mx = camm->getFenster().x;
         float my = camm->getFenster().y;
         float dx = float(lx/mx);
         float dy = float(ly/my);
         std::cout<<"dx/dy "<<dx<<" "<<dy<<" mx/my "<<mx<<" "<<my<<" lx/ly "<<lx<<" "<<ly<<std::endl;
         glm::vec2 temp = glm::vec2((2*dx-1),(2*dy-1));


         m_triangle->addLine(temp.x,temp.y, camm);
         m_renderer->redraw();
         */
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

        if(ev->key() == Cg::Key_N || ev->key() == Cg::Key_0){
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
        if(ev->key() == Cg::Key_T || ev->key() == Cg::Key_5){
            m_scene_graph->tTranslateSelectedEntity(transVec);
        }
        if(ev->key() == Cg::Key_8){
            m_scene_graph->tTranslateSelectedEntity(glm::vec3(0,0,-0.1));
        }
        if(ev->key() == Cg::Key_2){
            m_scene_graph->tTranslateSelectedEntity(glm::vec3(0,0,0.1));
        }
        if(ev->key() == Cg::Key_4){
            m_scene_graph->tTranslateSelectedEntity(glm::vec3(-0.1,0,0));
        }
        if(ev->key() == Cg::Key_6){
            m_scene_graph->tTranslateSelectedEntity(glm::vec3(0.1,0,0));
        }
        if(ev->key() == Cg::Key_7){
            m_scene_graph->tTranslateSelectedEntity(glm::vec3(0,0.1,0));
        }
        if(ev->key() == Cg::Key_9){
            m_scene_graph->tTranslateSelectedEntity(glm::vec3(0,-0.1,0));
        }
        if(ev->key()==Cg::Key_W)
        {
            m_scene_graph->moveForward();
        }
        if(ev->key()==Cg::Key_S)
        {
           m_scene_graph->moveBackward();
        }

        if(ev->key()==Cg::Key_A)
        {
            m_scene_graph->moveRight();
        }
        if(ev->key()==Cg::Key_D)
        {
           m_scene_graph->moveLeft();
        }

        if(ev->key()==Cg::Key_E){
            m_scene_graph->rotateRight();
        }

        if(ev->key()==Cg::Key_Q){
            m_scene_graph->rotateLeft();
        }

        if(ev->key()==Cg::Key_R){
            m_scene_graph->moveUp();
        }

        if(ev->key()==Cg::Key_F){
            m_scene_graph->moveDown();
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
       m_scene_graph->changeColorOfAllObjects(glm::vec4(customColor,1.0f));
   //     m_scene_graph->changeColorOfSelectedObjects(glm::vec4(customColor,1.0f));
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
        m_scene_graph->setRenderScene(ev->getRenderScene());

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

    //DON
    if(e->getType() == Cg::CgChangeMaterial){
        m_scene_graph->setMaterialProperties((CgMaterialChangeEvent*) e);
    }

    if(e->getType() == Cg::CgChangeProjection){
        if(((ProjektionEvent*)e)->getValue().x==1){
            m_scene_graph->setProjection(1);
        }
        if(((ProjektionEvent*)e)->getValue().x==2){
            m_scene_graph->setProjection(2);
        }
    }


    if(e->getType()== Cg::CgChangeFrustum){

        if(((ProjektionEvent*)e)->getValue().y==0){
            m_scene_graph->setFrustum(0,(float)(((ProjektionEvent*)e)->getValue().z)/10);
        }
        if(((ProjektionEvent*)e)->getValue().y==1){
            m_scene_graph->setFrustum(1,(float)(((ProjektionEvent*)e)->getValue().z)/10);
        }
        if(((ProjektionEvent*)e)->getValue().y==2){
            m_scene_graph->setFrustum(2,(float)(((ProjektionEvent*)e)->getValue().z)/10);
        }
        if(((ProjektionEvent*)e)->getValue().y==3){
            m_scene_graph->setFrustum(3,(float)(((ProjektionEvent*)e)->getValue().z)/10);
        }
        if(((ProjektionEvent*)e)->getValue().y==4){
            m_scene_graph->setFrustum(4,(float)(((ProjektionEvent*)e)->getValue().z)/10);
        }
        if(((ProjektionEvent*)e)->getValue().y==5){
            m_scene_graph->setFrustum(5,(float)(((ProjektionEvent*)e)->getValue().z)/10);
        }
    }


    if(e->getType() == Cg::CgShaderEvent){
        CgShaderEvent* ev = (CgShaderEvent*) e;

        m_scene_graph->setNone(ev->getNoneShader());
        m_scene_graph->setPhong(ev->getPhong());
        m_scene_graph->setGouraud(ev->getGouraud());

        m_scene_graph->setFlat(ev->getFlat());
        m_scene_graph->setSmooth(ev->getSmooth());


        if(ev->getMaterialIndex() == 0){
            m_scene_graph->setAmb(glm::vec4(.25f,.25f,.25f,1.0));
            m_scene_graph->setDef(glm::vec4(.40f,.40f,.40f,1.0));
            m_scene_graph->setSpec(glm::vec4(.77f,.77f,.77f,1.0));
            m_scene_graph->setShininess(76.8);
        }else if(ev->getMaterialIndex() == 1){
            m_scene_graph->setAmb(glm::vec4(.25f,.21f,.21f,.90f));
            m_scene_graph->setDef(glm::vec4(0.99f,.83f,.83f,.90f));
            m_scene_graph->setSpec(glm::vec4(0.30f,0.30f,0.30f,0.90f));
            m_scene_graph->setShininess(11.3);
        }
        else if(ev->getMaterialIndex() == 2){ //GOLD
            m_scene_graph->setAmb(glm::vec4(0.5f,0.5f,0.7f,0.8f));
            m_scene_graph->setDef(glm::vec4(0.18f,0.17f,0.23f,0.8f));
            m_scene_graph->setSpec(glm::vec4(0.33f,0.33f,0.35f,0.8f));
            m_scene_graph->setShininess(38.4);
        }
        else if(ev->getMaterialIndex() == 3){
            m_scene_graph->setAmb(glm::vec4(0.25f,0.20f,0.07f,1.f));
            m_scene_graph->setDef(glm::vec4(0.75f,0.61f,0.23f,1.f));
            m_scene_graph->setSpec(glm::vec4(0.63f,0.56f,0.37f,0.9f));
            m_scene_graph->setShininess(51.2);
        }
        else if(ev->getMaterialIndex() == 4){
            m_scene_graph->setAmb(glm::vec4(0.25f,0.20f,0.07f,1.f));
            m_scene_graph->setDef(glm::vec4(0.75f,0.61f,0.23f,1.f));
            m_scene_graph->setSpec(glm::vec4(0.63f,0.56f,0.37f,0.9f));
            m_scene_graph->setShininess(51.2);
        }
        else if(ev->getMaterialIndex() == 5){
            m_scene_graph->setAmb(glm::vec4(0.19f,0.19f,0.19f,1.0f));
            m_scene_graph->setDef(glm::vec4(0.51f,0.51f,0.51f,1.0f));
            m_scene_graph->setSpec(glm::vec4(0.51f,0.51f,0.51f,1.f));
            m_scene_graph->setShininess(51.2);
        }
        else if(ev->getMaterialIndex() == 6){
            m_scene_graph->setAmb(glm::vec4(0.2f,0.2f,0.2f,1.0f));
            m_scene_graph->setDef(glm::vec4(0.1f,0.1f,0.1f,1.0f));
            m_scene_graph->setSpec(glm::vec4(0.5f,0.5f,0.5f,1.f));
            m_scene_graph->setShininess(51.2);
        }

       m_scene_graph->setMaterialPropertiesForSelectedObject();
    }

    delete e;


}
