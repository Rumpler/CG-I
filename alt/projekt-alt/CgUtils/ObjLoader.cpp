#include "ObjLoader.h"

#include <iostream>

#include <cstdlib>
#include <fstream>
#include <sstream>
#include<string>
#include <assert.h>
#include <map>

using namespace std;




float& TexCoord::operator[](int idx)
{
    assert(idx > 0);
    assert(idx < 3);
    return *(&u + idx);
}

struct FaceVert
{
    FaceVert() : vert(-1), norm(-1), coord(-1) {}

    int vert;
    int norm;
    int coord;
};

struct vert_less {
    bool operator() (const FaceVert& lhs, const FaceVert& rhs) const
    {
        // handle any size mesh
        if (lhs.vert != rhs.vert) return (lhs.vert<rhs.vert);
        if (lhs.norm != rhs.norm) return (lhs.norm<rhs.norm);
        if (lhs.coord!=rhs.coord) return (lhs.coord<rhs.coord);
        return false;
        // the following breaks down on very large meshes
        // const unsigned long prime1 = 73856093;
        // const unsigned long prime2 = 19349663;
        // const unsigned long prime3 = 83492791;
        // unsigned long lh = (lhs.vert * prime1) ^ (lhs.norm * prime2) ^ (lhs.coord * prime3);
        // unsigned long rh = (rhs.vert * prime1) ^ (rhs.norm * prime2) ^ (rhs.coord * prime3);
        // return lh < rh;
    }
};

ObjLoader::ObjLoader()
    : TexCoordLayers(1)
{

}

ObjLoader::~ObjLoader()
{
    Positions.clear();
    Normals.clear();
    Faces.clear();
}

