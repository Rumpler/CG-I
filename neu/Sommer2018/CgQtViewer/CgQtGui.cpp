#include "CgQtGLRenderWidget.h"
#include "CgQtGui.h"
#include "CgQtMainApplication.h"
#include "../CgBase/CgEnums.h"
#include "../CgEvents/CgMouseEvent.h"
#include "../CgEvents/CgKeyEvent.h"
#include "../CgEvents/CgWindowResizeEvent.h"
#include "../CgEvents/CgColorChangeEvent.h"
#include "../CgEvents/CgObjectSelectionChangedEvent.h"
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
#include <CgEvents/CgLoadObjFileEvent.h>
#include <CgEvents/CgResetEvent.h>
#include <CgEvents/CgSubdivisionEvent.h>
#include <CgEvents/CgTrackballEvent.h>
#include <CgEvents/CgTransformationEvent.h>



CgQtGui::CgQtGui(CgQtMainApplication *mw)
    : m_mainWindow(mw)
{
    m_glRenderWidget = new CgQtGLRenderWidget;

    connect(m_glRenderWidget, SIGNAL(mouseEvent(QMouseEvent*)), this, SLOT(mouseEvent(QMouseEvent*)));
    connect(m_glRenderWidget, SIGNAL(viewportChanged(int,int)), this, SLOT(viewportChanged(int,int)));
    connect(m_glRenderWidget, SIGNAL(trackballChanged()), this, SLOT(slotTrackballChanged()));


    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;

    //Add new panels here
    m_panel_objects = new QWidget;
    createOptionPanelObjects(m_panel_objects);
    m_panel_rotate_objects = new QWidget;
    createOptionPanelRotateObjects(m_panel_rotate_objects);
    m_panel_tranformation = new QWidget;
    createOptionPanelTransformation(m_panel_tranformation);

    QTabWidget* m_tabs = new QTabWidget();

    m_tabs->addTab(m_panel_objects,"&Objects");
    m_tabs->addTab(m_panel_rotate_objects, "&Rotate Objects");
    m_tabs->addTab(m_panel_tranformation, "&Tranformation");
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
    slider->setRange(0, 100);
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
    QRadioButton* radiobuttonRotationBodyNormals = new QRadioButton("&Rotation Body Normals");
    QRadioButton* radiobuttonLoadedObject = new QRadioButton("&Loaded Object");
    QRadioButton* radiobuttonLoadedObjectNormals = new QRadioButton("&Loaded Object Normals");

    radiobuttonCoordinateSystem->setChecked(true);

    ButtonGroupObjects->addButton(radiobuttonCoordinateSystem,0);
    ButtonGroupObjects->addButton(radiobuttonCube,1);
    ButtonGroupObjects->addButton(radiobuttonCubeNormals,2);
    ButtonGroupObjects->addButton(radiobuttonCylinder,3);
    ButtonGroupObjects->addButton(radiobuttonCylinderNormals,4);
    ButtonGroupObjects->addButton(radiobuttonRotationCurve,5);
    ButtonGroupObjects->addButton(radiobuttonRotationBody,6);
    ButtonGroupObjects->addButton(radiobuttonRotationBodyNormals,7);
    ButtonGroupObjects->addButton(radiobuttonLoadedObject,8);
    ButtonGroupObjects->addButton(radiobuttonLoadedObjectNormals,9);

    ButtonGroupObjects->button(2)->setDisabled(true);
    ButtonGroupObjects->button(4)->setDisabled(true);
    ButtonGroupObjects->button(7)->setDisabled(true);
//    ButtonGroupObjects->button(8)->setDisabled(true);
//    ButtonGroupObjects->button(9)->setDisabled(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radiobuttonCoordinateSystem);
    vbox->addWidget(radiobuttonCube);
    vbox->addWidget(radiobuttonCubeNormals);
    vbox->addWidget(radiobuttonCylinder);
    vbox->addWidget(radiobuttonCylinderNormals);
    vbox->addWidget(radiobuttonRotationCurve);
    vbox->addWidget(radiobuttonRotationBody);
    vbox->addWidget(radiobuttonRotationBodyNormals);

    //Button Load Mesh File
    QPushButton* buttonLoadMeshFile = new QPushButton("&Load Mesh");
    connect(buttonLoadMeshFile, SIGNAL( clicked() ), this, SLOT(slotLoadMeshFile()) );
    vbox->addWidget(buttonLoadMeshFile);

    vbox->addWidget(radiobuttonLoadedObject);
    vbox->addWidget(radiobuttonLoadedObjectNormals);

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

    sliderRed->setValue(45);
    sliderGreen->setValue(45);
    sliderBlue->setValue(50);


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


    //DoubleSpinBox height
    spinBoxHeightCylinder = new QDoubleSpinBox();
    spinBoxHeightCylinder->setMinimum(0.01);
    spinBoxHeightCylinder->setValue(0.3);
    spinBoxHeightCylinder->setSingleStep(0.01);
    spinBoxHeightCylinder->setPrefix("Height: ");
    connect(spinBoxHeightCylinder, SIGNAL(valueChanged(double) ), this, SLOT(slotCylinderChanged()) );
    vboxCylinder->addWidget(spinBoxHeightCylinder);

    //DoubleSpinBox radius
    spinBoxRadiusCylinder = new QDoubleSpinBox();
    spinBoxRadiusCylinder->setMinimum(0.01);
    spinBoxRadiusCylinder->setValue(0.2);
    spinBoxRadiusCylinder->setSingleStep(0.01);
    spinBoxRadiusCylinder->setPrefix("Radius: ");
    connect(spinBoxRadiusCylinder, SIGNAL(valueChanged(double) ), this, SLOT(slotCylinderChanged()) );
    vboxCylinder->addWidget(spinBoxRadiusCylinder);



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

    //Button Show RotationBodyNormals
    QPushButton* buttonShowRotationBodyNormals = new QPushButton("&Show Normals");
    connect(buttonShowRotationBodyNormals, SIGNAL( clicked() ), this, SLOT(slotShowRotationBodyNormals()) );
    vboxRotationBody->addWidget(buttonShowRotationBodyNormals);

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
    connect(buttonResetRotationCurve, SIGNAL( clicked() ), this, SLOT(slotResetRotationObjects()) );
    vboxSubdivision->addWidget(buttonResetRotationCurve);

    groupBoxSubdivision->setLayout(vboxSubdivision);
    vboxRotationBody->addWidget(groupBoxSubdivision);



    groupBoxRotationBody->setLayout(vboxRotationBody);
    panel_layout->addWidget(groupBoxRotationBody);

    panel_layout->addStretch(1);
    parent->setLayout(panel_layout);
}

