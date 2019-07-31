#include "checkertask.h"
#include "ui_checkertask.h"
#include "mainwindow.h"
#include <QLabel>
#include <QTextBrowser>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QMessageBox>
#include "sqlquery.h"
#include <QHeaderView>

/*************************************************************************
【函数名称】CheckerTask
【函数功能】 checkertask类的构造函数，构造界面并且设置界面样式表
【参数】QWidget *parent
【返回值】 无
【开发者及日期】李佳芸 2019.7.30
【更改记录】
*************************************************************************/
CheckerTask::CheckerTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckerTask)
{
    ui->setupUi(this);
    SetStyle();
}

/*************************************************************************
【函数名称】~CheckerTask
【函数功能】 CheckerTask类的析构函数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.30
【更改记录】
*************************************************************************/
CheckerTask::~CheckerTask()
{
    delete ui;
    ui=NULL;
    delete[] m_translaterTaskList;
    m_translaterTaskList=NULL;
    for(int i=0;i<m_taskList.size();i++){
        delete[] *(m_confrmBtn+i);
        *(m_confrmBtn+i)=NULL;
    }
    delete[] m_confrmBtn;
    for(int i=0;i<m_taskList.size();i++){
        delete[] *(m_saveBtn+i);
        *(m_saveBtn+i)=NULL;
    }
    delete[] m_saveBtn;
    for(int i=0;i<m_taskList.size();i++){
        delete[] *(m_NewComment+i);
        *(m_NewComment+i)=NULL;
    }
    delete[] m_NewComment;
}

/*************************************************************************
【函数名称】ShowValue
【函数功能】 显示整个页面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.30
【更改记录】
*************************************************************************/
void CheckerTask::ShowValue(){
    m_taskList=g_backUp.m_listTaskLeader
            .SearchTaskForChecker(g_backUp.m_User);
    m_confrmBtn=new QPushButton*[m_taskList.size()];
    m_saveBtn=new QPushButton*[m_taskList.size()];
    m_NewComment=new QTextEdit*[m_taskList.size()];
    m_endBtn=new QPushButton*[m_taskList.size()];
    m_translaterTaskList=new QList<taskTranslater>[m_taskList.size()];
    for(int i=0;i<m_taskList.size();i++){
        if(m_taskList[i].GetFlag()==301){
            Show301(i);
        }
    }
}


