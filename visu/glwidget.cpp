#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
 : QOpenGLWidget(parent)
{
    this->R = 1;
    this->koef1 = 1;
    this-> koef2 = 1;
    for(int i = 0; i<3; i++){
        this->arrR0[i] = 0;
        this->arrE[i] = 0;
        this->arrP0[i] = 0;
    }
}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // заполняем экран белым цветом
    glEnable(GL_DEPTH_TEST); // задаем глубину проверки пикселей
    glShadeModel(GL_FLAT); // убираем режим сглаживания цветов
    glEnable(GL_CULL_FACE); // говорим, что будем строить только внешние поверхности
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); // фигуры будут закрашены с обеих сторон
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера изображения и глубины

      glMatrixMode(GL_MODELVIEW); // устанавливает положение и ориентацию матрице моделирования
      glLoadIdentity();           // загружает единичную матрицу моделирования

      glRotatef(xRotation, 1.0f, 0.0f, 0.0f); // поворот по X
      glRotatef(yRotation, 0.0f, 1.0f, 0.0f); // поворот по Y
      glRotatef(zRotation, 0.0f, 0.0f, 1.0f); // поворот по Z

     // drawVector(arrR0, arrE);
      drawAxis();
      drawSphere(R, arrP0);
      paintVectors(arrR0, arrE, arrP0, R, koef1, koef2);
}
void GLWidget::mousePressEvent(QMouseEvent *pe)
{
    mousePos = pe->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *pe)
{
       xRotation += 180*(GLfloat)(pe->y()-mousePos.y())/height(); // вычисляем углы поворота
       zRotation += 180*(GLfloat)(pe->x()-mousePos.x())/width();
       update(); // обновляем изображение
       mousePos = pe->pos();
}

void GLWidget::drawAxis()
{
       glLineWidth(2.0f); // устанавливаем ширину линии
       glColor4f(1.0f, 0.00f, 0.00f, 1.0f); // устанавливается цвет последующих линий
       // ось x
       glBegin(GL_LINES); // построение линии
           glVertex3f( 1.0f,  0.0f,  0.0f); // первая точка
           glVertex3f(-1.0f,  0.0f,  0.0f); // вторая точка
       glEnd();
       glColor4f(0.00f, 1.00f, 0.00f, 1.0f);
       glBegin(GL_LINES);
           // ось y
           glVertex3f( 0.0f,  1.0f,  0.0f);
           glVertex3f( 0.0f, -1.0f,  0.0f);

           glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
           // ось z
           glVertex3f( 0.0f,  0.0f,  1.0f);
           glVertex3f( 0.0f,  0.0f, -1.0f);
       glEnd();
}

