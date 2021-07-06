#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_r0x_valueChanged(double arg1)
{
    this->ui->openGLWidget->arrR0[0] = arg1;
}


void MainWindow::on_r0y_valueChanged(double arg1)
{
    this->ui->openGLWidget->arrR0[1] = arg1;
}


void MainWindow::on_r0z_valueChanged(double arg1)
{
    this->ui->openGLWidget->arrR0[2] = arg1;
}


void MainWindow::on_eX_valueChanged(double arg1)
{
    this->ui->openGLWidget->arrE[0] = arg1;
}


void MainWindow::on_eY_valueChanged(double arg1)
{
    this->ui->openGLWidget->arrE[1] = arg1;
}


void MainWindow::on_eZ_valueChanged(double arg1)
{
    this->ui->openGLWidget->arrE[2] = arg1;
}


void MainWindow::on_radius_valueChanged(double arg1)
{
    this->ui->openGLWidget->R = arg1;
}


void MainWindow::on_p0x_valueChanged(double arg1)
{
    this->ui->openGLWidget->arrP0[0] = arg1;
}


void MainWindow::on_p0y_valueChanged(double arg1)
{
    this->ui->openGLWidget->arrP0[1] = arg1;
}


void MainWindow::on_p0z_valueChanged(double arg1)
{
    this->ui->openGLWidget->arrP0[2] = arg1;
}


void MainWindow::on_koefN1_valueChanged(double arg1)
{
 this->ui->openGLWidget->koef1 = arg1;
}


void MainWindow::on_koefN2_valueChanged(double arg1)
{
 this->ui->openGLWidget->koef2 = arg1;
}

