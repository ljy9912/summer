#include "translatertask.h"
#include "ui_translatertask.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QTextBrowser>
#include <QPushButton>
#include <QHBoxLayout>
#include "mainwindow.h"
#include <QMessageBox>
#include "sqlquery.h"
#include <QListWidgetItem>
#include <QScrollBar>



translaterTask::translaterTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::translaterTask)
{
    ui->setupUi(this);
    SetStyle();
}

/*************************************************************************
【函数名称】~translaterTask
【函数功能】translatertTask的析构函数
【参数】无
【返回值】无
【开发者及日期】李佳芸 2019.7.17
【更改记录】
*************************************************************************/
translaterTask::~translaterTask()
{
    delete ui;
    ui=NULL;
    delete m_confrmBtn;
    m_confrmBtn=NULL;
    delete m_saveBtn;
    m_saveBtn=NULL;
    delete m_result;
    m_result=NULL;

}

/*************************************************************************
【函数名称】ShowValue
【函数功能】显示界面
【参数】无
【返回值】无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
void translaterTask::ShowValue(){
    m_taskList=g_backUp.m_listTaskTranslater.SearchTaskForTranslater(g_backUp.m_User);
    //定义界面要用到的控件
    m_result=new QTextEdit[m_taskList.size()];
    m_result->setStyleSheet(m_TextEditStyle);
    m_saveBtn=new QPushButton[m_taskList.size()];
    m_saveBtn->setStyleSheet(m_BtnStyle1);
    m_saveBtn->setFixedSize(171,51);
    m_confrmBtn=new QPushButton[m_taskList.size()];
    m_confrmBtn->setStyleSheet(m_BtnStyle1);
    m_confrmBtn->setFixedSize(171,51);
    for(int i=0;i<m_taskList.size();i++){
        connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,
                SLOT(setCurrentIndex(int)));
        m_iPage=i;
        if(m_taskList[i].GetFlag()==301){
            //译者第一次翻译的界面，没有负责人的评价
            if(m_taskList[i].GetFlagToLeader()==0){
                QListWidgetItem* item=new QListWidgetItem(QIcon(":/images/task.svg"),
                                                          tr("<任务来啦！>%1")
                                                          .arg(m_taskList[i].GetTitle()));
                ui->listWidget->insertItem(i,item);
            
            
                QWidget *window=new QWidget();
                QLabel *label=new QLabel(tr("任务来啦！注意截止日期噢！"));
                label->setStyleSheet(m_LabelStyle);
                QLabel *taskClass;
                if(m_taskList[i].GetTaskClass()==0){
                    taskClass=new QLabel(tr("翻译性质：中译英"));
                }
                else{
                    taskClass=new QLabel(tr("翻译性质：英译中"));
                }
                taskClass->setStyleSheet(m_LabelStyle);
                QLabel* title=new QLabel(tr("翻译标题：%1").arg(m_taskList[i].GetTitle()));
                title->setStyleSheet(m_LabelStyle);
                QLabel *intro=new QLabel(tr("任务简介：%1")
                                         .arg(m_taskList[i].GetIntroduction()));
                intro->setStyleSheet(m_LabelStyle);
                QLabel *tasks=new QLabel(tr("翻译内容："));
                tasks->setStyleSheet(m_LabelStyle);
                QTextBrowser *myTask=new QTextBrowser;
                myTask->setText(m_taskList[i].GetTask());
                myTask->setStyleSheet(m_BrowserStyle);
                QLabel *date=new QLabel(tr("翻译截止日期：%1年%2月%3日")
                                        .arg(m_taskList[i].GetEndYear())
                                        .arg(m_taskList[i].GetEndMonth())
                                        .arg(m_taskList[i].GetEndDay()));
                date->setStyleSheet(m_LabelStyle);
                QLabel *money=new QLabel(tr("任务总金额：%1元")
                                         .arg(m_taskList[i].GetMoney()));
                money->setStyleSheet(m_LabelStyle);
                QLabel *label2=new QLabel(tr("我的译文："));
                label2->setStyleSheet(m_LabelStyle);
                //对window添加排版
                QVBoxLayout *layout=new QVBoxLayout();
                layout->addWidget(label);
                layout->addWidget(taskClass);
                layout->addWidget(title);
                layout->addWidget(intro);
                layout->addWidget(tasks);
                layout->addWidget(myTask);
                layout->addWidget(date);
                layout->addWidget(money);
                layout->addWidget(label2);
                (m_result+i)->setText(m_taskList[i].GetResult());
                (m_result+i)->setStyleSheet(m_TextEditStyle);
                layout->addWidget(m_result+i);
                QHBoxLayout *btn=new QHBoxLayout;
                (m_saveBtn+i)->setText(tr("暂存"));
                (m_saveBtn+i)->setStyleSheet(m_BtnStyle1);
                (m_saveBtn+i)->setFixedSize(171,51);
                (m_confrmBtn+i)->setText(tr("提交"));
                (m_confrmBtn+i)->setStyleSheet(m_BtnStyle1);
                (m_confrmBtn+i)->setFixedSize(171,51);
                btn->addSpacing(300);
                btn->addWidget(m_saveBtn+i);
                btn->addWidget(m_confrmBtn+i);
                btn->addSpacing(300);
                layout->addLayout(btn);
                window->setLayout(layout);
                window->setStyleSheet("background-color:white;");
                ui->stackedWidget->addWidget(window);
                connect(m_saveBtn+i,SIGNAL(pressed()),this,SLOT(GetPage301save()));
                connect(m_confrmBtn+i,SIGNAL(pressed()),this,SLOT(GetPage301confrm()));
            }
            //译者修改翻译的界面，显示译者原来的翻译和历史评价
            else if(m_taskList[i].GetFlagToLeader()==2){
                QListWidgetItem* item=new QListWidgetItem(QIcon(":/images/edit.svg"),
                                                          tr("<负责人有新的修改意见啦！>%1")
                                                          .arg(m_taskList[i].GetTitle()));
                ui->listWidget->insertItem(i,item);
            
            
                QWidget *window=new QWidget();
                QLabel *label=new QLabel(tr("负责人有新的修改意见啦！请及时修改并提交！"));
                QLabel *taskClass;
                if(m_taskList[i].GetTaskClass()==0){
                    taskClass=new QLabel(tr("翻译性质：中译英"));
                }
                else{
                    taskClass=new QLabel(tr("翻译性质：英译中"));
                }
                taskClass->setStyleSheet(m_LabelStyle);
                QLabel* title=new QLabel(tr("翻译标题：%1").arg(m_taskList[i].GetTitle()));
                title->setStyleSheet(m_LabelStyle);
                QLabel *intro=new QLabel(tr("任务简介：%1")
                                         .arg(m_taskList[i].GetIntroduction()));
                intro->setStyleSheet(m_LabelStyle);
                QLabel *tasks=new QLabel(tr("翻译内容：%1").arg(m_taskList[i].GetTask()));
                tasks->setStyleSheet(m_LabelStyle);
                QLabel *money=new QLabel(tr("任务总金额：%1元").arg(m_taskList[i].GetMoney()));
                money->setStyleSheet(m_LabelStyle);
                QLabel *label1=new QLabel(tr("负责人评论："));
                label1->setStyleSheet(m_LabelStyle);
                QLabel *label2=new QLabel(tr("我的译文："));
                label2->setStyleSheet(m_LabelStyle);
                QTextBrowser *comment=new QTextBrowser;
                comment->setText(m_taskList[i].GetComment());
                comment->setStyleSheet(m_BrowserStyle);
                (m_saveBtn+i)->setText(tr("暂存"));
                (m_saveBtn+i)->setStyleSheet(m_BtnStyle1);
                (m_saveBtn+i)->setFixedSize(171,51);
                (m_confrmBtn+i)->setText(tr("提交"));
                (m_confrmBtn+i)->setStyleSheet(m_BtnStyle1);
                (m_confrmBtn+i)->setFixedSize(171,51);
                //对window添加排版
                QVBoxLayout *layout=new QVBoxLayout();
                layout->addWidget(label);
                layout->addWidget(taskClass);
                layout->addWidget(title);
                layout->addWidget(intro);
                layout->addWidget(tasks);
                layout->addWidget(money);
                layout->addWidget(label1);
                layout->addWidget(comment);
                layout->addWidget(label2);
                (m_result+i)->setText(m_taskList[i].GetResult());
                (m_result+i)->setStyleSheet(m_TextEditStyle);
                layout->addWidget(m_result+i);
                QHBoxLayout *btn=new QHBoxLayout;
                btn->addSpacing(300);
                btn->addWidget(m_saveBtn+i);
                btn->addWidget(m_confrmBtn+i);
                btn->addSpacing(300);
                layout->addLayout(btn);
                window->setLayout(layout);
                window->setStyleSheet("background-color:white;");
                ui->stackedWidget->addWidget(window);
                //连接按钮和get301save函数
                connect(m_saveBtn+i,SIGNAL(pressed()),this,SLOT(GetPage301save()));
                connect(m_confrmBtn+i,SIGNAL(pressed()),this,SLOT(GetPage301confrm()));
            }
        }
    }
}

/*************************************************************************
【函数名称】on_main_clicked
【函数功能】点击main之后，显示mainwindow
【参数】无
【返回值】无
【开发者及日期】李佳芸 2019.7.19
【更改记录】
*************************************************************************/
void translaterTask::on_Main_clicked()
{
    close();
    MainWindow r;
    r.exec();
}