/*************************************************************************
【函数名称】Show301
【函数功能】任务状态为301时stackwidget上页面的构造
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.30
【更改记录】
*************************************************************************/
void CheckerTask::Show301(int i){

    m_iPage=i;
    //筛选已经提交的文章或已经修改并且提交的文章
    m_translaterTaskList[i]=g_backUp.m_listTaskTranslater
            .SearchTaskForTranslater_flag13(m_taskList[i].GetID());
    if(!m_translaterTaskList[i].isEmpty()){
        QListWidgetItem* item=new QListWidgetItem(QIcon(":/images/comment.svg"),
                                                  tr("<译者的翻译出炉！请点评！>%1")
                                                  .arg(m_taskList[i].GetTitle()));
        ui->listWidget->insertItem(i,item);
    //对每一个译者构建一个tabWidget来显示对应的译文并让负责人进行评价
        QTabWidget *Tab=new QTabWidget;
        SetTabStyle(Tab);
        m_NewComment[i]=new QTextEdit[m_translaterTaskList[i].size()];
        m_saveBtn[i]=new QPushButton[m_translaterTaskList[i].size()];
        m_confrmBtn[i]=new QPushButton[m_translaterTaskList[i].size()];
        m_endBtn[i]=new QPushButton[m_translaterTaskList[i].size()];
        int iFlag=0;
        for(int j=0;j<m_translaterTaskList[i].size();j++){
            m_iTab=j;
            //如果flag是1或3，表明译者完成翻译或者完成修改
           if(m_translaterTaskList[i][j].GetFlagToLeader()==1||
                    m_translaterTaskList[i][j].GetFlagToLeader()==3){
                iFlag=1;
                QString idUser=m_translaterTaskList[i][j].GetTranslater();
                QWidget *window=new QWidget;
                QLabel *title=new QLabel(tr("译者%1的翻译如下，请点评！").arg(idUser));
                title->setStyleSheet(m_LabelStyle);
                QLabel *date=new QLabel(tr("翻译截止日期：%1年%2月%3日").arg(m_translaterTaskList[i][j]
                                                                   .GetEndYear())
                                        .arg(m_translaterTaskList[i][j].GetEndMonth())
                                        .arg(m_translaterTaskList[i][j].GetEndDay()));
                date->setStyleSheet(m_LabelStyle);
                QLabel *inform1=new QLabel(tr("翻译原文："));
                inform1->setStyleSheet(m_LabelStyle);
                QLabel *inform2=new QLabel(tr("译者翻译结果"));
                inform2->setStyleSheet(m_LabelStyle);
                QLabel *inform3=new QLabel(tr("历史评价："));
                inform3->setStyleSheet(m_LabelStyle);
                QLabel *inform4=new QLabel(tr("我的评价："));
                inform4->setStyleSheet(m_LabelStyle);
                QTextBrowser *Task=new QTextBrowser;
                Task->setStyleSheet(m_BrowserStyle);
                Task->setText(m_translaterTaskList[i][j].GetTask());
                QTextBrowser *Result=new QTextBrowser;
                Result->setStyleSheet(m_BrowserStyle);
                Result->setText(m_translaterTaskList[i][j].GetResult());
                QTextBrowser *comment=new QTextBrowser;
                comment->setStyleSheet(m_BrowserStyle);
                comment->setText(m_translaterTaskList[i][j].GetComment());
                //设置写评论的TextEdit的样式
                (m_NewComment[i]+j)->setText(m_translaterTaskList[i][j]
                                             .GetCommentEditting());
                (m_NewComment[i]+j)->setStyleSheet(m_TextEditStyle);
                //设置按钮的样式
                (m_saveBtn[i]+j)->setText(tr("暂存"));
                (m_saveBtn[i]+j)->setStyleSheet(m_BtnStyle1);
                (m_saveBtn[i]+j)->setFixedSize(171,51);
                (m_confrmBtn[i]+j)->setText(tr("确定"));
                (m_confrmBtn[i]+j)->setStyleSheet(m_BtnStyle1);
                (m_confrmBtn[i]+j)->setFixedSize(171,51);
                (m_endBtn[i]+j)->setText(tr("收稿"));
                (m_endBtn[i]+j)->setStyleSheet(m_BtnStyle1);
                (m_endBtn[i]+j)->setFixedSize(171,51);
                //在布局中添加控件
                QVBoxLayout *layout=new QVBoxLayout;
                layout->addWidget(title);
                layout->addWidget(date);
                layout->addWidget(inform1);
                layout->addWidget(Task);
                layout->addWidget(inform2);
                layout->addWidget(Result);
                layout->addWidget(inform3);
                layout->addWidget(comment);
                layout->addWidget(inform4);
                layout->addWidget(m_NewComment[i]+j);
                QHBoxLayout *Btn=new QHBoxLayout;
                Btn->addWidget(m_saveBtn[i]+j);
                Btn->addWidget(m_confrmBtn[i]+j);
                Btn->addWidget(m_endBtn[i]+j);
                layout->addSpacing(30);
                layout->addLayout(Btn);
                window->setLayout(layout);
                window->setStyleSheet("background-color:white;");
                Tab->addTab(window,idUser);
                //如果点击提交，改变flag使得译者可见，审核人页面不必显示
                //修改list当中译者的历史评价的内容
                connect(m_confrmBtn[i]+j,SIGNAL(pressed()),this,SLOT(GetPage301confrm()));
                connect(m_saveBtn[i]+j,SIGNAL(pressed()),this,SLOT(GetPage301save()));
                connect(m_endBtn[i]+j,SIGNAL(pressed()),this,SLOT(GetPage301end()));
            }
           if(iFlag==0){
               QLabel* inform=new QLabel(tr("译者都在认真的翻译，休息一下吧！"));
               Tab->addTab(inform,"没有新任务");
           }
        ui->stackedWidget->addWidget(Tab);
        }
    }
}