void GLWidget::drawSphere(float radius, float center[])
{
    float radio = toScale(radius);
    float px, py, pz;
    int i, j;
    int n = 30;
    float incO = 2 * M_PI / n;
    float incA = M_PI / n;
    glColor4f(0.00f, 0.00f, 0.00f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    for (i = 0; i <= n; i++){
        for (j = 0; j <= n; j++) {
            pz = cos(M_PI - (incA*j))*radio;
            py = sin(M_PI - (incA*j))*sin(incO*i)*radio;
            px = sin(M_PI - (incA*j))*cos(incO*i)*radio;
            glVertex3f(px + toScale(center[0]), py + toScale(center[1]), pz + toScale(center[2]));
            pz = cos(M_PI - (incA*j))*radio;
            py = sin(M_PI - (incA*j))*sin(incO*(i + 1))*radio;
            px = sin(M_PI - (incA*j))*cos(incO*(i + 1))*radio;
            glVertex3f(px + toScale(center[0]), py + toScale(center[1]), pz + toScale(center[2]));
        }
    }
    glEnd();
}

float GLWidget::toScale(float val)
{
    return(0.1 * val);
}

float GLWidget::scall(float arr1[], float arr2[])
{
    return(arr1[0] * arr2[0] + arr1[1] * arr2[1] + arr1[2] * arr2[2]);
}

float GLWidget::norma(float arr1[], float arr2[])
{
    float arr[3];
    float sum = 0;
    for (int i = 0; i < 3; i++) {
        arr[i] = pow(arr1[i] - arr2[i], 2);
        sum += arr[i];
    }
    return(sqrt(sum));
}

void GLWidget::paintVectors(float r0[], float e[], float p0[], float rad, float k1, float k2)
{
    float arrSub[3];
    for(int i = 0; i < 3; i++){
        arrSub[i] = r0[i] - p0[i];
    }
    float scal1 = -1*scall(arrSub, e);
    float scal2 = pow(scall(arrSub, e), 2);
    float scal3 = scall(arrSub, arrSub);
    if((scal2 - (scal3 - rad * rad)) >= 0 && sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2])==1){
        float t1 = scal1 - sqrt(scal2 - scal3 + rad*rad);
        float t2 = scal1 + sqrt(scal2 - scal3 + rad*rad);
        float pointCross1[3];
        float pointCross2[3];
        for(int i = 0; i < 3; i++){
            pointCross1[i] = r0[i] + e[i] * t1;
            pointCross2[i] = r0[i] + e[i] * t2;
        }
        glLineWidth(2.0f); // устанавливаем ширину линии
        glColor4f(1.0f, 1.0f, 0.00f, 1.0f); // устанавливается цвет последующих лини
        glBegin(GL_LINE_STRIP); // построение линии
            glVertex3f(0, 0, 0);
            glVertex3f(toScale(r0[0]),  toScale(r0[1]),  toScale(r0[2])); // вторая точка
            glVertex3f(toScale(pointCross1[0]),  toScale(pointCross1[1]), toScale(pointCross1[2]));
            glVertex3f(toScale(r0[0]) + e[0], toScale(r0[1]) + e[1], toScale(r0[2]) + e[2]);
        glEnd();
        float n1[3], n2[3], eRefl1[3], eRefl2[3], eRefr1[3], eRefr2[3];
        for (int i = 0; i < 3; i++) {
            n1[i] = (pointCross1[i] - p0[i]) / norma(pointCross1, p0);
            n2[i] = (pointCross2[i] - p0[i]) / norma(pointCross2, p0);
        }
        for (int i = 0; i < 3; i++) {
            eRefl1[i] = e[i] - 2 * scall(e, n1) * n1[i];
            eRefl2[i] = e[i] - 2 * scall(e, n2) * n2[i];
        }
        float reflVec1[3], reflVec2[3], refrVec1[3], refrVec2[3];
        for (int i = 0; i < 3; i++){
            reflVec1[i] = toScale(pointCross1[i]) + eRefl1[i];
            reflVec2[i] = toScale(pointCross2[i]) + eRefl2[i];
        }
        glColor4f(0.0f, 1.0f, 1.00f, 1.0f);
        glBegin(GL_LINE_STRIP); // построение линии
            glVertex3f(toScale(pointCross1[0]),  toScale(pointCross1[1]), toScale(pointCross1[2]));
            glVertex3f(reflVec1[0], reflVec1[1], reflVec1[2]);
        glEnd();
        glBegin(GL_LINE_STRIP); // построение линии
            glVertex3f(toScale(pointCross2[0]),  toScale(pointCross2[1]), toScale(pointCross2[2]));
            glVertex3f(reflVec2[0], reflVec2[1], reflVec2[2]);
        glEnd();
        for(int i = 0; i<3; i++){
            eRefr1[i] = (k1 * e[i] - scall(e, n1) * n1[i] * k2 * (1 - sqrt((k2 * k2 - k1 * k1) / (pow(scall(e, n1), 2) * k1 * k1) + 1))) / koef2;
            eRefr2[i] = (k1 * e[i] - scall(e, n2) * n1[i] * k2 * (1 - sqrt((k2 * k2 - k1 * k1) / (pow(scall(e, n2), 2) * k1 * k1) + 1))) / koef2;
        }
        for (int i = 0; i < 3; i++){
            refrVec1[i] = toScale(pointCross1[i]) + eRefr1[i];
            refrVec2[i] = toScale(pointCross2[i]) + eRefr2[i];
        }
        glColor4f(1.0f, 0.0f, 1.00f, 1.0f);
        glBegin(GL_LINE_STRIP); // построение линии
            glVertex3f(toScale(pointCross1[0]),  toScale(pointCross1[1]), toScale(pointCross1[2]));
            glVertex3f(refrVec1[0], refrVec1[1], refrVec1[2]);
        glEnd();
        glBegin(GL_LINE_STRIP); // построение линии
            glVertex3f(toScale(pointCross2[0]),  toScale(pointCross2[1]), toScale(pointCross2[2]));
            glVertex3f(refrVec2[0], refrVec2[1], refrVec2[2]);
        glEnd();
    }
}
