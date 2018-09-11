#include "CgQtGLRenderWidget.h"
#include "CgQtGui.h"
#include "CgQtGui.h"
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
#include <CgEvents/CgButtonEvent.h>
#include <CgEvents/CgLoadObjFileEvent.h>
#include <CgEvents/CgResetEvent.h>
#include <CgEvents/CgSubdivisionEvent.h>
#include <CgEvents/CgTrackballEvent.h>
#include <CgEvents/CgTransformationEvent.h>
#include <CgEvents/CgMaterialChangeEvent.h>
#include <CgEvents/CgBoxEvent.h>
#include <CgEvents/CgShaderEvent.h>


//DON
int CgQtGui::calculateShadingMode()
{
//    int shadingmode=0;
//    //phong flat
//    if(combo_box_shader->currentIndex()==1 && combo_box_interpolation->currentIndex()==0){
//        shadingmode=1;
//    }
//    //phong smoth
//    else if(combo_box_shader->currentIndex()==1 && combo_box_interpolation->currentIndex()==1){
//        shadingmode=2;
//    }
//    //garaoud flat
//    else if(combo_box_shader->currentIndex()==2 && combo_box_interpolation->currentIndex()==0){
//        shadingmode=3;
//    }
//    //garaoud smooth
//    else if(combo_box_shader->currentIndex()==2 && combo_box_interpolation->currentIndex()==1){
//        shadingmode=4;
//    }
//    else{
//        shadingmode=0;
//    }

//    std::cout<<"modus:"<<shadingmode<<std::endl;
//    return shadingmode;
}

void CgQtGui::createMats()
{
    amb.push_back(glm::vec4(.25f,.25f,.25f,1.0));
    def.push_back(glm::vec4(.40f,.40f,.40f,1.0));
    spec.push_back(glm::vec4(.77f,.77f,.77f,1.0));
    scala.push_back(76.8);

    amb.push_back(glm::vec4(.25f,.21f,.21f,.90f));
    def.push_back(glm::vec4(0.99f,.83f,.83f,.90f));
    spec.push_back(glm::vec4(0.30f,0.30f,0.30f,0.90f));
    scala.push_back(11.3);

    amb.push_back(glm::vec4(0.5f,0.5f,0.7f,0.8f));
    def.push_back(glm::vec4(0.18f,0.17f,0.23f,0.8f));
    spec.push_back(glm::vec4(0.33f,0.33f,0.35f,0.8f));
    scala.push_back(38.4);
    //gold

    amb.push_back(glm::vec4(0.25f,0.20f,0.07f,1.f));
    def.push_back(glm::vec4(0.75f,0.61f,0.23f,1.f));
    spec.push_back(glm::vec4(0.63f,0.56f,0.37f,0.9f));
    scala.push_back(51.2);

    amb.push_back(glm::vec4(0.19f,0.19f,0.19f,1.0f));
    def.push_back(glm::vec4(0.51f,0.51f,0.51f,1.0f));
    spec.push_back(glm::vec4(0.51f,0.51f,0.51f,1.f));
    scala.push_back(51.2);

    amb.push_back(glm::vec4(0.2f,0.2f,0.2f,1.0f));
    def.push_back(glm::vec4(0.1f,0.1f,0.1f,1.0f));
    spec.push_back(glm::vec4(0.5f,0.5f,0.5f,1.f));
    scala.push_back(51.2);
}

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
    m_panel_color = new QWidget;
    createOptionPanelShader(m_panel_color);
    m_panel_camera = new QWidget();
    createOptionPanelCamera(m_panel_camera);

    QTabWidget* m_tabs = new QTabWidget();
    m_tabs->addTab(m_panel_objects,"&Objects");
    m_tabs->addTab(m_panel_rotate_objects, "&Rotate Objects");
    m_tabs->addTab(m_panel_color, "&Shader");
    m_tabs->addTab(m_panel_camera,"&Camera");
    container->addWidget(m_tabs);


    m_tabs->setMaximumWidth(400);

    container->addWidget(m_glRenderWidget);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);

    setLayout(mainLayout);
    setWindowTitle(tr("Computergrafik 1"));

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

    //DON
    createMats();
}


/*****************************************************************************/
/*                      CREATE GROUPBOXES AND PANELS                         */
/*****************************************************************************/


void CgQtGui::createOptionPanelObjects(QWidget *parent)
{
    QVBoxLayout *panel_layout = new QVBoxLayout();
    buttonGroupObjectSelection = new QButtonGroup(panel_layout);
    buttonGroupObjectSelection->setExclusive(false);
    panel_layout->addWidget(createGBObjects());
    panel_layout->addWidget(createGBTransformation());
    panel_layout->addStretch(1);
    parent->setLayout(panel_layout);
}

