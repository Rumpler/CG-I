#include "CgCylinder.h"
#include <math.h>
#include <iostream>
#include "CgUtils/CgUtils.h"

CgCylinder::CgCylinder(int id, int amountOfSegments, double height):
    m_type(Cg::TriangleMesh),
    m_id(id)
{
    //Test if enaugh segments are given
    if(amountOfSegments < 3){
        std::cout << "Too few segments" << std::endl;
        //throgh exception;
        return;
    }

    idGen = IdSingleton::instance();

    //Initial values
    double angleOfRotation = 360.0 / amountOfSegments;
    angleOfRotation = ((2.0 * M_PI) / 360.0) * angleOfRotation;     //Translate in rad
    double x = 0.2;                                                 //Radius of cylinder
    double y = 0.0;

    //First 3 points
    m_vertices.push_back(glm::vec3(0.0f, (float)height, 0.0f));     //Top of cylinder
    m_vertices.push_back((glm::vec3(0.0f, 0.0f, 0.0f)));            //Bottom center of cylinder
    m_vertices.push_back(glm::vec3((float) x, 0.0f, (float) y));    //First point

    //Indices
    int top = 0;
    int bottom = 1;
    int first = 2;
    int last = 2;

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

    //Calculate next point, next normal etc. - First with normal calculation and then with rotation of first
    for(int i = 0; i < amountOfSegments; i++){
        currentAngle = angleOfRotation * (i + 1);

        //Calculate new x and y and push new point
        x = (0.2 * cos(currentAngle)) - (0.0 * sin(currentAngle));
        y = (0.0 * cos(currentAngle)) + (0.2 * sin(currentAngle));
        m_vertices.push_back(glm::vec3((float) x, 0.0f, (float) y));

        //Create 2 new faces
        createFace(top, last, last +1);
        createFace(bottom, last +1, last);

        //Only in first loop (calculate first normals for first faces)
        if(i == 0){

            /* ################# Calculate 2 face normals for first top and bottom face ################# */

                //Calculate focusPoints
                focusPointTop = CgUtils::calcFocusPointTriangle(m_vertices.at(top), m_vertices.at(last), m_vertices.at(last + 1));
                focusPointBottom = CgUtils::calcFocusPointTriangle(m_vertices.at(bottom), m_vertices.at(last + 1), m_vertices.at(last));

                //Calculate and push faceNormals
                faceNormalTop = CgUtils::calcFaceNormal(m_vertices.at(last), m_vertices.at(top), m_vertices.at(last + 1));
                m_face_normals.push_back(faceNormalTop);
                faceNormalBottom = CgUtils::calcFaceNormal(m_vertices.at(last + 1), m_vertices.at(bottom), m_vertices.at(last));
                m_face_normals.push_back(faceNormalBottom);

                //Push polylines
                pushPoly(focusPointTop, focusPointTop + faceNormalTop * 0.1f);
                pushPoly(focusPointBottom, focusPointBottom + faceNormalBottom * 0.1f);

            /* ################# Calculate 2 face normals for first top and bottom face ################# */


            //Top
            //Rotate focusPoint
            newFocusPointTop = CgUtils::rotatePointYAxis(currentAngle, focusPointTop);

            //Rotate normal endpoint
            newFaceNormalTopPoint = focusPointTop + faceNormalTop * 0.1f;
            newFaceNormalTopPoint = CgUtils::rotatePointYAxis(currentAngle, newFaceNormalTopPoint);


            //Push polyline
            CgPolyline* poly = new CgPolyline(idGen->getNextId());
            poly->addVertice(newFocusPointTop);
            poly->addVertice(newFaceNormalTopPoint);
            polylineNormals.push_back(poly);


            //Bottom
            //Rotate focusPoint
            newFocusPointBottom = glm::vec3((focusPointBottom.x * cos(currentAngle)) - (focusPointBottom.z * sin(currentAngle)),
                                            focusPointBottom.y,
                                            (focusPointBottom.z * cos(currentAngle)) + (focusPointBottom.x * sin(currentAngle)) );

            //Rotate normal endpoint
            newFaceNormalBottomPoint = focusPointBottom + faceNormalBottom * 0.1f;
            newFaceNormalBottomPoint = glm::vec3((newFaceNormalBottomPoint.x * cos(currentAngle)) - (newFaceNormalBottomPoint.z * sin(currentAngle)),
                                                 newFaceNormalBottomPoint.y,
                                                 (newFaceNormalBottomPoint.z * cos(currentAngle)) + (newFaceNormalBottomPoint.x * sin(currentAngle)) );

            //Push polyline
            poly = new CgPolyline(idGen->getNextId());
            poly->addVertice(newFocusPointBottom);
            poly->addVertice(newFaceNormalBottomPoint);
            polylineNormals.push_back(poly);




            //Calculate next faceNormals with rotation routine in any other loop but the first
        }else if(i > 0 && i < amountOfSegments - 1){
            std::cout << "Normal loop" << std::endl;

            //Top
            //Rotate fcousPoint
            glm::vec3 newFocusPointTop = glm::vec3( (focusPointTop.x * cos(currentAngle)) - (focusPointTop.z * sin(currentAngle)),
                                                    focusPointTop.y,
                                                    ( focusPointTop.z * cos(currentAngle)) + (focusPointTop.x * sin(currentAngle)) );
            //Rotate normal endpoint
            glm::vec3 newFaceNormalTopPoint = focusPointTop + faceNormalTop * 0.1f;
            newFaceNormalTopPoint = glm::vec3( (newFaceNormalTopPoint.x * cos(currentAngle)) - (newFaceNormalTopPoint.z * sin(currentAngle)),
                                               newFaceNormalTopPoint.y,
                                               (newFaceNormalTopPoint.z * cos(currentAngle)) + (newFaceNormalTopPoint.x * sin(currentAngle)) );

            //Push polyline
            CgPolyline* poly = new CgPolyline(idGen->getNextId());
            poly->addVertice(newFocusPointTop);
            poly->addVertice(newFaceNormalTopPoint);
            polylineNormals.push_back(poly);


            //Bottom
            //Rotate focusPoint
            glm::vec3 newFocusPointBottom = glm::vec3((focusPointBottom.x * cos(currentAngle)) - (focusPointBottom.z * sin(currentAngle)),
                                                      focusPointBottom.y,
                                                      (focusPointBottom.z * cos(currentAngle)) + (focusPointBottom.x * sin(currentAngle)) );

            //Rotate normal endpoint
            glm::vec3 newFaceNormalBottomPoint = focusPointBottom + faceNormalBottom * 0.1f;
            newFaceNormalBottomPoint = glm::vec3((newFaceNormalBottomPoint.x * cos(currentAngle)) - (newFaceNormalBottomPoint.z * sin(currentAngle)),
                                                 newFaceNormalBottomPoint.y,
                                                 (newFaceNormalBottomPoint.z * cos(currentAngle)) + (newFaceNormalBottomPoint.x * sin(currentAngle)) );

            //Push polyline
            poly = new CgPolyline(idGen->getNextId());
            poly->addVertice(newFocusPointBottom);
            poly->addVertice(newFaceNormalBottomPoint);
            polylineNormals.push_back(poly);


        }
        //Only in last loop
        if(i == amountOfSegments - 1 && false){

            //Last face with first point
            m_triangle_indices.push_back(top);
            m_triangle_indices.push_back(last);
            m_triangle_indices.push_back(first);

            m_triangle_indices.push_back(bottom);
            m_triangle_indices.push_back(last);
            m_triangle_indices.push_back(first);


        }
        last++;
        std::cout << std::endl;
    }

}





CgCylinder::~CgCylinder()
{
    polylineNormals.clear();

    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}

Cg::ObjectType CgCylinder::getType() const
{
    return m_type;
}

unsigned int CgCylinder::getID() const
{
    return m_id;
}

const std::vector<glm::vec3> &CgCylinder::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3> &CgCylinder::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3> &CgCylinder::getVertexColors() const
{
    return m_vertex_colors;
}

const std::vector<glm::vec2> &CgCylinder::getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int> &CgCylinder::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3> &CgCylinder::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3> &CgCylinder::getFaceColors() const
{
    return m_face_colors;
}

std::vector<CgPolyline *>* CgCylinder::getPolylineNormals()
{
    return &polylineNormals;
}

void CgCylinder::createFace(int p1, int p2, int p3)
{
    m_triangle_indices.push_back(p1);
    m_triangle_indices.push_back(p2);
    m_triangle_indices.push_back(p3);
}

void CgCylinder::pushPoly(glm::vec3 p1, glm::vec3 p2)
{
    CgPolyline* poly = new CgPolyline(idGen->getNextId());
    poly->addVertice(p1);
    poly->addVertice(p2);
    polylineNormals.push_back(poly);
}


