#-------------------------------------------------
# Struct from motion
# Project created by QtCreator 5.1
# Author: zdd
# Email: zddmail@gmail.com / zddhub@gmail.com
#
#-------------------------------------------------

QT       += core gui \
            opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stereo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qmatlabel.cpp \
    mdichild.cpp \
    disparity.cpp \
    gray2pseudocolor.cpp \
    triangulationstrategy.cpp \
    meshwidget/meshwidget.cpp \
    meshwidget/meshview/trimeshview.cpp \
    meshwidget/meshview/trianglemesh_tstrips.cpp \
    meshwidget/meshview/trianglemesh_stats.cpp \
    meshwidget/meshview/trianglemesh_pointareas.cpp \
    meshwidget/meshview/trianglemesh_normals.cpp \
    meshwidget/meshview/trianglemesh_io.cpp \
    meshwidget/meshview/trianglemesh_curvature.cpp \
    meshwidget/meshview/trianglemesh_connectivity.cpp \
    meshwidget/meshview/trianglemesh_bounding.cpp \
    meshwidget/meshview/KDtree.cpp \
    meshwidget/meshview/GLCamera.cpp \
    meshwidget/meshwindow.cpp \
    progressindicator.cpp \
    waitingdialog.cpp \
    readthread.cpp

HEADERS  += mainwindow.h \
    qmatlabel.h \
    mdichild.h \
    algo.h \
    triangulationstrategy.h \
    meshwidget/meshwidget.h \
    meshwidget/meshview/XForm.h \
    meshwidget/meshview/Vec.h \
    meshwidget/meshview/trimeshview.h \
    meshwidget/meshview/trianglemesh.h \
    meshwidget/meshview/timestamp.h \
    meshwidget/meshview/strutil.h \
    meshwidget/meshview/mempool.h \
    meshwidget/meshview/lineqn.h \
    meshwidget/meshview/KDtree.h \
    meshwidget/meshview/GLCamera.h \
    meshwidget/meshview/Color.h \
    meshwidget/meshview/bsphere.h \
    meshwidget/meshwindow.h \
    progressindicator.h \
    waitingdialog.h \
    readthread.h

FORMS    += mainwindow.ui \
    meshwidget/meshwindow.ui

INCLUDEPATH += C:/OpenCV2.4.6/opencv/build/include

CONFIG(debug, debug|release) {
#debug
LIBS += -LC:/OpenCV2.4.6/opencv/build/x86/vc10/lib/ \
    -lopencv_core246d \
    -lopencv_calib3d246d \
    -lopencv_highgui246d \
    -lopencv_imgproc246d \

} else {
#release
LIBS += -LC:/OpenCV2.4.6/opencv/build/x86/vc10/lib/ \
    -lopencv_core246 \
    -lopencv_contrib246 \
    -lopencv_calib3d246 \
    -lopencv_highgui246 \
    -lopencv_imgproc246 \
}
