

#include "CgQtGLRenderWidget.h"
#include "CgQtGui.h"
#include "CgQtMainApplication.h"
#include "../CgBase/CgEnums.h"
#include "../CgEvents/CgMouseEvent.h"
#include "../CgEvents/CgKeyEvent.h"
#include "../CgEvents/CgWindowResizeEvent.h"
#include "../CgEvents/CgColorChangeEvent.h"
#include "../CgEvents/CgObjectSelectionChangeEvent.h"
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
#include <QActionGroup>
#include <iostream>



CgQtGui::CgQtGui(CgQtMainApplication *mw)
    : m_mainWindow(mw)
{
    m_glRenderWidget = new CgQtGLRenderWidget;

    connect(m_glRenderWidget, SIGNAL(mouseEvent(QMouseEvent*)), this, SLOT(mouseEvent(QMouseEvent*)));
    connect(m_glRenderWidget, SIGNAL(viewportChanged(int,int)), this, SLOT(viewportChanged(int,int)));


    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;

    //Add new panels here
    m_panel_color = new QWidget;
    createOptionPanelColor(m_panel_color);
    m_panel_objects = new QWidget;
    createOptionPanelObjects(m_panel_objects);
    m_panel_example = new QWidget;
    createOptionPanelExample(m_panel_example);

    QTabWidget* m_tabs = new QTabWidget();

    m_tabs->addTab(m_panel_objects,"&Objects");
    m_tabs->addTab(m_panel_color, "&Color");
    m_tabs->addTab(m_panel_example,"&Examples");
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


void CgQtGui::createOptionPanelColor(QWidget* parent){
    QVBoxLayout *panel_layout = new QVBoxLayout();

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


    panel_layout->addWidget(label_red);
    panel_layout->addWidget(sliderRed);

    panel_layout->addWidget(label_green);
    panel_layout->addWidget(sliderGreen);

    panel_layout->addWidget(label_blue);
    panel_layout->addWidget(sliderBlue);

    parent->setLayout(panel_layout);
}

void CgQtGui::createOptionPanelObjects(QWidget *parent)
{
    QVBoxLayout *panel_layout = new QVBoxLayout();
    QHBoxLayout *subBox = new QHBoxLayout();

    //Apply changes in slot methode and CgObjectSelectionChangeEvent!

    //Example for using a button group

    QGroupBox* myGroupBox = new QGroupBox("Objects for rendering ");

    myButtonGroup = new QButtonGroup(subBox);
    myButtonGroup->setExclusive(false);

    QRadioButton* radiobuttonCoordinateSystem = new QRadioButton( "&Coordinate-System");
    QRadioButton* radiobuttonTriangle = new QRadioButton( "&Triangle");
    QRadioButton* radiobuttonCube = new QRadioButton( "&Cube");

    radiobuttonCoordinateSystem->setChecked(true);

    myButtonGroup->addButton(radiobuttonCoordinateSystem,0);
    myButtonGroup->addButton(radiobuttonTriangle,1);
    myButtonGroup->addButton(radiobuttonCube,2);


    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radiobuttonCoordinateSystem);
    vbox->addWidget(radiobuttonTriangle);
    vbox->addWidget(radiobuttonCube);
    vbox->addStretch(1);
    myGroupBox->setLayout(vbox);
    subBox->addWidget(myGroupBox);
    panel_layout->addLayout(subBox);

    connect(myButtonGroup, SIGNAL( buttonClicked(int) ), this, SLOT( slotButtonGroupSelectionChanged() ) );



    parent->setLayout(panel_layout);
}






