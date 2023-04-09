#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QIntValidator>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MyMainWindow; }
QT_END_NAMESPACE

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();

private slots:

    void on_m_pb_newGame_clicked();

    void on_m_pb_records_clicked();

    void on_m_pb_check_clicked();

private:
    Ui::MyMainWindow *ui;
    QIntValidator m_intValidator;

    QString m_hidden_number;
    QString m_current_number;
    QString m_bulls_and_cows;
    QString m_username_main;

    int m_random_number = 0;
    int m_bulls = 0;
    int m_cows = 0;
    int m_count_of_try = 0;

private:
    bool IsDiffNumbersInNumber(QString number_);
    void GenerateHiddenNumber();
    void CheckNumber();
    void TableFill();
    void WriteIntoFileRecord();
    void ReadFromFileRecord();
};
#endif // MYMAINWINDOW_H