/*************************************************************************
【函数名称】GetPage301save
【函数功能】301，saveBtn被点击之后，从leaderTask类中获得stackedwidget的i参数和TabWidget的
j参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void CheckerTask::GetPage301save(){
    for(int i=0;i<m_taskList.size();i++){
        //筛选为301状态
        if(m_taskList[i].GetFlag()==301){
            //得到i任务译者人数并筛选是哪个button正在被按下
            for(int j=0;j<g_backUp.m_listTaskTranslater
                .GetSize_301(m_taskList[i].GetID());j++){
                if((m_saveBtn[i]+j)->isDown()){
                    OnClicked_301save(i,j);
                }
            }
        }
    }
}

/*************************************************************************
【函数名称】GetPage301confrm
【函数功能】301，confrmBtn被点击之后，从leaderTask类中获得stackedwidget的i参数和TabWidget的
j参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void CheckerTask::GetPage301confrm(){
    for(int i=0;i<m_taskList.size();i++){
        //筛选为301状态
        if(m_taskList[i].GetFlag()==301){
            //得到i任务译者人数并筛选是哪个button正在被按下
            for(int j=0;j<g_backUp.m_listTaskTranslater
                .GetSize_301(m_taskList[i].GetID());j++){
                if((m_confrmBtn[i]+j)->isDown()){
                    OnClicked_301confrm(i,j);
                }
            }
        }
    }
}

/*************************************************************************
【函数名称】GetPage301end
【函数功能】301，endBtn被点击之后，从leaderTask类中获得stackedwidget的i参数和TabWidget的
j参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void CheckerTask::GetPage301end(){
    for(int i=0;i<m_taskList.size();i++){
        //筛选为301状态
        if(m_taskList[i].GetFlag()==301){
            //得到i任务译者人数并筛选是哪个button正在被按下
            for(int j=0;j<g_backUp.m_listTaskTranslater
                .GetSize_301(m_taskList[i].GetID());j++){
                if((m_endBtn[i]+j)->isDown()){
                    OnClicked_301end(i,j);
                }
            }
        }
    }
}

/*************************************************************************
【函数名称】OnClicked_301save
【函数功能】301，saveBtn被点击之后，从leaderTask类中获得stackedwidget的i参数和TabWidget的
j参数
【参数】int i,int j
【返回值】 无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void CheckerTask::OnClicked_301save(int i,int j){
    SetInformBox("评价暂存成功！");
    //存储译者暂存的评价
    m_translaterTaskList[i][j].EditCommentEditting
            ((m_NewComment[i]+j)->toPlainText());
    //将新保存的信息存入内存
    g_backUp.m_listTaskTranslater.Update(m_translaterTaskList[i][j]);
    close();
    CheckerTask r;
    r.ShowValue();
    r.exec();
}

/*************************************************************************
【函数名称】OnClicked_301confrm
【函数功能】301，confrmBtn被点击之后，从leaderTask类中获得stackedwidget的i参数和TabWidget的
j参数
【参数】int i,int j
【返回值】 无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void CheckerTask::OnClicked_301confrm(int i,int j){
    if(!(m_NewComment[i]+j)->toPlainText().isEmpty()){
        SetInformBox("评价成功！");
        QString newComment=(m_NewComment[i]+j)->toPlainText();

        //向译者和负责人发送信息提醒
        g_backUp.SubmitCommentDone(m_translaterTaskList[i][j],newComment);
        //切换页面
        close();
        CheckerTask r;
        r.ShowValue();
        r.exec();
    }
    else{
        SetWarningBox("评价不能为空！");
    }
}

/*************************************************************************
【函数名称】OnClicked_301end
【函数功能】301，endBtn被点击之后，从leaderTask类中获得stackedwidget
的i参数和TabWidget的j参数
【参数】int i,int j
【返回值】 无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void CheckerTask::OnClicked_301end(int i,int j){
    SetInformBox("收稿成功！");
    //更改任务状态

    g_backUp.EndTranslateDone_Translater(m_taskList[i]
                                         ,m_translaterTaskList[i][j]);
    //切换页面
    close();
    CheckerTask r;
    r.ShowValue();
    r.exec();

}

/*************************************************************************
【函数名称】SetStyle
【函数功能】设置页面的样式表
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.29
【更改记录】
*************************************************************************/
void CheckerTask::SetStyle(){
    //设置普通按钮的样式
    m_BtnStyle1="QPushButton{"
                "background-color:rgb(0, 188, 212);\
                 color: white;   "
                "border-radius: 10px; \
                 border-style: outset;font:12pt,\"等线\";}"
                 "QPushButton:hover{background-color:#198fb6; color: white;}"
                 "QPushButton:pressed{background-color:#3F51B5;\
                  border-style: inset; }";
    //设置标签的样式
    m_LabelStyle="QLabel{font:12pt,\"等线\";}";
    //设置Lineedit的样式
    m_LineEditStyle="QLineEdit{font:12pt,\"等线\";}";
    //设置textedit的样式
    m_TextEditStyle="QTextEdit{font:12pt,\"等线\";}";
    //设置textbrowser的样式
    m_BrowserStyle="QTextBrowser{font:12pt,\"等线\";}";
    //设置页面为无边框
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
    //设置Listwidget样式表
    SetListStyle(ui->listWidget);
    //设置返回主界面的按钮的样式
    QString BtnStyle2="QPushButton{border:white;background-color:white; color:black;}"
          "QPushButton:hover{backgroud-color:white;color:#3F51B5;}"
          "QPushButton:pressed{background-color:white;color:#303F9F;}";
    ui->Main->setStyleSheet(BtnStyle2);
    ui->exitBtn->setStyleSheet(BtnStyle2);
}

