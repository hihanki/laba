#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_r0x_valueChanged(double arg1);

    void on_r0y_valueChanged(double arg1);

    void on_r0z_valueChanged(double arg1);

    void on_eX_valueChanged(double arg1);

    void on_eY_valueChanged(double arg1);

    void on_eZ_valueChanged(double arg1);

    void on_radius_valueChanged(double arg1);

    void on_p0x_valueChanged(double arg1);

    void on_p0y_valueChanged(double arg1);

    void on_p0z_valueChanged(double arg1);

    void on_koefN1_valueChanged(double arg1);

    void on_koefN2_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
