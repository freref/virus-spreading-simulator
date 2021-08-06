//
// Created by Frederic on 05/08/2021.
//

#include "UI.h"

UI::UI(QObject *parent) : QGraphicsScene(parent){
    nPieceWidth = 45;
    nBorderWidth = 0;

    gezond = Qt::green;
    asymptomatisch = Qt::white;
    dood = Qt::black;
    gehospitaliseerd = Qt::red;
    ziek = Qt::darkYellow;
    incuberend = Qt::yellow;
}

void UI::draw(Simulatie &sim){
    s = sim;

    for (int x=0; x<sim.world.grid.size(); x++) {
        for (int y=0; y<sim.world.grid[x].size() ;y++) {
            if(sim.world.grid[x][y]->toestand == "A"){
                drawTile(x, y, asymptomatisch);
            }
            else if(sim.world.grid[x][y]->toestand == "G"){
                drawTile(x, y, gezond);
            }
            else if(sim.world.grid[x][y]->toestand == "X"){
                drawTile(x, y, dood);
            }
            else if(sim.world.grid[x][y]->toestand == "Z"){
                drawTile(x, y, ziek);
            }
            else if(sim.world.grid[x][y]->toestand == "H"){
                drawTile(x, y, gehospitaliseerd);
            }
            else if(sim.world.grid[x][y]->toestand == "I"){
                drawTile(x, y, incuberend);
            }
        }
    }
}

void UI::drawTile(int i, int j, QColor color){
    QGraphicsRectItem *rect = new QGraphicsRectItem( j * nPieceWidth , i * nPieceWidth , nPieceWidth , nPieceWidth );

    rect->setBrush(QBrush(color, Qt::SolidPattern));
    rect->setCacheMode(QGraphicsItem::NoCache);
    addItem(rect);
}

void UI::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    emit(doubleClicked());
}

void UI::mousePressEvent(QGraphicsSceneMouseEvent *e) {
    QPointF scenePos = e->scenePos();

    focusRow = rowFromPoint( scenePos.y() );
    focusCol = colFromPoint( scenePos.x() );

    if(e->button() == Qt::RightButton)
    {
        if (scenePos.x()>=0 && scenePos.x() < s.world.grid.size()* nPieceWidth && scenePos.y() >=0 && scenePos.y()< s.world.grid[0].size()* nPieceWidth) {
            emit(rightClicked((int) focusRow, (int) focusCol));
        }
    }
    else{
        if (scenePos.x()>=0 && scenePos.x() < s.world.grid.size()* nPieceWidth && scenePos.y() >=0 && scenePos.y()< s.world.grid[0].size()* nPieceWidth) {
            emit(clicked((int) focusRow, (int) focusCol));
        }
        else{
            emit(missClicked());
        }
    }

    QGraphicsScene::mousePressEvent(e);
}