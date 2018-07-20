#include "CgCylinder.h"

#include <CgUtils/CgUtils.h>

CgCylinder::CgCylinder(int id, int amountOfSegments, double height, double radius): CgTriangleMesh(id),
    amountOfSegments(amountOfSegments),
    height(height)
{
    //Initial values
    double angleOfRotation = 360.0 / amountOfSegments;
    angleOfRotation = (2.0 * M_PI / 360.0) * angleOfRotation;       //Translate in rad

    //First 4 points
    m_vertices.push_back((glm::vec3(0.0f, 0.0f, 0.0f)));                    //Bottom center
    m_vertices.push_back(glm::vec3(0.0f, (float)height, 0.0f));             //Top center
    m_vertices.push_back(glm::vec3((float) radius, 0.0f, 0.0f));            //Bottom edge
    m_vertices.push_back(glm::vec3((float) radius, (float)height, 0.0f));   //Top edge

    //Indices
    int bottomCenter = 0;
    int topCenter = 1;
    int bottomEdge = 2;
    int topEdge = 3;

    int lastBot = 2;
    int lastTop = 3;
    int nextBot = 4;
    int nextTop = 5;

    //Vars for loop
    double currentAngle;
    glm::vec3 focusPointTop;
    glm::vec3 focusPointBottom;
    glm::vec3 faceNormalTop;
    glm::vec3 faceNormalBottom;
    glm::vec3 newFocusPointTop;
    glm::vec3 newFocusPointBottom;
    glm::vec3 newFaceNormalTopPoint;
    glm::vec3 newFaceNormalBottomPoint;

    //Calculate next point, next normal etc.
    //First loop normal calculation and then with rotation of first calculation
    for(int i = 0; i < amountOfSegments; i++){
        currentAngle = angleOfRotation * (i + 1);

        nextBot = lastBot + 2;
        if(nextBot > (amountOfSegments * 2) + 1){nextBot = 2;}
        nextTop = lastTop + 2;
        if(nextTop > (amountOfSegments * 2) + 1){nextTop = 3;}



        std:: cout << "lastBot:" << lastBot << ", nextBot:" << nextBot << std::endl;
        std:: cout << "lastTop:" << lastTop << ", nextTop:" << nextTop << std::endl;

        //Calculate and push new points
        m_vertices.push_back(CgUtils::rotatePointYAxis(currentAngle, m_vertices.at(bottomEdge)));
        m_vertices.push_back(CgUtils::rotatePointYAxis(currentAngle, m_vertices.at(topEdge)));

        //Create 4 new faces
            createFace(nextBot, lastBot, lastTop);
            createFace(nextBot, lastTop, nextTop);
            createFace(bottomCenter, lastBot, nextBot);
            createFace(topCenter, nextTop, lastTop);


        //        //Only in first loop (calculate first normals for first faces)
        //        if(i == 0){

        //            /* ################# Calculate 2 faceNormals for first top and bottom face ################# */

        //                //Calculate focusPoints
        //                focusPointTop = CgUtils::calcFocusPointTriangle(m_vertices.at(top), m_vertices.at(last), m_vertices.at(last + 1));
        //                focusPointBottom = CgUtils::calcFocusPointTriangle(m_vertices.at(bottom), m_vertices.at(last + 1), m_vertices.at(last));

        //                //Calculate and push faceNormals
        //                faceNormalTop = CgUtils::calcFaceNormal(m_vertices.at(last), m_vertices.at(top), m_vertices.at(last + 1));
        //                m_face_normals.push_back(faceNormalTop);
        //                faceNormalBottom = CgUtils::calcFaceNormal(m_vertices.at(last + 1), m_vertices.at(bottom), m_vertices.at(last));
        //                m_face_normals.push_back(faceNormalBottom);

        //                //Push polylines
        //                pushPoly(focusPointTop, focusPointTop + faceNormalTop * 0.1f);
        //                pushPoly(focusPointBottom, focusPointBottom + faceNormalBottom * 0.1f);

        //            /* ################# END ################# */

        //            /* ################# Calculate next step faceNormals for bottom and top to get in order (with rotation) ################# */

        //                //Rotate focusPoint
        //                newFocusPointTop = CgUtils::rotatePointYAxis(currentAngle, focusPointTop);
        //                newFocusPointBottom = CgUtils::rotatePointYAxis(currentAngle, focusPointBottom);

        //                //Rotate normal endpoint
        //                newFaceNormalTopPoint = focusPointTop + faceNormalTop * 0.1f;
        //                newFaceNormalTopPoint = CgUtils::rotatePointYAxis(currentAngle, newFaceNormalTopPoint);
        //                newFaceNormalBottomPoint = focusPointBottom + faceNormalBottom * 0.1f;
        //                newFaceNormalBottomPoint = CgUtils::rotatePointYAxis(currentAngle, newFaceNormalBottomPoint);

        //                //Push polyline
        //                pushPoly(newFocusPointTop, newFaceNormalTopPoint);
        //                pushPoly(newFocusPointBottom, newFaceNormalBottomPoint);

        //            /* ################# END ################# */


        //        //Calculate faceNormals with rotation routine in any loop but the first and last
        //        }else if(i > 0 && i < amountOfSegments - 1){

        //            //Rotate fcousPoint
        //            newFocusPointTop = CgUtils::rotatePointYAxis(currentAngle, focusPointTop);
        //            newFocusPointBottom = CgUtils::rotatePointYAxis(currentAngle, focusPointBottom);

        //            //Rotate normal endpoint
        //            newFaceNormalTopPoint = focusPointTop + faceNormalTop * 0.1f;
        //            newFaceNormalTopPoint = CgUtils::rotatePointYAxis(currentAngle, newFaceNormalTopPoint);
        //            newFaceNormalBottomPoint = focusPointBottom + faceNormalBottom * 0.1f;
        //            newFaceNormalBottomPoint = CgUtils::rotatePointYAxis(currentAngle, newFaceNormalBottomPoint);

        //            //Push polyline
        //            pushPoly(newFocusPointTop, newFaceNormalTopPoint);
        //            pushPoly(newFocusPointBottom, newFaceNormalBottomPoint);
        //        }
        lastBot = nextBot;
        lastTop = nextTop;
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
    polylineNormals.push_back(poly);
}
