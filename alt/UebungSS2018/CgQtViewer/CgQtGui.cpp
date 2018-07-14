

#include "CgQtGLRenderWidget.h"
#include "CgQtGui.h"
#include "CgQtMainApplication.h"
#include "../CgBase/CgEnums.h"
#include "../CgEvents/CgMouseEvent.h"
#include "../CgEvents/CgKeyEvent.h"
#include "../CgEvents/CgWindowResizeEvent.h"
#include "../CgEvents/CgColorChangeEvent.h"
#include "../CgEvents/CgObjectSelectionChangeEvent.h"
#include "../CgEvents/CgValueChangedEvent.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QMenuBar>
#include <QLine>
#include <QActionGroup>
#include <iostream>
#include <QFileDialog>
#include <CgEvents/CgResetEvent.h>
#include <CgEvents/CgSubdivisionEvent.h>



CgQtGui::CgQtGui(CgQtMainApplication *mw)
    : m_mainWindow(mw)
{
    m_glRenderWidget = new CgQtGLRenderWidget;

    connect(m_glRenderWidget, SIGNAL(mouseEvent(QMouseEvent*)), this, SLOT(mouseEvent(QMouseEvent*)));
    connect(m_glRenderWidget, SIGNAL(viewportChanged(int,int)), this, SLOT(viewportChanged(int,int)));


    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;

    //Add new panels here
    m_panel_objects = new QWidget;
    createOptionPanelObjects(m_panel_objects);
    m_panel_rotate_objects = new QWidget;
    createOptionPanelRotateObjects(m_panel_rotate_objects);

    QTabWidget* m_tabs = new QTabWidget();

    m_tabs->addTab(m_panel_objects,"&Objects");
    m_tabs->addTab(m_panel_rotate_objects, "&Rotate Objects");
    container->addWidget(m_tabs);

    m_tabs->setMaximumWidth(400);

    container->addWidget(m_glRenderWidget);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);

    setLayout(mainLayout);
    setWindowTitle(tr("Übung Computergrafik 1 -  SoSe 2018"));


    /* create Menu Bar */
    m_menuBar = new QMenuBar;
    QMenu *file_menu = new QMenu("&File" );
    file_menu->addAction("&Open Mesh Model", this, SLOT(slotLoadMeshFile()));
    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    QMenu *settings_menu = new QMenu("&Setting" );
    QMenu *polygon_mode_menu = new QMenu("&Polygon Mode" );

    QAction* m_custom_rot=settings_menu->addAction("&Custom Rotations", m_glRenderWidget, SLOT(slotCustomRotation()));
    m_custom_rot->setCheckable(true);
    m_custom_rot->setChecked(false);

    QAction* m_lighting=settings_menu->addAction("&Lighting on", m_glRenderWidget, SLOT(slotLighting()));
    m_lighting->setCheckable(true);
    m_lighting->setChecked(false);


    QActionGroup* polygonmode_group = new QActionGroup(this);
    polygonmode_group->setExclusive(true);

    QAction* points=polygon_mode_menu->addAction("&Points", m_glRenderWidget, SLOT(slotPolygonPoints()));
    points->setCheckable(true);
    points->setChecked(false);


    QAction* wireframe=polygon_mode_menu->addAction("&Wireframe", m_glRenderWidget, SLOT(slotPolygonWireframe()));
    wireframe->setCheckable(true);
    wireframe->setChecked(true);

    QAction* filled=polygon_mode_menu->addAction("&Filled", m_glRenderWidget, SLOT(slotPolygonFilled()));
    filled->setCheckable(true);
    filled->setChecked(false);



    polygonmode_group->addAction(points);
    polygonmode_group->addAction(wireframe);
    polygonmode_group->addAction(filled);



    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    m_menuBar->addMenu( settings_menu );
    m_menuBar->addMenu( polygon_mode_menu );


    m_mainWindow->setMenuBar(m_menuBar);

}

