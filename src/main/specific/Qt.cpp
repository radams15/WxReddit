//
// Created by rhys on 31/03/2022.
//

#include <QMainWindow>
#include <QToolBar>

extern "C" void tweak(void* window){
    QMainWindow* win = (QMainWindow*) window;

    win->setUnifiedTitleAndToolBarOnMac(true);

    QToolBar* tb = win->findChild<QToolBar*>();

    tb->setMovable(false);
}