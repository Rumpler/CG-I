
#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "CgQtViewer/CgQtMainApplication.h"
#include "CgQtViewer/CgQtGLRenderWidget.h"
#include "CgQtViewer/CgQtGui.h"
#include "CgSceneGraph/CgSceneControl.h"

int main(int argc, char **argv) {




    /*************************************************************************************/
    /*   View: Qt-Anwendung und QtGL-View erzeugen                                       */
    /*************************************************************************************/


    QApplication app(argc, argv);

       QCoreApplication::setApplicationName("Übung Computergrafik 1 -  SoSe 2018");
       QCoreApplication::setOrganizationName("QtProject");
       QCoreApplication::setApplicationVersion(QT_VERSION_STR);
       QCommandLineParser parser;
       parser.setApplicationDescription(QCoreApplication::applicationName());
       parser.addHelpOption();
       parser.addVersionOption();
       QCommandLineOption multipleSampleOption("multisample", "Multisampling");
       parser.addOption(multipleSampleOption);
       QCommandLineOption coreProfileOption("coreprofile", "Use core profile");
       parser.addOption(coreProfileOption);
       QCommandLineOption transparentOption("transparent", "Transparent window");
       parser.addOption(transparentOption);

       parser.process(app);

       QSurfaceFormat fmt;
       fmt.setDepthBufferSize(24);
       if (parser.isSet(multipleSampleOption))
           fmt.setSamples(4);
       if (parser.isSet(coreProfileOption)) {
           fmt.setVersion(3, 2);
           fmt.setProfile(QSurfaceFormat::CoreProfile);
       }
       QSurfaceFormat::setDefaultFormat(fmt);

       CgQtMainApplication mainApp;

       CgQtGLRenderWidget::setTransparent(parser.isSet(transparentOption));
       if (CgQtGLRenderWidget::isTransparent()) {
           mainApp.setAttribute(Qt::WA_TranslucentBackground);
           mainApp.setAttribute(Qt::WA_NoSystemBackground, false);
       }
       mainApp.resize(mainApp.sizeHint());
       int desktopArea = QApplication::desktop()->width() *
                        QApplication::desktop()->height();
       int widgetArea = mainApp.width() * mainApp.height();
       if (((float)widgetArea / (float)desktopArea) < 0.75f)
           mainApp.show();
       else
           mainApp.showMaximized();


    /*************************************************************************************/
    /*   Control: Scene-Controller erzeugen                                              */
    /*************************************************************************************/

       CgSceneControl* scene_control = new CgSceneControl();

       // Controller und View über Observer Pattern verbinden
       mainApp.getGui()->attachObserver(scene_control);


       // Renderer über Control ansteuerbar machen
       scene_control->setRenderer(mainApp.getGui()->getRenderer());


   /*************************************************************************************/
   /*   Model: Scene erzeugen                                                           */
   /*************************************************************************************/

       //  innerhalbb der SceneControl Klasse,



    return app.exec();
}


