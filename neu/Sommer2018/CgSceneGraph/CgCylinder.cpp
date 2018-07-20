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

    //push polylines for topCenter vertex and bottomCenter vertex
    pushPoly(m_vertices.at(bottomCenter), glm::vec3(0.0f,-0.1f, 0.0f));
    pushPoly(m_vertices.at(topCenter), glm::vec3(0.0f,(float)height + 0.1f, 0.0f));

    //Vars for loop
        double currentAngle;

        //for rotatet points
        glm::vec3 focus;
        glm::vec3 normal;

        //for first points
        glm::vec3 fpr;  //focusPointRight
        glm::vec3 fpl;  //focusPointLeft
        glm::vec3 fpt;  //focusPointTop
        glm::vec3 fpb;  //focusPointBottom
        glm::vec3 nr;   //normalRight
        glm::vec3 nl;   //normalLeft
        glm::vec3 nt;   //normalTop
        glm::vec3 nb;   //normalBottom

        glm::vec3 vnt;  //vertexNormalTop
        glm::vec3 vnb;  //vertexNormalbottom
    //


    /* calculate points, faceNormals (and soon vertexNormals). First loop does normal calculation, than calculate rotation of first values */
    for(int i = 0; i < amountOfSegments; i++){
        currentAngle = angleOfRotation * (i + 1);

        //calculate closed mesh
        nextBot = lastBot + 2;
        if(nextBot > (amountOfSegments * 2) + 1){nextBot = 2;}
        nextTop = lastTop + 2;
        if(nextTop > (amountOfSegments * 2) + 1){nextTop = 3;}

        //calculate and push new points
        m_vertices.push_back(CgUtils::rotatePointYAxis(currentAngle, m_vertices.at(bottomEdge)));
        m_vertices.push_back(CgUtils::rotatePointYAxis(currentAngle, m_vertices.at(topEdge)));

        //create 4 new faces
            createFace(nextBot, lastBot, lastTop);      //right
            createFace(nextBot, lastTop, nextTop);      //left
            createFace(topCenter, nextTop, lastTop);    //top
            createFace(bottomCenter, lastBot, nextBot); //bottom


            //first loop
            if(i == 0){

                /************* normals per FACE (first loop)*************/

                //right
                fpr = CgUtils::calcFocusPointTriangle(m_vertices.at(nextBot), m_vertices.at(lastBot), m_vertices.at(lastTop));
                nr  = CgUtils::calcFaceNormal(m_vertices.at(nextBot), m_vertices.at(lastBot), m_vertices.at(lastTop));
                pushPoly(fpr, fpr + nr * 0.1f);
                //left
                fpl  = CgUtils::calcFocusPointTriangle(m_vertices.at(nextBot), m_vertices.at(lastTop), m_vertices.at(nextTop));
                nl   = CgUtils::calcFaceNormal(m_vertices.at(nextBot), m_vertices.at(lastTop), m_vertices.at(nextTop));
                pushPoly(fpl, fpl + nl * 0.1f);
                //top
                fpt  = CgUtils::calcFocusPointTriangle(m_vertices.at(topCenter), m_vertices.at(nextTop), m_vertices.at(lastTop));
                nt   = CgUtils::calcFaceNormal(m_vertices.at(topCenter), m_vertices.at(nextTop), m_vertices.at(lastTop));
                pushPoly(fpt, fpt + nt * 0.1f);
                //bottom
                fpb  = CgUtils::calcFocusPointTriangle(m_vertices.at(bottomCenter), m_vertices.at(lastBot), m_vertices.at(nextBot));
                nb   = CgUtils::calcFaceNormal(m_vertices.at(bottomCenter), m_vertices.at(lastBot), m_vertices.at(nextBot));
                pushPoly(fpb, fpb + nb * 0.1f);


                /************* normals per VERTEX (first loop)*************/

                //Calculate faceNormal for next RIGHT face
                glm::vec3 focus =  CgUtils::rotatePointYAxis(currentAngle, fpr);
                glm::vec3 normalP = CgUtils::rotatePointYAxis(currentAngle, fpr + nr);
                glm::vec3 nextRightFaceNormal = normalP - focus;
                nextRightFaceNormal = glm::normalize(nextRightFaceNormal);





                //Calculate first vertexNormal for bottomEdge
                vnb = (nl + nr + nb + nb + nextRightFaceNormal) / 5.0f;
                vnb = glm::normalize(vnb);
                pushPoly(m_vertices.at(nextBot), m_vertices.at(nextBot) + vnb * 0.1f);

                //Calculate first vertexNormal for topEdge
                vnt = (nl + nextRightFaceNormal + nextRightFaceNormal + nt + nt) / 5.0f;
                vnt = glm::normalize(vnt);
                pushPoly(m_vertices.at(nextTop), m_vertices.at(nextTop) + vnt * 0.1f);





            //any other loop than first
            }else if(false){
                currentAngle = angleOfRotation * i;

                //right
                focus =  CgUtils::rotatePointYAxis(currentAngle, fpr);
                normal = CgUtils::rotatePointYAxis(currentAngle, nr);
                pushPoly(focus, focus + normal * 0.1f);
                //left
                focus =  CgUtils::rotatePointYAxis(currentAngle, fpl);
                normal = CgUtils::rotatePointYAxis(currentAngle, nl);
                pushPoly(focus, focus + normal * 0.1f);
                //top
                focus =  CgUtils::rotatePointYAxis(currentAngle, fpt);
                normal = CgUtils::rotatePointYAxis(currentAngle, nt);
                pushPoly(focus, focus + normal * 0.1f);
                //bottom
                focus =  CgUtils::rotatePointYAxis(currentAngle, fpb);
                normal = CgUtils::rotatePointYAxis(currentAngle, nb);
                pushPoly(focus, focus + normal * 0.1f);


            }

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
    poly->setColor(glm::vec3(1.0f,1.0f,1.0f));
    polylineNormals.push_back(poly);
}
