#ifndef CGQTVIEWER_CGQTGLRENDERWINDOW_H_
#define CGQTVIEWER_CGQTGLRENDERWINDOW_H_

#include "CgBase/CgBaseRenderWindow.h"
#include <GL/gl.h>
#include <QGLFunctions>

class CgQtGLRenderWindow: public CgBaseRenderWindow, public QGLWidget, public QGLFunctions
{
    Q_OBJECT


    public:

     /* Constuctors and destructor */
    CgQtGLRenderWindow(const QGLFormat & format, QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0  );
    ~CgQtGLRenderWindow(void);


    private:

        /* Transforming colors to opengl */
        glm::vec3 m_backgroundcolor;

        /* Transforming modelview and projection matrix to opengl */
        glm::mat4 m_view;
        glm::mat4 m_projection;


        /* Transforming camera and screen to opengl */
        glm::mat4 m_look_at_matrix;


        /* Methods *******************************************************************/
    protected:
        void paintGL();
    public:
        void initializeGL();
        void resizeGL( int w, int h );

        void setLookAtMatrix( const glm::mat4 arg );


       /* // Qt mouse and key events
        void mousePressEvent( QMouseEvent* );
        void mouseReleaseEvent( QMouseEvent* );
        void mouseMoveEvent( QMouseEvent* );
        void wheelEvent( QWheelEvent* );
        bool event(QEvent *e);
        virtual void keyPressEvent( QKeyEvent* );
        void keyReleaseEvent( QKeyEvent* );

        //Draw
        void drawRenderableObjects( const std::map<int,FhhSgObject*>& objects );
*/


};


#endif /* CGQTVIEWER_CGQTGLRENDERWINDOW_H_ */
