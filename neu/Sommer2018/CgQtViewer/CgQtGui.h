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

#include <QWidget>
#include <qgroupbox.h>
#include "../CgBase/CgObservable.h"

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

public:
    CgQtGui(CgQtMainApplication *mw);
    CgBaseRenderer* getRenderer();


protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;


private:
    QSlider *createColorSlider();

    // parts of the view
    CgQtGLRenderWidget*    m_glRenderWidget;
    CgQtMainApplication*   m_mainWindow;
    QTabWidget*            m_exercises_tabWidget;
    QWidget*			   m_scene_tree_view;
    QTextEdit*             m_log_browser;
    QMenuBar *             m_menuBar;

    CgQtGuiEventHandler*   m_event_handler;


    //Panels
    QWidget*               m_panel_objects;
    QWidget*               m_panel_rotate_objects;
    QWidget*               m_panel_color;


    void createOptionPanelObjects(QWidget* parent);
    void createOptionPanelRotateObjects(QWidget* parent);
    void createOptionPanelColor(QWidget* parent);

    QGroupBox* createGBObjects();
    QGroupBox* createGBTransformation();
    QGroupBox* createGBColor();


    QButtonGroup* ButtonGroupObjects;

    QSlider* sliderRed;
    QSlider* sliderGreen;
    QSlider* sliderBlue;

    QDoubleSpinBox* spinBoxHeightCylinder;
    QSpinBox* spinBoxAmountOfSegmentsCylinder;
    QDoubleSpinBox* spinBoxRadiusCylinder;

    QSpinBox* spinBoxAmountOfSegmentsRotationBody;

    QDoubleSpinBox* spinBoxTranslateVectorX;
    QDoubleSpinBox* spinBoxTranslateVectorY;
    QDoubleSpinBox* spinBoxTranslateVectorZ;





private slots:



    /* slots to catch events directly from renderer */
    void mouseEvent(QMouseEvent* event);
    void viewportChanged(int,int);
    void slotLoadMeshFile();
    void slotTrackballChanged();

    void slotSelectNextObject();

    //Gerrit
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

    void slotScalePlus();
    void slotScaleMinus();

    void slotRotateX();
    void slotRotateY();
    void slotRotateZ();

    void slotTranslate();



    void showObject(int i);

    void slotSubdivision();





};

#endif
