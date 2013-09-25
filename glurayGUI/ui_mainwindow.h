/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Jun 22 16:28:52 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave;
    QAction *actionLoad;
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *renderPB;
    QPushButton *applyPB;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QSpinBox *aoSB;
    QLabel *label;
    QSpinBox *sppSB;
    QLineEdit *envTB;
    QCheckBox *envCB;
    QCheckBox *aoCB;
    QCheckBox *shadowsCB;
    QGroupBox *groupBox_2;
    QDoubleSpinBox *focalDistanceSB;
    QLabel *label_2;
    QLabel *label_3;
    QDoubleSpinBox *apertureSB;
    QRadioButton *pinholeRB;
    QRadioButton *thinLensRB;
    QToolButton *envPB;
    QSpinBox *skyDomeSB;
    QCheckBox *skyDomeCB;
    QLabel *label_4;
    QDoubleSpinBox *ao_distanceSB;
    QGroupBox *groupBox_3;
    QRadioButton *phongRB;
    QRadioButton *glassRB;
    QRadioButton *lambertianRB;
    QDoubleSpinBox *riSB;
    QLabel *label_6;
    QLabel *label_7;
    QDoubleSpinBox *ri2SB;
    QRadioButton *thinDielectricRB;
    QLabel *label_8;
    QDoubleSpinBox *thicknessSB;
    QLabel *label_9;
    QDoubleSpinBox *etaSB;
    QRadioButton *transparentRB;
    QRadioButton *orenNayarRB;
    QLabel *label_10;
    QDoubleSpinBox *roughnessSB;
    QLabel *label_5;
    QDoubleSpinBox *reflectivitySB;
    QGroupBox *groupBox;
    QLabel *statusLabel;
    GLWidget *glview;
    QToolButton *previewPB;
    QToolButton *rotatePB;
    QLabel *fpsLB;
    QMenuBar *menuBar;
    QMenu *menuGLuRay;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(560, 1035);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("#scrollArea{\n"
"	background-color: qlineargradient(spread:pad, x1:0.023, y1:0.965909, x2:1, y2:0, stop:0 rgba(195, 195, 195, 255), stop:1 rgba(216, 216, 216, 255));\n"
"padding: 1px;\n"
"border-style: solid;\n"
"border: 2px solid gray;\n"
"border-radius:12px;\n"
"}\n"
"#envTB\n"
" {\n"
"padding: 1px;\n"
"border-style: solid;\n"
"border: 2px solid gray;\n"
"border-radius: 8px;\n"
"}\n"
"#MainWindow\n"
"{\n"
"	/*background-color: qlineargradient(spread:pad, x1:0.023, y1:0.965909, x2:1, y2:0, stop:0 rgba(195, 195, 195, 255), stop:1 rgba(216, 216, 216, 255));*/\n"
"}"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(350, 940, 178, 29));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        renderPB = new QPushButton(layoutWidget);
        renderPB->setObjectName(QString::fromUtf8("renderPB"));
        renderPB->setEnabled(false);

        horizontalLayout->addWidget(renderPB);

        applyPB = new QPushButton(layoutWidget);
        applyPB->setObjectName(QString::fromUtf8("applyPB"));
        applyPB->setEnabled(false);

        horizontalLayout->addWidget(applyPB);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setEnabled(true);
        scrollArea->setGeometry(QRect(30, 290, 489, 601));
        scrollArea->setAutoFillBackground(false);
        scrollArea->setStyleSheet(QString::fromUtf8(""));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 483, 595));
        aoSB = new QSpinBox(scrollAreaWidgetContents);
        aoSB->setObjectName(QString::fromUtf8("aoSB"));
        aoSB->setGeometry(QRect(390, 60, 55, 27));
        aoSB->setMinimum(0);
        aoSB->setMaximum(1000);
        aoSB->setValue(0);
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 20, 131, 17));
        sppSB = new QSpinBox(scrollAreaWidgetContents);
        sppSB->setObjectName(QString::fromUtf8("sppSB"));
        sppSB->setGeometry(QRect(390, 10, 55, 27));
        sppSB->setMinimum(1);
        sppSB->setMaximum(1000);
        envTB = new QLineEdit(scrollAreaWidgetContents);
        envTB->setObjectName(QString::fromUtf8("envTB"));
        envTB->setGeometry(QRect(50, 170, 371, 27));
        envCB = new QCheckBox(scrollAreaWidgetContents);
        envCB->setObjectName(QString::fromUtf8("envCB"));
        envCB->setGeometry(QRect(30, 140, 161, 22));
        aoCB = new QCheckBox(scrollAreaWidgetContents);
        aoCB->setObjectName(QString::fromUtf8("aoCB"));
        aoCB->setGeometry(QRect(40, 60, 231, 22));
        shadowsCB = new QCheckBox(scrollAreaWidgetContents);
        shadowsCB->setObjectName(QString::fromUtf8("shadowsCB"));
        shadowsCB->setGeometry(QRect(30, 200, 231, 22));
        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 250, 421, 111));
        focalDistanceSB = new QDoubleSpinBox(groupBox_2);
        focalDistanceSB->setObjectName(QString::fromUtf8("focalDistanceSB"));
        focalDistanceSB->setGeometry(QRect(280, 50, 62, 27));
        focalDistanceSB->setValue(2);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(150, 60, 111, 17));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(150, 90, 111, 17));
        apertureSB = new QDoubleSpinBox(groupBox_2);
        apertureSB->setObjectName(QString::fromUtf8("apertureSB"));
        apertureSB->setGeometry(QRect(280, 80, 62, 27));
        apertureSB->setValue(0.01);
        pinholeRB = new QRadioButton(groupBox_2);
        pinholeRB->setObjectName(QString::fromUtf8("pinholeRB"));
        pinholeRB->setGeometry(QRect(30, 20, 109, 22));
        pinholeRB->setChecked(true);
        thinLensRB = new QRadioButton(groupBox_2);
        thinLensRB->setObjectName(QString::fromUtf8("thinLensRB"));
        thinLensRB->setGeometry(QRect(150, 20, 109, 22));
        envPB = new QToolButton(scrollAreaWidgetContents);
        envPB->setObjectName(QString::fromUtf8("envPB"));
        envPB->setGeometry(QRect(430, 170, 26, 25));
        skyDomeSB = new QSpinBox(scrollAreaWidgetContents);
        skyDomeSB->setObjectName(QString::fromUtf8("skyDomeSB"));
        skyDomeSB->setGeometry(QRect(360, 230, 55, 27));
        skyDomeSB->setMinimum(0);
        skyDomeSB->setMaximum(1000);
        skyDomeSB->setValue(0);
        skyDomeCB = new QCheckBox(scrollAreaWidgetContents);
        skyDomeCB->setObjectName(QString::fromUtf8("skyDomeCB"));
        skyDomeCB->setGeometry(QRect(30, 230, 231, 22));
        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(150, 100, 131, 17));
        ao_distanceSB = new QDoubleSpinBox(scrollAreaWidgetContents);
        ao_distanceSB->setObjectName(QString::fromUtf8("ao_distanceSB"));
        ao_distanceSB->setGeometry(QRect(390, 90, 62, 27));
        ao_distanceSB->setValue(10);
        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(30, 380, 421, 191));
        phongRB = new QRadioButton(groupBox_3);
        phongRB->setObjectName(QString::fromUtf8("phongRB"));
        phongRB->setGeometry(QRect(10, 30, 71, 22));
        phongRB->setChecked(true);
        glassRB = new QRadioButton(groupBox_3);
        glassRB->setObjectName(QString::fromUtf8("glassRB"));
        glassRB->setGeometry(QRect(190, 30, 109, 22));
        glassRB->setChecked(false);
        lambertianRB = new QRadioButton(groupBox_3);
        lambertianRB->setObjectName(QString::fromUtf8("lambertianRB"));
        lambertianRB->setGeometry(QRect(80, 30, 101, 22));
        lambertianRB->setChecked(false);
        riSB = new QDoubleSpinBox(groupBox_3);
        riSB->setObjectName(QString::fromUtf8("riSB"));
        riSB->setGeometry(QRect(210, 50, 62, 27));
        riSB->setValue(1.5);
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(180, 60, 21, 17));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(170, 80, 31, 20));
        ri2SB = new QDoubleSpinBox(groupBox_3);
        ri2SB->setObjectName(QString::fromUtf8("ri2SB"));
        ri2SB->setGeometry(QRect(210, 80, 62, 27));
        ri2SB->setValue(1);
        thinDielectricRB = new QRadioButton(groupBox_3);
        thinDielectricRB->setObjectName(QString::fromUtf8("thinDielectricRB"));
        thinDielectricRB->setGeometry(QRect(300, 30, 121, 22));
        thinDielectricRB->setChecked(false);
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(290, 80, 71, 20));
        thicknessSB = new QDoubleSpinBox(groupBox_3);
        thicknessSB->setObjectName(QString::fromUtf8("thicknessSB"));
        thicknessSB->setGeometry(QRect(360, 80, 62, 27));
        thicknessSB->setValue(1);
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(330, 60, 31, 17));
        etaSB = new QDoubleSpinBox(groupBox_3);
        etaSB->setObjectName(QString::fromUtf8("etaSB"));
        etaSB->setGeometry(QRect(360, 50, 62, 27));
        etaSB->setValue(1.5);
        transparentRB = new QRadioButton(groupBox_3);
        transparentRB->setObjectName(QString::fromUtf8("transparentRB"));
        transparentRB->setGeometry(QRect(10, 110, 111, 22));
        transparentRB->setChecked(false);
        orenNayarRB = new QRadioButton(groupBox_3);
        orenNayarRB->setObjectName(QString::fromUtf8("orenNayarRB"));
        orenNayarRB->setGeometry(QRect(130, 110, 111, 22));
        orenNayarRB->setChecked(false);
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(140, 140, 71, 17));
        roughnessSB = new QDoubleSpinBox(groupBox_3);
        roughnessSB->setObjectName(QString::fromUtf8("roughnessSB"));
        roughnessSB->setGeometry(QRect(150, 160, 62, 27));
        roughnessSB->setValue(1.5);
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(0, 60, 91, 17));
        reflectivitySB = new QDoubleSpinBox(groupBox_3);
        reflectivitySB->setObjectName(QString::fromUtf8("reflectivitySB"));
        reflectivitySB->setGeometry(QRect(10, 80, 62, 27));
        reflectivitySB->setDecimals(3);
        reflectivitySB->setMaximum(1);
        reflectivitySB->setSingleStep(0.05);
        reflectivitySB->setValue(0);
        scrollArea->setWidget(scrollAreaWidgetContents);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 71, 21));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        statusLabel = new QLabel(centralWidget);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(10, 890, 521, 21));
        glview = new GLWidget(centralWidget);
        glview->setObjectName(QString::fromUtf8("glview"));
        glview->setGeometry(QRect(130, 10, 256, 256));
        glview->setMinimumSize(QSize(256, 256));
        glview->setMaximumSize(QSize(256, 256));
        previewPB = new QToolButton(centralWidget);
        previewPB->setObjectName(QString::fromUtf8("previewPB"));
        previewPB->setGeometry(QRect(400, 230, 26, 25));
        rotatePB = new QToolButton(centralWidget);
        rotatePB->setObjectName(QString::fromUtf8("rotatePB"));
        rotatePB->setGeometry(QRect(400, 200, 26, 25));
        rotatePB->setCheckable(true);
        rotatePB->setChecked(true);
        fpsLB = new QLabel(centralWidget);
        fpsLB->setObjectName(QString::fromUtf8("fpsLB"));
        fpsLB->setGeometry(QRect(400, 256, 71, 21));
        fpsLB->setFrameShadow(QFrame::Plain);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 560, 25));
        menuGLuRay = new QMenu(menuBar);
        menuGLuRay->setObjectName(QString::fromUtf8("menuGLuRay"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuGLuRay->menuAction());
        menuGLuRay->addAction(actionSave);
        menuGLuRay->addAction(actionLoad);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        actionLoad->setText(QApplication::translate("MainWindow", "Load...", 0, QApplication::UnicodeUTF8));
        renderPB->setText(QApplication::translate("MainWindow", "Render...", 0, QApplication::UnicodeUTF8));
        applyPB->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Samples Per Pixel: ", 0, QApplication::UnicodeUTF8));
        envCB->setText(QApplication::translate("MainWindow", "Environment Map:", 0, QApplication::UnicodeUTF8));
        aoCB->setText(QApplication::translate("MainWindow", "Ambient Occlusion Samples: ", 0, QApplication::UnicodeUTF8));
        shadowsCB->setText(QApplication::translate("MainWindow", "Shadows", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Camera", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Focal Distance:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Aperture:", 0, QApplication::UnicodeUTF8));
        pinholeRB->setText(QApplication::translate("MainWindow", "Pinhole", 0, QApplication::UnicodeUTF8));
        thinLensRB->setText(QApplication::translate("MainWindow", "ThinLens", 0, QApplication::UnicodeUTF8));
        envPB->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        skyDomeCB->setText(QApplication::translate("MainWindow", "Sky Dome", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Distance: ", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Material", 0, QApplication::UnicodeUTF8));
        phongRB->setText(QApplication::translate("MainWindow", "Phong", 0, QApplication::UnicodeUTF8));
        glassRB->setText(QApplication::translate("MainWindow", "Glass", 0, QApplication::UnicodeUTF8));
        lambertianRB->setText(QApplication::translate("MainWindow", "Lambertian", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "ri :", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "ri 2:", 0, QApplication::UnicodeUTF8));
        thinDielectricRB->setText(QApplication::translate("MainWindow", "ThinDielectric", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "thickness:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "eta :", 0, QApplication::UnicodeUTF8));
        transparentRB->setText(QApplication::translate("MainWindow", "Transparent", 0, QApplication::UnicodeUTF8));
        orenNayarRB->setText(QApplication::translate("MainWindow", "OrenNayar", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "roughness:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Reflectivity:", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Preview", 0, QApplication::UnicodeUTF8));
        statusLabel->setText(QApplication::translate("MainWindow", "Connecting...", 0, QApplication::UnicodeUTF8));
        previewPB->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        rotatePB->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        fpsLB->setText(QString());
        menuGLuRay->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
