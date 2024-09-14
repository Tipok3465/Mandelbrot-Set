#include "MainWindow.h"
#pragma GCC optimize("Ofast,unroll-loops,mfma,mavx,mavx2")
#pragma GCC target("avx,avx2,fma")

MainWindow::MainWindow(QWidget *parent) {
    setMouseTracking(true);
    setParent(parent);

    int id = QFontDatabase::addApplicationFont("/Users/noname/Documents/Programming/Applied/Fractal_Editor/resources/main_font.ttf");
    font_family_ = QFontDatabase::applicationFontFamilies(id).at(0);

    states_.push_back(Texture(cur_x_, cur_y_, sz_, coef_));
    mandelbrot_view_ = new GraphWidget(this);
    mandelbrot_view_->resize(800, 800);
    mandelbrot_scene_ = new QGraphicsScene();
    mandelbrot_scene_->setBackgroundBrush(QColor(64, 64, 64));
    mandelbrot_scene_->setItemIndexMethod(QGraphicsScene::NoIndex);
    mandelbrot_view_->setScene(mandelbrot_scene_);

    warning_ = new QLabel();
    warning_->resize(800, 800);
    warning_->setFont(QFont(font_family_, 20));
    warning_->setText("Just few seconds, please, wait..");
    warning_->setAlignment(Qt::AlignCenter);
    warning_->hide();

    render();
    area_ = new QLabel(this);
    area_->setStyleSheet("QLabel {"
                         "background-color: rgba(169, 0, 161, 40);"
                         "border: 2px solid rgba(111, 0, 106, 60);"
                         "}");
    area_->raise(); // fucking fuck with fuckers
    area_->hide();

    settings_area_ = new QLabel(this);
    settings_area_->resize(200, 300);
    settings_area_->setStyleSheet("QLabel {"
                                  "background-color: rgba(17, 17, 17, 80);"
                                  "}");
    settings_area_->hide();

//    QToolBar* pToolBar = new QToolBar(settings_area_);
//    pToolBar->setOrientation(Qt::Horizontal);
//    pToolBar->setLayoutDirection(Qt::LeftToRight);

    QLabel* sensitivity_label = new QLabel("Count of iterations", settings_area_);
    sensitivity_label->resize(200, 50);
    sensitivity_label->move(0, 60);
    sensitivity_label->setFont(QFont(font_family_, 20));
    sensitivity_label->setAlignment(Qt::AlignCenter);
    sensitivity_label->setStyleSheet("QLabel {"
                                    "background-color: #404040;"
                                  "}");

    QSlider* sensitivity_slider = new QSlider(Qt::Horizontal, settings_area_);
    sensitivity_slider->resize(200, 50);
    sensitivity_slider->move(0, 110);
    sensitivity_slider->setRange(100, 500);
    sensitivity_slider->setPageStep(25);

    connect(sensitivity_slider, &QSlider::sliderMoved,
            [=](int val) { sensitivity_ = val;render();});

    QLabel* brightness_label = new QLabel("Brightness of set", settings_area_);
    brightness_label->resize(200, 50);
    brightness_label->move(0, 160);
    brightness_label->setFont(QFont(font_family_, 20));
    brightness_label->setAlignment(Qt::AlignCenter);
    brightness_label->setStyleSheet("QLabel {"
                                    "background-color: #404040;"
                                    "}");

    QSlider* brightness_slider = new QSlider(Qt::Horizontal, settings_area_);
    brightness_slider->resize(200, 50);
    brightness_slider->move(0, 210);
    brightness_slider->setRange(0, 50);
    brightness_slider->setPageStep(25);

    connect(brightness_slider, &QSlider::sliderMoved,
            [=](int val) { bright_ = val;render();});

    mandelbrot_set_label_ = new QLabel(this);
    mandelbrot_set_label_->setFont(QFont(font_family_, 30));
    mandelbrot_set_label_->setText("Mandelbrot set");
    mandelbrot_set_label_->resize(300, 50);
    mandelbrot_set_label_->setAlignment(Qt::AlignCenter);
    mandelbrot_set_label_->move(250, 0);

    settings_ = new Label(this);
    settings_->setFont(QFont(font_family_, 50));
    settings_->setAlignment(Qt::AlignCenter);
    settings_->resize(50, 50);
    settings_->setText("⚙");
    connect(settings_, SIGNAL(clicked()), this, SLOT(goToSettings()));

}

