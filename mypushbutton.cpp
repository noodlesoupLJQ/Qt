#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>
#include"chooselevelscene.h"
#include"mycoin.h"
//MyPushButton::MyPushButton(QWidget *parent) : QWidget(parent)
//{

//}
MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

    QPixmap pix;
    bool ret=pix.load(normalImg);
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);
    //大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}
void MyPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation * animation1 = new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    animation1->setDuration(200);
    //创建起始位置
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //创建结束位置
    animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation1->start();
}

void MyPushButton::zoom2()
{
    QPropertyAnimation * animation1 =  new QPropertyAnimation(this,"geometry");
    animation1->setDuration(200);
    animation1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();
}
//鼠标事件
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath != "") //选中路径不为空，显示选中图片
    {
        QPixmap pixmap;
        bool ret = pixmap.load(pressImgPath);
        if(!ret)
        {
            qDebug() << pressImgPath << "加载图片失败!";
        }

        this->setFixedSize( pixmap.width(), pixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    //交给父类执行按下事件
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(normalImgPath != "") //选中路径不为空，显示选中图片
    {
        QPixmap pixmap;
        bool ret = pixmap.load(normalImgPath);
        if(!ret)
        {
            qDebug() << normalImgPath << "加载图片失败!";
        }
        this->setFixedSize( pixmap.width(), pixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    //交给父类执行 释放事件
    return QPushButton::mouseReleaseEvent(e);
}
