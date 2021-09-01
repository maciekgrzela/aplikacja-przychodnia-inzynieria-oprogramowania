#ifndef GODZINYPRACY_H
#define GODZINYPRACY_H

#include <QString>
#include "czas.h"

class GodzinyPracy
{
private:
    QString dzienTygodnia;
    Czas *godzinaOd;
    Czas *godzinaDo;
public:
    GodzinyPracy(QString dzienTygodnia, Czas *godzinaOd, Czas *godzinaDo);
    void modyfikuj(QString dzienTygodnia, Czas godzinaOd, Czas godzinaDo);
    bool czyDzienPracowniczy();


    Czas *getGodzinaOd() const;
    void setGodzinaOd(Czas *value);
    Czas *getGodzinaDo() const;
    void setGodzinaDo(Czas *value);
    QString getDzienTygodnia() const;
    void setDzienTygodnia(const QString &value);
};

#endif // GODZINYPRACY_H
