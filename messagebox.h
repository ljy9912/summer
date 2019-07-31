#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QDialog>
#include "backup.h"
#include <QToolBox>

namespace Ui {
class MessageBox;
}

class MessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit MessageBox(QWidget *parent = nullptr);
    ~MessageBox();
    void ShowMessage();

private slots:
    void OnClicked(int i);

    void on_Main_clicked();

private:
    Ui::MessageBox *ui;
    void SetStyle();
    void SetBoxStyle(QToolBox* box);
    QList<Message> m_messageList;
};

#endif // MESSAGEBOX_H
