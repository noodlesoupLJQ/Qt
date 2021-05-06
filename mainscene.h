#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include"chooselevelscene.h"
namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();

    void paintEvent(QPaintEvent*);

    //选择关卡场景
    ChooseLevelScene *chooseScene = NULL;

private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
