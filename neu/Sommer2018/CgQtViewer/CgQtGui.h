/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include <QComboBox>
#include <QWidget>
#include <qgroupbox.h>
#include "../CgBase/CgObservable.h"
#include <glm/glm.hpp>

QT_BEGIN_NAMESPACE
class QSlider;
class QPushButton;
class QButtonGroup;
class QTabWidget;
class QTextEdit;
class QCheckBox;
class QSpinBox;
class QRadioButton;
class QDoubleSpinBox;
class QMenuBar;
class QAction;
QT_END_NAMESPACE

class CgQtGLRenderWidget;
class CgQtMainApplication;
class CgQtGuiEventHandler;
class CgBaseRenderer;

class CgQtGui : public QWidget,public CgObservable
{
    Q_OBJECT

private:

    //DON
    std::vector<glm::vec4> amb;
    std::vector<glm::vec4> def;
    std::vector<glm::vec4> spec;
    std::vector<float>scala;
    std::vector<QString> names;

    void createMats();
    void selectMaterialShaderOn();
    void selectMaterialShaderOff();
    void selectShader();
    void selectInterpolation();
    void Aufgabe6(QWidget* parent);
    void createComboBox(QComboBox* combo);
    void clearComboBox(QComboBox* combo);


    QComboBox* combo_box_material;
    QComboBox* combo_box_shader;
    QComboBox* combo_box_interpolation;






    QSlider *createColorSlider();

    //Panels
    QWidget*               m_panel_objects;
    QWidget*               m_panel_rotate_objects;
    QWidget*               m_panel_color;

    QButtonGroup* ButtonGroupObjects;

    QSlider* sliderRed;
    QSlider* sliderGreen;
    QSlider* sliderBlue;

    QDoubleSpinBox* spinBoxHeightCylinder;
    QSpinBox* spinBoxAmountOfSegmentsCylinder;
    QDoubleSpinBox* spinBoxRadiusCylinder;

    QSpinBox* spinBoxAmountOfSegmentsRotationBody;

    QDoubleSpinBox* spinBoxRotateVectorX;
    QDoubleSpinBox* spinBoxRotateVectorY;
    QDoubleSpinBox* spinBoxRotateVectorZ;

    QDoubleSpinBox* spinBoxTranslateVectorX;
    QDoubleSpinBox* spinBoxTranslateVectorY;
    QDoubleSpinBox* spinBoxTranslateVectorZ;

    //Helper methodes
    void showObject(int i);

    void createOptionPanelObjects(QWidget* parent);
    void createOptionPanelRotateObjects(QWidget* parent);
    void createOptionPanelColor(QWidget* parent);

    QGroupBox* createGBObjects();
    QGroupBox* createGBTransformation();
    QGroupBox* createGBColor();
    QGroupBox* createGBCylinder();
    QGroupBox* createGBRotationBody();
    QGroupBox* createGBShader();



    // parts of the view
    CgQtGLRenderWidget*    m_glRenderWidget;
    CgQtMainApplication*   m_mainWindow;
    QTabWidget*            m_exercises_tabWidget;
    QWidget*			   m_scene_tree_view;
    QTextEdit*             m_log_browser;
    QMenuBar *             m_menuBar;

    CgQtGuiEventHandler*   m_event_handler;


private slots:
    void mouseEvent(QMouseEvent* event);
    void viewportChanged(int,int);
    void slotLoadMeshFile();
    void slotTrackballChanged();

    void slotSelectNextObject();
    void slotColorChanged();
    void slotButtonGroupSelectionChanged();
    void slotCylinderChanged();
    void slotRotationBodyChanged();
    void slotResetCylinder();
    void slotResetRotationObjects();
    void slotShowCylinder();
    void slotShowRotationCurve();
    void slotShowRotationBody();
    void slotShowRotationBodyNormals();
    void slotShowLoadedObject();
    void slotSubdivision();

    void slotScalePlus();
    void slotScaleMinus();
    void slotRotateVector();
    void slotRotateX();
    void slotRotateY();
    void slotRotateZ();
    void slotTranslate();

    //DON
    void selectShaderSlot();
    void selectInterpolationSlot();
    void selectObjectMaterial();
    void selectColor();


public:
    CgQtGui(CgQtMainApplication *mw);
    CgBaseRenderer* getRenderer();


protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

};

#endif
