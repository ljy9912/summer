#include "leadertask.h"
#include "ui_leadertask.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include "mainwindow.h"
#include "signupfortranslater.h"
#include <QTableWidget>
#include <QTextBrowser>
#include <QMessageBox>
#include <QTabWidget>
#include "sqlquery.h"
#include <QDate>
#include <QInputDialog>
#include <QScrollBar>

/*************************************************************************
【函数名称】leaderTask
【函数功能】leaderTask类的构造函数，设置样式表
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】2019.7.29 增加设置样式表功能
*************************************************************************/
leaderTask::leaderTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::leaderTask)
{
    ui->setupUi(this);
    SetStyle();
}

/*************************************************************************
【函数名称】~leaderTask
【函数功能】leaderTask类析构函数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
leaderTask::~leaderTask()
{
    delete ui;
    ui=NULL;
    delete[] m_yearEdit;
    m_yearEdit=NULL;
    delete[] m_monthEdit;
    m_monthEdit=NULL;
    delete[] m_dayEdit;
    m_dayEdit=NULL;
    for(int i=0;i<m_taskList.size();i++){
        delete[] *(m_confrmBtn+i);
        *(m_confrmBtn+i)=NULL;
    }
    delete[] m_confrmBtn;
    m_confrmBtn=NULL;
    for(int i=0;i<m_taskList.size();i++){
        delete[] *(m_saveBtn+i);
        *(m_saveBtn+i)=NULL;
    }
    delete[] m_saveBtn;
    m_saveBtn=NULL;
    for(int i=0;i<m_taskList.size();i++){
        delete[] *(m_endBtn+i);
        *(m_endBtn+i)=NULL;
    }
    delete[] m_endBtn;
    m_endBtn=NULL;
    for(int i=0;i<m_taskList.size();i++){
        delete[] *(m_table+i);
        *(m_table+i)=NULL;
    }
    delete[] m_table;
    m_table=NULL;
    for(int i=0;i<m_taskList.size();i++){
        delete[] *(m_NewComment+i);
        *(m_NewComment+i)=NULL;
    }
    delete[] m_NewComment;
    m_NewComment=NULL;
    delete[] m_myResult;
    m_myResult=NULL;
    delete[]m_translaterTaskList;
    m_translaterTaskList=NULL;
    delete[]m_translaterList;
    m_translaterList=NULL;
}


/*************************************************************************
【函数名称】ShowValue
【函数功能】显示整个界面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::ShowValue(){
    //开辟需要用到的控件的控件或指针的空间
    m_taskList=g_backUp.m_listTaskLeader.SearchTaskForLeader(g_backUp.m_User);
    m_yearEdit=new QLineEdit[m_taskList.size()];
    m_monthEdit=new QLineEdit[m_taskList.size()];
    m_dayEdit=new QLineEdit[m_taskList.size()];
    m_confrmBtn=new QPushButton*[m_taskList.size()];
    m_table=new QTableWidget*[m_taskList.size()];
    m_saveBtn=new QPushButton*[m_taskList.size()];
    m_NewComment=new QTextEdit*[m_taskList.size()];
    m_endBtn=new QPushButton*[m_taskList.size()];
    m_myResult=new QTextEdit[m_taskList.size()];
    m_prolongBtn=new QPushButton[m_taskList.size()];
    m_translaterTaskList=new QList<taskTranslater>[m_taskList.size()];
    m_translaterList=new QList<signUpForTranslater>[m_taskList.size()];
    //分任务状态显示不同页面的详细信息
    for(int i=0;i<m_taskList.size();i++){
        connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
        switch(m_taskList[i].GetFlag()){
        case 201:
            Show201(i);
            break;
        case 202:
            Show202(i);
            break;
        case 203:
            Show203(i);
            break;
        case 301:
            Show301(i);
            break;
        case 302:
            Show302(i);
            break;
        }
    }
}

/*************************************************************************
【函数名称】Show201
【函数功能】如果flag是201，显示界面
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::Show201(int i){
    m_iPage=i;
    m_confrmBtn[i]=new QPushButton(tr("确定"));
    //在页面左边的listWidget中添加新的item
    QListWidgetItem* item=new QListWidgetItem(QIcon(":/images/time.svg"),tr("<设定译者招募结束日期>%1").arg(m_taskList[i].GetTitle()));
    ui->listWidget->insertItem(i,item);
    //声明需要的页面的控件
    QWidget *window=new QWidget();
    QLabel *inform1=new QLabel(tr("恭喜成为负责人！请设定译者招募结束日期"));
    inform1->setStyleSheet(m_LabelStyle);
    QLabel *inform2=new QLabel(tr("翻译任务详情如下："));
    inform1->setStyleSheet(m_LabelStyle);
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
    QLabel *intro=new QLabel(tr("任务简介：%1").arg(m_taskList[i].GetIntroduction()));
    intro->setStyleSheet(m_LabelStyle);
    QLabel *tasks=new QLabel(tr("翻译内容：%1").arg(m_taskList[i].GetTask()));
    tasks->setStyleSheet(m_LabelStyle);
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(m_taskList[i].GetTime()));
    time->setStyleSheet(m_LabelStyle);
    QLabel *date1=new QLabel(tr("任务开始日期：%1年%2月%3日").arg(m_taskList[i].GetStartYear())
                             .arg(m_taskList[i].GetStartMonth())
                             .arg(m_taskList[i].GetStartDay()));
    date1->setStyleSheet(m_LabelStyle);
    QLabel *money=new QLabel(tr("任务总金额：%1元").arg(m_taskList[i].GetMoney()));
    money->setStyleSheet(m_LabelStyle);
    QLabel *date2=new QLabel(tr("译者招募结束日期："));
    date2->setStyleSheet(m_LabelStyle);
    QLabel *year=new QLabel(tr("年"));
    year->setStyleSheet(m_LabelStyle);
    QLabel *month=new QLabel(tr("月"));
    month->setStyleSheet(m_LabelStyle);
    QLabel *day=new QLabel(tr("日"));
    day->setStyleSheet(m_LabelStyle);
    //设置控件的样式
    (m_yearEdit+i)->setFixedHeight(51);
    (m_monthEdit+i)->setFixedHeight(51);
    (m_dayEdit+i)->setFixedHeight(51);
    (m_yearEdit+i)->setStyleSheet(m_LineEditStyle);
    (m_monthEdit+i)->setStyleSheet(m_LineEditStyle);
    (m_dayEdit+i)->setStyleSheet(m_LineEditStyle);
    m_confrmBtn[i]->setText(tr("确定"));
    m_confrmBtn[i]->setStyleSheet(m_BtnStyle1);
    m_confrmBtn[i]->setFixedSize(171,51);
    //在水平布局当中加入控件，为显示日期布局
    QHBoxLayout *date=new QHBoxLayout;
    date->addWidget(date2);
    date->addWidget(m_yearEdit+i);
    date->addWidget(year);
    date->addWidget(m_monthEdit+i);
    date->addWidget(month);
    date->addWidget(m_dayEdit+i);
    date->addWidget(day);
    //在垂直布局中加入控件
    QVBoxLayout *layout=new QVBoxLayout();
    layout->addWidget(inform1);
    layout->addWidget(inform2);
    layout->addWidget(taskClass);
    layout->addWidget(title);
    layout->addWidget(intro);
    layout->addWidget(tasks);
    layout->addWidget(time);
    layout->addWidget(date1);
    layout->addWidget(money);
    layout->addLayout(date);
    layout->addSpacing(30);
    layout->addWidget(m_confrmBtn[i],0,Qt::AlignCenter);
    //设定窗口为垂直布局，内嵌水平布局
    window->setLayout(layout);
    window->setStyleSheet("background-color:white;");
    //将窗口添加到stackedWidget中
    ui->stackedWidget->addWidget(window);
    //连接确定按钮和getPage201函数
    connect(m_confrmBtn[i],SIGNAL(pressed()),this,SLOT(GetPage201()));
}

/*************************************************************************
【函数名称】GetPage201
【函数功能】从leaderTask类中获得stackedwidget的i参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void leaderTask::GetPage201(){
    for(int i=0;i<m_taskList.size();i++){
        if(m_taskList[i].GetFlag()==201){
            if(m_confrmBtn[i]->isDown()){
                OnClicked_201(i);
            }
        }
    }
}

/*************************************************************************
【函数名称】OnClicked_201
【函数功能】在Show201中点击确定按钮之后并获得m_iPage的槽函数，存储用户填写的译者选择的截止日期
并更改任务状态为201
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void leaderTask::OnClicked_201(int i){
    //判断输入是否有空，如果有，提示重新输入
    if(m_yearEdit[i].text().isEmpty()||m_monthEdit[i].text().isEmpty()||m_dayEdit[i].text().isEmpty()){
        SetWarningBox("截止日期不能为空！");
    }
    //如果输入日期没有空，判断输入日期是否有效
    else{
        int iTranslaterYear=m_yearEdit[i].text().toInt();
        int iTranslaterMonth=m_monthEdit[i].text().toInt();
        int iTranslaterDay=m_dayEdit[i].text().toInt();
        QDate time;
        time.setDate(iTranslaterYear,iTranslaterMonth,iTranslaterDay);
        if(time.isValid()){
            //如果输入有效，存储并提示设置日期成功

            SetInformBox("译者报名截止时间设置成功！");
            g_backUp.SetTranslaterDone(m_taskList[i],iTranslaterYear,iTranslaterMonth,iTranslaterDay);
            close();
            leaderTask r;
            r.ShowValue();
            r.exec();
        }
        //如果输入无效，提示重新输入，并清空用户输入的数据
        else{
            SetWarningBox("输入的日期无效，请重新输入！");
            m_yearEdit[i].clear();
            m_monthEdit[i].clear();
            m_dayEdit[i].clear();
            m_yearEdit[i].setFocus();
        }
    }
}

/*************************************************************************
【函数名称】Show202
【函数功能】如果flag是202，显示界面
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::Show202(int i){
    //向listWidget中插入新的item
    QListWidgetItem* item=new QListWidgetItem(QIcon(":/images/baomingblue.svg")
                                              ,tr("<译者报名火热进行中>%1").arg(m_taskList[i].GetTitle()));
    ui->listWidget->insertItem(i,item);
    //开辟需要的控件的空间
    m_translaterList[i]=g_backUp.m_listSignUpForTranslater.SearchTranslaterForTask(m_taskList[i]);
    m_table[i]=new QTableWidget(m_translaterList[i].size(),3);
    SetTableStyle(m_table[i]);
    QWidget *window=new QWidget;
    QVBoxLayout *layout=new QVBoxLayout();
    QLabel *label=new QLabel(tr("已报名译者："));
    label->setStyleSheet(m_LabelStyle);
    //设置表格的性质为不可编辑
    m_table[i]->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置表格标题
    m_table[i]->setWindowTitle("已报名译者");
    //设置表头
    QStringList header;
    header<<"用户名"<<"英语资历"<<"积分";
    m_table[i]->setHorizontalHeaderLabels(header);
    //设置表格内容
    for(int j=0;j<m_translaterList[i].size();j++){
        m_table[i]->setItem(j,0,new QTableWidgetItem(m_translaterList[i][j].GetID()));
        m_table[i]->setItem(j,1,new QTableWidgetItem(m_translaterList[i][j].GetEnglish()));
        m_table[i]->setItem(j,2,new QTableWidgetItem(QString::number(m_translaterList[i][j].GetRewrdPoint())));
    }
    layout->addWidget(label);
    layout->addWidget(m_table[i]);
    window->setLayout(layout);
    ui->stackedWidget->addWidget(window);
}

/*************************************************************************
【函数名称】Show203
【函数功能】如果flag是203，显示界面
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::Show203(int i){
    m_iPage=i;
    //向Listwidget中添加新的item
    QListWidgetItem* item=new QListWidgetItem(QIcon(":/images/choose1.svg")
                                              ,tr("<译者报名完毕，请分配任务！>%1")
                                              .arg(m_taskList[i].GetTitle()));
    ui->listWidget->insertItem(i,item);
    //声明要用到的控件
    m_translaterList[i]=g_backUp.m_listSignUpForTranslater.SearchTranslaterForTask(m_taskList[i]);
    m_table[i]=new QTableWidget(m_translaterList[i].size(),5);
    SetTableStyle(m_table[i]);
    QWidget *window=new QWidget;
    QVBoxLayout *layout=new QVBoxLayout();
    QLabel *label1=new QLabel(tr("翻译原文"));
    label1->setStyleSheet(m_LabelStyle);
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(m_taskList[i].GetTime()));
    time->setStyleSheet(m_LabelStyle);
    QLabel *date1=new QLabel(tr("任务开始日期：%1年%2月%3日").arg(m_taskList[i].GetStartYear())
                             .arg(m_taskList[i].GetStartMonth())
                             .arg(m_taskList[i].GetStartDay()));
    date1->setStyleSheet(m_LabelStyle);
    QLabel *label2=new QLabel(tr("已报名译者："));
    label2->setStyleSheet(m_LabelStyle);
    QTextBrowser *Task=new QTextBrowser;
    Task->setText(m_taskList[i].GetTask());
    Task->setStyleSheet(m_BrowserStyle);
    (m_table[i])->setWindowTitle("分配任务：（任务和截止日期均为空白表示未被选为译者）");
    //设置表头
    QStringList header;
    header<<"用户名"<<"英语资历"<<"积分"<<"任务"<<"任务截止日期（年-月-日）";
    (m_table[i])->setHorizontalHeaderLabels(header);
    //在表格中添加内容
    for(int j=0;j<m_translaterList[i].size();j++){
        (m_table[i])->setItem(j,0,new QTableWidgetItem(m_translaterList[i][j].GetID()));
        (m_table[i])->setItem(j,1,new QTableWidgetItem(m_translaterList[i][j].GetEnglish()));
        (m_table[i])->setItem(j,2,new QTableWidgetItem(QString::number(m_translaterList[i][j].GetRewrdPoint())));
    }
    //在布局中添加控件
    layout->addWidget(label1);
    layout->addWidget(Task);
    layout->addWidget(time);
    layout->addWidget(date1);
    layout->addWidget(label2);
    layout->addWidget(m_table[i]);
    m_confrmBtn[i]=new QPushButton(tr("确定"));
    m_confrmBtn[i]->setStyleSheet(m_BtnStyle1);
    m_confrmBtn[i]->setFixedSize(171,51);
    m_prolongBtn[i].setText("延期");
    m_prolongBtn[i].setStyleSheet(m_BtnStyle1);
    m_prolongBtn[i].setFixedSize(171,51);
    QHBoxLayout* Btn=new QHBoxLayout;
    Btn->addSpacing(300);
    Btn->addWidget(m_confrmBtn[i]);
    Btn->addWidget(m_prolongBtn+i);
    Btn->addSpacing(300);
    layout->addLayout(Btn);
    window->setLayout(layout);
    window->setStyleSheet("background-color:white;");
    ui->stackedWidget->addWidget(window);
    //如果负责人分配任务完成，确认按钮被点击，将表格中的内容存储
    //连接按钮和GetPage203函数
    connect(m_confrmBtn[i],SIGNAL(pressed()),this,SLOT(GetPage203confrm()));
    connect((m_prolongBtn+i),SIGNAL(pressed()),this,SLOT(GetPage203prolong()));
}

/*************************************************************************
【函数名称】GetPage203confrm
【函数功能】点击确认按钮之后从leaderTask类中获得stackedwidget的i参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.28
【更改记录】
*************************************************************************/
void leaderTask::GetPage203confrm(){
    for(int i=0;i<m_taskList.size();i++){
        if(m_taskList[i].GetFlag()==203){
            if(m_confrmBtn[i]->isDown()){
                OnClicked_203confrm(i);
            }
        }
    }
}