QSlider *CgQtGui::createColorSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(1, 100);
    slider->setSingleStep(1);
    slider->setPageStep(1);
    slider->setTickInterval(1);
    slider->setOrientation(Qt::Horizontal);
    return slider;
}


void CgQtGui::createOptionPanelObjects(QWidget *parent)
{
    QVBoxLayout *panel_layout = new QVBoxLayout();
    QVBoxLayout *subBox = new QVBoxLayout();


    QGroupBox* groupBox = new QGroupBox("Objects for rendering ");

    ButtonGroupObjects = new QButtonGroup(subBox);
    ButtonGroupObjects->setExclusive(false);

    QRadioButton* radiobuttonCoordinateSystem = new QRadioButton("&Coordinate-System");
    QRadioButton* radiobuttonCube = new QRadioButton("&Cube");
    QRadioButton* radiobuttonCubeNormals = new QRadioButton("&Cube normals");
    QRadioButton* radiobuttonCylinder = new QRadioButton("&Cylinder");
    QRadioButton* radiobuttonCylinderNormals = new QRadioButton("&Cylinder normals");
    QRadioButton* radiobuttonRotationCurve = new QRadioButton("&Rotation curve");
    QRadioButton* radiobuttonRotationBody = new QRadioButton("&Rotation Body");

    radiobuttonCoordinateSystem->setChecked(true);

    ButtonGroupObjects->addButton(radiobuttonCoordinateSystem,0);
    ButtonGroupObjects->addButton(radiobuttonCube,1);
    ButtonGroupObjects->addButton(radiobuttonCubeNormals,2);
    ButtonGroupObjects->addButton(radiobuttonCylinder,3);
    ButtonGroupObjects->addButton(radiobuttonCylinderNormals,4);
    ButtonGroupObjects->addButton(radiobuttonRotationCurve,5);
    ButtonGroupObjects->addButton(radiobuttonRotationBody,6);

    ButtonGroupObjects->button(2)->setDisabled(true);
    ButtonGroupObjects->button(4)->setDisabled(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radiobuttonCoordinateSystem);
    vbox->addWidget(radiobuttonCube);
    vbox->addWidget(radiobuttonCubeNormals);
    vbox->addWidget(radiobuttonCylinder);
    vbox->addWidget(radiobuttonCylinderNormals);
    vbox->addWidget(radiobuttonRotationCurve);
    vbox->addWidget(radiobuttonRotationBody);

    vbox->addStretch(1);
    groupBox->setLayout(vbox);
    subBox->addWidget(groupBox);

    // COLOR ------------------------------------

    QGroupBox* groupBoxColor = new QGroupBox("Color");
    QVBoxLayout *vboxColor = new QVBoxLayout;

    sliderRed = createColorSlider();
    sliderGreen = createColorSlider();
    sliderBlue = createColorSlider();

    QLabel *label_red = new QLabel("Red");
    QLabel *label_green = new QLabel("Green");
    QLabel *label_blue = new QLabel("Blue");

    sliderRed->setValue(100);
    sliderGreen->setValue(40);
    sliderBlue->setValue(1);


    connect(sliderRed, SIGNAL( valueChanged(int) ), this, SLOT( slotColorChanged() ));
    connect(sliderGreen, SIGNAL( valueChanged(int) ), this, SLOT( slotColorChanged() ));
    connect(sliderBlue, SIGNAL( valueChanged(int) ), this, SLOT( slotColorChanged() ));


    vboxColor->addWidget(label_red);
    vboxColor->addWidget(sliderRed);

    vboxColor->addWidget(label_green);
    vboxColor->addWidget(sliderGreen);

    vboxColor->addWidget(label_blue);
    vboxColor->addWidget(sliderBlue);

    vboxColor->addStretch(1);

    groupBoxColor->setLayout(vboxColor);

    subBox->addWidget(groupBoxColor);

    //-------------------------------------------


    subBox->addStretch(1);
    panel_layout->addLayout(subBox);

    connect(ButtonGroupObjects, SIGNAL( buttonClicked(int) ), this, SLOT( slotButtonGroupSelectionChanged() ) );



    parent->setLayout(panel_layout);
}