void CgQtGui::createOptionPanelTransformation(QWidget *parent)
{
    QVBoxLayout *panel_layout = new QVBoxLayout();

    QGroupBox* gbScale = new QGroupBox("Scaling");
    QHBoxLayout* gblScale = new QHBoxLayout;

    //Button Scale +
    QPushButton* btScalePlus = new QPushButton("&Scale bigger (+)");
    connect(btScalePlus, SIGNAL( clicked() ), this, SLOT(slotScalePlus()) );
    btScalePlus->setAutoRepeat(true);
    gblScale->addWidget(btScalePlus);

    //Button Scale -
    QPushButton* btScaleMinus = new QPushButton("&Scale smaller (-)");
    connect(btScaleMinus, SIGNAL( clicked() ), this, SLOT(slotScaleMinus()) );
    btScaleMinus->setAutoRepeat(true);
    gblScale->addWidget(btScaleMinus);

    gbScale->setLayout(gblScale);
    panel_layout->addWidget(gbScale);


    QGroupBox* gbRotating = new QGroupBox("Rotating");
    QHBoxLayout* gblRotating = new QHBoxLayout;

    //Button Rotate X Axis
    QPushButton* btRotateX = new QPushButton("&X Axis (x)");
    connect(btRotateX, SIGNAL( clicked() ), this, SLOT(slotRotateX()) );
    btRotateX->setAutoRepeat(true);
    gblRotating->addWidget(btRotateX);

    //Button Rotate Y Axis
    QPushButton* btRotateY = new QPushButton("&Y Axis (y)");
    connect(btRotateY, SIGNAL( clicked() ), this, SLOT(slotRotateY()) );
    btRotateY->setAutoRepeat(true);
    gblRotating->addWidget(btRotateY);

    //Button Rotate Z Axis
    QPushButton* btRotateZ = new QPushButton("&Z Axis (z)");
    connect(btRotateZ, SIGNAL( clicked() ), this, SLOT(slotRotateZ()) );
    btRotateZ->setAutoRepeat(true);
    gblRotating->addWidget(btRotateZ);

    gbRotating->setLayout(gblRotating);
    panel_layout->addWidget(gbRotating);

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
    showObject(5);
}

void CgQtGui::slotShowRotationBody()
{
    showObject(6);
}

void CgQtGui::slotShowRotationBodyNormals()
{
    std::cout << "slotShowRotationBodyNormals" << std::endl;
    for(QAbstractButton* b : ButtonGroupObjects->buttons()){
        b->setChecked(false);
    }
    ButtonGroupObjects->button(0)->setChecked(true);
    ButtonGroupObjects->button(6)->setChecked(true);
    ButtonGroupObjects->button(7)->setChecked(true);
    slotButtonGroupSelectionChanged();
}

void CgQtGui::slotShowLoadedObject()
{
    showObject(8);
}

void CgQtGui::slotScalePlus()
{
    CgTransformationEvent *e = new CgTransformationEvent(glm::vec3(1.1f));
    notifyObserver(e);
}

void CgQtGui::slotScaleMinus()
{
    CgTransformationEvent *e = new CgTransformationEvent(glm::vec3(0.9f));
    notifyObserver(e);
}

