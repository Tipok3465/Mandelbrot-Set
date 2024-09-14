#include "App.h"

App::~App() {
    delete window_;
}

App::App(int width, int height) {
    int id = QFontDatabase::addApplicationFont("/Users/noname/Documents/Programming/Applied/Fractal_Editor/resources/main_font.ttf");
    font_family_ = QFontDatabase::applicationFontFamilies(id).at(0);
    window_ = new MainWindow();
    window_->setFixedSize(width, height);
    window_->setStyleSheet("QMainWindow {"
                           "background: #000000"
                           "}");
}



