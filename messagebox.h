#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QDialog>
#include "backup.h"

namespace Ui {
class MessageBox;
}

class MessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit MessageBox(QWidget *parent = 0);
    ~MessageBox();
    void ShowMessage();
    void EditBackUp(BackUp myBackUp);

private slots:
    void on_main_clicked();

private:
    Ui::MessageBox *ui;
    BackUp m_BackUp;
    QList<Message> m_messageList;
};

#endif // MESSAGEBOX_H
