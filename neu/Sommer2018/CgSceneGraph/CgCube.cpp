#include "CgCube.h"
#include "CgBase/CgEnums.h"
#include <iostream>
#include <map>
#include <CgUtils/CgUtils.h>



CgCube::CgCube(int id) : CgTriangleMesh(id)
{
    m_vertices.push_back(glm::vec3(.5,.5,.5));      //0
    m_vertices.push_back(glm::vec3(-.5,.5,.5));     //1
    m_vertices.push_back(glm::vec3(.5,-.5,.5));     //2
    m_vertices.push_back(glm::vec3(-.5,-.5,.5));    //3
    m_vertices.push_back(glm::vec3(.5,.5,-.5));     //4
    m_vertices.push_back(glm::vec3(-.5,.5,-.5));    //5
    m_vertices.push_back(glm::vec3(.5,-.5,-.5));    //6
    m_vertices.push_back(glm::vec3(-.5,-.5,-.5));   //7

    initFace(4,6,7);
    initFace(7,5,4);
    initFace(0,2,6);
    initFace(6,4,0);
    initFace(1,3,2);
    initFace(2,0,1);
    initFace(5,7,3);
    initFace(3,1,5);
    initFace(4,5,1);
    initFace(1,0,4);
    initFace(7,6,2);
    initFace(2,3,7);

    calculateNormals();
    fillPolylineNormals();
}


CgCube::~CgCube()
{

}


