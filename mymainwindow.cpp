#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include "profile.h"
#include "record.h"

MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
    , m_intValidator(1000, 9999, this)
{
    ui->setupUi(this);

    ui->m_lnedit_enterNum->setValidator(&m_intValidator);
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

bool MyMainWindow::IsDiffNumbersInNumber(QString number_)
{
    if (number_[0] != number_[1] &&  number_[0] != number_[2] && number_[0] != number_[3])
        if(number_[1] != number_[2] && number_[1] != number_[3] && number_[2] != number_[3])
            return true;

    return false;
}

void MyMainWindow::GenerateHiddenNumber()
{
    do
    {
        m_random_number = rand() % 9000 + 1000;
        m_hidden_number = QString::number(m_random_number);
    }
    while(!IsDiffNumbersInNumber(m_hidden_number));
}

void MyMainWindow::on_m_pb_newGame_clicked()
{
    while(m_count_of_try > 0) //перед началом игры очищаем таблицу результатов
    {
        m_count_of_try--;
        ui->m_tbl_gameRes->removeRow(m_count_of_try);
    }

    Profile* profile = new Profile(this);
    profile->exec();
    m_username_main = profile->m_username;
    //проверка на существующее имя из таблицы рекордов, выдаётся предупреждение, что рекорд перезапишется.

    GenerateHiddenNumber();
    qDebug() << m_hidden_number;

    ui->m_lbl_chatBar->setText("Идёт игра...");
}


void MyMainWindow::on_m_pb_records_clicked()
{
    Record* record = new Record(this);
    record->
    record->exec();
}

void MyMainWindow::CheckNumber()
{
    m_bulls = 0;
    m_cows = 0;
    for(int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if(m_current_number[i] == m_hidden_number[j])
            {
                if (i == j)
                    m_bulls++;
                else
                    m_cows++;
            }
        }
    }

    m_bulls_and_cows = "Быков: " + QString::number(m_bulls) + "; Коров: " + QString::number(m_cows);
}

void MyMainWindow::TableFill()
{
    QTableWidgetItem* item1 = new QTableWidgetItem(m_current_number);
    QTableWidgetItem* item2 = new QTableWidgetItem(m_bulls_and_cows);

    ui->m_tbl_gameRes->insertRow(m_count_of_try);
    ui->m_tbl_gameRes->setItem(m_count_of_try, 0, item1);
    ui->m_tbl_gameRes->setItem(m_count_of_try, 1, item2);

    m_count_of_try++;
}

void MyMainWindow::WriteIntoFileRecord()
{
    QFile file("record_list.txt");
    if(!file.exists())
    {
        qDebug() << "Файла не существует";
        return;
    }

    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream writeStream(&file);
        QString note = QString::number(m_count_of_try) + ' ' + m_username_main + ';';
        writeStream << note;
        file.close();
    }
}

void MyMainWindow::ReadFromFileRecord()
{
    QFile file("record_list.txt");
    if(!file.exists())
    {
        qDebug() << "Файла не существует";
        return;
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
            qDebug() << file.readLine();
        file.close();
    }
}

void MyMainWindow::on_m_pb_check_clicked()
{
    m_current_number = ui->m_lnedit_enterNum->text();
    if(m_current_number.size() != 4)
    {
        ui->m_lbl_chatBar->setText("Вы ввели некорректное число: длина меньше 4");
        return;
    }
    if (!IsDiffNumbersInNumber(m_current_number))
    {
        ui->m_lbl_chatBar->setText("Вы ввели некорректное число: в числе есть одинаковые цифры");
        return;
    }

    CheckNumber();
    TableFill();

    if (m_bulls != 4)
    {
        ui->m_lbl_chatBar->setText("Неправильно! Попробуй... ещё раз...");
    }
    else
    {
        QMessageBox* victory = new QMessageBox();
        QString message;
        message = "Правильно! Вы победили!!!\nЗагаданным числом было: " + m_hidden_number + "\n" +
                "Вы, " + m_username_main + ", угадали c " + QString::number(m_count_of_try) + " попытки!";
        victory->setText(message);
        victory->exec();

        WriteIntoFileRecord();
        ReadFromFileRecord();
    }
}

