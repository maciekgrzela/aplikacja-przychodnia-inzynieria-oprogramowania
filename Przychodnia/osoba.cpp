#include "osoba.h"

QString Osoba::getImie()
{
    return imie;
}

QString Osoba::getNazwisko()
{
    return nazwisko;
}

void Osoba::setImie(QString imie)
{
    this->imie = imie;
}

void Osoba::setNazwisko(QString nazwisko)
{
    this->nazwisko = nazwisko;
}