/*************************************************************************
【函数名称】GetPage203prolong
【函数功能】点击延长按钮之后从leaderTask类中获得stackedwidget的i参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.28
【更改记录】
*************************************************************************/
void leaderTask::GetPage203prolong(){
    for(int i=0;i<m_taskList.size();i++){
        if(m_taskList[i].GetFlag()==203){
            if((m_prolongBtn+i)->isDown()){
                OnClicked_203prolong(i);
            }
        }
    }
}

/*************************************************************************
【函数名称】OnClicked_203
【函数功能】在Show203中点击确定按钮之后并获得m_iPage的槽函数，存储用户分配的任务并且
删除报名表中的该任务的报名信息，同时更改用户状态为301
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.23
【更改记录】2019.7.27 增加容错功能
*************************************************************************/
void leaderTask::OnClicked_203confrm(int i){
    int iFlag=0;
    for(int j=0;j<m_translaterList[i].size();j++){
        //对表格的每一行，即每一个译者，生成一个译者的任务对象并且加入List当中
        int iEndYear;
        int iEndMonth;
        int iEndDay;
        if(m_table[i]->item(j,3)!=NULL||(m_table[i]->item(j,3)
                                         &&m_table[i]->item(j,3)->text()!=tr(""))){
            iFlag=2;
            if(m_table[i]->item(j,4)!=NULL||(m_table[i]->item(j,4)
                                             &&m_table[i]->item(j,4)->text()!=tr(""))){
                //检验输入的日期是否合法
                QString EndDate=m_table[i]->item(j,4)->text();
                iEndYear=EndDate.mid(0,4).toInt();
                iEndMonth=EndDate.mid(5,2).toInt();
                iEndDay=EndDate.mid(8,2).toInt();
                if(EndDate[4]=='-'&&EndDate[7]=='-'&&iEndYear!=NULL&&
                        iEndMonth!=NULL&&iEndDay!=NULL){
                    //检验设定的日期是否在当前日期之后
                    QDate time;
                    time.setDate(iEndYear,iEndMonth,iEndDay);
                    if(time.isValid()){
                        QDate currentTime=QDate::currentDate();
                        if(time>=currentTime){
                            iFlag=1;
                        }
                        else{
                            SetWarningBox("输入日期不正确，请重新输入！");
                            m_table[i]->item(j,4)->setText("");
                            break;
                        }
                    }
                    else{
                        SetWarningBox("输入日期不正确，请重新输入！");
                        m_table[i]->item(j,4)->setText("");
                        close();
                        break;
                    }
                }
                else{
                    SetWarningBox("输入日期格式不正确，请重新输入！");
                    m_table[i]->item(j,4)->setText("");
                    leaderTask r;
                    r.ShowValue();
                    r.exec();
                    break;
                }
            }
            else{
                SetWarningBox("输入日期不完整！");
                break;
            }
        }
        if(iFlag==1){
            //从表格中用户填写的截至日期当中提取截至的年月日
            QString newTask=m_table[i]->item(j,3)->text();

            g_backUp.SelectTranslaterDone_Translater(m_taskList[i],m_translaterList[i][j],iEndYear,
                                                     iEndMonth,iEndDay,newTask);
        }
    }
    //如果以上检测全都通过
    if(iFlag==1){
        SetInformBox("分配任务成功！");

        g_backUp.SelectTranslaterDone_Leader(m_taskList[i]);

        //刷新页面
        close();
        leaderTask r;
        r.ShowValue();
        r.exec();
    }
    else if(iFlag==0){
        SetWarningBox("并未分配任务！");
    }
}

