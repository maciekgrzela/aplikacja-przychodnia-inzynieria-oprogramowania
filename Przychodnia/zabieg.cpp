#include "zabieg.h"

Zabieg::Zabieg(QString nazwa, double cena, double czasTrwania, QString opis) {
    this->modyfikuj(nazwa, cena, czasTrwania, opis);
}

void Zabieg::modyfikuj(QString nazwa, double cena, double czasTrwania, QString opis) {
    this->setNazwa(nazwa);
    this->setCena(cena);
    this->setCzasTrwania(czasTrwania);
    this->setOpis(opis);
}

double Zabieg::getCena() const
{
    return cena;
}

void Zabieg::setCena(double value)
{
    cena = value;
}

double Zabieg::getCzasTrwania() const
{
    return czasTrwania;
}

void Zabieg::setCzasTrwania(double value)
{
    czasTrwania = value;
}

QString Zabieg::getOpis() const
{
    return opis;
}

void Zabieg::setOpis(const QString &value)
{
    opis = value;
}

bool Zabieg::operator ==(Zabieg &inny) {
    if(this->getNazwa() == inny.getNazwa() &&
       this->getOpis() == inny.getOpis() &&
       this->getCena() == inny.getCena() &&
       this->getCzasTrwania() == inny.getCzasTrwania()){
        return true;
    }
    return false;
}

void Zabieg::wypelnijModel(QStandardItemModel *model, int index) {
    QStandardItem *itemNazwa = new QStandardItem(this->getNazwa());
    QStandardItem *itemCena = new QStandardItem(QVariant(this->getCena()).toString()+" PLN");
    QStandardItem *itemCzasTrwania = new QStandardItem(QVariant(this->getCzasTrwania()).toString()+"h");
    QStandardItem *itemOpis = new QStandardItem(this->getOpis());

    model->setItem(index, 0, itemNazwa);
    model->setItem(index, 1, itemCena);
    model->setItem(index, 2, itemCzasTrwania);
    model->setItem(index, 3, itemOpis);
}

bool Zabieg::czySpelniaKryteria(QString kryterium) {
    if(kryterium.length() > 0){
        if(this->getNazwa().contains(kryterium) || this->getNazwa().contains(kryterium) ||
           this->getOpis().contains(kryterium) || this->getOpis().contains(kryterium) ||
           QVariant(this->getCena()).toString().contains(kryterium) || QVariant(this->getCena()).toString().contains(kryterium) ||
           QVariant(this->getCzasTrwania()).toString().contains(kryterium) || QVariant(this->getCzasTrwania()).toString().contains(kryterium)){
            return true;
        }
    }
    return false;
}

QString Zabieg::getNazwa() const
{
    return nazwa;
}

void Zabieg::setNazwa(const QString &value)
{
    nazwa = value;
}
