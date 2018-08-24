#include "CgLine.h"

#include <CgUtils/CgUtils.h>

CgLine::CgLine(int id): CgPolyline::CgPolyline(id)
{

}

CgLine::CgLine(int id, glm::vec3 p1, glm::vec3 p2) : CgPolyline::CgPolyline(id)
{
    vertices.push_back(p1);
    vertices.push_back(p2);
}

CgLine::~CgLine()
{
    vertices.clear();
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
    for(int posVertices = 1; posVertices < vertices.size() - 2; posVertices ++)
    {
        //Update futureVertices with old points
        futureVertices.push_back(vertices.at(posVertices));

        //Indexing
        p0 = posVertices - 1;
        p1 = posVertices;
        p2 = posVertices + 1;
        p3 = posVertices + 2;

        //Calculate new Point
        futureVertices.push_back(glm::vec3(CgU::multVecScalar(-w, vertices.at(p0)) +
                                           CgU::multVecScalar(0.5 + w, vertices.at(p1)) +
                                           CgU::multVecScalar(0.5 + w, vertices.at(p2)) -
                                           CgU::multVecScalar(w, vertices.at(p3))));
    }

    //Update futureVertices with last two old points
    futureVertices.push_back(vertices.at(vertices.size() - 2));
    futureVertices.push_back(vertices.at(vertices.size() - 1));

    vertices = futureVertices;
}

void CgLine::sdChaikins()
{

}

void CgLine::sdLaneRiesenfeld()
{

}