/*************************************************************************
【函数名称】OnClicked_203prolong
【函数功能】在Show203中点击延时按钮之后并获得m_iPage的槽函数，提示用户输入延期天数，并
判断输入是否合法，若合法，存储延期天数
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.28
【更改记录】
*************************************************************************/
void leaderTask::OnClicked_203prolong(int i){
    int iAdd= QInputDialog::getInt(this, "延期","请输入延期天数");
    if(iAdd>=0){
        SetInformBox("延期成功！");
        g_backUp.Prolong_203(iAdd,m_taskList[i]);
    }
    else{
        SetWarningBox("延期天数不能为负！");
    }
}

/*************************************************************************
【函数名称】Show301
【函数功能】如果flag是301，显示界面
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::Show301(int i){
    m_iPage=i;
    //筛选已经提交的文章或已经修改并且提交的文章
    for(int j=0;j<g_backUp.m_listTaskTranslater.m_List.size();j++){
        if(g_backUp.m_listTaskTranslater.m_List[j].GetIDTask()==m_taskList[i].GetID()
                &&(g_backUp.m_listTaskTranslater.m_List[j].GetFlagToLeader()==1||
                   g_backUp.m_listTaskTranslater.m_List[j].GetFlagToLeader()==3)){
            m_translaterTaskList[i].append(g_backUp.m_listTaskTranslater.m_List[j]);
        }
    }
    if(!m_translaterTaskList[i].isEmpty()){
        QListWidgetItem* item=new QListWidgetItem(QIcon(":/images/comment.svg"),
                                                  tr("<译者的翻译出炉！请点评！>%1")
                                                  .arg(m_taskList[i].GetTitle()));
        ui->listWidget->insertItem(i,item);
    }
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
            (m_NewComment[i]+j)->setText(m_translaterTaskList[i][j]
                                         .GetCommentEditting());
            (m_NewComment[i]+j)->setStyleSheet(m_TextEditStyle);
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
            //如果点击提交，改变flag使得译者可见，负责人页面不必显示
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

/*************************************************************************
【函数名称】GetPage301save
【函数功能】301，saveBtn被点击之后，从leaderTask类中获得stackedwidget的i参数和TabWidget的
j参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::GetPage301save(){
    for(int i=0;i<m_taskList.size();i++){
        //筛选为301状态
        if(m_taskList[i].GetFlag()==301){
            //得到i任务译者人数并筛选是哪个button正在被按下
            for(int j=0;j<g_backUp.m_listTaskTranslater.GetSize_301(m_taskList[i].GetID());j++){
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
void leaderTask::GetPage301confrm(){
    for(int i=0;i<m_taskList.size();i++){
        //筛选为301状态
        if(m_taskList[i].GetFlag()==301){
            //得到i任务译者人数并筛选是哪个button正在被按下
            for(int j=0;j<g_backUp.m_listTaskTranslater.GetSize_301(m_taskList[i].GetID());j++){
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
void leaderTask::GetPage301end(){
    for(int i=0;i<m_taskList.size();i++){
        //筛选为301状态
        if(m_taskList[i].GetFlag()==301){
            //得到i任务译者人数并筛选是哪个button正在被按下
            for(int j=0;j<g_backUp.m_listTaskTranslater.GetSize_301(m_taskList[i].GetID());j++){
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
void leaderTask::OnClicked_301save(int i,int j){
    SetInformBox("评价暂存成功！");
    //存储译者暂存的评价
    m_translaterTaskList[i][j].EditCommentEditting((m_NewComment[i]+j)->toPlainText());
    //将新保存的信息存入内存
    g_backUp.m_listTaskTranslater.Update(m_translaterTaskList[i][j]);
    close();
    leaderTask r;
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
【更改记录】2019.7.27 增加容错功能
*************************************************************************/
void leaderTask::OnClicked_301confrm(int i,int j){
    if(!(m_NewComment[i]+j)->toPlainText().isEmpty()){
        SetInformBox("评价成功！");
        QString newComment=(m_NewComment[i]+j)->toPlainText();

        //向译者和负责人发送信息提醒
        g_backUp.SubmitCommentDone(m_translaterTaskList[i][j],newComment);
        //切换页面
        close();
        leaderTask r;
        r.ShowValue();
        r.exec();
    }
    else{
        SetWarningBox("评价不能为空！");
    }
}

