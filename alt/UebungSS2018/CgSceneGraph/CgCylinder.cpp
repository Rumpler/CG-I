#include "CgCylinder.h"
#include <math.h>
#include <iostream>

CgCylinder::CgCylinder(int id):
    m_type(Cg::TriangleMesh),
    m_id(id)
{
    makeCylinder(0.5, 50);

}





CgCylinder::~CgCylinder()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}

//Only works when amountOfSegments > 1
void CgCylinder::makeCylinder(double height, int amountOfSegments)
{
    if(amountOfSegments >= 2){


        //Reset
        m_vertices.clear();
        m_vertex_normals.clear();
        m_triangle_indices.clear();
        m_face_normals.clear();


        //Initial values
        double angleOfRotation = 360.0 / amountOfSegments;
        //Translate in rad
        angleOfRotation = ((2 * M_PI) / 360) * angleOfRotation;
        double x = 0.2;
        double y = 0.0;

        //Top of cylinder
        m_vertices.push_back(glm::vec3(0.0, height, 0.0));

        //First point
        m_vertices.push_back(glm::vec3(x, 0.0, y));

        int top = 0;
        int first = 1;
        int last = 1;

        //Calculate next point and push new face
        for(int i = 0; i < amountOfSegments - 1; i++){

            //TODO BUG new x and y are not correct (getting smaller)

            //Calculation of new x and y
            x = (x * cos(angleOfRotation)) - (y * sin(angleOfRotation));
            y =(y * cos(angleOfRotation)) + (x * sin(angleOfRotation));
            m_vertices.push_back(glm::vec3(x, 0.0, y));

            m_triangle_indices.push_back(top);
            m_triangle_indices.push_back(last);
            m_triangle_indices.push_back(last + 1);
            last++;
        }
        //Last face with first point
        m_triangle_indices.push_back(top);
        m_triangle_indices.push_back(last);
        m_triangle_indices.push_back(first);


    }else{
        std::cout << "To few Segments" << std::endl;
    }
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
