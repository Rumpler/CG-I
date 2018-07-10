

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
#include <CgEvents/CgResetEvent.h>



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
    //TODO
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
    QRadioButton* radiobuttonTriangle = new QRadioButton("&Triangle");
    QRadioButton* radiobuttonCube = new QRadioButton("&Cube");
    QRadioButton* radiobuttonCubeNormals = new QRadioButton("&Cube normals");
    QRadioButton* radiobuttonCylinder = new QRadioButton("&Cylinder");
    QRadioButton* radiobuttonCylinderNormals = new QRadioButton("&Cylinder normals");

    radiobuttonCoordinateSystem->setChecked(true);

    ButtonGroupObjects->addButton(radiobuttonCoordinateSystem,0);
    ButtonGroupObjects->addButton(radiobuttonTriangle,1);
    ButtonGroupObjects->addButton(radiobuttonCube,2);
    ButtonGroupObjects->addButton(radiobuttonCubeNormals,3);
    ButtonGroupObjects->addButton(radiobuttonCylinder,4);
    ButtonGroupObjects->addButton(radiobuttonCylinderNormals,5);

    ButtonGroupObjects->button(3)->setDisabled(true);
    ButtonGroupObjects->button(5)->setDisabled(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radiobuttonCoordinateSystem);
    vbox->addWidget(radiobuttonTriangle);
    vbox->addWidget(radiobuttonCube);
    vbox->addWidget(radiobuttonCubeNormals);
    vbox->addWidget(radiobuttonCylinder);
    vbox->addWidget(radiobuttonCylinderNormals);

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



    //Lable
    QLabel* labelAmountOfSegments = new QLabel("Amount of Segments:");
    labelAmountOfSegments->setAlignment(Qt::AlignLeft);
    panel_layout->addWidget(labelAmountOfSegments);

    //SpinBox AmountOfSegments
    spinBoxAmountOfSegments = new QSpinBox();
    spinBoxAmountOfSegments->setMinimum(2);
    spinBoxAmountOfSegments->setValue(50);
    connect(spinBoxAmountOfSegments, SIGNAL(valueChanged(int) ), this, SLOT(slotRotateObjectChanged()) );
    panel_layout->addWidget(spinBoxAmountOfSegments);

    //Lable
    QLabel* labelHeight = new QLabel("Height:");
    panel_layout->addWidget(labelHeight);
    labelHeight->setAlignment(Qt::AlignLeft);

    //DoubleSpinBox Height
    spinBoxHeightCylinderCone = new QDoubleSpinBox();
    spinBoxHeightCylinderCone->setMinimum(0.01);
    spinBoxHeightCylinderCone->setValue(0.5);
    spinBoxHeightCylinderCone->setSingleStep(0.01);
    connect(spinBoxHeightCylinderCone, SIGNAL(valueChanged(double) ), this, SLOT(slotRotateObjectChanged()) ); // TODO
    panel_layout->addWidget(spinBoxHeightCylinderCone);



    //Button Show cylinder
    QPushButton* buttonCylinder = new QPushButton("&Show Cylinder");
    connect(buttonCylinder, SIGNAL( clicked() ), this, SLOT(slotShowCylinder()) );
    panel_layout->addWidget(buttonCylinder);

    //Button Reset
    QPushButton* buttonReset = new QPushButton("&Reset Values");
    connect(buttonReset, SIGNAL( clicked() ), this, SLOT(slotReset()) );
    panel_layout->addWidget(buttonReset);


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
    ButtonGroupObjects->button(1)->setChecked(false);
    ButtonGroupObjects->button(2)->setChecked(false);
    ButtonGroupObjects->button(3)->setChecked(false);

    ButtonGroupObjects->button(4)->setChecked(true);

    slotButtonGroupSelectionChanged();
}

void CgQtGui::slotButtonGroupSelectionChanged()
{
    //Check if cube is not displayed and disable cubeNormals in case
    if( ! ButtonGroupObjects->button(2)->isChecked()){
        ButtonGroupObjects->button(3)->setChecked(false);
        ButtonGroupObjects->button(3)->setDisabled(true);
    }else{
        ButtonGroupObjects->button(3)->setDisabled(false);
    }
    //disable cylinder normals
    if( ! ButtonGroupObjects->button(4)->isChecked()){
        ButtonGroupObjects->button(5)->setChecked(false);
        ButtonGroupObjects->button(5)->setDisabled(true);
    }else{
        ButtonGroupObjects->button(5)->setDisabled(false);
    }

    CgObjectSelectionChangeEvent* e = new CgObjectSelectionChangeEvent();
    e->setRenderCoordinateSystem(ButtonGroupObjects->button(0)->isChecked());
    e->setRenderTriangle(ButtonGroupObjects->button(1)->isChecked());
    e->setRenderCube(ButtonGroupObjects->button(2)->isChecked());
    e->setRenderCubeNormals(ButtonGroupObjects->button(3)->isChecked());
    e->setRenderCylinder(ButtonGroupObjects->button(4)->isChecked());
    e->setRenderCylinderNormals(ButtonGroupObjects->button(5)->isChecked());
    notifyObserver(e);
}

void CgQtGui::slotRotateObjectChanged()
{
    CgValueChangedEvent* e = new CgValueChangedEvent();
    e->setValueAmountOfSegments(spinBoxAmountOfSegments->value());
    e->setValueHeight(spinBoxHeightCylinderCone->value());
    notifyObserver(e);
}

void CgQtGui::slotReset()
{
    spinBoxAmountOfSegments->setValue(50);
    spinBoxHeightCylinderCone->setValue(0.5);
    CgResetEvent* e = new CgResetEvent();
    notifyObserver(e);
}






void CgQtGui::slotLoadMeshFile()
{
    std::cout << "load Mesh file callback reached, but not implemented..." << std::endl;
    // Hier FileChooser öffnen, datei selektieren
    // und dann neuen Event implementieren, der das an den Controller schickt.
    // dort wird dann die Datei tatsächliche geöffnet und ein entsprechendes Mesh Objekt angelegt
    // im View(GUI) passiert nichts außer festellung DASS geladen werden soll und welche Datei und zu welchem Zweck (Mesh)
}




void CgQtGui::mouseEvent(QMouseEvent* event)
{

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



