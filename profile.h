#ifndef PROFILE_H
#define PROFILE_H

#include <QDialog>

namespace Ui {
class Profile;
}

class Profile : public QDialog
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);
    ~Profile();

private slots:
    void on_m_linedit_editname_editingFinished();

private:
    Ui::Profile *ui;

public:
    QString m_username;

};

#endif // PROFILE_H
