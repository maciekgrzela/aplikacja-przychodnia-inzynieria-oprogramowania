#ifndef PACJENT_H
#define PACJENT_H

#include "osoba.h"
#include "porownywalny.h"
#include <QDebug>
#include <QString>
#include <QStandardItemModel>

class Pacjent : public Osoba, public Porownywalny<Pacjent> {
private:
    QString email;
    QString telefon;
    QString ulica;
    int numer;
    int kod;
    QString miejscowosc;
public:
    Pacjent(QString imie, QString nazwisko, QString email, QString telefon, QString ulica, int numer, int kod, QString miejscowosc);
    void modyfikuj(QString imie, QString nazwisko, QString email, QString telefon, QString ulica, int numer, int kod, QString miejscowosc);
    void wyswietlDane() override;
    bool operator ==(Pacjent &inny) override;

    bool czySpelniaKryteria(QString kryteria);
    void wypelnijModel(QStandardItemModel *model, int index);

    QString getEmail() const;
    void setEmail(const QString &value);
    QString getTelefon() const;
    void setTelefon(const QString &value);
    QString getUlica() const;
    void setUlica(const QString &value);
    int getNumer() const;
    void setNumer(int value);
    int getKod() const;
    void setKod(int value);
    QString getMiejscowosc() const;
    void setMiejscowosc(const QString &value);
};

#endif // PACJENT_H