/*************************************************************************
【函数名称】OnClicked_301end
【函数功能】301，endBtn被点击之后，从leaderTask类中获得stackedwidget的i参数和TabWidget的
j参数
【参数】int i,int j
【返回值】 无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void leaderTask::OnClicked_301end(int i,int j){
    SetInformBox("收稿成功！");
    //更改任务状态

    g_backUp.EndTranslateDone_Translater(m_taskList[i],m_translaterTaskList[i][j]);
    //切换页面
    close();
    leaderTask r;
    r.ShowValue();
    r.exec();

}

/*************************************************************************
【函数名称】Show302
【函数功能】如果flag是302，显示界面
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::Show302(int i){
    //向listWidget中添加新的item
    QListWidgetItem* item=new QListWidgetItem(QIcon(":/images/iconsz1.svg"),
                                              tr("<所有译者的翻译均已通过，请整合译文！>%1")
                                              .arg(m_taskList[i].GetTitle()));
    ui->listWidget->insertItem(i,item);
    //寻找所有i任务的子任务
    m_translaterTaskList[i]=g_backUp.m_listTaskTranslater.SearchTaskForTranslater(m_taskList[i].GetID());
    //定义页面所需的控件
    QLabel *inform1=new QLabel(tr("所有译者的翻译均已通过，请整合译文！"));
    inform1->setStyleSheet(m_LabelStyle);
    QLabel *inform2=new QLabel(tr("译文："));
    inform2->setStyleSheet(m_LabelStyle);
    QLabel *inform3=new QLabel(tr("所有译文："));
    inform3->setStyleSheet(m_LabelStyle);
    QHBoxLayout* Btn=new QHBoxLayout;
    m_confrmBtn[i]=new QPushButton(tr("确定"));
    m_confrmBtn[i]->setStyleSheet(m_BtnStyle1);
    m_confrmBtn[i]->setFixedSize(171,51);
    m_saveBtn[i]=new QPushButton(tr("暂存"));
    m_saveBtn[i]->setStyleSheet(m_BtnStyle1);
    m_saveBtn[i]->setFixedSize(171,51);
    (m_myResult+i)->setText(m_taskList[i].GetResultEditting());
    (m_myResult+i)->setStyleSheet(m_TextEditStyle);
    Btn->addSpacing(300);
    Btn->addWidget(m_saveBtn[i]);
    Btn->addWidget(m_confrmBtn[i]);
    Btn->addSpacing(300);
    QWidget *window=new QWidget;
    QVBoxLayout *layout=new QVBoxLayout();
    m_table[i]=new QTableWidget(m_translaterTaskList[i].size(),3);
    SetTableStyle(m_table[i]);
    m_table[i]->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table[i]->setWindowTitle("翻译原文及译文");
    //设定表格文件头
    QStringList header;
    header<<"用户名"<<"原文"<<"译文";
    //设定水平排布表格头
    m_table[i]->setHorizontalHeaderLabels(header);
    //设定表格内容
    for(int j=0;j<m_translaterTaskList[i].size();j++){
        m_table[i]->setItem(j,0,new QTableWidgetItem(m_translaterTaskList[i][j].GetTranslater()));
        m_table[i]->setItem(j,1,new QTableWidgetItem(m_translaterTaskList[i][j].GetTask()));
        m_table[i]->setItem(j,2,new QTableWidgetItem(m_translaterTaskList[i][j].GetResult()));
    }
    //向布局中添加控件
    layout->addWidget(inform1);
    layout->addWidget(inform2);
    layout->addWidget(m_table[i]);
    layout->addWidget(inform3);
    layout->addWidget(m_myResult+i);
    layout->addLayout(Btn);
    window->setLayout(layout);
    window->setStyleSheet("background-color:white;");
    ui->stackedWidget->addWidget(window);
    //如果负责人点击暂存，暂存负责人整合的任务
    connect(m_saveBtn[i],SIGNAL(pressed()),this,SLOT(GetPage302save()));
    //如果负责人点击提交，将完成的任务交给负责人，并编辑任务状态为401
    connect(m_confrmBtn[i],SIGNAL(pressed()),this,SLOT(GetPage302confrm()));
    ui->stackedWidget->addWidget(window);
}

/*************************************************************************
【函数名称】GetPage302save
【函数功能】在状态302下用户点击暂存按钮寻找用户正在按下的按钮
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.24
【更改记录】
*************************************************************************/
void leaderTask::GetPage302save(){
    for(int i=0;i<m_taskList.size();i++){
        if(m_taskList[i].GetFlag()==302){
            if(m_saveBtn[i]->isDown()){
                OnClicked_302save(i);
            }
        }
    }
}

