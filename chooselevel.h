#ifndef CHOOSELEVEL_H
#define CHOOSELEVEL_H

#include <QMainWindow>
#include <mypushbutton.h>
#include <QWidget>
#include <QPainter>
#include "titlescene.h"
#include "playscene.h"
#include <QDebug>

class playScene;
class titleScene;

class ChooseLevel : public QMainWindow
{
    Q_OBJECT
public:
    int width, height;
    explicit ChooseLevel(titleScene * title ,QWidget *parent = nullptr);
    ~ChooseLevel();

//    void Start();
//    void Info();
//    void Exit();
    void paintEvent(QPaintEvent*);

    void backToChoose();

private:
    playScene * ps;
    titleScene * ts;

signals:

};

#endif // CHOOSELEVEL_H
