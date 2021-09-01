#ifndef PRACOWNIK_H
#define PRACOWNIK_H

#include <QObject>
#include <QString>
#include <QList>
#include <QDebug>
#include <QStandardItemModel>
#include "osoba.h"
#include "godzinypracy.h"
#include "zabieg.h"
#include "porownywalny.h"
#include "termin.h"
#include "wizyta.h"


class Pracownik : public Osoba, public Porownywalny<Pracownik>
{
private:
    QList<GodzinyPracy*> godzinyPracy;
    QString kodLogowania;
    QByteArray haslo;
    QList<Zabieg*> kompetencje;
public:
    void wyswietlDane() override;

    Pracownik(QString imie, QString nazwisko, QString kodLogowania);
    void modyfikuj(QString imie, QString nazwisko, QString kodLogowania, QByteArray haslo);

    QString getKodLogowania() const;
    void setKodLogowania(const QString &value);

    QByteArray getHaslo() const;
    void setHaslo(const QByteArray &value);

    QList<GodzinyPracy*> getGodzinyPracy() const;
    void setGodzinyPracy(const QList<GodzinyPracy*> &value);
    GodzinyPracy* godzinyPracyWDniuTygodnia(QString dzienTygodnia);

    void setGodzinyPracyWDniuTygodnia(QString dzienTygodnia, Czas *godzinaOd, Czas *godzinaDo);

    QList<Zabieg*> kompetencjePracownika();
    bool czyPosiadaKompetencje(Zabieg *zabieg);
    void dodajKompetencje(Zabieg *zabieg);
    void usunKompetencje(Zabieg *zabieg);

    bool operator== (Pracownik &inny) override;

    void wypelnijModel(QStandardItemModel *model, int index);

    void ustawGodzinyPracyWDniu(GodzinyPracy *godzinyPracy);

    bool czyWykonujeWizyteWDanymTerminie(Termin termin, QList<Wizyta*> wizyty, double czasTrwaniaWizyty);

    bool czySpelniaKryteria(QString kryterium);
};

#endif // PRACOWNIK_H