/*************************************************************************
【函数名称】OnClicked_302save
【函数功能】用户按下i层的暂存按钮，进行数据存储等工作，并发消息
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.24
【更改记录】
*************************************************************************/
void leaderTask::OnClicked_302save(int i){
    SetInformBox("译文整合暂存成功！");
    m_taskList[i].EditResultEditting((m_myResult+i)->toPlainText());
    g_backUp.m_listTaskLeader.Update(m_taskList[i]);
    close();
    leaderTask r;
    r.ShowValue();
    r.exec();
}

/*************************************************************************
【函数名称】GetPage302confrm
【函数功能】如果用户在302状态按下确定按钮，寻找按下的按钮的所在层数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.24
【更改记录】
*************************************************************************/
void leaderTask::GetPage302confrm(){
    for(int i=0;i<m_taskList.size();i++){
        if(m_taskList[i].GetFlag()==302){
            if(m_confrmBtn[i]->isDown()){
                OnClicked_302confrm(i);
            }
        }
    }
}

/*************************************************************************
【函数名称】OnClicked_302confrm
【函数功能】用户按下i层的确定按钮，进行数据存储等工作，并发消息
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.24
【更改记录】2019.7.28 增加容错功能
*************************************************************************/
void leaderTask::OnClicked_302confrm(int i){
    if(!(m_myResult+i)->toPlainText().isEmpty()){
        SetInformBox("译文提交成功！");
        QString newResult=(m_myResult+i)->toPlainText();

        //向负责人和发布者发送消息
        g_backUp.IntegratingDone(m_taskList[i],newResult);
        close();
        leaderTask r;
        r.ShowValue();
        r.exec();
    }
    else{
        SetWarningBox("整合译文不能为空！");

    }
}

