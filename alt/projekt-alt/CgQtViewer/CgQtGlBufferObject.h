#ifndef CGQTGLBUFFEROBJECT_H
#define CGQTGLBUFFEROBJECT_H


class CgBasePolyline;
class CgBaseTriangleMesh;
class CgBasePolygonMesh;
class CgBasePointCloud;
class CgBaseRenderableObject;

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

class CgQtGlBufferObject
{
public:
    CgQtGlBufferObject();
    CgQtGlBufferObject(QOpenGLShaderProgram *);


    QOpenGLBuffer vertexbuffer;
    QOpenGLBuffer normalbuffer;
    QOpenGLBuffer indexbuffer;

    QOpenGLShaderProgram *m_program;

    void draw(CgBaseRenderableObject*);

    void initPolyline(CgBasePolyline* obj);
    void initTriangleMesh(CgBaseTriangleMesh* obj);
    void initPolygonMesh(CgBasePolygonMesh* obj);
    void initPointCloud(CgBasePointCloud* obj);

private:

    void drawPolyline(CgBasePolyline* obj);
    void drawTriangleMesh(CgBaseTriangleMesh* obj);
    void drawPolygonMesh(CgBasePolygonMesh* obj);
    void drawPointCloud(CgBasePointCloud* obj);

};

#endif // CGQTGLBUFFEROBJECT_H