void CgQtGui::createOptionPanelRotateObjects(QWidget *parent)
{
    QVBoxLayout *panel_layout = new QVBoxLayout();
    panel_layout->addWidget(createGBCylinder());
    panel_layout->addWidget(createGBRotationBody());
    panel_layout->addStretch(1);
    parent->setLayout(panel_layout);
}

void CgQtGui::createOptionPanelShader(QWidget *parent)
{
    QVBoxLayout *panel_layout = new QVBoxLayout();
    panel_layout->addWidget(createGBShader());
    panel_layout->addWidget(createGBColor());
    panel_layout->addStretch(1);
    parent->setLayout(panel_layout);
}

void CgQtGui::createOptionPanelCamera(QWidget *parent)
{
    QVBoxLayout *tabLayout = new QVBoxLayout();
    tabLayout->addWidget(createGBProjection());
    tabLayout->addWidget(createGBFrustum());


    tabLayout->addStretch(1);
    parent->setLayout(tabLayout);
}

QGroupBox *CgQtGui::createGBObjects()
{
    QGroupBox* groupBox = new QGroupBox("Objects for rendering ");

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
    QRadioButton* radiobuttonCustomRotationAxis = new QRadioButton("&Custom Rotation Axis");
    QRadioButton* radiobuttonScene = new QRadioButton("&Scene");

    radiobuttonCoordinateSystem->setChecked(true);
    radiobuttonScene->setChecked(true);

    buttonGroupObjectSelection->addButton(radiobuttonCoordinateSystem,0);
    buttonGroupObjectSelection->addButton(radiobuttonCube,1);
    buttonGroupObjectSelection->addButton(radiobuttonCubeNormals,2);
    buttonGroupObjectSelection->addButton(radiobuttonCylinder,3);
    buttonGroupObjectSelection->addButton(radiobuttonCylinderNormals,4);
    buttonGroupObjectSelection->addButton(radiobuttonRotationCurve,5);
    buttonGroupObjectSelection->addButton(radiobuttonRotationBody,6);
    buttonGroupObjectSelection->addButton(radiobuttonRotationBodyNormals,7);
    buttonGroupObjectSelection->addButton(radiobuttonLoadedObject,8);
    buttonGroupObjectSelection->addButton(radiobuttonLoadedObjectNormals,9);
    buttonGroupObjectSelection->addButton(radiobuttonCustomRotationAxis,10);
    buttonGroupObjectSelection->addButton(radiobuttonScene,11);

    buttonGroupObjectSelection->button(2)->setDisabled(true);
    buttonGroupObjectSelection->button(4)->setDisabled(true);
    buttonGroupObjectSelection->button(7)->setDisabled(true);
    buttonGroupObjectSelection->button(9)->setDisabled(true);

    connect(buttonGroupObjectSelection, SIGNAL( buttonClicked(int) ), this, SLOT( slotButtonGroupSelectionChanged() ) );

    QVBoxLayout* container = new QVBoxLayout();
    QHBoxLayout *subBox = new QHBoxLayout();
    QVBoxLayout *sb1 = new QVBoxLayout();
    QVBoxLayout *sb2 = new QVBoxLayout();

    sb1->addWidget(radiobuttonCoordinateSystem);
    sb1->addWidget(radiobuttonCube);
    sb1->addWidget(radiobuttonCubeNormals);
    sb1->addWidget(radiobuttonCylinder);
    sb1->addWidget(radiobuttonCylinderNormals);
    sb1->addWidget(radiobuttonRotationCurve);
    sb2->addWidget(radiobuttonRotationBody);
    sb2->addWidget(radiobuttonRotationBodyNormals);
    sb2->addWidget(radiobuttonLoadedObject);
    sb2->addWidget(radiobuttonLoadedObjectNormals);
    sb2->addWidget(radiobuttonCustomRotationAxis);
    sb2->addWidget(radiobuttonScene);

    subBox->addLayout(sb1);
    subBox->addLayout(sb2);

    container->addLayout(subBox);

    //Button Load Mesh File
    QPushButton* buttonLoadMeshFile = new QPushButton("&Load Mesh");
    connect(buttonLoadMeshFile, SIGNAL( clicked() ), this, SLOT(slotLoadMeshFile()) );
    container->addWidget(buttonLoadMeshFile);

    container->addStretch(1);
    groupBox->setLayout(container);
    return groupBox;
}