/*************************************************************************
【函数名称】on_Main_clicked
【函数功能】如果main按钮被按下，显示mainwindow
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::on_Main_clicked()
{
    close();
    MainWindow r;
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
void leaderTask::SetStyle(){
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

/*************************************************************************
【函数名称】SetTableStyle
【函数功能】设置表格的样式表
【参数】QTableWidget *table
【返回值】 无
【开发者及日期】李佳芸 2019.7.29
【更改记录】
*************************************************************************/
void leaderTask::SetTableStyle(QTableWidget *table){
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setDefaultSectionSize(200); //设置行高
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
    ui->exitBtn->setStyleSheet(BtnStyle2);
}

/*************************************************************************
【函数名称】SetListStyle
【函数功能】设置listwidget的样式
【参数】QListWidget* list
【返回值】 无
【开发者及日期】李佳芸 2019.7.29
【更改记录】
*************************************************************************/
void leaderTask::SetListStyle(QListWidget* list){
    list->setIconSize(QSize(50,30));
    list->setStyleSheet("QListWidget{color:black; }"
                        "QListWidget::Item{padding-top:4px; padding-bottom:4px; font:12pt,\"等线\";}"
                        "QListWidget::Item:hover{background:#B2EBF2; }"
                        "QListWidget::item:selected{background:#03A9F4; color:white; }");
}

