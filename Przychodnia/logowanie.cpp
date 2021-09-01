#include "logowanie.h"
#include "ui_logowanie.h"

Logowanie::Logowanie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Logowanie) {
    ui->setupUi(this);
    ui->wrongLoginDataLabel->setVisible(false);
    przychodnia = Przychodnia::getInstancja();
}

Logowanie::~Logowanie()
{
    delete ui;
}

void Logowanie::on_zalogujBtn_clicked() {
    QString podanyKodLogowania = ui->kodLogowaniaLineEdit->text();
    QString podaneHaslo = ui->hasloLineEdit->text();

    QList<Pracownik*> pracownicy = przychodnia->zwrocPracownikow();

    foreach(Pracownik *pracownik, pracownicy){
        if(pracownik->getKodLogowania() == podanyKodLogowania &&
           pracownik->getHaslo() == QCryptographicHash::hash(podaneHaslo.toUtf8(), QCryptographicHash::Sha1)){
            window = new MainWindow(nullptr, false, pracownik);
            window->show();
            this->hide();
        }
    }

    if(przychodnia->zwrocManagera()->getKodLogowania() == podanyKodLogowania &&
       przychodnia->zwrocManagera()->getHaslo() == QCryptographicHash::hash(podaneHaslo.toUtf8(), QCryptographicHash::Sha1)){
        window = new MainWindow(nullptr, true, przychodnia->zwrocManagera());
        window->show();
        this->hide();
    }

    ui->wrongLoginDataLabel->setVisible(true);
}

void Logowanie::on_zamknijBtn_clicked()
{
    QCoreApplication::quit();
}
