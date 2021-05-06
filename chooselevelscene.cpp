#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include<QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{

    //设置窗口固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    //创建按钮菜单项
    QAction * quitAction = startMenu->addAction("退出");
    //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //选择关卡按钮音效
    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);

    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    //返回按钮
    MyPushButton*backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //返回按钮功能实现
    connect(backBtn,&MyPushButton::clicked,[=](){
        backSound->play();
        QTimer::singleShot(500, this,[=](){
            this->hide();
            //触发自定义信号，关闭自身，该信号写到 signals下做声明
            emit this->chooseSceneBack();
        });
    });
    //创建关卡按钮
    for(int i = 0 ; i < 20;i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + (i%4)*70 , 130+ (i/4)*70);

        //监听选择关卡按钮的信号槽
        connect(menuBtn,&MyPushButton::clicked,[=](){
            // qDebug() << "select: " << i;
            chooseSound->play();
            this->hide();
            play = new PlayScene(i+1); //将选择的关卡号 传入给PlayerScene
            play->setGeometry(this->geometry());
            play->show();//显示游戏场景
            //监听
            connect(play,&PlayScene::chooseSceneBack,[=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play = NULL;
            });

        });

        //按钮上显示的文字
        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //设置居中
        label->move(25 + (i%4)*70 , 130+ (i/4)*70);
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);  //鼠标事件穿透
    }
}
void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
