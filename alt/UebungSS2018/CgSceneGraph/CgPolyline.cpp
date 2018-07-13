#include "CgPolyline.h"

#include <CgUtils/CgUtils.h>

CgPolyline::CgPolyline(int id):
    m_type(Cg::Polyline),
    m_id(id),
    lineWidth(1)
{

}

CgPolyline::~CgPolyline()
{
    vertices.clear();
}

void CgPolyline::addVertice(glm::vec3 vertice)
{
    vertices.push_back(vertice);
}

void CgPolyline::sdForPointScheme()
{
    if(vertices.size() < 4){return;} //Check if enough vertices exist




    std::vector<glm::vec3> futureVertices;
    futureVertices.reserve((vertices.size() * 2) - 3); //Size after For-Point-Scheme

    //Vars
    double w = 1.0/16.0;
    int p0, p1, p2, p3;

    //Push first Point (other in loop)
    futureVertices.push_back(vertices.at(0));

    //Calculates new points and adds them futureVertices
    for(int posVertices = 1; posVertices < vertices.size() - 2; posVertices ++){

        //Update futureVertices with old points
        futureVertices.push_back(vertices.at(posVertices));

        //Indexing
        p0 = posVertices - 1;
        p1 = posVertices;
        p2 = posVertices + 1;
        p3 = posVertices + 2;

        //Calculate new Point
        futureVertices.push_back(glm::vec3(CgUtils::multVecScalar(-w, vertices.at(p0)) +
                                           CgUtils::multVecScalar(0.5 + w, vertices.at(p1)) +
                                           CgUtils::multVecScalar(0.5 + w, vertices.at(p2)) -
                                           CgUtils::multVecScalar(w, vertices.at(p3))));
    }

    //Update futureVertices with last two old points
    futureVertices.push_back(vertices.at(vertices.size() - 2));
    futureVertices.push_back(vertices.at(vertices.size() - 1));

    vertices = futureVertices;







    //printVertices();
}

void CgPolyline::sdChaikins()
{

}

void CgPolyline::sdLaneRiesenfeld()
{

}

Cg::ObjectType CgPolyline::getType() const
{
    return m_type;
}

unsigned int CgPolyline::getID() const
{
    return m_id;
}

const std::vector<glm::vec3> &CgPolyline::getVertices() const
{
    return vertices;
}

glm::vec3 CgPolyline::getColor() const
{
    return color;
}

unsigned int CgPolyline::getLineWidth() const
{
    return lineWidth;
}

void CgPolyline::setColor(const glm::vec3 value)
{
    color = value;
}

void CgPolyline::setLineWidth(unsigned int value)
{
    lineWidth = value;
}

void CgPolyline::setRotationCurveExample1()
{
    vertices.clear();
    vertices.push_back(glm::vec3(0.2f, -0.4f, 0.0f));
    vertices.push_back(glm::vec3(0.2f, -0.3f, 0.0f));
    vertices.push_back(glm::vec3(0.4f, -0.2f, 0.0f));
    vertices.push_back(glm::vec3(0.4f, -0.1f, 0.0f));
    vertices.push_back(glm::vec3(0.3f, 0.0f, 0.0f));
    vertices.push_back(glm::vec3(0.1f, 0.1f, 0.0f));
    vertices.push_back(glm::vec3(0.4f, 0.2f, 0.0f));
    vertices.push_back(glm::vec3(0.3f, 0.3f, 0.0f));
    vertices.push_back(glm::vec3(0.3f, 0.4f, 0.0f));
}

void CgPolyline::printVertices()
{
    std::cout << "Vertices(" << vertices.size() << "):" << std::endl;
    for(glm::vec3 v : vertices){
        std::cout << "(" << v.x << "," << v.y << "," << v.z << ")" << std::endl;
    }
}
