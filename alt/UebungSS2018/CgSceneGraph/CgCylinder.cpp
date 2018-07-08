#include "CgCylinder.h"
#include <math.h>
#include <iostream>

CgCylinder::CgCylinder(int id, int amountOfSegments, double height):
    m_type(Cg::TriangleMesh),
    m_id(id)
{
    if(amountOfSegments >= 2){
        idGen = IdSingleton::instance();

        //Initial values
        double angleOfRotation = 360.0 / amountOfSegments;
        //Translate in rad
        angleOfRotation = ((2.0 * M_PI) / 360.0) * angleOfRotation;
        double x = 0.2;
        double y = 0.0;

        //Top of cylinder
        m_vertices.push_back(glm::vec3(0.0f, (float)height, 0.0f));

        //Bottom center of cylinder
        m_vertices.push_back((glm::vec3(0.0f, 0.0f, 0.0f)));

        //First point
        m_vertices.push_back(glm::vec3((float) x, 0.0f, (float) y));

        int top = 0;
        int bottom = 1;
        int first = 2;
        int last = 2;

        //Vars for faceNormals
        glm::vec3 focusPointTop;
        glm::vec3 focusPointBottom;
        glm::vec3 faceNormalTop;
        glm::vec3 faceNormalBottom;

        //Calculate next point and push new face
        for(int i = 0; i < amountOfSegments - 1; i++){

            //Calculation of new x and y
            x = (0.2 * cos(angleOfRotation * (i+1) )) - (0.0 * sin(angleOfRotation * (i+1) ));
            y = (0.0 * cos(angleOfRotation * (i+1) )) + (0.2 * sin(angleOfRotation * (i+1) ));
            m_vertices.push_back(glm::vec3((float) x, 0.0f, (float) y));

            m_triangle_indices.push_back(top);
            m_triangle_indices.push_back(last);
            m_triangle_indices.push_back(last + 1);

            m_triangle_indices.push_back(bottom);
            m_triangle_indices.push_back(last + 1);
            m_triangle_indices.push_back(last);

            //####################### Normal calculation with rotate routine #######################

            //Only in first loop (calculate first normals for first faces)
            if(i == 0){

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
                std::cout << "faceNormalTop before normalize: " << faceNormalTop.x << "," << faceNormalTop.y << "," << faceNormalTop.z << " normal: " << sqrt(faceNormalTop.x * faceNormalTop.x + faceNormalTop.y *faceNormalTop.y + faceNormalTop.z *faceNormalTop.z) << std::endl;
                faceNormalTop = glm::normalize(faceNormalTop);
                std::cout << "faceNormalTop after normalize: "  << faceNormalTop.x << "," << faceNormalTop.y << "," << faceNormalTop.z << " normal: " << sqrt(faceNormalTop.x * faceNormalTop.x + faceNormalTop.y *faceNormalTop.y + faceNormalTop.z *faceNormalTop.z) << std::endl;

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



                //Calculate next faceNormals with rotation routine in any other loop
            }else{

                //Top
                //Rotate fcousPoint
                glm::vec3 newFocusPointTop = glm::vec3( (focusPointTop.x * cos(angleOfRotation * (i+1) )) - (focusPointTop.z * sin(angleOfRotation * (i+1) )),
                                                        focusPointTop.y,
                                                        ( focusPointTop.z * cos(angleOfRotation * (i+1) )) + (focusPointTop.x * sin(angleOfRotation * (i+1) )) );
                //Rotate normal endpoint
                glm::vec3 newFaceNormalTopPoint = focusPointTop + faceNormalTop * 0.1f;
                newFaceNormalTopPoint = glm::vec3( (newFaceNormalTopPoint.x * cos(angleOfRotation * (i+1) )) - (newFaceNormalTopPoint.z * sin(angleOfRotation * (i+1) )),
                                                   newFaceNormalTopPoint.y,
                                                   (newFaceNormalTopPoint.z * cos(angleOfRotation * (i+1) )) + (newFaceNormalTopPoint.x * sin(angleOfRotation * (i+1) )) );

                CgPolyline* poly = new CgPolyline(idGen->getNextId());
                poly->addVertice(newFocusPointTop);
                poly->addVertice(newFaceNormalTopPoint);
                polylineNormals.push_back(poly);


                //Bottom
                //Rotate fcousPoint
                glm::vec3 newFocusPointBottom = glm::vec3((focusPointBottom.x * cos(angleOfRotation * (i+1) )) - (focusPointBottom.z * sin(angleOfRotation * (i+1) )),
                                                           focusPointBottom.y,
                                                          (focusPointBottom.z * cos(angleOfRotation * (i+1) )) + (focusPointBottom.x * sin(angleOfRotation * (i+1) )) );
                //Rotate normal endpoint
                glm::vec3 newFaceNormalBottomPoint = focusPointBottom + faceNormalBottom * 0.1f;
                newFaceNormalBottomPoint = glm::vec3((newFaceNormalBottomPoint.x * cos(angleOfRotation * (i+1) )) - (newFaceNormalBottomPoint.z * sin(angleOfRotation * (i+1) )),
                                                      newFaceNormalBottomPoint.y,
                                                     (newFaceNormalBottomPoint.z * cos(angleOfRotation * (i+1) )) + (newFaceNormalBottomPoint.x * sin(angleOfRotation * (i+1) )) );

                poly = new CgPolyline(idGen->getNextId());
                poly->addVertice(newFocusPointBottom);
                poly->addVertice(newFaceNormalBottomPoint);
                polylineNormals.push_back(poly);

            }

            //####################### Normal calculation END #######################

            last++;
        }
        //Last face with first point
        m_triangle_indices.push_back(top);
        m_triangle_indices.push_back(last);
        m_triangle_indices.push_back(first);

        m_triangle_indices.push_back(bottom);
        m_triangle_indices.push_back(last);
        m_triangle_indices.push_back(first);


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


