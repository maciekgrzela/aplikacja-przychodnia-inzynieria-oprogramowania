#ifndef OSOBA_H
#define OSOBA_H

#include <QString>

class Osoba
{
public:
    virtual ~Osoba(){}
    virtual void wyswietlDane() = 0;
    virtual QString getImie();
    virtual QString getNazwisko();
    virtual void setImie(QString imie);
    virtual void setNazwisko(QString nazwisko);
protected:
    QString imie;
    QString nazwisko;
};

#endif // OSOBA_H