void CgQtGui::createOptionPanelRotateObjects(QWidget *parent)
{
    QVBoxLayout *panel_layout = new QVBoxLayout();

    //################################### Cylinder ###################################

    QGroupBox* groupBoxCylinder = new QGroupBox("Cylinder");
    QVBoxLayout *vboxCylinder = new QVBoxLayout;


    //SpinBox AmountOfSegments
    spinBoxAmountOfSegmentsCylinder = new QSpinBox();
    //spinBoxAmountOfSegments->setMinimum(2);
    spinBoxAmountOfSegmentsCylinder->setValue(50);
    spinBoxAmountOfSegmentsCylinder->setMaximum(10000);
//    spinBoxAmountOfSegmentsCylinder->setSuffix(" Segments");
    spinBoxAmountOfSegmentsCylinder->setPrefix("Segments: ");
    connect(spinBoxAmountOfSegmentsCylinder, SIGNAL(valueChanged(int) ), this, SLOT(slotCylinderChanged()) );
    vboxCylinder->addWidget(spinBoxAmountOfSegmentsCylinder);


    //DoubleSpinBox Height
    spinBoxHeightCylinderCone = new QDoubleSpinBox();
    spinBoxHeightCylinderCone->setMinimum(0.01);
    spinBoxHeightCylinderCone->setValue(0.5);
    spinBoxHeightCylinderCone->setSingleStep(0.01);
//    spinBoxHeightCylinderCone->setSuffix(" Height");
    spinBoxHeightCylinderCone->setPrefix("Height: ");
    connect(spinBoxHeightCylinderCone, SIGNAL(valueChanged(double) ), this, SLOT(slotCylinderChanged()) ); // TODO
    vboxCylinder->addWidget(spinBoxHeightCylinderCone);



    //Button Show cylinder and normals
    QPushButton* buttonCylinder = new QPushButton("&Show Cylinder and Normals");
    connect(buttonCylinder, SIGNAL( clicked() ), this, SLOT(slotShowCylinder()) );
    vboxCylinder->addWidget(buttonCylinder);

    //Button Reset
    QPushButton* buttonReset = new QPushButton("&Reset Cylinder");
    connect(buttonReset, SIGNAL( clicked() ), this, SLOT(slotResetCylinder()) );
    vboxCylinder->addWidget(buttonReset);

    groupBoxCylinder->setLayout(vboxCylinder);
    panel_layout->addWidget(groupBoxCylinder);


    //################################### Rotation ###################################


        QGroupBox* groupBoxRotationBody = new QGroupBox("Rotation Body");
        QVBoxLayout *vboxRotationBody = new QVBoxLayout;

            //Button Show RotationCurve
            QPushButton* buttonRotationCurve = new QPushButton("&Show Rotation Curve");
            connect(buttonRotationCurve, SIGNAL( clicked() ), this, SLOT(slotShowRotationCurve()) );
            vboxRotationBody->addWidget(buttonRotationCurve);

            //Button Show RotationBody
            QPushButton* buttonShowRotationBody = new QPushButton("&Show Rotation Body");
            connect(buttonShowRotationBody, SIGNAL( clicked() ), this, SLOT(slotShowRotationBody()) );
            vboxRotationBody->addWidget(buttonShowRotationBody);

            //Lable
            QLabel* labelAmountOfSegmentsRotationBody = new QLabel("Amount of Segments:");
            labelAmountOfSegmentsRotationBody->setAlignment(Qt::AlignLeft);
            vboxRotationBody->addWidget(labelAmountOfSegmentsRotationBody);

            //SpinBox AmountOfSegments
            spinBoxAmountOfSegmentsRotationBody = new QSpinBox();
            //spinBoxAmountOfSegments->setMinimum(2);
            spinBoxAmountOfSegmentsRotationBody->setValue(50);
            spinBoxAmountOfSegmentsRotationBody->setMaximum(10000);
            spinBoxAmountOfSegmentsRotationBody->setSuffix(" Segments");
            connect(spinBoxAmountOfSegmentsRotationBody, SIGNAL(valueChanged(int) ), this, SLOT(slotRotationBodyChanged()) );
            vboxRotationBody->addWidget(spinBoxAmountOfSegmentsRotationBody);

            QGroupBox* groupBoxSubdivision = new QGroupBox("Subdivision");
            QVBoxLayout* vboxSubdivision = new QVBoxLayout;

                //Button Subdivison 4-Point-Scheme
                QPushButton* buttonSdForPointScheme = new QPushButton("&For-Point-Scheme");
                connect(buttonSdForPointScheme, SIGNAL( clicked() ), this, SLOT(slotSubdivision()) );
                vboxSubdivision->addWidget(buttonSdForPointScheme);

                //Button Reset RotationCurve
                QPushButton* buttonResetRotationCurve = new QPushButton("&Reset Rotation Curve");
                connect(buttonResetRotationCurve, SIGNAL( clicked() ), this, SLOT(slotResetRotationCurve()) );
                vboxSubdivision->addWidget(buttonResetRotationCurve);

            groupBoxSubdivision->setLayout(vboxSubdivision);
            vboxRotationBody->addWidget(groupBoxSubdivision);



        groupBoxRotationBody->setLayout(vboxRotationBody);
        panel_layout->addWidget(groupBoxRotationBody);

    panel_layout->addStretch(1);
    parent->setLayout(panel_layout);
}