void ObjLoader::load(std::string filename)
{

    if (filename.substr(filename.size() - 4, 4) != ".obj")
        return;

    std::ifstream inf(filename.c_str());

    if (!inf.is_open()) {
        cerr << "[!] Failed to load file: " << filename << endl;
    }

    Positions.clear();
    Normals.clear();
    TexCoords.clear();
    Faces.clear();



    std::vector<glm::vec3> verts;
    std::vector<glm::vec3> norms;
    std::vector<TexCoord> texcoords;

    std::map<FaceVert, int, vert_less> uniqueverts;
    unsigned int vert_count = 0;

    std::string curline;

    while (std::getline(inf, curline))
    {

        std::string token=firstToken(curline);

        if (token == "" || token == "#" || token == "$"|| token == "m" || token == "g" || token == "u"|| token == "s")
            continue;



        // Generate a Vertex Position
        if (token == "v")
        {
            std::vector<std::string> spos;
            split(tail(curline), spos, " ");



            double x = s2f(spos[0]);
            double y = s2f(spos[1]);
            double z = s2f(spos[2]);

            verts.push_back( glm::vec3(x,y,z));
        }
        // Generate a Vertex Texture Coordinate
        if (token == "vt")
        {
            std::vector<std::string> stex;

            split(tail(curline), stex, " ");

            float x = s2f(stex[0]);
            float y = s2f(stex[1]);

            texcoords.push_back( TexCoord(x, y));
        }
        // Generate a Vertex Normal;
        if (token == "vn")
        {

            std::vector<std::string> snor;
            split(tail(curline), snor, " ");

            float x = s2f(snor[0]);
            float y = s2f(snor[1]);
            float z = s2f(snor[2]);

            norms.push_back(glm::vec3(x,y,z) );
        }

        // faces start with:
        //	f
        if (token == "f")
        {

            std::vector<int> vindices;
            std::vector<int> nindices;
            std::vector<int> tindices;

            std::vector<std::string> sface, svert;

            split(tail(curline), sface, " ");



            // For every given vertex do this
            for (int i = 0; i < int(sface.size()); i++)
            {
                // See What type the vertex is.
                int vtype;

                split(sface[i], svert, "/");

                // Check for just position - v1
                if (svert.size() == 1)
                {
                    // Only position
                    vtype = 1;
                }

                // Check for position & texture - v1/vt1
                if (svert.size() == 2)
                {
                    // Position & Texture
                    vtype = 2;
                }

                // Check for Position, Texture and Normal - v1/vt1/vn1
                // or if Position and Normal - v1//vn1
                if (svert.size() == 3)
                {
                    if (svert[1] != "")
                    {
                        // Position, Texture, and Normal
                        vtype = 4;
                    }
                    else
                    {
                        // Position & Normal
                        vtype = 3;
                    }
                }

                // Calculate and store the vertex
                switch (vtype)
                {
                    case 1: // P
                    {
                        vindices.push_back(s2i(svert[0])-1);
                        break;
                    }
                    case 2: // P/T
                    {
                        vindices.push_back(s2i(svert[0])-1);
                        tindices.push_back(s2i(svert[1])-1);
                        break;
                    }
                    case 3: // P//N
                    {
                        vindices.push_back(s2i(svert[0])-1);
                        nindices.push_back(s2i(svert[2])-1);
                        break;
                    }
                    case 4: // P/T/N
                    {
                        vindices.push_back(s2i(svert[0])-1);
                        tindices.push_back(s2i(svert[1])-1);
                        nindices.push_back(s2i(svert[2])-1);
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }



            // being that some exporters can export either 3 or 4 sided polygon's
            // convert what ever was exported into triangles
            for (size_t i=1; i<vindices.size()-1; ++i)
            {
                Face face;
                FaceVert tri;

                tri.vert = vindices[0];
                if (!nindices.empty())
                    tri.norm = nindices[0];
                if (!tindices.empty())
                    tri.norm = tindices[0];

                if (uniqueverts.count(tri) == 0)
                    uniqueverts[tri] = vert_count++;
                face.a = uniqueverts[tri];

                tri.vert = vindices[i];
                if (!nindices.empty())
                    tri.norm = nindices[i];
                if (!tindices.empty())
                    tri.norm = tindices[i];

                if (uniqueverts.count(tri) == 0)
                    uniqueverts[tri] = vert_count++;
                face.b = uniqueverts[tri];

                tri.vert = vindices[i+1];
                if (!nindices.empty())
                    tri.norm = nindices[i+1];
                if (!tindices.empty())
                    tri.norm = tindices[i+1];

                if (uniqueverts.count(tri) == 0)
                    uniqueverts[tri] = vert_count++;
                face.c = uniqueverts[tri];
                Faces.push_back(face);
            } // for convert to triangle


         }// for each index in line

        }//if line starts with "f"

    } // for each line

    inf.close();

    // use resize instead of reserve because we'll be indexing in random locations.
    Positions.resize(vert_count);
    if (norms.size() > 0)
        Normals.resize(vert_count);
    if (texcoords.size() > 0)
        TexCoords.resize(vert_count);

    std::map<FaceVert, int, vert_less>::iterator iter;
    for (iter = uniqueverts.begin(); iter != uniqueverts.end(); ++iter) {

        Positions[iter->second] = verts[iter->first.vert];

        if ( norms.size() > 0 ) {
            Normals[iter->second] = norms[iter->first.norm];
        }

        if ( texcoords.size() > 0) {
            TexCoords[iter->second] = texcoords[iter->first.coord];
        }
    }
}

int ObjLoader::getIndexCount()
{
    return (int)Faces.size() * 3;
}

int ObjLoader::getVertCount()
{
    return (int)Positions.size();
}



void ObjLoader::getFaceIndexData(std::vector<unsigned int>& arg_indices)
{
    arg_indices.clear();
    for(unsigned int i=0;i<Faces.size();i++)
    {
         arg_indices.push_back(Faces[i].a);
         arg_indices.push_back(Faces[i].b);
         arg_indices.push_back(Faces[i].c);
    }

}

void ObjLoader::getPositionData(std::vector<glm::vec3>& arg_verts)
{
    arg_verts.clear();
    arg_verts=Positions;
}

void ObjLoader::getNormalData(std::vector<glm::vec3>& arg_normals)
{
    arg_normals.clear();
    arg_normals=Normals;
}

int ObjLoader::getTexCoordLayers()
{
    return TexCoordLayers;
}

const float* ObjLoader::getTexCoords(int multiTexCoordLayer)
{
    assert(multiTexCoordLayer < TexCoordLayers);
    return (const float*)&TexCoords[0];
}


// Split a String into a string array at a given token
void ObjLoader::split(const std::string &in,
        std::vector<std::string> &out,
        std::string token)
{
    out.clear();

    std::string temp;

    for (int i = 0; i < int(in.size()); i++)
    {
        std::string test = in.substr(i, token.size());

        if (test == token)
        {
            if (!temp.empty())
            {
                out.push_back(temp);
                temp.clear();
                i += (int)token.size() - 1;
            }
            else
            {
                out.push_back("");
            }
        }
        else if (i + token.size() >= in.size())
        {
            temp += in.substr(i, token.size());
            out.push_back(temp);
            break;
        }
        else
        {
            temp += in[i];
        }
    }
}

// Get tail of string after first token and possibly following spaces
std::string ObjLoader::tail(const std::string &in)
{
    size_t token_start = in.find_first_not_of(" \t");
    size_t space_start = in.find_first_of(" \t", token_start);
    size_t tail_start = in.find_first_not_of(" \t", space_start);
    size_t tail_end = in.find_last_not_of(" \t");
    if (tail_start != std::string::npos && tail_end != std::string::npos)
    {
        return in.substr(tail_start, tail_end - tail_start + 1);
    }
    else if (tail_start != std::string::npos)
    {
        return in.substr(tail_start);
    }
    return "";
}

// Get first token of string
std::string ObjLoader::firstToken(const std::string &in)
{
    if (!in.empty())
    {
        size_t token_start = in.find_first_not_of(" \t");
        size_t token_end = in.find_first_of(" \t", token_start);
        if (token_start != std::string::npos && token_end != std::string::npos)
        {
            return in.substr(token_start, token_end - token_start);
        }
        else if (token_start != std::string::npos)
        {
            return in.substr(token_start);
        }
    }
    return "";
}


double ObjLoader::s2f(std::string str)
{
 istringstream buffer(str);
 double temp;
 buffer >> temp;
 return temp;
}

int ObjLoader::s2i(std::string str)
{
 istringstream buffer(str);
 int temp;
 buffer >> temp;
 return temp;
}
