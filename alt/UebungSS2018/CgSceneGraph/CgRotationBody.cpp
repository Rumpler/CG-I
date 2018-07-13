#include "CgRotationBody.h"

CgRotationBody::CgRotationBody(int id, CgPolyline* contourCurve, int amountOfSegments):
    m_type(Cg::TriangleMesh),
    m_id(id),
    contourCurve(contourCurve)
{
    std::vector<glm::vec3> contourCurveVertices = contourCurve->getVertices();

    //Check if enough vertices exist
    if(contourCurveVertices.size() < 2 || amountOfSegments < 2){return;}

    //Angle calculation
    double angleOfRotation = 360.0 / amountOfSegments;
    angleOfRotation = ((2.0 * M_PI) / 360.0) * angleOfRotation;     //Translate in rad

    //Vars for loop
    double currentAngle;
    glm::vec3 currentRotateVertice;

    /* ##################### Add all vertices ##################### */
    for(int i = 0; i < contourCurveVertices.size() /* ? */; i++){   //For every vertice in contourCurve
        currentRotateVertice = contourCurveVertices.at(i);

        for(int j = 0; j < amountOfSegments; j++){                  //Rotate current vertice and add to vertices
            currentAngle = currentAngle * j;
            m_vertices.push_back(CgUtils::rotatePointYAxis(currentAngle, currentRotateVertice));
        }
    }











    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(2);

}

Cg::ObjectType CgRotationBody::getType() const
{
    return m_type;
}

unsigned int CgRotationBody::getID() const
{
    return m_id;
}

const std::vector<glm::vec3> &CgRotationBody::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3> &CgRotationBody::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3> &CgRotationBody::getVertexColors() const
{
    return m_vertex_colors;
}

const std::vector<glm::vec2> &CgRotationBody::getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int> &CgRotationBody::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3> &CgRotationBody::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3> &CgRotationBody::getFaceColors() const
{
    return m_face_colors;
}
