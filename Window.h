//
// Created by Frederic on 05/08/2021.
//

#ifndef VSS_WINDOW_H
#define VSS_WINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "Simulatie.h"
#include "UI.h"
#include "Tools.h"

class UI;
class QSettings;

class Window : public QMainWindow{
    Q_OBJECT
public slots:
    void rightClicked(int x, int y);
    void clicked(int x, int y);
    void missClicked();
    void doubleClicked();
    void save();
public:
    Simulatie s;
    UI* ui;

    Window(QWidget *parent, Simulatie &sim);

    void on_actionExit_triggered();

private:
    void createActions();
    void createMenus();
    void createOverlay();

    QMenu *fileMenu;
    QAction *exitAct;
    QAction *saveAct;
    QPushButton *nextButton;
    QPushButton *autoButton;
};


#endif //VSS_WINDOW_H
