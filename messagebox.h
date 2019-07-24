#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QDialog>
#include "user.h"
#include "list.h"

namespace Ui {
class MessageBox;
}

class MessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit MessageBox(QWidget *parent = 0);
    ~MessageBox();
    void ShowValue();
    void EditUser(user NewUser);
    void EditList(list NewList);

private:
    Ui::MessageBox *ui;
    user m_User;
    list m_List;
    QList<Message> m_messageList;
};

#endif // MESSAGEBOX_H