void CgQtGui::slotRotateX()
{
    CgTransformationEvent *e = new CgTransformationEvent(glm::vec3(1.0f));
    e->setRotate(true);
    e->setRotateAxis(glm::vec3(1.0f,0.0f,0.0f));
    notifyObserver(e);
}

void CgQtGui::slotRotateY()
{
    CgTransformationEvent *e = new CgTransformationEvent(glm::vec3(1.0f));
    e->setRotate(true);
    e->setRotateAxis(glm::vec3(0.0f,1.0f,0.0f));
    notifyObserver(e);
}

void CgQtGui::slotRotateZ()
{
    CgTransformationEvent *e = new CgTransformationEvent(glm::vec3(1.0f));
    e->setRotate(true);
    e->setRotateAxis(glm::vec3(0.0f,0.0f,1.0f));
    notifyObserver(e);
}

void CgQtGui::showObject(int i)
{
    for(QAbstractButton* b : ButtonGroupObjects->buttons()){
        b->setChecked(false);
    }
    ButtonGroupObjects->button(0)->setChecked(true);
    ButtonGroupObjects->button(i)->setChecked(true);
    slotButtonGroupSelectionChanged();
}

void CgQtGui::slotSubdivision()
{
    CgValueChangedEvent* e = new CgValueChangedEvent();

    e->setRotationCurveChanged(true);
    e->setSdForPointScheme(true);
    notifyObserver(e);
    slotRotationBodyChanged();
    slotShowRotationCurve();
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
    //disable rotation body normals
    if( ! ButtonGroupObjects->button(6)->isChecked()){
        ButtonGroupObjects->button(7)->setChecked(false);
        ButtonGroupObjects->button(7)->setDisabled(true);
    }else{
        ButtonGroupObjects->button(7)->setDisabled(false);
    }
    //disable loaded object normals
    if( ! ButtonGroupObjects->button(8)->isChecked()){
        ButtonGroupObjects->button(9)->setChecked(false);
        ButtonGroupObjects->button(9)->setDisabled(true);
    }else{
        ButtonGroupObjects->button(9)->setDisabled(false);
    }

    CgObjectSelectionChangeEvent* e = new CgObjectSelectionChangeEvent();
    e->setRenderCoordinateSystem(ButtonGroupObjects->button(0)->isChecked());
    e->setRenderCube(ButtonGroupObjects->button(1)->isChecked());
    e->setRenderCubeNormals(ButtonGroupObjects->button(2)->isChecked());
    e->setRenderCylinder(ButtonGroupObjects->button(3)->isChecked());
    e->setRenderCylinderNormals(ButtonGroupObjects->button(4)->isChecked());
    e->setRenderRotationCurve(ButtonGroupObjects->button(5)->isChecked());
    e->setRenderRotationBody(ButtonGroupObjects->button(6)->isChecked());
    e->setRenderRotationBodyNormals(ButtonGroupObjects->button(7)->isChecked());
    e->setRenderLoadedObject(ButtonGroupObjects->button(8)->isChecked());
    e->setRenderLoadedObjectNormals(ButtonGroupObjects->button(9)->isChecked());
    notifyObserver(e);
}

void CgQtGui::slotCylinderChanged()
{
    slotShowCylinder();
    CgValueChangedEvent* e = new CgValueChangedEvent();
    e->setCylinderChanged(true);
    e->setValueAmountOfSegmentsCylinder(spinBoxAmountOfSegmentsCylinder->value());
    e->setValueHeightCylinder(spinBoxHeightCylinder->value());
    e->setValueRadiusCylinder(spinBoxRadiusCylinder->value());
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
    spinBoxHeightCylinder->setValue(0.3f);
    spinBoxRadiusCylinder->setValue(0.2f);
    slotCylinderChanged();
}

void CgQtGui::slotResetRotationObjects()
{
    CgValueChangedEvent* e = new CgValueChangedEvent();
    e->setRotationCurveChanged(true);
    notifyObserver(e);
    slotRotationBodyChanged();
}

void CgQtGui::slotLoadMeshFile()
{
    QString file =  QFileDialog::getOpenFileName(this, tr("Open Obj-File"),"",tr("Model Files (*.obj)"));
    CgBaseEvent* e = new CgLoadObjFileEvent(Cg::CgLoadObjFileEvent, file.toStdString());
    notifyObserver(e);
    slotShowLoadedObject();
}

void CgQtGui::slotTrackballChanged()
{
    CgBaseEvent* e = new CgTrackballEvent(Cg::CgTrackballEvent, m_glRenderWidget->getTrackballRotation());
    notifyObserver(e);
}

//################################### SLOTS END ###################################

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
    CgBaseEvent* e = new CgWindowResizeEvent(Cg::CgWindowResizeEvent,w,h);
    notifyObserver(e);
}

CgBaseRenderer* CgQtGui::getRenderer()
{
    return m_glRenderWidget;
}



