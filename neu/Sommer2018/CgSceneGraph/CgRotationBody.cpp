#include "CgRotationBody.h"

CgRotationBody::CgRotationBody(int id, CgLine* contourCurve, int amountOfSegments): CgTriangleMesh::CgTriangleMesh(id),
    contourCurve(contourCurve),
    amountOfSegments(amountOfSegments)
{
    makeRotationBody(contourCurve, amountOfSegments);
}

void CgRotationBody::makeRotationBody(CgLine *contourCurve, int amountOfSegments)
{
    std::vector<glm::vec3> contourCurveVertices = contourCurve->getVertices();

    //Check if enough vertices exist
    if(contourCurveVertices.size() < 2 || amountOfSegments < 2){return;}

    //memory if normals should be displayed
    bool displayPolyNormals;
    if(polylineNormals.size() > 0){displayPolyNormals = polylineNormals.at(0)->getDisplay();}else{displayPolyNormals = false;}  //else when cylinder is constructed

    //reset
    m_vertices.clear();
    m_triangle_indices.clear();
    polylineNormals.clear();
    m_vertex_normals.clear();
    m_face_normals.clear();


    //Angle calculation
    double angleOfRotation = 360.0 / amountOfSegments;
    angleOfRotation = ((2.0 * M_PI) / 360.0) * angleOfRotation;     //Translate in rad

    //Vars for loops
    double currentAngle;
    glm::vec3 currentRotateVertice;
    int layerCounter;

    /* ##################### Add all vertices ##################### */
    for(int i = 0; i < contourCurveVertices.size(); i++){   //For every vertice in contourCurve
        currentRotateVertice = contourCurveVertices.at(i);

        for(int j = 0; j < amountOfSegments; j++){                  //Rotate current vertice and add to vertices
            currentAngle = angleOfRotation * j;
            m_vertices.push_back(CgU::rotatePointYAxis(currentAngle, currentRotateVertice));
        }
    }

    /* ##################### Add triangle indices ##################### */
    for(int i = 0; i < amountOfSegments * (contourCurveVertices.size() - 1); i++){
        layerCounter = (i / amountOfSegments);

        m_triangle_indices.push_back(i + amountOfSegments);
        m_triangle_indices.push_back( ((i + 1) % amountOfSegments) + (layerCounter * amountOfSegments) + amountOfSegments);
        m_triangle_indices.push_back(i);

        m_triangle_indices.push_back( ((i + 1) % amountOfSegments) + (layerCounter * amountOfSegments) + amountOfSegments);
        m_triangle_indices.push_back( ((i + 1) % amountOfSegments) + (layerCounter * amountOfSegments));
        m_triangle_indices.push_back(i);
    }
    computeNormals();
    fillPolylineNormals();
}

int CgRotationBody::getAmountOfSegments() const
{
    return amountOfSegments;
}