/*************************************************************************
【函数名称】SetTableStyle
【函数功能】设置表格的样式表
【参数】QTableWidget *table
【返回值】 无
【开发者及日期】李佳芸 2019.7.29
【更改记录】
*************************************************************************/
void CheckerTask::SetTableStyle(QTableWidget *table){
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    table->horizontalHeader()->setStretchLastSection(true);
    //设置行高
    table->verticalHeader()->setDefaultSectionSize(200);
    //设置无边框
    table->setFrameShape(QFrame::NoFrame);
    //设置表头的高度
    table->horizontalHeader()->setFixedHeight(70);
    //设置选中背景色
    table->setStyleSheet("selection-background-color:#03A9F4;font:12pt"
                         ",\"等线\";");
    //设置表头的格式和颜色
    table->horizontalHeader()->setStyleSheet("QHeaderView::"
                                             "section{background:#B2EBF2;"
                                             "border:0px;font:12pt,\"等线\";}");
    //设置表格旁边的scrollbar的样式
    table->horizontalScrollBar()->setStyleSheet("QScrollBar{background:"
                                                "transparent; height:10px;}"
      "QScrollBar::handle{background:lightgray; border:2px solid transparent"
                                                "; border-radius:5px;}"
      "QScrollBar::handle:hover{background:gray;}"
      "QScrollBar::sub-line{background:transparent;}"
      "QScrollBar::add-line{background:transparent;}");
    table->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent;"
                                              " width: 10px;}"
      "QScrollBar::handle{background:lightgray; border:2px solid transparent;"
                                              " border-radius:5px;}"
      "QScrollBar::handle:hover{background:gray;}"
      "QScrollBar::sub-line{background:transparent;}"
      "QScrollBar::add-line{background:transparent;}");

}

/*************************************************************************
【函数名称】SetListStyle
【函数功能】设置listwidget的样式
【参数】QListWidget* list
【返回值】 无
【开发者及日期】李佳芸 2019.7.29
【更改记录】
*************************************************************************/
void CheckerTask::SetListStyle(QListWidget* list){
    list->setIconSize(QSize(50,30));
    list->setStyleSheet("QListWidget{color:black; }"
                        "QListWidget::Item{padding-top:4px; padding-bottom:"
                        "4px; font:12pt,\"等线\";}"
                        "QListWidget::Item:hover{background:#B2EBF2; }"
                        "QListWidget::item:selected{background:#03A9F4; "
                        "color:white; }");
}

