#include "CgQtGlBufferObject.h"
#include "CgBase/CgBasePolyline.h"
#include "CgBase/CgBasePolygonMesh.h"
#include "CgBase/CgBaseTriangleMesh.h"
#include "CgBase/CgBasePointCloud.h"

CgQtGlBufferObject::CgQtGlBufferObject():
 indexbuffer(QOpenGLBuffer::IndexBuffer)
{
       vertexbuffer.create();
       normalbuffer.create();
       indexbuffer.create();
}


CgQtGlBufferObject::CgQtGlBufferObject(QOpenGLShaderProgram* program):
 indexbuffer(QOpenGLBuffer::IndexBuffer)
{
    m_program = program;
    vertexbuffer.create();
    normalbuffer.create();
    indexbuffer.create();
}






void CgQtGlBufferObject::initPolyline(CgBasePolyline* obj)
{

    vertexbuffer.bind();
    vertexbuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexbuffer.allocate(obj->getVertices().data(),  obj->getVertices().size()* sizeof(glm::vec3));
}



void CgQtGlBufferObject::initTriangleMesh(CgBaseTriangleMesh* obj)
{


    vertexbuffer.bind();
    vertexbuffer.allocate(obj->getVertices().data(),  obj->getVertices().size()* sizeof(glm::vec3));

    normalbuffer.bind();
    normalbuffer.allocate(obj->getVertexNormals().data(),  obj->getVertexNormals().size()* sizeof(glm::vec3));

    indexbuffer.bind();
    indexbuffer.allocate(obj->getTriangleIndices().data(),  obj->getTriangleIndices().size()* sizeof(unsigned int));

}

void CgQtGlBufferObject::initPolygonMesh(CgBasePolygonMesh* obj)
{

    // do something more
}

void CgQtGlBufferObject::initPointCloud(CgBasePointCloud* obj)
{

    // do something morec
}

void CgQtGlBufferObject::draw(CgBaseRenderableObject* obj)
{

    if(obj->getType()==Cg::TriangleMesh)
        drawTriangleMesh((CgBaseTriangleMesh*) obj);
    if(obj->getType()==Cg::PolygonalMesh)
        drawPolygonMesh((CgBasePolygonMesh*) obj);
    if(obj->getType()==Cg::Polyline)
        drawPolyline((CgBasePolyline*)obj);
    if(obj->getType()==Cg::PointCloud)
        drawPointCloud((CgBasePointCloud*) obj);
}

void CgQtGlBufferObject::drawTriangleMesh(CgBaseTriangleMesh* obj)
{

    m_program->bind();

    if(obj->getVertices().size()!=0)
    {
        vertexbuffer.bind();
        int vertexlocation = m_program->attributeLocation("vertex");
        m_program->enableAttributeArray(vertexlocation);
        m_program->setAttributeBuffer(vertexlocation, GL_FLOAT, 0, 3 , sizeof(glm::vec3));
    }

    if(obj->getVertexNormals().size()!=0)
    {
        normalbuffer.bind();
        int normallocation = m_program->attributeLocation("normal");
        m_program->enableAttributeArray(normallocation);
        m_program->setAttributeBuffer(normallocation, GL_FLOAT, 0, 3 , sizeof(glm::vec3));
    }

    if(obj->getTriangleIndices().size()!=0)
    {
        indexbuffer.bind();
        glDrawElements(GL_TRIANGLES,obj->getTriangleIndices().size(), GL_UNSIGNED_INT,0);
    }
}


void CgQtGlBufferObject::drawPolyline(CgBasePolyline* obj)
{
    vertexbuffer.bind();
    int vertexlocation = m_program->attributeLocation("vertex");
    m_program->enableAttributeArray(vertexlocation);
    m_program->setAttributeBuffer(vertexlocation, GL_FLOAT, 0, 3 , sizeof(glm::vec3));


    glLineWidth((GLfloat) obj->getLineWidth());
    glDrawArrays(GL_LINE_STRIP,0,obj->getVertices().size());
}


void CgQtGlBufferObject::drawPolygonMesh(CgBasePolygonMesh* obj)
{
    if(obj->getVertices().size()!=0)
    {
        // do something
    }
}

void CgQtGlBufferObject::drawPointCloud(CgBasePointCloud* obj)
{
    if(obj->getVertices().size()!=0)
    {
        // do something
    }
}