/*************************************************************************
【函数名称】OnClicked_301save
【函数功能】点击暂存按钮并且获得i参数之后，显示存数据成功并且存储数据
【参数】int i
【返回值】无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void translaterTask::OnClicked_301save(int i){
    QMessageBox::information(this, tr("提示"),
                       tr("翻译暂存成功！")
                      ,tr("确定"));

    QString myResult=(m_result+i)->toPlainText();
    m_taskList[i].EditResultEditting(myResult);
    g_backUp.m_listTaskTranslater.Update(m_taskList[i]);
    close();
    translaterTask r;
    r.ShowValue();
    r.exec();
}

/*************************************************************************
【函数名称】OnClicked_301confrm
【函数功能】点击确定按钮并且获得i参数之后，显示存数据成功并且存储数据
【参数】int i
【返回值】无
【开发者及日期】李佳芸 2019.7.16
【更改记录】
*************************************************************************/
void translaterTask::OnClicked_301confrm(int i){
    if(!(m_result+i)->toPlainText().isEmpty()){
        QMessageBox::information(this, tr("提示"),
                           tr("翻译提交成功！")
                          ,tr("确定"));
        QString myResult=(m_result+i)->toPlainText();

        g_backUp.SubmitResultDone(m_taskList[i],myResult);
        close();
        translaterTask r;
        r.ShowValue();
        r.exec();
    }
    else{
        QMessageBox::warning(this, tr("警告"),
                           tr("提交译文不能为空！")
                          ,tr("确定"));
    }
}

