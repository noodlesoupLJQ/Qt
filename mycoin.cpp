#include "mycoin.h"
#include<QDebug>
#include<QMouseEvent>
#include<QTimer>
//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}
MyCoin::MyCoin(QString butImg)
{

    QPixmap pix;
    bool ret = pix.load(butImg);
    if(!ret)
    {
        qDebug() << butImg << "加载图片失败!";
    }

    this->setFixedSize( pix.width(), pix.height() );
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻转的信号槽
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min > this->max) //如果大于最大值，重置最小值，并停止定时器
        {
            this->min = 1;
            isAnimation = false;
            timer1->stop();
        }
    });

    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg((this->max)-- );
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->max < this->min) //如果小于最小值，重置最大值，并停止定时器
        {
            this->max = 8;
            isAnimation = false;
            timer2->stop();
        }
    });
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin)
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(e);
    }
}

void MyCoin::changeFlag()
{
    if(this->flag) //如果是正面，执行下列代码
    {
        timer1->start(30);
        isAnimation  = true; //做翻转动画的标志
        this->flag = false;
    }
    else //反面执行下列代码
    {
        timer2->start(30);
        isAnimation = true;
        this->flag = true;
    }
}