//################################### SLOTS ###################################

void CgQtGui::slotColorChanged()
{
    CgBaseEvent* e = new CgColorChangeEvent(sliderRed->value(), sliderGreen->value(), sliderBlue->value());
    notifyObserver(e);
}

void CgQtGui::slotShowCylinder()
{
    for(QAbstractButton* b : ButtonGroupObjects->buttons()){
        b->setChecked(false);
    }
    ButtonGroupObjects->button(0)->setChecked(true);
    ButtonGroupObjects->button(3)->setChecked(true);
    ButtonGroupObjects->button(4)->setChecked(true);
    slotButtonGroupSelectionChanged();
}

void CgQtGui::slotShowRotationCurve()
{
    for(QAbstractButton* b : ButtonGroupObjects->buttons()){
        b->setChecked(false);
    }
    ButtonGroupObjects->button(0)->setChecked(true);
    ButtonGroupObjects->button(5)->setChecked(true);
    slotButtonGroupSelectionChanged();
}

void CgQtGui::slotShowRotationBody()
{
    for(QAbstractButton* b : ButtonGroupObjects->buttons()){
        b->setChecked(false);
    }
    ButtonGroupObjects->button(0)->setChecked(true);
    ButtonGroupObjects->button(6)->setChecked(true);
    slotButtonGroupSelectionChanged();
}

void CgQtGui::slotSubdivision()
{
    CgSubdivisionEvent* e = new CgSubdivisionEvent();
    notifyObserver(e);
    slotRotationBodyChanged();
}

void CgQtGui::slotButtonGroupSelectionChanged()
{
    //Check if cube is not displayed and disable cubeNormals in case
    if( ! ButtonGroupObjects->button(1)->isChecked()){
        ButtonGroupObjects->button(2)->setChecked(false);
        ButtonGroupObjects->button(2)->setDisabled(true);
    }else{
        ButtonGroupObjects->button(2)->setDisabled(false);
    }
    //disable cylinder normals
    if( ! ButtonGroupObjects->button(3)->isChecked()){
        ButtonGroupObjects->button(4)->setChecked(false);
        ButtonGroupObjects->button(4)->setDisabled(true);
    }else{
        ButtonGroupObjects->button(4)->setDisabled(false);
    }

    CgObjectSelectionChangeEvent* e = new CgObjectSelectionChangeEvent();
    e->setRenderCoordinateSystem(ButtonGroupObjects->button(0)->isChecked());
    e->setRenderCube(ButtonGroupObjects->button(1)->isChecked());
    e->setRenderCubeNormals(ButtonGroupObjects->button(2)->isChecked());
    e->setRenderCylinder(ButtonGroupObjects->button(3)->isChecked());
    e->setRenderCylinderNormals(ButtonGroupObjects->button(4)->isChecked());
    e->setRenderRotationCurve(ButtonGroupObjects->button(5)->isChecked());
    e->setRenderRotationBody(ButtonGroupObjects->button(6)->isChecked());
    notifyObserver(e);
}

