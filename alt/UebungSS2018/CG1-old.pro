QT       += core gui opengl widgets

TEMPLATE = app

TARGET = CgQtViewer

SOURCES += main.cpp \
    CgQtViewer/CGQtGLRenderWidget.cpp \
    CgQtViewer/CgQtGui.cpp \
    CgBase/CgObservable.cpp \
    CgEvents/CgMouseEvent.cpp \
    CgQtViewer/CgQtMainApplication.cpp \
    CgSceneGraph/CgSceneControl.cpp \
    CgEvents/CgKeyEvent.cpp \
    CgQtViewer/CgQtGlBufferObject.cpp \
    CgQtViewer/CgTrackball.cpp \
    CgEvents/CgWindowResizeEvent.cpp \
    CgUtils/ObjLoader.cpp \
    CgEvents/CgColorChangeEvent.cpp \
    CgSceneGraph/CgPolyline.cpp \
    CgEvents/CgObjectSelectionChangeEvent.cpp \
    CgSceneGraph/CgCube.cpp \
    CgSceneGraph/CgTriangles.cpp \
    CgSceneGraph/CgCylinder.cpp \
    CgUtils/IdSingleton.cpp \
    CgEvents/CgValueChangedEvent.cpp \
    CgEvents/CgResetEvent.cpp \
    CgUtils/CgUtils.cpp \
    CgEvents/CgSubdivisionEvent.cpp \
    CgSceneGraph/CgRotationBody.cpp \
    CgEvents/CgLoadEvent.cpp \
    CgEvents/CgTransformationEvent.cpp

HEADERS += \
    CgBase/CgBaseRenderWindow.h \
    CgQtViewer/CgQtGLRenderWidget.h \
    CgQtViewer/CgQtGui.h \
    CgBase/CgObserver.h \
    CgBase/CgObservable.h \
    CgBase/CgBaseEvent.h \
    CgBase/CgEnums.h \
    CgEvents/CgMouseEvent.h \
    CgQtViewer/CgQtMainApplication.h \
    CgSceneGraph/CgSceneControl.h \
    CgEvents/CgKeyEvent.h \
    CgBase/CgBaseRenderer.h \
    CgBase/CgBaseRenderableObject.h \
    CgBase/CgBasePointCloud.h \
    CgBase/CgBaseTriangleMesh.h \
    CgBase/CgBasePolygonMesh.h \
    CgBase/CgBasePolyline.h \
    CgBase/CgBaseSceneControl.h \
    CgQtViewer/CgQtGlBufferObject.h \
    CgQtViewer/CgTrackball.h \
    CgEvents/CgWindowResizeEvent.h \
    CgUtils/ObjLoader.h \
    CgEvents/CgColorChangeEvent.h \
    CgSceneGraph/CgPolyline.h \
    CgEvents/CgObjectSelectionChangeEvent.h \
    CgSceneGraph/CgCube.h \
    CgSceneGraph/CgTriangles.h \
    CgSceneGraph/CgCylinder.h \
    CgUtils/IdSingleton.h \
    CgEvents/CgValueChangedEvent.h \
    CgEvents/CgResetEvent.h \
    CgUtils/CgUtils.h \
    CgEvents/CgSubdivisionEvent.h \
    CgSceneGraph/CgRotationBody.h \
    CgEvents/CgLoadEvent.h \
    CgEvents/CgTransformationEvent.h

