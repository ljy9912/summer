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

private slots:
    void on_main_clicked();
    void OnClicked(int i);

private:
    Ui::MessageBox *ui;

    QList<Message> m_messageList;
};

#endif // MESSAGEBOX_H
