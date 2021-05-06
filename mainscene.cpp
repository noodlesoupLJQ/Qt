#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QDebug>
#include<QTimer>
#include<QSound>
MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    setFixedSize(320,588);
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowTitle("翻金币");

    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    //开始按钮
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    chooseScene=new ChooseLevelScene;

    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
        chooseScene->hide();//隐藏选择关卡
        this->show();
    });

    QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);

    connect(startBtn,&MyPushButton::clicked,[=](){
        //qDebug()<<"点击了开始";
        startSound->play(); //开始音效
        //做弹起特效
        startBtn->zoom1();
        startBtn->zoom2();

        QTimer::singleShot(500, this,[=](){
            this->hide();
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();

            //监听选择场景的返回按钮
            connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
                this->setGeometry(chooseScene->geometry());

            });

        });

    });
}
void MainScene::paintEvent(QPaintEvent *)
{
    //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/res/PlayLevelSceneBg.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    //加载标题
    pix.load(":/res/Title.png");
    //缩放图片
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    //绘制标题
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);
}

MainScene::~MainScene()
{
    delete ui;
}
