#include "pacjent.h"

Pacjent::Pacjent(QString imie, QString nazwisko, QString email, QString telefon, QString ulica, int numer, int kod, QString miejscowosc) {
    this->modyfikuj(imie, nazwisko, email, telefon, ulica, numer, kod, miejscowosc);
}

void Pacjent::modyfikuj(QString imie, QString nazwisko, QString email, QString telefon, QString ulica, int numer, int kod, QString miejscowosc) {
    this->setImie(imie);
    this->setNazwisko(nazwisko);
    this->setEmail(email);
    this->setTelefon(telefon);
    this->setUlica(ulica);
    this->setNumer(numer);
    this->setKod(kod);
    this->setMiejscowosc(miejscowosc);
}

QString Pacjent::getEmail() const {
    return email;
}

void Pacjent::setEmail(const QString &value) {
    email = value;
}

QString Pacjent::getTelefon() const {
    return telefon;
}

void Pacjent::setTelefon(const QString &value) {
    telefon = value;
}

QString Pacjent::getUlica() const {
    return ulica;
}

void Pacjent::setUlica(const QString &value) {
    ulica = value;
}

int Pacjent::getNumer() const {
    return numer;
}

void Pacjent::setNumer(int value) {
    numer = value;
}

int Pacjent::getKod() const {
    return kod;
}

void Pacjent::setKod(int value) {
    kod = value;
}

QString Pacjent::getMiejscowosc() const {
    return miejscowosc;
}

void Pacjent::setMiejscowosc(const QString &value) {
    miejscowosc = value;
}

void Pacjent::wyswietlDane() {
    qDebug() << this->getImie() << this->getNazwisko() << this->getTelefon();
}

bool Pacjent::operator ==(Pacjent &inny) {
    if(this->getImie() == inny.getImie() &&
       this->getNazwisko() == inny.getNazwisko() &&
       this->getEmail() == inny.getEmail() &&
       this->getUlica() == inny.getUlica() &&
       this->getTelefon() == inny.getTelefon() &&
       this->getMiejscowosc() == inny.getMiejscowosc() &&
       this->getKod() == inny.getKod() &&
       this->getNumer() == inny.getNumer()){
        return true;
    }
    return false;
}

bool Pacjent::czySpelniaKryteria(QString kryteria) {
    if(kryteria.length() > 0){
        if(this->getImie().contains(kryteria) || this->getNazwisko().contains(kryteria) ||
           this->getEmail().contains(kryteria) || this->getUlica().contains(kryteria) ||
           this->getTelefon().contains(kryteria) || this->getMiejscowosc().contains(kryteria) ||
           QVariant(this->getKod()).toString().contains(kryteria) || QVariant(this->getNumer()).toString().contains(kryteria)){
            return true;
        }
    }
    return false;
}

void Pacjent::wypelnijModel(QStandardItemModel *model, int index) {
    QStandardItem *itemImie = new QStandardItem(this->getImie());
    QStandardItem *itemNazwisko = new QStandardItem(this->getNazwisko());
    QStandardItem *itemEmail = new QStandardItem(this->getEmail());
    QStandardItem *itemTelefon = new QStandardItem(this->getTelefon());
    QStandardItem *itemMiejscowosc = new QStandardItem(this->getMiejscowosc());
    QStandardItem *itemUlica = new QStandardItem(this->getUlica());
    QStandardItem *itemNumer = new QStandardItem(QVariant(this->getNumer()).toString());
    QStandardItem *itemKod = new QStandardItem(QVariant(this->getKod()).toString());

    model->setItem(index, 0, itemImie);
    model->setItem(index, 1, itemNazwisko);
    model->setItem(index, 2, itemEmail);
    model->setItem(index, 3, itemTelefon);
    model->setItem(index, 4, itemUlica);
    model->setItem(index, 5, itemNumer);
    model->setItem(index, 6, itemKod);
    model->setItem(index, 7, itemMiejscowosc);
}