QGroupBox *CgQtGui::createGBTransformation()
{
    QGroupBox* groupBoxTranformation = new QGroupBox("Transformation");
    QVBoxLayout* vboxTransformattion = new QVBoxLayout();

    //Button select next objects
    QPushButton* btSelectNnextObject = new QPushButton("&Select next object (n)");
    connect(btSelectNnextObject, SIGNAL( clicked() ), this, SLOT(slotSelectNextObject()) );
    vboxTransformattion->addWidget(btSelectNnextObject);

    /***************** SCALING *****************/

    QGroupBox* gbScale = new QGroupBox("Scale selected object");
    QHBoxLayout* gblScale = new QHBoxLayout;

    //Button Scale +
    QPushButton* btScalePlus = new QPushButton("&Bigger (+)");
    connect(btScalePlus, SIGNAL( clicked() ), this, SLOT(slotScalePlus()) );
    btScalePlus->setAutoRepeat(true);
    gblScale->addWidget(btScalePlus);

    //Button Scale -
    QPushButton* btScaleMinus = new QPushButton("&Smaller (-)");
    connect(btScaleMinus, SIGNAL( clicked() ), this, SLOT(slotScaleMinus()) );
    btScaleMinus->setAutoRepeat(true);
    gblScale->addWidget(btScaleMinus);

    gbScale->setLayout(gblScale);
    vboxTransformattion->addWidget(gbScale);

    /***************** ROTATING *****************/

    QGroupBox* gbRotating = new QGroupBox("Rotate selected object");
    QVBoxLayout* sb1 = new QVBoxLayout;
    QHBoxLayout* sb2 = new QHBoxLayout;

    //Button Rotate X Axis
    QPushButton* btRotateX = new QPushButton("&X Axis (x)");
    connect(btRotateX, SIGNAL( clicked() ), this, SLOT(slotRotateX()) );
    btRotateX->setAutoRepeat(true);
    sb2->addWidget(btRotateX);

    //Button Rotate Y Axis
    QPushButton* btRotateY = new QPushButton("&Y Axis (y)");
    connect(btRotateY, SIGNAL( clicked() ), this, SLOT(slotRotateY()) );
    btRotateY->setAutoRepeat(true);
    sb2->addWidget(btRotateY);

    //Button Rotate Z Axis
    QPushButton* btRotateZ = new QPushButton("&Z Axis (z)");
    connect(btRotateZ, SIGNAL( clicked() ), this, SLOT(slotRotateZ()) );
    btRotateZ->setAutoRepeat(true);
    sb2->addWidget(btRotateZ);
    sb1->addLayout(sb2);

    //Button rotate Vector
    QPushButton* btRotateVector = new QPushButton("&Custom axis (c)");
    connect(btRotateVector, SIGNAL( clicked() ), this, SLOT( slotRotateVector() ));
    btRotateVector->setAutoRepeat(true);
    sb1->addWidget(btRotateVector);

    QHBoxLayout* sb3 = new QHBoxLayout;

    //DoubleSpinBox RotateVectorX
    spinBoxRotateVectorX = new QDoubleSpinBox();
    spinBoxRotateVectorX->setMaximum(100);
    spinBoxRotateVectorX->setMinimum(-100);
    spinBoxRotateVectorX->setValue(1);
    spinBoxRotateVectorX->setSingleStep(0.1);
    spinBoxRotateVectorX->setPrefix("X: ");
    sb3->addWidget(spinBoxRotateVectorX);

    //DoubleSpinBox RotateVectorY
    spinBoxRotateVectorY = new QDoubleSpinBox();
    spinBoxRotateVectorY->setMaximum(100);
    spinBoxRotateVectorY->setMinimum(-100);
    spinBoxRotateVectorY->setValue(1);
    spinBoxRotateVectorY->setSingleStep(0.1);
    spinBoxRotateVectorY->setPrefix("Y: ");
    sb3->addWidget(spinBoxRotateVectorY);

    //DoubleSpinBox RotateVectorZ
    spinBoxRotateVectorZ = new QDoubleSpinBox();
    spinBoxRotateVectorZ->setMaximum(100);
    spinBoxRotateVectorZ->setMinimum(-100);
    spinBoxRotateVectorZ->setValue(1);
    spinBoxRotateVectorZ->setSingleStep(0.1);
    spinBoxRotateVectorZ->setPrefix("Z: ");
    sb3->addWidget(spinBoxRotateVectorZ);
    sb1->addLayout(sb3);


    gbRotating->setLayout(sb1);
    vboxTransformattion->addWidget(gbRotating);

    /***************** Translating *****************/

    QGroupBox* gbTranslating = new QGroupBox("Translate selected object");
    QVBoxLayout* gblTranslating = new QVBoxLayout;

    //Button Translate
    QPushButton* btTranslate = new QPushButton("&Translate (t)");
    connect(btTranslate, SIGNAL( clicked() ), this, SLOT(slotTranslate()) );
    btTranslate->setAutoRepeat(true);
    gblTranslating->addWidget(btTranslate);

    QHBoxLayout* sb10 = new QHBoxLayout();

    //DoubleSpinBox TranslateVector X
    spinBoxTranslateVectorX = new QDoubleSpinBox();
    spinBoxTranslateVectorX->setMaximum(100);
    spinBoxTranslateVectorX->setMinimum(-100);
    spinBoxTranslateVectorX->setValue(0.1);
    spinBoxTranslateVectorX->setSingleStep(0.1);
    spinBoxTranslateVectorX->setPrefix("X: ");
    sb10->addWidget(spinBoxTranslateVectorX);

    //DoubleSpinBox TranslateVector X
    spinBoxTranslateVectorY = new QDoubleSpinBox();
    spinBoxTranslateVectorY->setMaximum(100);
    spinBoxTranslateVectorY->setMinimum(-100);
    spinBoxTranslateVectorY->setValue(0.0);
    spinBoxTranslateVectorY->setSingleStep(0.1);
    spinBoxTranslateVectorY->setPrefix("Y: ");
    sb10->addWidget(spinBoxTranslateVectorY);

    //DoubleSpinBox TranslateVector X
    spinBoxTranslateVectorZ = new QDoubleSpinBox();
    spinBoxTranslateVectorZ->setMaximum(100);
    spinBoxTranslateVectorZ->setMinimum(-100);
    spinBoxTranslateVectorZ->setValue(0.0);
    spinBoxTranslateVectorZ->setSingleStep(0.1);
    spinBoxTranslateVectorZ->setPrefix("Z: ");
    sb10->addWidget(spinBoxTranslateVectorZ);

    gblTranslating->addLayout(sb10);

    gbTranslating->setLayout(gblTranslating);
    vboxTransformattion->addWidget(gbTranslating);

    vboxTransformattion->addStretch(1);
    groupBoxTranformation->setLayout(vboxTransformattion);
    return groupBoxTranformation;
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

QGroupBox *CgQtGui::createGBColor()
{
    QGroupBox* groupBoxColor = new QGroupBox("Color");
    QVBoxLayout *vboxColor = new QVBoxLayout;

    sliderRed = createColorSlider();
    sliderGreen = createColorSlider();
    sliderBlue = createColorSlider();

    QLabel *label_red = new QLabel("Red");
    QLabel *label_green = new QLabel("Green");
    QLabel *label_blue = new QLabel("Blue");

    sliderRed->setValue(0);
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
    return groupBoxColor;
}

QGroupBox *CgQtGui::createGBCylinder()
{
    QGroupBox* groupBoxCylinder = new QGroupBox("Cylinder");
    QVBoxLayout *vboxCylinder = new QVBoxLayout;


    //SpinBox AmountOfSegments
    spinBoxAmountOfSegmentsCylinder = new QSpinBox();
    spinBoxAmountOfSegmentsCylinder->setValue(50);
    spinBoxAmountOfSegmentsCylinder->setMaximum(10000);
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
    return groupBoxCylinder;
}

QGroupBox *CgQtGui::createGBRotationBody()
{
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

    return groupBoxRotationBody;
}

QGroupBox *CgQtGui::createGBShader()
{
    QGroupBox* groupBoxShader = new QGroupBox("Shader");
    QVBoxLayout *shaderLayout = new QVBoxLayout;

    //SHADING MODE
    QHBoxLayout *subShaderLayout1 = new QHBoxLayout;

        buttonGroupShadingMode = new QButtonGroup(subShaderLayout1);
        connect(buttonGroupShadingMode, SIGNAL( buttonClicked(int) ),this,SLOT(shaderSlot()));

        QRadioButton* radiobuttonNoneShader = new QRadioButton("&None");
        QRadioButton* radiobuttonPhongShader = new QRadioButton("&Phong");
        QRadioButton* radiobuttonGouraudShader = new QRadioButton("&Gouraud");

        buttonGroupShadingMode->addButton(radiobuttonNoneShader,0);
        buttonGroupShadingMode->addButton(radiobuttonPhongShader,1);
        buttonGroupShadingMode->addButton(radiobuttonGouraudShader,2);

        buttonGroupShadingMode->setExclusive(true);
        buttonGroupShadingMode->button(0)->setChecked(true);

        subShaderLayout1->addWidget(radiobuttonNoneShader);
        subShaderLayout1->addWidget(radiobuttonPhongShader);
        subShaderLayout1->addWidget(radiobuttonGouraudShader);

    shaderLayout->addLayout(subShaderLayout1);

    QHBoxLayout *subShaderLayout2 = new QHBoxLayout;

        buttonGroupShadingInterpolation = new QButtonGroup(subShaderLayout2);
        connect(buttonGroupShadingInterpolation, SIGNAL( buttonClicked(int) ),this,SLOT(shaderSlot()));

        QRadioButton* radiobuttonFlat = new QRadioButton("&Flat");
        QRadioButton* radiobuttonSmooth = new QRadioButton("&Smoth");

        buttonGroupShadingInterpolation->addButton(radiobuttonFlat,0);
        buttonGroupShadingInterpolation->addButton(radiobuttonSmooth,1);

        buttonGroupShadingInterpolation->setExclusive(true);
        buttonGroupShadingInterpolation->button(0)->setChecked(true);

        subShaderLayout2->addWidget(radiobuttonFlat);
        subShaderLayout2->addWidget(radiobuttonSmooth);

    shaderLayout->addLayout(subShaderLayout2);


    combo_box_material = new QComboBox();

    combo_box_material->addItem("Gold");
    combo_box_material->addItem("Silver");


    connect(combo_box_material, SIGNAL(currentIndexChanged(int)),this,SLOT(shaderSlot()));




    shaderLayout->addWidget(combo_box_material);

    groupBoxShader->setLayout(shaderLayout);
    return groupBoxShader;
}

QGroupBox *CgQtGui::createGBFrustum()
{
    QGroupBox* groupBoxFrustum = new QGroupBox("Frustum");

    QVBoxLayout *subBox = new QVBoxLayout();

    QSpinBox* mySpinBox1 = new QSpinBox();
    mySpinBox1->setPrefix("Right ");
    mySpinBox1->setSuffix( " /10");
    subBox->addWidget(mySpinBox1);
    mySpinBox1->setMinimum(1);
    mySpinBox1->setMaximum(30);
    mySpinBox1->setValue(10);
    connect(mySpinBox1, SIGNAL(valueChanged(int) ), this, SLOT(slotChangeFrustumR(int)));

    QSpinBox* mySpinBox2 = new QSpinBox();
    mySpinBox2->setPrefix("Left ");
    mySpinBox2->setSuffix( " /10");
    subBox->addWidget(mySpinBox2);
    mySpinBox2->setMinimum(1);
    mySpinBox2->setMaximum(30);
    mySpinBox2->setValue(10);
    connect(mySpinBox2, SIGNAL(valueChanged(int) ), this, SLOT(slotChangeFrustumL(int)) );

    QSpinBox* mySpinBox3 = new QSpinBox();
    mySpinBox3->setPrefix("Top ");
    mySpinBox3->setSuffix( " /10");
    subBox->addWidget(mySpinBox3);
    mySpinBox3->setMinimum(1);
    mySpinBox3->setMaximum(30);
    mySpinBox3->setValue(10);
    connect(mySpinBox3, SIGNAL(valueChanged(int) ), this, SLOT(slotChangeFrustumT(int)) );

    QSpinBox* mySpinBox4 = new QSpinBox();
    mySpinBox4->setPrefix("Bottom ");
    mySpinBox4->setSuffix( " /10");
    subBox->addWidget(mySpinBox4);
    mySpinBox4->setMinimum(1);
    mySpinBox4->setMaximum(30);
    mySpinBox4->setValue(10);
    connect(mySpinBox4, SIGNAL(valueChanged(int) ), this, SLOT(slotChangeFrustumB(int)) );

    QSpinBox* mySpinBox5 = new QSpinBox();
    mySpinBox5->setPrefix("Front ");
    mySpinBox5->setSuffix( " /10");
    subBox->addWidget(mySpinBox5);
    mySpinBox5->setMinimum(1);
    mySpinBox5->setMaximum(30);
    mySpinBox5->setValue(10);
    connect(mySpinBox5, SIGNAL(valueChanged(int) ), this, SLOT(slotChangeFrustumF(int)) );

    QSpinBox* mySpinBox6 = new QSpinBox();
    mySpinBox6->setPrefix("Near ");
    mySpinBox6->setSuffix( " /10");
    subBox->addWidget(mySpinBox6);
    mySpinBox6->setMinimum(1);
    mySpinBox6->setMaximum(30);
    mySpinBox6->setValue(10);
    connect(mySpinBox6, SIGNAL(valueChanged(int) ), this, SLOT(slotChangeFrustumN(int)) );

    groupBoxFrustum->setLayout(subBox);
    return groupBoxFrustum;

}

QGroupBox *CgQtGui::createGBProjection()
{
    QGroupBox* groupBoxProjection = new QGroupBox("Projection");

    QHBoxLayout *subBox = new QHBoxLayout();
    QPushButton* btCentralProj = new QPushButton("&Central");
    QPushButton* btParallelProj = new QPushButton("&Parallel");
    subBox->addWidget(btCentralProj);
    subBox->addWidget(btParallelProj);

    connect(btCentralProj, SIGNAL( clicked() ), this, SLOT(slotChangeProjectionToCentral()) );
    connect(btParallelProj, SIGNAL( clicked() ), this, SLOT(slotChangeProjectionToParallel()) );

    groupBoxProjection->setLayout(subBox);
    return groupBoxProjection;
}

QGroupBox *CgQtGui::createGBShaderBACKUP()
{
    QGroupBox* groupBoxShader = new QGroupBox("Shader");
//    QVBoxLayout *vboxShader = new QVBoxLayout;

//    QLabel * opt = new QLabel("selektiere eine Objekteigenschaft");
//    combo_box_shader = new QComboBox();
//    combo_box_interpolation = new QComboBox();
//    combo_box_material = new QComboBox();
//    selectMaterialShaderOff();
//    createComboBox(combo_box_material);
//    selectShader();
//    createComboBox(combo_box_shader);
//    selectInterpolation();
//    createComboBox(combo_box_interpolation);

//    vboxShader->addWidget(combo_box_material);
//    vboxShader->addWidget(combo_box_shader);
//    vboxShader->addWidget(combo_box_interpolation);
//    vboxShader->addWidget(opt);

//    connect(combo_box_material, SIGNAL(currentIndexChanged(int)),this,SLOT(selectColorSLOT()));
//    connect(combo_box_shader, SIGNAL(currentIndexChanged(int)),this,SLOT(selectShaderSlot()));
//    connect(combo_box_interpolation, SIGNAL(currentIndexChanged(int)),this,SLOT(selectInterpolationSlot()));

//    groupBoxShader->setLayout(vboxShader);

    return groupBoxShader;
}

//DON
void CgQtGui::selectMaterialShaderOn()
{
    names.clear();
    names.push_back("Chrom");
    names.push_back("Perle");
    names.push_back("Obsidian");
    names.push_back("Gold");
    names.push_back("Silber");
    names.push_back("Plastik");
}

void CgQtGui::selectMaterialShaderOff()
{
    names.clear();
    names.push_back("Rot");
    names.push_back("Gruen");
    names.push_back("Blau");
}

void CgQtGui::selectShader()
{
    names.clear();
    names.push_back("none");
    names.push_back("Phong");
    names.push_back("Gouraud");
}




//DON --COPPYED
/**
 * Auswahl an Interpolationsmöglichkeiten
 * @brief CgQtGui::selectInterpolation
 * @param names
 */
void CgQtGui::selectInterpolation()
{
    names.clear();
    names.push_back("flat");
    names.push_back("smooth");
}

/**
 * Erstelle Tab 6
 * @brief CgQtGui::Aufgabe6
 * @param parent
 */


/**
 * Erstelle Inhalt der Comboboxen
 * @brief CgQtGui::createComboBox
 * @param names
 * @param combo
 */
void CgQtGui::createComboBox(QComboBox* combo){
    for(int i =0; i<names.size(); i++){
        combo->addItem(names.at(i));
    }
}

/**
 * Löschen Inhalt der Combobox
 * @brief CgQtGui::clearComboBox
 * @param combo
 */
void CgQtGui::clearComboBox(QComboBox* combo){
    combo->clear();
}

/**
 * Slot um Farbe auszuwählen
 * @brief CgQtGui::selectColor
 */
void CgQtGui::selectColorSLOT()
{
    CgMaterialChangeEvent * materialChangeEvent = new CgMaterialChangeEvent(amb.at(1),calculateShadingMode());
    notifyObserver(materialChangeEvent);
}

void CgQtGui::slotChangeProjectionToParallel()
{
    CgBaseEvent* e = new ProjektionEvent(Cg::CgChangeProjection, glm::vec3(1,0,0));
    notifyObserver(e);
}

void CgQtGui::slotChangeProjectionToCentral()
{
    CgBaseEvent* e = new ProjektionEvent(Cg::CgChangeProjection, glm::vec3(2,0,0));
    notifyObserver(e);
}

void CgQtGui::slotChangeFrustumR(int i)
{

    CgBaseEvent* e = new ProjektionEvent(Cg::CgChangeFrustum, glm::vec3(0,0,i));
    notifyObserver(e);
}

void CgQtGui::slotChangeFrustumL(int i)
{
    CgBaseEvent* e = new ProjektionEvent(Cg::CgChangeFrustum, glm::vec3(0,1,i));
    notifyObserver(e);
}

void CgQtGui::slotChangeFrustumT(int i)
{

    CgBaseEvent* e = new ProjektionEvent(Cg::CgChangeFrustum, glm::vec3(0,2,i));
    notifyObserver(e);
}

void CgQtGui::slotChangeFrustumB(int i)
{

    CgBaseEvent* e = new ProjektionEvent(Cg::CgChangeFrustum, glm::vec3(0,3,i));
    notifyObserver(e);
}

void CgQtGui::slotChangeFrustumN(int i)
{
    CgBaseEvent* e = new ProjektionEvent(Cg::CgChangeFrustum, glm::vec3(0,4,i));
    notifyObserver(e);
}

void CgQtGui::slotChangeFrustumF(int i)
{
    CgBaseEvent* e = new ProjektionEvent(Cg::CgChangeFrustum, glm::vec3(0,5,i));
    notifyObserver(e);
}



/*****************************************************************************/
/*                                  SLOTS                                    */
/*****************************************************************************/

void CgQtGui::slotColorChanged()
{
    CgBaseEvent* e = new CgColorChangeEvent(sliderRed->value(), sliderGreen->value(), sliderBlue->value());
    notifyObserver(e);
}

void CgQtGui::slotShowCylinder()
{
    for(QAbstractButton* b : buttonGroupObjectSelection->buttons()){
        b->setChecked(false);
    }
    buttonGroupObjectSelection->button(0)->setChecked(true);
    buttonGroupObjectSelection->button(3)->setChecked(true);
    buttonGroupObjectSelection->button(4)->setChecked(true);
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
    for(QAbstractButton* b : buttonGroupObjectSelection->buttons()){
        b->setChecked(false);
    }
    buttonGroupObjectSelection->button(0)->setChecked(true);
    buttonGroupObjectSelection->button(6)->setChecked(true);
    buttonGroupObjectSelection->button(7)->setChecked(true);
    slotButtonGroupSelectionChanged();
}

void CgQtGui::slotShowLoadedObject()
{
    showObject(8);
}

void CgQtGui::slotScalePlus()
{
    CgButtonEvent* e = new CgButtonEvent();
    e->setBtScalePlus(true);
    notifyObserver(e);
}

void CgQtGui::slotScaleMinus()
{
    CgButtonEvent* e = new CgButtonEvent();
    e->setBtScaleMinus(true);
    notifyObserver(e);
}

void CgQtGui::slotRotateX()
{
    CgButtonEvent* e = new CgButtonEvent();
    e->setBtRotateX(true);
    notifyObserver(e);
}

void CgQtGui::slotRotateY()
{
    CgButtonEvent* e = new CgButtonEvent();
    e->setBtRotateY(true);
    notifyObserver(e);
}

void CgQtGui::slotRotateZ()
{
    CgButtonEvent* e = new CgButtonEvent();
    e->setBtRotateZ(true);
    notifyObserver(e);
}

void CgQtGui::slotTranslate()
{
    CgButtonEvent* e = new CgButtonEvent();
    e->setBtTranslate(true, glm::vec3(spinBoxTranslateVectorX->value(), spinBoxTranslateVectorY->value(), spinBoxTranslateVectorZ->value()));
    notifyObserver(e);
}

void CgQtGui::slotRotateVector()
{
    CgButtonEvent* e = new CgButtonEvent();
    glm::vec3 rotateVec = glm::vec3(spinBoxRotateVectorX->value(),spinBoxRotateVectorY->value(), spinBoxRotateVectorZ->value());
    e->setBtRotateCustom(true, glm::vec3(spinBoxRotateVectorX->value(),spinBoxRotateVectorY->value(), spinBoxRotateVectorZ->value()));
    notifyObserver(e);
}

void CgQtGui::showObject(int i)
{
    for(QAbstractButton* b : buttonGroupObjectSelection->buttons()){
        b->setChecked(false);
    }
    buttonGroupObjectSelection->button(0)->setChecked(true);
    buttonGroupObjectSelection->button(i)->setChecked(true);
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
    if( ! buttonGroupObjectSelection->button(1)->isChecked()){
        buttonGroupObjectSelection->button(2)->setChecked(false);
        buttonGroupObjectSelection->button(2)->setDisabled(true);
    }else{
        buttonGroupObjectSelection->button(2)->setDisabled(false);
    }
    //disable cylinder normals
    if( ! buttonGroupObjectSelection->button(3)->isChecked()){
        buttonGroupObjectSelection->button(4)->setChecked(false);
        buttonGroupObjectSelection->button(4)->setDisabled(true);
    }else{
        buttonGroupObjectSelection->button(4)->setDisabled(false);
    }
    //disable rotation body normals
    if( ! buttonGroupObjectSelection->button(6)->isChecked()){
        buttonGroupObjectSelection->button(7)->setChecked(false);
        buttonGroupObjectSelection->button(7)->setDisabled(true);
    }else{
        buttonGroupObjectSelection->button(7)->setDisabled(false);
    }
    //disable loaded object normals
    if( ! buttonGroupObjectSelection->button(8)->isChecked()){
        buttonGroupObjectSelection->button(9)->setChecked(false);
        buttonGroupObjectSelection->button(9)->setDisabled(true);
    }else{
        buttonGroupObjectSelection->button(9)->setDisabled(false);
    }

    CgObjectSelectionChangeEvent* e = new CgObjectSelectionChangeEvent();
    e->setRenderCoordinateSystem(buttonGroupObjectSelection->button(0)->isChecked());
    e->setRenderCube(buttonGroupObjectSelection->button(1)->isChecked());
    e->setRenderCubeNormals(buttonGroupObjectSelection->button(2)->isChecked());
    e->setRenderCylinder(buttonGroupObjectSelection->button(3)->isChecked());
    e->setRenderCylinderNormals(buttonGroupObjectSelection->button(4)->isChecked());
    e->setRenderRotationCurve(buttonGroupObjectSelection->button(5)->isChecked());
    e->setRenderRotationBody(buttonGroupObjectSelection->button(6)->isChecked());
    e->setRenderRotationBodyNormals(buttonGroupObjectSelection->button(7)->isChecked());
    e->setRenderLoadedObject(buttonGroupObjectSelection->button(8)->isChecked());
    e->setRenderLoadedObjectNormals(buttonGroupObjectSelection->button(9)->isChecked());
    e->setRenderCustomRotationAxis(buttonGroupObjectSelection->button(10)->isChecked());
    e->setRenderScene(buttonGroupObjectSelection->button(11)->isChecked());
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
    e->setResetRotationCurve(true);
    notifyObserver(e);
    slotRotationBodyChanged();
    slotShowRotationCurve();
}

void CgQtGui::slotLoadMeshFile()
{
    QString file =  QFileDialog::getOpenFileName(this, tr("Open Obj-File"),"../Sommer2018/CgData/",tr("Model Files (*.obj)"));
    CgBaseEvent* e = new CgLoadObjFileEvent(Cg::CgLoadObjFileEvent, file.toStdString());
    notifyObserver(e);
    slotShowLoadedObject();
}

void CgQtGui::slotTrackballChanged()
{
    CgBaseEvent* e = new CgTrackballEvent(Cg::CgTrackballEvent, m_glRenderWidget->getTrackballRotation());
    notifyObserver(e);
}

void CgQtGui::slotSelectNextObject()
{
    CgButtonEvent* e = new CgButtonEvent();
    e->setBtSelectNextObject(true);
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

//DON
void CgQtGui::shaderSlot()
{
    CgShaderEvent* ev = new CgShaderEvent();

    ev->setNoneShader(buttonGroupShadingMode->button(0)->isChecked());
    ev->setPhong(buttonGroupShadingMode->button(1)->isChecked());
    ev->setGouraud(buttonGroupShadingMode->button(2)->isChecked());

    ev->setFlat(buttonGroupShadingInterpolation->button(0)->isChecked());
    ev->setSmooth(buttonGroupShadingInterpolation->button(1)->isChecked());

    ev->setMaterialIndex(combo_box_material->currentIndex());

    notifyObserver(ev);
}

void CgQtGui::selectObjectMaterial()
{
    CgMaterialChangeEvent * materialChangeEvent = new CgMaterialChangeEvent(); //TODO
    materialChangeEvent->setShadingmode(calculateShadingMode());
    if(combo_box_material->currentIndex()!=-1){
        setMaterial(materialChangeEvent);
    }
    notifyObserver(materialChangeEvent);

}

void CgQtGui::setMaterial(CgMaterialChangeEvent* materialChangeEvent)
{
    materialChangeEvent->setAmb(amb.at(combo_box_material->currentIndex()));
    materialChangeEvent->setDiffuse(def.at(combo_box_material->currentIndex()));
    materialChangeEvent->setScalar(scala.at(combo_box_material->currentIndex()));
    materialChangeEvent->setMat(spec.at(combo_box_material->currentIndex()));
}

void CgQtGui::selectInterpolationSlot()
{
    CgMaterialChangeEvent * materialChangeEvent = new CgMaterialChangeEvent(); //TODO
    materialChangeEvent->setShadingmode(calculateShadingMode());
    if(combo_box_material->currentIndex()!=-1){
        setMaterial(materialChangeEvent);
    }
    notifyObserver(materialChangeEvent);
}