void CgQtGui::slotCylinderChanged()
{
    slotShowCylinder();
    CgValueChangedEvent* e = new CgValueChangedEvent();
    e->setCylinderChanged(true);
    e->setValueAmountOfSegmentsCylinder(spinBoxAmountOfSegmentsCylinder->value());
    e->setValueHeightCylinder(spinBoxHeightCylinderCone->value());
    notifyObserver(e);
}

void CgQtGui::slotRotationBodyChanged()
{
    CgValueChangedEvent* e = new CgValueChangedEvent();
    e->setRotationBodyChanged(true);
    e->setValueAmountOfSegmentsRotationBody(spinBoxAmountOfSegmentsRotationBody->value());
    notifyObserver(e);
    slotShowRotationBody();
}

void CgQtGui::slotResetCylinder()
{
    slotShowCylinder();
    spinBoxAmountOfSegmentsCylinder->setValue(50);
    spinBoxHeightCylinderCone->setValue(0.5);
    slotCylinderChanged();
}

void CgQtGui::slotResetRotationCurve()
{
    CgValueChangedEvent* e = new CgValueChangedEvent();
    e->setResetRotationCurve(true);
    notifyObserver(e);
    slotRotationBodyChanged();
}






void CgQtGui::slotLoadMeshFile()
{
    // Hier FileChooser öffnen, datei selektieren
    // und dann neuen Event implementieren, der das an den Controller schickt.
    // dort wird dann die Datei tatsächliche geöffnet und ein entsprechendes Mesh Objekt angelegt
    // im View(GUI) passiert nichts außer festellung DASS geladen werden soll und welche Datei und zu welchem Zweck (Mesh)

    QString fileName = QFileDialog::getOpenFileName(this, ("Open .obj"), "/home/gerrit/git/CG-I/alt/UebungSS2018/CgData", ("Object-file (*.obj)"));

    std::cout << fileName.toStdString() << std::endl;
}




void CgQtGui::mouseEvent(QMouseEvent* event)
{         //TODO set false

   // std::cout << QApplication::keyboardModifiers() << std::endl;

  //  if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)==true)
    //    std::cout << Cg::ControlModifier << endl;


   if(event->type()==QEvent::MouseButtonPress)
   {


        CgBaseEvent* e = new CgMouseEvent(Cg::CgMouseButtonPress,
                                          glm::vec2(event->localPos().x() ,event->localPos().y()),
                                          (Cg::MouseButtons)event->button());

        notifyObserver(e);
   }

   if(event->type()==QEvent::MouseMove)
   {
       CgBaseEvent* e= new CgMouseEvent(Cg::CgMouseMove,
                                        glm::vec2(event->localPos().x() ,event->localPos().y()),
                                        (Cg::MouseButtons)event->button());
       notifyObserver(e);
   }



}

void CgQtGui::keyPressEvent(QKeyEvent *event)
{
   CgBaseEvent* e= new CgKeyEvent(Cg::CgKeyPressEvent,(Cg::Key)event->key(),(Cg::KeyboardModifiers)event->nativeModifiers(),event->text().toStdString());
   notifyObserver(e);
}


void CgQtGui::viewportChanged(int w, int h)
{
     CgBaseEvent* e = new CgWindowResizeEvent(Cg::WindowResizeEvent,w,h);
     notifyObserver(e);
}


CgBaseRenderer* CgQtGui::getRenderer()
{
    return m_glRenderWidget;
}



