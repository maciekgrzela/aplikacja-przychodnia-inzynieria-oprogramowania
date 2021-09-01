#ifndef LOGOWANIE_H
#define LOGOWANIE_H

#include <QDialog>
#include "przychodnia.h"
#include "mainwindow.h"

namespace Ui {
class Logowanie;
}

class Logowanie : public QDialog
{
    Q_OBJECT

public:
    explicit Logowanie(QWidget *parent = nullptr);
    ~Logowanie();

private slots:
    void on_zalogujBtn_clicked();
    void on_zamknijBtn_clicked();

private:
    Ui::Logowanie *ui;
    Przychodnia *przychodnia;
    MainWindow *window;
};

#endif // LOGOWANIE_H