void CgQtGui::createOptionPanelExample(QWidget* parent)
{
    QVBoxLayout *panel_layout = new QVBoxLayout();
    QHBoxLayout *subBox = new QHBoxLayout();


    /*Example for using a label */

    QLabel *options_label = new QLabel("Options");
    panel_layout->addWidget(options_label);
    options_label->setAlignment(Qt::AlignCenter);


    /*Example for using a spinbox */

    mySpinBox1 = new QSpinBox();
    panel_layout->addWidget(mySpinBox1);
    mySpinBox1->setMinimum(1);
    mySpinBox1->setMaximum(50);
    mySpinBox1->setValue(3);
   // mySpinBox1->setSuffix("   suffix");
   // mySpinBox1->setPrefix("Prefix:  ");
    connect(mySpinBox1, SIGNAL(valueChanged(int) ), this, SLOT(slotMySpinBox1Changed()) );
    panel_layout->addWidget(mySpinBox1);


    /*Example for using a checkbox */

    myCheckBox1 = new QCheckBox("enable Option 1");
    myCheckBox1->setCheckable(true);
    myCheckBox1->setChecked(false);
    connect(myCheckBox1, SIGNAL( clicked() ), this, SLOT(slotMyCheckBox1Changed()) );
    panel_layout->addWidget(myCheckBox1);


    /*Example for using a button */

    QPushButton* myButton1 = new QPushButton("&drueck mich");
    panel_layout->addWidget(myButton1);

    connect(myButton1, SIGNAL( clicked() ), this, SLOT(slotMyButton1Pressed()) );



/*

    //Example for using a button group

    QGroupBox* myGroupBox = new QGroupBox("Radiobutton Group Example ");

    myButtonGroup = new QButtonGroup(subBox);
    myButtonGroup->setExclusive(true);

    QRadioButton* radiobutton1 = new QRadioButton( "&Option1");
    QRadioButton* radiobutton2 = new QRadioButton( "&Option2");
    QRadioButton* radiobutton3 = new QRadioButton( "&Option3");
    QRadioButton* radiobutton4 = new QRadioButton( "&Option4");
    QRadioButton* radiobutton5 = new QRadioButton( "&Option5");

    radiobutton2->setChecked(true);

    myButtonGroup->addButton(radiobutton1,0);
    myButtonGroup->addButton(radiobutton2,1);
    myButtonGroup->addButton(radiobutton3,2);
    myButtonGroup->addButton(radiobutton4,3);
    myButtonGroup->addButton(radiobutton5,4);


    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radiobutton1);
    vbox->addWidget(radiobutton2);
    vbox->addWidget(radiobutton3);
    vbox->addWidget(radiobutton4);
    vbox->addWidget(radiobutton5);
    vbox->addStretch(1);
    myGroupBox->setLayout(vbox);
    subBox->addWidget(myGroupBox);
    panel_layout->addLayout(subBox);

    connect(myButtonGroup, SIGNAL( buttonClicked(int) ), this, SLOT( slotButtonGroupSelectionChanged() ) );

*/

    parent->setLayout(panel_layout);

}


//################################### SLOTS ###################################

void CgQtGui::slotColorChanged()
{
    CgBaseEvent* e = new CgColorChangeEvent(sliderRed->value(), sliderGreen->value(), sliderBlue->value());
    notifyObserver(e);
}

void CgQtGui::slotButtonGroupSelectionChanged()
{
    CgObjectSelectionChangeEvent* e = new CgObjectSelectionChangeEvent();
    e->setRenderCoordinateSystem(myButtonGroup->button(0)->isChecked());
    e->setRenderTriangle(myButtonGroup->button(1)->isChecked());
    e->setRenderCube( myButtonGroup->button(2)->isChecked());
    notifyObserver(e);
}

void CgQtGui::slotMySpinBox1Changed()
{

}

void CgQtGui::slotMyCheckBox1Changed()
{

}


void CgQtGui::slotLoadMeshFile()
{
    std::cout << "load Mesh file callback reached, but not implemented..." << std::endl;
    // Hier FileChooser öffnen, datei selektieren
    // und dann neuen Event implementieren, der das an den Controller schickt.
    // dort wird dann die Datei tatsächliche geöffnet und ein entsprechendes Mesh Objekt angelegt
    // im View(GUI) passiert nichts außer festellung DASS geladen werden soll und welche Datei und zu welchem Zweck (Mesh)
}

void CgQtGui::slotMyButton1Pressed()
{
   std::cout << "button 1 pressed " << std::endl;

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


