//
// Created by Frederic on 05/08/2021.
//

#ifndef VSS_UI_H
#define VSS_UI_H

#include <QGraphicsScene>
#include <QtWidgets>
#include <QPixmap>
#include "Simulatie.h"
#include <QLabel>

class QAction;
class QActionGroup;

class UI : public QGraphicsScene  {
    Q_OBJECT
private:
    quint8 rowFromPoint(int y) const { return y / nPieceWidth; }
    quint8 colFromPoint(int x) const { return x / nPieceWidth; }
public:
    quint32 nPieceWidth;
    quint32 nBorderWidth;
    qint8 focusRow, focusCol;

    Simulatie s;

    QColor gezond;
    QColor asymptomatisch;
    QColor dood;
    QColor gehospitaliseerd;
    QColor ziek;
    QColor incuberend;

    explicit UI(QObject *parent = 0);

    void draw(Simulatie &sim);
    void drawTile(int row, int column, QColor color);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
signals:
    void clicked(int x,int y);
    void rightClicked(int x, int y);
    void missClicked();
    void doubleClicked();
};


#endif //VSS_UI_H
