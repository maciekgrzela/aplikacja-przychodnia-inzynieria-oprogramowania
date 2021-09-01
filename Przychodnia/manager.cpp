#include "manager.h"

Manager::Manager(QString imie, QString nazwisko, QString kodLogowania)
{
    this->imie = imie;
    this->nazwisko = nazwisko;
    this->kodLogowania = kodLogowania;
}

void Manager::wyswietlDane()
{
    qDebug() << this->getImie() << this->getNazwisko() << this->getKodLogowania();
}

QList<GodzinyPracy> Manager::getGodzinyPracy() const
{
    return godzinyPracy;
}

void Manager::setGodzinyPracy(const QList<GodzinyPracy> &value)
{
    godzinyPracy = value;
}

QString Manager::getKodLogowania() const
{
    return kodLogowania;
}

void Manager::setKodLogowania(const QString &value)
{
    kodLogowania = value;
}

QByteArray Manager::getHaslo() const
{
    return haslo;
}

void Manager::setHaslo(const QByteArray &value)
{
    haslo = value;
}

