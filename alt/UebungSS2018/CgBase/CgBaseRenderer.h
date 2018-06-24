#ifndef CGBASERENDERER
#define CGBASERENDERER

#include <glm/glm.hpp>
class CgBaseRenderableObject;
class CgBaseSceneControl;

class CgBaseRenderer
{


    public:

     virtual void render(CgBaseRenderableObject*,glm::mat4 world_coordinates)=0;
     virtual void init(CgBaseRenderableObject*)=0;
     virtual void setLookAtMatrix(glm::mat4 lookat)=0;
     virtual void setProjectionMatrix(glm::mat4 proj)=0;
     virtual void setSceneControl(CgBaseSceneControl*)=0;
    
     virtual void setShaderSourceFiles(std::string filename_vert,std::string filename_fragment)=0;

       // virtual void deleteUniformValue(std::string);
     virtual void setUniformValue(std::string,glm::mat3)=0;
     virtual void setUniformValue(std::string,glm::mat4)=0;
     virtual void setUniformValue(std::string,glm::vec3)=0;
     virtual void setUniformValue(std::string,glm::vec4)=0;
     virtual void setUniformValue(std::string,double)=0;
     virtual void setUniformValue(std::string,int)=0;

        virtual void redraw()=0;
};





#endif // CGBASERENDERER

