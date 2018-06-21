#ifndef CgQtGLRenderWidget_H
#define CgQtGLRenderWidget_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

#include "../CgBase/CgBaseRenderer.h"
#include <glm/glm.hpp>

class CgBaseSceneControl;
class CgQtGlBufferObject;
class CgTrackball;



QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class CgQtGLRenderWidget : public QOpenGLWidget,public CgBaseRenderer, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    CgQtGLRenderWidget(QWidget *parent = 0);
    ~CgQtGLRenderWidget();
    void redraw();


    static bool isTransparent() { return m_transparent; }
    static void setTransparent(bool t) { m_transparent = t; }

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public:

    // inherited interface from CgBaseRenderer
    void render(CgBaseRenderableObject*,glm::mat4 world_coordinates);
    void init(CgBaseRenderableObject*);
    void setLookAtMatrix(glm::mat4 lookat);
    void setProjectionMatrix(glm::mat4 proj);
    void setSceneControl(CgBaseSceneControl* scene_control) {m_scene_control=scene_control;}

    void setShaderSourceFiles(std::string filename_vert,std::string filename_fragment);

    void setUniformValue(std::string,glm::mat3);
    void setUniformValue(std::string,glm::mat4);
    void setUniformValue(std::string,glm::vec3);
    void setUniformValue(std::string,glm::vec4);
    void setUniformValue(std::string,double);
    void setUniformValue(std::string,int);

    void setCustomRotation(bool arg);
    bool getCustomRotation();
    void setLighting(bool arg);
    bool getLighting();


public slots:



    void slotCustomRotation();
    void slotLighting();
    void slotPolygonPoints();
    void slotPolygonWireframe();
    void slotPolygonFilled();
    void cleanup();

signals:

    void mouseEvent(QMouseEvent *event) ;
    void viewportChanged(int w, int h);


protected:
    void initializeGL() ;
    void paintGL() ;
    void resizeGL(int width, int height) ;
    void mousePressEvent(QMouseEvent *event) ;
    void mouseMoveEvent(QMouseEvent *event) ;
    void mouseReleaseEvent(QMouseEvent *event) ;

private:
    void setupVertexAttribs();

    bool m_core;


    QOpenGLShaderProgram *m_program;

    int m_projMatrixLoc;
    int m_mvMatrixLoc;
    int m_normalMatrixLoc;
    int m_lightPosLoc;
    int m_calcLightingLoc;
    int m_ColorLoc;
    int m_UseSingleColorLoc;

    glm::mat4x4 m_proj;
    glm::mat4x4 m_lookat;
    glm::mat4x4 m_world;
    static bool m_transparent;
    glm::vec3 m_light_pos;

    bool m_custom_rotation;
    bool m_lighting;


    CgBaseSceneControl* m_scene_control;
    bool m_backface_culling;
    int m_polygonmode;


    CgTrackball* m_trackball;

    std::map<unsigned int,CgQtGlBufferObject*> m_gl_buffer_objects;

    std::map<std::string,int> m_attribute_locations;

};




#endif // CgQtGLRenderWidget_H

