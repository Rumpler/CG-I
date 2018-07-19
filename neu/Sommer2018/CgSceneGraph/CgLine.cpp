#include "CgLine.h"

#include <CgUtils/CgUtils.h>

CgLine::CgLine(int id):
    m_type(Cg::Polyline),
    m_id(id),
    lineWidth(1)
{

}

CgLine::~CgLine()
{
    vertices.clear();
}

void CgLine::addVertice(glm::vec3 vertice)
{
    vertices.push_back(vertice);
}

void CgLine::sdForPointScheme()
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

void CgLine::sdChaikins()
{

}

void CgLine::sdLaneRiesenfeld()
{

}

Cg::ObjectType CgLine::getType() const
{
    return m_type;
}

unsigned int CgLine::getID() const
{
    return m_id;
}

const std::vector<glm::vec3> &CgLine::getVertices() const
{
    return vertices;
}

glm::vec3 CgLine::getColor() const
{
    return color;
}

unsigned int CgLine::getLineWidth() const
{
    return lineWidth;
}

void CgLine::setColor(const glm::vec3 value)
{
    color = value;
}

void CgLine::setLineWidth(unsigned int value)
{
    lineWidth = value;
}

void CgLine::setRotationCurveExample1()
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

void CgLine::printVertices()
{
    std::cout << "Vertices(" << vertices.size() << "):" << std::endl;
    for(glm::vec3 v : vertices){
        std::cout << "(" << v.x << "," << v.y << "," << v.z << ")" << std::endl;
    }
}
