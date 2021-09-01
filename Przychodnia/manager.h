#ifndef MANAGER_H
#define MANAGER_H

#include "osoba.h"
#include "godzinypracy.h"
#include <QString>
#include <QList>
#include <QDebug>

class Manager : public Osoba {
private:
    QList<GodzinyPracy> godzinyPracy;
    QString kodLogowania;
    QByteArray haslo;
public:
    Manager(QString imie, QString nazwisko, QString kodLogowania);
    void modyfikuj(QString imie, QString nazwisko, QList<GodzinyPracy> godzinyPracy, QString kodLogowania, QByteArray haslo);
    void wyswietlDane() override;
    QList<GodzinyPracy> getGodzinyPracy() const;
    void setGodzinyPracy(const QList<GodzinyPracy> &value);
    QString getKodLogowania() const;
    void setKodLogowania(const QString &value);
    QByteArray getHaslo() const;
    void setHaslo(const QByteArray &value);
};

#endif // MANAGER_H
