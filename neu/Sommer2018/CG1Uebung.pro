QT       += core gui opengl widgets

TEMPLATE = app

TARGET = CgViewer

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
    CgEvents/CgLoadObjFileEvent.cpp \
    CgUtils/ObjLoader.cpp \
    CgEvents/CgTrackballEvent.cpp \
    CgEvents/CgColorChangeEvent.cpp \
    CgEvents/CgObjectSelectionChangedEvent.cpp \
    CgEvents/CgResetEvent.cpp \
    CgEvents/CgSubdivisionEvent.cpp \
    CgEvents/CgTransformationEvent.cpp \
    CgEvents/CgValueChangedEvent.cpp \
    CgSceneGraph/CgCube.cpp \
    CgSceneGraph/CgCylinder.cpp \
    CgSceneGraph/CgPolyline.cpp \
    CgSceneGraph/CgRotationBody.cpp \
    CgUtils/CgUtils.cpp \
    CgUtils/IdSingleton.cpp \
    CgSceneGraph/CgExampleTriangle.cpp \
    CgSceneGraph/CgTriangleMesh.cpp



HEADERS += \
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
    CgEvents/CgLoadObjFileEvent.h \
    CgUtils/ObjLoader.h \
    CgBase/CgBaseImage.h \
    CgEvents/CgTrackballEvent.h \
    CgEvents/CgColorChangeEvent.h \
    CgEvents/CgObjectSelectionChangedEvent.h \
    CgEvents/CgResetEvent.h \
    CgEvents/CgSubdivisionEvent.h \
    CgEvents/CgTransformationEvent.h \
    CgEvents/CgValueChangedEvent.h \
    CgSceneGraph/CgCube.h \
    CgSceneGraph/CgCylinder.h \
    CgSceneGraph/CgPolyline.h \
    CgSceneGraph/CgRotationBody.h \
    CgUtils/CgUtils.h \
    CgUtils/IdSingleton.h \
    CgSceneGraph/CgExampleTriangle.h \
    CgSceneGraph/CgTriangleMesh.h

