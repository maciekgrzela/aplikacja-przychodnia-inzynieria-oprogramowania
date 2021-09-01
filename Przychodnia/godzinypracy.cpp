#include "godzinypracy.h"

GodzinyPracy::GodzinyPracy(QString dzienTygodnia, Czas *godzinaOd, Czas *godzinaDo) {
    this->dzienTygodnia = dzienTygodnia;
    this->godzinaOd = godzinaOd;
    this->godzinaDo = godzinaDo;
}

Czas *GodzinyPracy::getGodzinaOd() const
{
    return godzinaOd;
}

void GodzinyPracy::setGodzinaOd(Czas *value)
{
    godzinaOd = value;
}

Czas *GodzinyPracy::getGodzinaDo() const
{
    return godzinaDo;
}

void GodzinyPracy::setGodzinaDo(Czas *value)
{
    godzinaDo = value;
}

QString GodzinyPracy::getDzienTygodnia() const
{
    return dzienTygodnia;
}

void GodzinyPracy::setDzienTygodnia(const QString &value)
{
    dzienTygodnia = value;
}
