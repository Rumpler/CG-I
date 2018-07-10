#include "CgCylinder.h"
#include <math.h>
#include <iostream>
#include "CgUtils/CgUtils.h"

CgCylinder::CgCylinder(int id, int amountOfSegments, double height):
    m_type(Cg::TriangleMesh),
    m_id(id)
{
    if(amountOfSegments >= 2){
        idGen = IdSingleton::instance();

        //Initial values
        double angleOfRotation = 360.0 / amountOfSegments;
        angleOfRotation = ((2.0 * M_PI) / 360.0) * angleOfRotation;     //Translate in rad
        double x = 0.2;                                                 //Radius
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
        glm::vec3 focusPointTop;
        glm::vec3 focusPointBottom;
        glm::vec3 faceNormalTop;
        glm::vec3 faceNormalBottom;
        glm::vec3 newFocusPointTop;
        glm::vec3 newFocusPointBottom;
        glm::vec3 newFaceNormalTopPoint;
        glm::vec3 newFaceNormalBottomPoint;
        double currentAngle;

        //Calculate next point, next normal etc. first with normal calculation and then with rotation of previous
        for(int i = 0; i < amountOfSegments; i++){

            currentAngle = angleOfRotation * (i + 1);

            //Calculate new x and y and push new point
            x = (0.2 * cos(currentAngle)) - (0.0 * sin(currentAngle));
            y = (0.0 * cos(currentAngle)) + (0.2 * sin(currentAngle));
            m_vertices.push_back(glm::vec3((float) x, 0.0f, (float) y));

            //Create 2 new faces
            m_triangle_indices.push_back(top);
            m_triangle_indices.push_back(last);
            m_triangle_indices.push_back(last + 1);
            m_triangle_indices.push_back(bottom);
            m_triangle_indices.push_back(last + 1);
            m_triangle_indices.push_back(last);

            //Only in first loop (calculate first normals for first faces)
            if(i == 0){
                std::cout << "First loop" << std::endl;

                //Calculate focusPoints
                focusPointTop = glm::vec3(   (m_vertices.at(top).x + m_vertices.at(last).x + m_vertices.at(last + 1).x) / 3.0,
                                             (m_vertices.at(top).y + m_vertices.at(last).y + m_vertices.at(last + 1).y) / 3.0,
                                             (m_vertices.at(top).z + m_vertices.at(last).z + m_vertices.at(last + 1).z) / 3.0);
                focusPointBottom = glm::vec3((m_vertices.at(bottom).x + m_vertices.at(last + 1).x + m_vertices.at(last).x) / 3.0,
                                             (m_vertices.at(bottom).y + m_vertices.at(last + 1).y + m_vertices.at(last).y) / 3.0,
                                             (m_vertices.at(bottom).z + m_vertices.at(last + 1).z + m_vertices.at(last).z) / 3.0);

                //Calculate first faceNormal for top and bottom face

                //Calculate and push faceNormals
                //Top
                glm::vec3 u = m_vertices.at(last) - m_vertices.at(top);
                glm::vec3 v = m_vertices.at(last + 1) - m_vertices.at(top);
                faceNormalTop = glm::cross(v,u);
                faceNormalTop = glm::normalize(faceNormalTop);

                m_face_normals.push_back(faceNormalTop);
                //Bottom
                u = m_vertices.at(last +1) - m_vertices.at(bottom);
                v = m_vertices.at(last) - m_vertices.at(bottom);
                faceNormalBottom = glm::cross(v,u);
                faceNormalBottom = glm::normalize(faceNormalBottom);
                m_face_normals.push_back(faceNormalBottom);

                //Push polylines
                //Top
                CgPolyline* poly = new CgPolyline(idGen->getNextId());
                poly->addVertice(focusPointTop);
                poly->addVertice(focusPointTop + faceNormalTop * 0.1f);
                polylineNormals.push_back(poly);
                //Bottom
                poly = new CgPolyline(idGen->getNextId());
                poly->addVertice(focusPointBottom);
                poly->addVertice(focusPointBottom + faceNormalBottom *0.1f);
                polylineNormals.push_back(poly);




                //Top
                //Rotate focusPoint
                newFocusPointTop = glm::vec3( (focusPointTop.x * cos(currentAngle)) - (focusPointTop.z * sin(currentAngle)),
                                                        focusPointTop.y,
                                                        ( focusPointTop.z * cos(currentAngle)) + (focusPointTop.x * sin(currentAngle)) );
                CgUtils::printVec3("newFocusPointTop", &newFocusPointTop);
                //Rotate normal endpoint
                newFaceNormalTopPoint = focusPointTop + faceNormalTop * 0.1f;
                newFaceNormalTopPoint = glm::vec3( (newFaceNormalTopPoint.x * cos(currentAngle)) - (newFaceNormalTopPoint.z * sin(currentAngle)),
                                                   newFaceNormalTopPoint.y,
                                                   (newFaceNormalTopPoint.z * cos(currentAngle)) + (newFaceNormalTopPoint.x * sin(currentAngle)) );
                CgUtils::printVec3("newFaceNormalTopPoint", &newFaceNormalTopPoint);

                //Push polyline
                poly = new CgPolyline(idGen->getNextId());
                poly->addVertice(newFocusPointTop);
                poly->addVertice(newFaceNormalTopPoint);
                polylineNormals.push_back(poly);


                //Bottom
                //Rotate focusPoint
                newFocusPointBottom = glm::vec3((focusPointBottom.x * cos(currentAngle)) - (focusPointBottom.z * sin(currentAngle)),
                                                           focusPointBottom.y,
                                                          (focusPointBottom.z * cos(currentAngle)) + (focusPointBottom.x * sin(currentAngle)) );
                CgUtils::printVec3("newFocusPointBottom", &newFocusPointBottom);

                //Rotate normal endpoint
                newFaceNormalBottomPoint = focusPointBottom + faceNormalBottom * 0.1f;
                newFaceNormalBottomPoint = glm::vec3((newFaceNormalBottomPoint.x * cos(currentAngle)) - (newFaceNormalBottomPoint.z * sin(currentAngle)),
                                                      newFaceNormalBottomPoint.y,
                                                     (newFaceNormalBottomPoint.z * cos(currentAngle)) + (newFaceNormalBottomPoint.x * sin(currentAngle)) );
                CgUtils::printVec3("newFaceNormalBottomPoint", &newFaceNormalBottomPoint);

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
                CgUtils::printVec3("newFocusPointTop", &newFocusPointTop);
                //Rotate normal endpoint
                glm::vec3 newFaceNormalTopPoint = focusPointTop + faceNormalTop * 0.1f;
                newFaceNormalTopPoint = glm::vec3( (newFaceNormalTopPoint.x * cos(currentAngle)) - (newFaceNormalTopPoint.z * sin(currentAngle)),
                                                   newFaceNormalTopPoint.y,
                                                   (newFaceNormalTopPoint.z * cos(currentAngle)) + (newFaceNormalTopPoint.x * sin(currentAngle)) );
                CgUtils::printVec3("newFaceNormalTopPoint", &newFaceNormalTopPoint);

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
                CgUtils::printVec3("newFocusPointBottom", &newFocusPointBottom);

                //Rotate normal endpoint
                glm::vec3 newFaceNormalBottomPoint = focusPointBottom + faceNormalBottom * 0.1f;
                newFaceNormalBottomPoint = glm::vec3((newFaceNormalBottomPoint.x * cos(currentAngle)) - (newFaceNormalBottomPoint.z * sin(currentAngle)),
                                                      newFaceNormalBottomPoint.y,
                                                     (newFaceNormalBottomPoint.z * cos(currentAngle)) + (newFaceNormalBottomPoint.x * sin(currentAngle)) );
                CgUtils::printVec3("newFaceNormalBottomPoint", &newFaceNormalBottomPoint);

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




    }else{
        std::cout << "Too few Segments" << std::endl;
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


