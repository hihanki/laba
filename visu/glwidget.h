#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include<GL/gl.h>
#include <GL/glu.h>
#pragma once
#include <QMouseEvent>
#include<math.h>
#define _USE_MATH_DEFINES // for C++
#include <cmath>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent = nullptr);
     ~GLWidget();
    float R, arrR0[3], arrE[3], arrP0[3], koef1, koef2;
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *pe);
    void mouseMoveEvent (QMouseEvent *pe);
    void drawAxis();
    void drawSphere(float radius, float center[3]);
    float toScale(float val);
    float scall(float arr1[3], float arr2[3]);
    float norma(float arr1[3], float arr2[]);
    void paintVectors(float r0[3], float e[3], float p0[3], float rad, float k1, float k2);

private:
    int xRotation = 0,yRotation = 0,zRotation = 0; // переменные поворота и масштаба
    QPoint mousePos; // переменная для запоминания позиции нажатия мышки
};

#endif // GLWIDGET_H
