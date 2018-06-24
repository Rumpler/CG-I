
#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <string>
#include <glm/glm.hpp>



struct Face
{
    int a;
    int b;
    int c;
};

struct TexCoord
{
    float u;
    float v;
    TexCoord(): u(0), v(0) {}
    TexCoord(float _u, float _v): u(_u), v(_v) {}
    float& operator[](int idx);
};



class ObjLoader
{
public:
    ObjLoader();
    ~ObjLoader();

    void load(std::string filename);

    int getIndexCount();
    int getVertCount();

    void getFaceIndexData(std::vector<unsigned int>& arg_indices);
    void getPositionData(std::vector<glm::vec3>& arg_verts);
    void getNormalData(std::vector<glm::vec3>& arg_normals);

    int getTexCoordLayers();
    const float* getTexCoords(int multiTexCoordLayer);

private:

    std::vector<Face> Faces;
    std::vector<glm::vec3> Positions;
    std::vector<glm::vec3> Normals;

    // obj's only have 1 layer ever
    std::vector<TexCoord> TexCoords;
    unsigned int TexCoordLayers;

    void split(const std::string &in,
            std::vector<std::string> &out,
            std::string token);

    std::string tail(const std::string &in);
    std::string firstToken(const std::string &in);

    double s2f(std::string str);
    int s2i(std::string str);


};

#endif // OBJLOADER_H