/*************************************************************************
【函数名称】GetPage301save
【函数功能】得到按钮点击在stackedwidget中的page数
【参数】无
【返回值】无
【开发者及日期】李佳芸 2019.7.16
【更改记录】
*************************************************************************/
void translaterTask::GetPage301save(){
    for(int i=0;i<m_taskList.size();i++){
        if(m_saveBtn[i].isDown()){
            OnClicked_301save(i);
        }
    }
}

/*************************************************************************
【函数名称】GetPage301confrm
【函数功能】得到按钮点击在stackedwidget中的page数
【参数】无
【返回值】无
【开发者及日期】李佳芸 2019.7.16
【更改记录】
*************************************************************************/
void translaterTask::GetPage301confrm(){
    for(int i=0;i<m_taskList.size();i++){
        if(m_confrmBtn[i].isDown()){
            OnClicked_301confrm(i);
        }
    }
}

void translaterTask::SetStyle(){
    m_BtnStyle1="QPushButton{"
                "background-color:rgb(0, 188, 212);\
                 color: white;   "
                "border-radius: 10px; \
                 border-style: outset;font:12pt,\"等线\";}"
                 "QPushButton:hover{background-color:#198fb6; color: white;}"
                 "QPushButton:pressed{background-color:#3F51B5;\
                  border-style: inset; }";
    m_LabelStyle="QLabel{font:12pt,\"等线\";}";
    m_LineEditStyle="QLineEdit{font:12pt,\"等线\";}";
    m_TextEditStyle="QTextEdit{font:12pt,\"等线\";}";
    m_BrowserStyle="QTextBrowser{font:12pt,\"等线\";}";
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
    SetListStyle(ui->listWidget);
    QString BtnStyle2="QPushButton{border:white;background-color:white; color:black;}"
          "QPushButton:hover{backgroud-color:white;color:#3F51B5;}"
          "QPushButton:pressed{background-color:white;color:#303F9F;}";
    ui->Main->setStyleSheet(BtnStyle2);
}

void translaterTask::SetTableStyle(QTableWidget *table){
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setDefaultSectionSize(60); //设置行高
    table->setFrameShape(QFrame::NoFrame); //设置无边框
    //table->setShowGrid(false); //设置不显示格子线
    table->horizontalHeader()->setFixedHeight(70); //设置表头的高度
    table->setStyleSheet("selection-background-color:#03A9F4;font:12pt,\"等线\";"); //设置选中背景色
    table->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#B2EBF2;border:0px;font:12pt,\"等线\";}");
    table->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
      "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
      "QScrollBar::handle:hover{background:gray;}"
      "QScrollBar::sub-line{background:transparent;}"
      "QScrollBar::add-line{background:transparent;}");
    table->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
      "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
      "QScrollBar::handle:hover{background:gray;}"
      "QScrollBar::sub-line{background:transparent;}"
      "QScrollBar::add-line{background:transparent;}");
    QString BtnStyle2="QPushButton{border:white;background-color:white; color:black;}"
          "QPushButton:hover{backgroud-color:white;color:#3F51B5;}"
          "QPushButton:pressed{background-color:white;color:#303F9F;}";
    ui->Main->setStyleSheet(BtnStyle2);

}

void translaterTask::SetListStyle(QListWidget* list){
    list->setIconSize(QSize(50,30));
    list->setStyleSheet("QListWidget{color:black; }"
                        "QListWidget::Item{padding-top:4px; padding-bottom:4px; font:12pt,\"等线\";}"
                        "QListWidget::Item:hover{background:#B2EBF2; }"
                        "QListWidget::item:selected{background:#03A9F4; color:white; }");
}