MainWindow::~MainWindow() {
    delete mandelbrot_scene_;
    delete mandelbrot_view_;
    delete area_;
    delete warning_;
    delete settings_;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->buttons() == Qt::LeftButton) {
        start_ = event->pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() == Qt::LeftButton) {
        end_ = event->pos();
        int x, y;
        if (abs(start_.x() - end_.x()) <= abs(start_.y() - end_.y())) {
            x = end_.x();
            y = (start_.y() <= end_.y() ? start_.y() + abs(start_.x() - end_.x()) : start_.y() - abs(start_.x() - end_.x()));
        } else {
            x = (start_.x() <= end_.x() ? start_.x() + abs(start_.y() - end_.y()) : start_.x() - abs(start_.y() - end_.y()));
            y = end_.y();
        }
        area_->setGeometry(QRect(QPoint(start_.x(), start_.y()), QPoint(x, y)).normalized());
        area_->raise();
        area_->show();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (!settings_area_->isHidden()){
        area_->hide();
        return;
    }
    end_ = event->pos();
    int x, y;
    if (abs(start_.x() - end_.x()) <= abs(start_.y() - end_.y())) {
        x = end_.x();
        y = (start_.y() <= end_.y() ? start_.y() + abs(start_.x() - end_.x()) : start_.y() - abs(start_.x() - end_.x()));
    } else {
        x = (start_.x() <= end_.x() ? start_.x() + abs(start_.y() - end_.y()) : start_.x() - abs(start_.y() - end_.y()));
        y = end_.y();
    }
    if (start_.x() < 50 || start_.y() < 50) return;
    states_.push_back(Texture(cur_x_, cur_y_, sz_, coef_));
    double cur_sz = abs(start_.x() - x) * coef_;
    cur_x_ = start_.x() * coef_/100000000. + cur_x_;
    cur_y_ = start_.y() * coef_/100000000. + cur_y_;
    coef_ = coef_ * (cur_sz / sz_);
    sz_ = cur_sz;
    render();
    area_->hide();
}

QColor MainWindow::getColor(double x, double y) {
    Complex cur_p(x,y);
    Complex z(0, 0);
    int bright = bright_;
    while (z.check() && bright < sensitivity_) {
        z = z*z + cur_p;
        ++bright;
    }
    if (bright < sensitivity_) return QColor((255*bright) / sensitivity_, (255*bright) / sensitivity_/3, (255*bright) / sensitivity_);
    else return QColor(0, 0, 0);

}

void MainWindow::render() { // i don't wanna die..
    mandelbrot_scene_->clear();
    for (int x = 0; x < 800; ++x) {
        for (int y = 0; y < 800; ++y) {
            auto rect = new QGraphicsRectItem(x, y, 1, 1);
            rect->setPen(Qt::NoPen);
            rect->setBrush(QBrush(getColor(static_cast<double>(x*coef_/100000000. + cur_x_),
                                           static_cast<double>(y*coef_/100000000. + cur_y_))));
            mandelbrot_scene_->addItem(rect);
        }
    }
    mandelbrot_scene_->update();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Escape:
            auto t =  states_.back();
            cur_x_ = t.cur_x;
            cur_y_ = t.cur_y;
            sz_ = t.sz_;
            coef_ = t.coef_;
            if (!states_.empty()) states_.pop_back();
            render();
    }
}

void MainWindow::goToSettings() {
    settings_area_->raise();
    if (settings_area_->isHidden()) settings_area_->show();
    else settings_area_->hide();
    settings_->raise();
    update();
}