/*************************************************************************
【函数名称】SetTabStyle
【函数功能】设置tabwidget的样式
【参数】QTabWidget* tab
【返回值】 无
【开发者及日期】李佳芸 2019.7.29
【更改记录】
*************************************************************************/
void CheckerTask::SetTabStyle(QTabWidget* tab){
    tab->setIconSize(QSize(50,30));
    tab->setStyleSheet("QTabWidget::pane{top:60px;border:none;}"
                       "QTabWidget::tab-bar{alignment:left;top:10px;"
                       "left:30px;}");
    tab->tabBar()->setStyleSheet("QTabBar::tab{color:black;background:"
                                 "transparent;font:12pt,\"等线\";"
                                 "padding-right:30px;padding-left:30px;"
                                 "margin-right:0px;margin-left:0px;min-width:"
                                 "75px;min-height:30px;"
                                 "max-width:75px;max-height:30px;}"
                                 "QTabBar::tab:selected{color:#00BCD4;"
                                 "background:transparent;"
                                 "font:12pt,\"等线\";border-bottom:2px "
                                 "solid rgb(0, 188, 212);}"
                                 "QTabBar::hover:{color:rgb(0, 188, 212);"
                                 "background:transparent;"
                                 "font:12pt,\"等线\";}");
}

/*************************************************************************
【函数名称】SetWarningBox
【函数功能】显示警告的messagebox以及设置样式表
【参数】QString Text
【返回值】 无
【开发者及日期】李佳芸 2019.7.29
【更改记录】
*************************************************************************/
void CheckerTask::SetWarningBox(QString Text){
    QMessageBox message(this);
    message.setIconPixmap(QPixmap(":/images/warning.svg"));
    message.setStyleSheet("font:12pt,\"等线\";background:white;");
    message.setText(Text);
    message.setWindowTitle("警告");
    QPushButton* ysBtn=new QPushButton("确定");
    ysBtn->setStyleSheet(m_BtnStyle1);
    ysBtn->setFixedSize(171,51);
    message.addButton(ysBtn,QMessageBox::AcceptRole);
    message.exec();
}

/*************************************************************************
【函数名称】SetInformBox
【函数功能】显示information的Messagebox以及设置样式表
【参数】QString Text
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void CheckerTask::SetInformBox(QString Text){
    QMessageBox message(this);
    //设置图标
    message.setIconPixmap(QPixmap(":/images/information.svg"));
    //设置字体和背景颜色
    message.setStyleSheet("font:12pt,\"等线\";background:white;");
    //设置文字
    message.setText(Text);
    message.setWindowTitle("提示");
    //设置button的大小和样式
    QPushButton* ysBtn=new QPushButton("确定");
    ysBtn->setStyleSheet(m_BtnStyle1);
    ysBtn->setFixedSize(171,51);
    message.addButton(ysBtn,QMessageBox::AcceptRole);
    message.exec();
}

/*************************************************************************
【函数名称】on_Main_clicked
【函数功能】点击按钮返回主页面时，显示主页面并关闭该页面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void CheckerTask::on_Main_clicked()
{
    close();
    MainWindow r;
    r.exec();
}

void CheckerTask::on_exitBtn_clicked()
{
    SqlQuery query;
    query.saveUser(g_backUp.m_listUser.m_List);
    query.saveTasks(g_backUp.m_listTaskPublisher.m_List);
    query.saveSignUpForLeader(g_backUp.m_listSignUpForLeader.m_List);
    query.saveSignUpForTranslater(g_backUp.m_listSignUpForTranslater.m_List);
    query.saveTaskLeader(g_backUp.m_listTaskLeader.m_List);
    query.saveTaskTranslater(g_backUp.m_listTaskTranslater.m_List);
    query.saveMessage(g_backUp.m_listMessage.m_List);
    query.saveSignUpForChecker(g_backUp.m_listSignUpForChecker.m_List);
    close();
    exit(0);
}
