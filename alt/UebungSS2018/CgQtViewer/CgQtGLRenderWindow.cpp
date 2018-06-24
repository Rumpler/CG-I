
#include <iostream>

#include <GL/glew.h>
#include "CgQtGLRenderWindow.h"
#include <QtOpenGL/QtOpenGL>


CgQtGLRenderWindow::CgQtGLRenderWindow(const QGLFormat& format, QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f)
    : QGLWidget(format, parent, shareWidget, f),
      m_view(1.0),
      m_projection(1.0),
      m_backgroundcolor(0.0,0.0,0.0)
{

    setFocusPolicy(Qt::StrongFocus);
    setWindowTitle(tr("OpenGL Render Window"));

    makeCurrent();
    initializeGL();
}



void CgQtGLRenderWindow::initializeGL()
{

    //GLEW aktivieren und testen
    GLenum err = glewInit();
    if( GLEW_OK != err )
        std::cout << "Error initializing GLEW: %s\n" << glewGetErrorString(err) << std::endl;
    else
        std::cout<< "GLEW erfolgreich geladen" << std::endl;



    //Ausgabe der aktiven GLSL-Version
    const GLubyte *renderer = glGetString( GL_RENDERER );
    const GLubyte *vendor = glGetString( GL_VENDOR );
    const GLubyte *version = glGetString( GL_VERSION );
    const GLubyte *glslVersion =
    glGetString( GL_SHADING_LANGUAGE_VERSION );
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);


    std::cout << "GL Vendor : \t\t" << vendor << std::endl;
    std::cout << "GL Renderer : \t\t" << renderer << std::endl;
    std::cout << "GL Version (string) : \t" << version << std::endl;
    std::cout << "GL Version (integer) : \t" << major << minor <<  std::endl;
    std::cout << "GLSL Version : \t\t" << glslVersion << std::endl << std::endl;


    //Allgemeine Einstellungen und initialisierungen
    initializeGLFunctions();
    initializeOverlayGL();


    glEnable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

}



void CgQtGLRenderWindow::paintGL()
{
    glClearColor(m_backgroundcolor.x,m_backgroundcolor.y,m_backgroundcolor.z, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //render();

    glFlush();
}

void CgQtGLRenderWindow::resizeGL( int w, int h )
{

    glViewport(0, 0, w, h);

    // todo: window resize event abschicken
}

void CgQtGLRenderWindow::setLookAtMatrix( const glm::mat4 arg )
{
    m_look_at_matrix=arg;
}











