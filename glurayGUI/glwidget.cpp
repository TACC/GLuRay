/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include <QtOpenGL>

#include <math.h>
#include <iostream>

#include "glwidget.h"
#include <GL/glu.h>

using namespace std;

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif




/* Draw a torus */
void DrawTorus(int numc, int numt)
{
   int i, j, k;
   double s, t, x, y, z, twopi;

   twopi = 2 * M_PI;
   glBegin(GL_QUAD_STRIP);
   for (i = 0; i < numc; i++) {
      for (j = 0; j <= numt; j++) {
         for (k = 1; k >= 0; k--) {
            s = (i + k) % numc + 0.1;
            t = j % numt;

            x = (1+.1*cos(s*twopi/numc))*cos(t*twopi/numt);
            y = (1+.1*cos(s*twopi/numc))*sin(t*twopi/numt);
            z = .1 * sin(s * twopi / numc);
            glVertex3f(x, y, z);
         }
      }
   }
   glEnd();
}


void DrawSphere(float r, int sec, int slice)
{
    //glPushMatrix();
    //glLoadIdentity();
        glColor3f(1,1,1);
        //GLUquadricObj* sphereObj = gluNewQuadric ();
        //can make the planets solid, wireframe, and points
        //gluQuadricDrawStyle (sphereObj, GLU_POINT);
       // gluSphere (sphereObj, r, sec, slice);

      //  glTranslatef(0,-r,0);
       // glRotatef(-90, 1,0,0);
//GLUquadricObj* discObj = gluNewQuadric ();
  //  gluDisk(discObj, 0, r*3, 32, 32);
        glBegin(GL_QUADS);
            glVertex3f(-1,0,-1);
            glVertex3f(-1,0,1);
            glVertex3f(1,0,1);
            glVertex3f(1,0,-1);
        glEnd();

}


//! [0]
GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
   // logo = 0;
    xRot = 0;
    yRot = 0;
    zRot = 0;

    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

    dirty = true;

 setAutoFillBackground(false);
    //QTimeLine* anim = new QTimeLine(750, this);
    //anim->setUpdateInterval(20);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
        timer->start(100);
}
//! [0]

//! [1]
GLWidget::~GLWidget()
{
}
//! [1]

//! [2]
QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}
//! [2]

//! [3]
QSize GLWidget::sizeHint() const
//! [3] //! [4]
{
    return QSize(400, 400);
}
//! [4]

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

//! [5]
void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}
//! [5]

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

//! [6]
void GLWidget::initializeGL()
{
    qglClearColor(qtPurple.dark());

    //logo = new QtLogo(this, 64);
    //logo->setColor(qtGreen.dark());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void GLWidget::refreshGL()
{
    cout << "refresh called\n";
    dirty = true;
    update();
 //   dirty = true;
 //   update();
}

void GLWidget::animate()
{
    xRot += 5;
    yRot += 5;
    zRot += 5;
    //updateGL();
    update();    //draw();
    //cout << "wee\n";
}

void GLWidget::toggleAnimation()
{

static bool on =true;
on = !on;
if (on)
    timer->start();
else
    timer->stop();
}

//! [6]

//! [7]
//void GLWidget::paintGL()
//{
void GLWidget::paintEvent(QPaintEvent *event)
{
    makeCurrent();
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if (dirty){
        cout << "creating new dl\n";
        dirty=false;
        dl = glGenLists(2);
        glNewList(dl, GL_COMPILE);
       // DrawSphere(dl, 1, 32, 32);
        DrawTorus(100,100);
        glEndList();

        glNewList(dl+1, GL_COMPILE);
        glPushMatrix();
        glScalef(10,10,10);
        glBegin(GL_QUADS);
            glVertex3f(-1,0,-1);
            glVertex3f(-1,0,1);
            glVertex3f(1,0,1);
            glVertex3f(1,0,-1);
        glEnd();

        glPopMatrix();
        glEndList();
    }
    gluLookAt(1,3,4,
              0,7.7,0,
              0,1,0);
    //glTranslatef(0.0, -0.0, -7.0);
    glColor3f(1,1,1);
//glTranslatef(0,-1,0);
    glCallList(dl+1);
    glTranslatef(0,1.7,0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    glCallList(dl);
    glScalef(0.82,0.82,0.82);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    glCallList(dl);
    glScalef(0.82,0.82,0.82);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    glCallList(dl);
    glScalef(0.82,0.82,0.82);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    glCallList(dl);

 //   logo->draw();
    glFinish();

    QPainter painter(this);
//         painter.setRenderHint(QPainter::Antialiasing);
//
//         QImage img(grabFrameBuffer());
//
//         QPoint start(0,0);
//         QPoint end(0, img.height());
//         QLinearGradient gradient(start,end);
//         gradient.setColorAt(0.5,Qt::black);
//         gradient.setColorAt(0,Qt::white);
//
//         QImage mask = img;
//         QPainter mpainter(&mask);
//         mpainter.fillRect(img.rect(), gradient);
//         mpainter.end();
//
//         QImage reflection = img.mirrored();
//         reflection.setAlphaChannel(mask);

         //painter.fillRect(img.rect(), reflection);
         //painter.drawRect(img.rect());
         painter.fillRect(rect(), Qt::white);

//         painter.fillRect(QRect(0, 0, width(), height() ),
//                           QColor(0, 0, 0, 127));
//
//         QString text = tr("Click and drag with the left mouse button "
//                           "to rotate the Qt logo.");
//         QFontMetrics metrics = QFontMetrics(font());
//         int border = qMax(4, metrics.leading());
//
//         QRect rect = metrics.boundingRect(0, 0, width() - 2*border, int(height()*0.125),
//                                           Qt::AlignCenter | Qt::TextWordWrap, text);
//         painter.setRenderHint(QPainter::TextAntialiasing);
//         painter.fillRect(QRect(0, 0, width(), rect.height() + 2),
//                          QColor(0, 0, 0, 127));
//         painter.setPen(Qt::white);
//         painter.fillRect(QRect(0, 0, width(), rect.height() + 2),
//                           QColor(0, 0, 0, 127));
//         painter.drawText((width() - rect.width())/2, border,
//                           rect.width(), rect.height(),
//                           Qt::AlignCenter | Qt::TextWordWrap, text);
         painter.end();

        onDraw();
}
//! [7]

//! [8]
void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    //glViewport((width - side) / 2, (height - side) / 2, side, side);
    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,width/height, 0.01, 100);
    glMatrixMode(GL_MODELVIEW);
}
//! [8]

//! [9]
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}
//! [9]

//! [10]
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}
//! [10]
