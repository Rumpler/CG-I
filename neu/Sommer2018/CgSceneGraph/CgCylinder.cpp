﻿#include "CgCylinder.h"

#include <CgUtils/CgUtils.h>

CgCylinder::CgCylinder(int id, int amountOfSegments, double height, double radius): CgTriangleMesh(id),
    amountOfSegments(amountOfSegments),
    height(height)
{
   makeCylinder(amountOfSegments, height, radius);
}

void CgCylinder::makeCylinder(int amountOfSegments, double height, double radius)
{
    //memory if normals should be displayed
    bool displayPolyNormals;
    if(polylineNormals.size() > 0){displayPolyNormals = polylineNormals.at(0)->getDisplay();}else{displayPolyNormals = false;}  //else when cylinder is constructed

    //reset object
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
    polylineNormals.clear();

    /*************  vars*************/
        double angleOfRotation;
        double currentAngle;

        //for rotatet points
        glm::vec3 focus;    //focus of triangle
        glm::vec3 normalP;  //normalPoint

        //for first points
        glm::vec3 fpr;   //focusPointRight
        glm::vec3 fpl;   //focusPointLeft
        glm::vec3 fpt;   //focusPointTop
        glm::vec3 fpb;   //focusPointBottom
        glm::vec3 nr;    //normalRight
        glm::vec3 nrP;   //normalRightPoint
        glm::vec3 nl;    //normalLeft
        glm::vec3 nlP;   //normalLeftPoint
        glm::vec3 nt;    //normalTop
        glm::vec3 ntP;   //normalTopPoint
        glm::vec3 nb;    //normalBottom
        glm::vec3 nbP;   //normalBottomPoint

        glm::vec3 vnt;   //vertexNormalTop  (not center)
        glm::vec3 vntP;  //vertexNormalTopPoint
        glm::vec3 vnb;   //vertexNormalbottom  (not center)
        glm::vec3 vnbP;  //vertexNormalbottomPoint

        //indices
        int iBottomCenter = 0;
        int iTopCenter = 1;
        int iBottomEdge = 2;
        int iTopEdge = 3;

        int iLastBot = 2;
        int iLastTop = 3;
        int iNextBot = 4;
        int iNextTop = 5;

    /*************  vars end *************/

    //initial values
    angleOfRotation = 360.0 / amountOfSegments;
    angleOfRotation = (2.0 * M_PI / 360.0) * angleOfRotation;       //Translate in rad

    //first 4 points
    m_vertices.push_back((glm::vec3(0.0f, 0.0f, 0.0f)));                    //Bottom center
    m_vertices.push_back(glm::vec3(0.0f, (float)height, 0.0f));             //Top center
    m_vertices.push_back(glm::vec3((float) radius, 0.0f, 0.0f));            //Bottom edge
    m_vertices.push_back(glm::vec3((float) radius, (float)height, 0.0f));   //Top edge

    //normals for vertices bottomCenter and topCenter
    m_vertex_normals.push_back(glm::vec3(0.0f,-1.0f,0.0f));
    m_vertex_normals.push_back(glm::vec3(0.0f,1.0f,0.0f));
    //push polylines for vertices bottomCenter and topCenter
    pushPoly(m_vertices.at(iBottomCenter), glm::vec3(0.0f,-0.1f, 0.0f));
    pushPoly(m_vertices.at(iTopCenter), glm::vec3(0.0f,(float)height + 0.1f, 0.0f));



    /******************************************************************************************************************************************/
    /*      Calculate points, faceNormals and vertexNormals. First loop does normal calculation, than calculate rotation of first values      */
    /******************************************************************************************************************************************/
    for(int i = 0; i < amountOfSegments; i++){
        currentAngle = angleOfRotation * (i + 1);

        //calculate closed mesh
        iNextBot = iLastBot + 2;
        if(iNextBot > (amountOfSegments * 2) + 1){iNextBot = 2;}
        iNextTop = iLastTop + 2;
        if(iNextTop > (amountOfSegments * 2) + 1){iNextTop = 3;}

        //calculate and push new points
        m_vertices.push_back(CgUtils::rotatePointYAxis(currentAngle, m_vertices.at(iBottomEdge)));
        m_vertices.push_back(CgUtils::rotatePointYAxis(currentAngle, m_vertices.at(iTopEdge)));

        //create 4 new faces
        createFace(iNextBot, iLastBot, iLastTop);      //right
        createFace(iNextBot, iLastTop, iNextTop);      //left
        createFace(iTopCenter, iNextTop, iLastTop);    //top
        createFace(iBottomCenter, iLastBot, iNextBot); //bottom



        if(i == 0){                 //FIRST LOOP

            /************* normals per FACE (first loop)*************/

            //right
            fpr = CgUtils::calcFocusPointTriangle(m_vertices.at(iNextBot), m_vertices.at(iLastBot), m_vertices.at(iLastTop));
            nr  = CgUtils::calcFaceNormal(m_vertices.at(iNextBot), m_vertices.at(iLastBot), m_vertices.at(iLastTop));
            nrP = fpr + nr * 0.1f;
            pushPoly(fpr, nrP);
            //left
            fpl  = CgUtils::calcFocusPointTriangle(m_vertices.at(iNextBot), m_vertices.at(iLastTop), m_vertices.at(iNextTop));
            nl   = CgUtils::calcFaceNormal(m_vertices.at(iNextBot), m_vertices.at(iLastTop), m_vertices.at(iNextTop));
            nlP  = fpl + nl * 0.1f;
            pushPoly(fpl, nlP);
            //top
            fpt  = CgUtils::calcFocusPointTriangle(m_vertices.at(iTopCenter), m_vertices.at(iNextTop), m_vertices.at(iLastTop));
            nt   = CgUtils::calcFaceNormal(m_vertices.at(iTopCenter), m_vertices.at(iNextTop), m_vertices.at(iLastTop));
            ntP  = fpt + nt * 0.1f;
            pushPoly(fpt, ntP);
            //bottom
            fpb  = CgUtils::calcFocusPointTriangle(m_vertices.at(iBottomCenter), m_vertices.at(iLastBot), m_vertices.at(iNextBot));
            nb   = CgUtils::calcFaceNormal(m_vertices.at(iBottomCenter), m_vertices.at(iLastBot), m_vertices.at(iNextBot));
            nbP  = fpb + nb * 0.1f;
            pushPoly(fpb, nbP);


            /************* normals per VERTEX (first loop)*************/

            //Calculate faceNormal for next RIGHT face
            glm::vec3 focus =  CgUtils::rotatePointYAxis(currentAngle, fpr);
            normalP = CgUtils::rotatePointYAxis(currentAngle, fpr + nr);
            glm::vec3 nextRightFaceNormal = normalP - focus;
            nextRightFaceNormal = glm::normalize(nextRightFaceNormal);


            //Calculate first vertexNormal for bottomEdge
            vnbP = (nl + nr + nb + nb + nextRightFaceNormal) / 5.0f;
            vnbP = glm::normalize(vnbP);
            vnbP = m_vertices.at(iNextBot) + vnbP * 0.1f;
            pushPoly(m_vertices.at(iNextBot),vnbP);

            //Calculate first vertexNormal for topEdge
            vntP = (nl + nextRightFaceNormal + nextRightFaceNormal + nt + nt) / 5.0f;
            vntP = glm::normalize(vntP);
            vntP = m_vertices.at(iNextTop) + vntP * 0.1f;
            pushPoly(m_vertices.at(iNextTop), vntP);



        }else if(true){                //ALL OTHER LOOPS
            currentAngle = angleOfRotation * i;

            /************* normals per FACE *************/

            //right
            focus =  CgUtils::rotatePointYAxis(currentAngle, fpr);
            normalP = CgUtils::rotatePointYAxis(currentAngle, fpr + nr * 0.1f);
            pushPoly(focus, normalP);
            //left
            focus =  CgUtils::rotatePointYAxis(currentAngle, fpl);
            normalP = CgUtils::rotatePointYAxis(currentAngle, fpl + nl * 0.1f);
            pushPoly(focus, normalP);
            //top
            focus =  CgUtils::rotatePointYAxis(currentAngle, fpt);
            normalP = CgUtils::rotatePointYAxis(currentAngle, fpt + nt * 0.1f);
            pushPoly(focus,normalP);
            //bottom
            focus =  CgUtils::rotatePointYAxis(currentAngle, fpb);
            normalP = CgUtils::rotatePointYAxis(currentAngle, fpb + nb * 0.1f);
            pushPoly(focus,normalP);

            /************* normals per VERTEX *************/

            //top
            normalP = CgUtils::rotatePointYAxis(currentAngle, vntP);
            pushPoly(m_vertices.at(iNextTop), normalP);
            //bottom
            normalP = CgUtils::rotatePointYAxis(currentAngle, vnbP);
            pushPoly(m_vertices.at(iNextBot), normalP);





        }

        iLastBot = iNextBot;
        iLastTop = iNextTop;
    }

    if(displayPolyNormals){
        for(CgLine* poly : polylineNormals){
            poly->setDisplay(true);
        }
    }

}

void CgCylinder::createFace(int p1, int p2, int p3)
{
    m_triangle_indices.push_back(p1);
    m_triangle_indices.push_back(p2);
    m_triangle_indices.push_back(p3);
}

void CgCylinder::pushPoly(glm::vec3 p1, glm::vec3 p2)
{
    CgLine* poly = new CgLine(idGen->getNextId());
    poly->addVertice(p1);
    poly->addVertice(p2);
    poly->setColor(glm::vec3(1.0f,1.0f,1.0f));
    polylineNormals.push_back(poly);
}