/*************************************************************************
【函数名称】SetTabStyle
【函数功能】设置tabwidget的样式
【参数】QTabWidget* tab
【返回值】 无
【开发者及日期】李佳芸 2019.7.29
【更改记录】
*************************************************************************/
void leaderTask::SetTabStyle(QTabWidget* tab){
    tab->setIconSize(QSize(50,30));
    tab->setStyleSheet("QTabWidget::pane{top:60px;border:none;}"
                       "QTabWidget::tab-bar{alignment:left;top:10px;left:30px;}");
    tab->tabBar()->setStyleSheet("QTabBar::tab{color:black;background:transparent;font:12pt,\"等线\";"
                                 "padding-right:30px;padding-left:30px;"
                                 "margin-right:0px;margin-left:0px;min-width:75px;min-height:30px;"
                                 "max-width:75px;max-height:30px;}"
                                 "QTabBar::tab:selected{color:#00BCD4;background:transparent;"
                                 "font:12pt,\"等线\";border-bottom:2px solid rgb(0, 188, 212);}"
                                 "QTabBar::hover:{color:rgb(0, 188, 212);background:transparent;"
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
void leaderTask::SetWarningBox(QString Text){
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
void leaderTask::SetInformBox(QString Text){
    QMessageBox message(this);
    message.setIconPixmap(QPixmap(":/images/information.svg"));
    message.setStyleSheet("font:12pt,\"等线\";background:white;");
    message.setText(Text);
    message.setWindowTitle("提示");
    QPushButton* ysBtn=new QPushButton("确定");
    ysBtn->setStyleSheet(m_BtnStyle1);
    ysBtn->setFixedSize(171,51);
    message.addButton(ysBtn,QMessageBox::AcceptRole);
    message.exec();
}

/*************************************************************************
【函数名称】on_exitBtn_clicked
【函数功能】用户按下退出键后保存进度退出
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.30
【更改记录】
*************************************************************************/
void leaderTask::on_exitBtn_clicked()
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
