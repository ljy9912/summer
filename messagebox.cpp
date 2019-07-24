#include "messagebox.h"
#include "ui_messagebox.h"
#include <QToolBox>

MessageBox::MessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageBox)
{
    ui->setupUi(this);
}

MessageBox::~MessageBox()
{
    delete ui;
}

void MessageBox::ShowMessage(QString title,QString content){
    QToolBox
}
