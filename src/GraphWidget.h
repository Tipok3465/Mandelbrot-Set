#pragma once
#include "header.h"

class Node;

class GraphWidget : public QGraphicsView
{

Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr); // c-tor
public slots:
    void zoomIn();
    void zoomOut();
protected:
    void keyPressEvent(QKeyEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void scaleView(qreal scaleFactor);
signals:
    void mousePressedSignal(int x, int y);
private:
    QGraphicsScene* scene_;
};