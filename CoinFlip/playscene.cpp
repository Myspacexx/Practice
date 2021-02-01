#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}


PlayScene::PlayScene(int levelNum)
{
    QString str = QString("进入了第 %1 关 ").arg(levelNum);
    qDebug() << str;
    this->levelIndex = levelNum;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    //创建退出 菜单项
    QAction *  quitAction = startMenu->addAction("退出");

    //点击退出 实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });


    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png" , ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width() , this->height() - backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        qDebug() << "翻金币场景中：点击了返回按钮";

        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });

    });









    //显示当前关卡数
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1 = QString("Level: %1").arg(this->levelIndex);
    //将字体设置到标签控件中
    label->setFont(font);
    label->setText( str1);
    label->setGeometry(30, this->height() - 50,120, 50);

 //初始化二维数组
     dataConfig config;
     for(int i = 0 ; i < 4;i++)
     {
         for(int j = 0 ; j < 4; j++)
         {
             this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
         }
     }

     QLabel* winLabel = new QLabel;
        QPixmap tmpPix;
        tmpPix.load(":/res/LevelCompletedDialogBg.png");
        winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
        winLabel->setPixmap(tmpPix);
        winLabel->setParent(this);
        winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());




    //显示金币的背景图片
        for(int i = 0 ; i < 4;i++)
        {
            for(int j = 0 ; j < 4; j++)
            {
               //绘制背景图片

                QPixmap pix=QPixmap(":/res/BoardNode.png");
                QLabel* label = new QLabel;
                label->setGeometry(0,0,pix.width(),pix.height());
                label->setPixmap(pix);
                label->setParent(this);
                label->move(57 + i*50,200+j*50);

  //金币对象
   QString img;
  if(gameArray[i][j] == 1)
  {
    img = ":/res/Coin0001.png";
  }
  else
  {
    img = ":/res/Coin0008.png";
  }
  MyCoin * coin = new MyCoin(img);
  coin->setParent(this);
  coin->move(59 + i*50,204+j*50);



  coin->posX = i; //记录x坐标
  coin->posY = j; //记录y坐标
  coin->flag =gameArray[i][j]; //记录正反标志

  //将金币放到二维数组中
  coinBtn[i][j]=coin;

  //翻金币音效
     QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);


              //翻转测试
  connect(coin,&MyCoin::clicked,[=](){
flipSound->play();


   //qDebug() << "点击的位置： x = " <<  coin->posX << " y = " << coin->posY ;
   coin->changeFlag();
   gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0; //数组内部记录的标志同步修改

   QTimer::singleShot(300, this,[=](){
                       if(coin->posX+1 <=3)
   {
     coinBtn[coin->posX+1][coin->posY]->changeFlag();
     gameArray[coin->posX+1][coin->posY] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
   }
   if(coin->posX-1>=0)
   {
     coinBtn[coin->posX-1][coin->posY]->changeFlag();
     gameArray[coin->posX-1][coin->posY] = gameArray[coin->posX-1][coin->posY]== 0 ? 1 : 0;
   }
   if(coin->posY+1<=3)
   {
    coinBtn[coin->posX][coin->posY+1]->changeFlag();
    gameArray[coin->posX][coin->posY+1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
   }
   if(coin->posY-1>=0)
   {
    coinBtn[coin->posX][coin->posY-1]->changeFlag();
    gameArray[coin->posX][coin->posY-1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
   }
//判断是否胜利
   this->isWin = true;
                   for(int i = 0 ; i < 4;i++)
   {
       for(int j = 0 ; j < 4; j++)
       {
           //qDebug() << coinBtn[i][j]->flag ;
           if( coinBtn[i][j]->flag == false)
           {
               this->isWin = false;
               break;
           }
       }
   }

   if(this->isWin)
          {
                 qDebug() << "胜利";
//    for(int j = 0 ; j < 4; j++)
//    {
//           //qDebug() << coinBtn[i][j]->flag ;
//           if( coinBtn[i][j]->flag == true)
//           {
//               this->isWin = true;
//               break;
//           }
//       }
                 //胜利按钮音效
                   QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);

       if(this->isWin)
           {
              qDebug() << "胜利";
   QPropertyAnimation * animation1 =  new QPropertyAnimation(winLabel,"geometry");
   animation1->setDuration(1000);
   animation1->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
   animation1->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
   animation1->setEasingCurve(QEasingCurve::OutBounce);
   animation1->start();

winSound->play();
                   }

                                              }





                   });


  });




            }
        }




}







void PlayScene::paintEvent(QPaintEvent *)
{
    //创建背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);



}
