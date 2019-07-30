#ifndef TRANSLATERTASK_H
#define TRANSLATERTASK_H

#include <QDialog>
#include "backup.h"
#include <QTextEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QListWidget>


namespace Ui {
class translaterTask;
}

class translaterTask : public QDialog
{
    Q_OBJECT

public:
    explicit translaterTask(QWidget *parent = 0);
    ~translaterTask();

    void ShowValue();

signals:
    void SendPage(int i);

private slots:
    void OnClicked_301save(int i);
    void OnClicked_301confrm(int i);
    void GetPage301save();
    void GetPage301confrm();

    void on_Main_clicked();

private:
    Ui::translaterTask *ui;

    QList<taskTranslater> m_taskList;
    int m_iPage;

    QTextEdit *m_result;
    QPushButton *m_saveBtn;
    QPushButton *m_confrmBtn;

    QString m_BtnStyle1;
    QString m_LabelStyle;
    QString m_LineEditStyle;
    QString m_TextEditStyle;
    QString m_TableWidgetStyle;
    QString m_BrowserStyle;

    void SetTableStyle(QTableWidget* table);
    void SetListStyle(QListWidget* list);

    void SetStyle();
};

#endif // TRANSLATERTASK_H
