#include "header.h"
#include "GraphWidget.h"
#include "Label.h"
#include "Complex.h"

#pragma once

struct Texture {
public:
    Texture(double x, double y, double size, double coef):
        cur_x(x),
        cur_y(y),
        sz_(size),
        coef_(coef){}
    double cur_x;
    double cur_y;
    double sz_;
    double coef_;
};

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void render();
protected:
    QColor getColor(double x, double y);
private slots:
    void goToSettings();
private:
    std::vector<Texture> states_;
    int bright_ = 0;
    int sensitivity_ = 100;
    QPoint start_, end_;
    QLabel* area_;
    QLabel* warning_;
    QString font_family_;
    GraphWidget* mandelbrot_view_;
    QGraphicsScene* mandelbrot_scene_;
    QLabel* settings_area_;
    double coef_ = 375000;
    double cur_x_ = -2.25;
    double cur_y_ = -1.5;
    double sz_ = 800 * coef_;
    Label* settings_;
    QLabel* mandelbrot_set_label_;
};