#include "header.h"
#include "GraphWidget.h"
#include "MainWindow.h"

#pragma once

class App : public QMainWindow {
Q_OBJECT

public:
    App(int width, int height);
    ~App() override;

    void render() {
        window_->show();
    }
private:
    QString font_family_;
    MainWindow* window_;
};