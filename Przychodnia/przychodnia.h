#ifndef PRZYCHODNIA_H
#define PRZYCHODNIA_H

#include <QObject>
#include <QList>
#include <QString>
#include <QCryptographicHash>
#include <QStandardItemModel>

#include "pracownik.h"
#include "przedsiebiorstwo.h"
#include "manager.h"
#include "pacjent.h"
#include "wizyta.h"
#include "zabieg.h"
#include "termin.h"

class Przychodnia
{
private:
    static Przychodnia *instancja;
    Manager *manager;
    QList<Pracownik*> pracownicy;
    QList<Pacjent*> pacjenci;
    QList<Zabieg*> zabiegi;
    QList<Wizyta*> wizyty;
    Przedsiebiorstwo *danePrzedsiebiorstwa;

    Przychodnia();
    ~Przychodnia();
public:
    QList<Pacjent*> zwrocPacjentow();
    QList<Pracownik*> zwrocPracownikow();
    QList<Wizyta*> zwrocWizyty();
    QList<Zabieg*> zwrocZabiegi();

    QList<Pacjent*> zwrocPacjentow(QString kryterium);
    QList<Pracownik*> zwrocPracownikow(QString kryterium);
    QList<Wizyta*> zwrocWizyty(QString kryterium);
    QList<Zabieg*> zwrocZabiegi(QString kryterium);
    QList<Zabieg *> zwrocZabiegiNiedozwoloneDla(Pracownik *pracownik);

    Przedsiebiorstwo* zwrocDanePrzedsiebiorstwa();
    Manager* zwrocManagera();

    Pracownik* szukajPracownika(QString imie, QString nazwisko, QString kodLogowania);
    Pacjent* szukajPacjenta(QString imie, QString nazwisko, QString email, QString telefon, QString ulica, int numer, int kod, QString miejscowosc);
    Wizyta* szukajWizyty(Pacjent pacjent, Zabieg zabieg, Pracownik pracownik, Termin termin, QString status);
    Zabieg* szukajZabiegu(QString nazwa, double cena, double czasTrwania, QString opis);

    void dodajPracownika(QString imie, QString nazwisko, QString kodLogowania);
    void modyfikujPracownika(Pracownik *pracownik, QString imie, QString nazwisko, QString kodLogowania);
    void usunPracownika(Pracownik *pracownik);
    void rozszerzKompetencjePracownika(Pracownik *pracownik, Zabieg *kompetencja);
    void redukujKompetencjePracownika(Pracownik *pracownik, Zabieg *kompetencja);
    void zmienGodzinyPracyPracownika(Pracownik *pracownik, GodzinyPracy *godzinyPracy);
    void zmienGodzinyPracyPracownika(Pracownik *pracownik, QList<GodzinyPracy*> godzinyPracy);
    void zmienGodzinyPracyPracownika(Pracownik *pracownik, QString dzienTygodnia, QString godzinaOd, QString godzinaDo);
    bool czyPracownikWykonujeWizyte(Termin *termin, Pracownik *pracownik, double czasTrwaniaWizyty);
    bool unikalnyKodLogowania(Pracownik *pracownik, QString kodLogowania);

    void dodajPacjenta(QString imie, QString nazwisko, QString email, QString telefon, QString ulica, int numer, int kod, QString miejscowosc);
    void modyfikujPacjenta(Pacjent *pacjent, QString imie, QString nazwisko, QString email, QString telefon, QString ulica, int numer, int kod, QString miejscowosc);
    void usunPacjenta(Pacjent *pacjent);

    void umowWizyte(Pacjent pacjent, Zabieg zabieg, Pracownik pracownik, Termin termin);
    bool umowWizyte(QList<QString> danePacjenta, QList<QString> daneZabiegu, QList<QString> danePracownika, QList<int> daneTerminu);
    void usunWizyte(Wizyta wizyta);
    Wizyta zwrocWizyteWDanymTerminie(Termin termin);
    QList<Wizyta*> zwrocWizyty(Pracownik pracownik, Termin termin);

    void ustawManagera(QString imie, QString nazwisko, QString kodLogowania);
    bool czyOsobaJestManagerem(Osoba& osoba);

    void dodajZabieg(QString nazwa, double cena, double czasTrwania, QString opis);
    void modyfikujZabieg(Zabieg *zabieg, QString nazwa, double cena, double czasTrwania, QString opis);
    void usunZabieg(Zabieg *zabieg);

    void modyfikujDanePrzedsiebiorstwa(QString nazwa, QString branza, QString email, QString adres, int kod, QString miejscowosc, QString wojewodztwo, QString kraj, QString nip);

    void wypelnijModelPacjentow(QList<Pacjent*> listaPacjentow, QStandardItemModel *model);
    void wypelnijModelPracownikow(QList<Pracownik*> listaPracownikow, QStandardItemModel *model);
    void wypelnijModelWizyt(QList<Wizyta*> wizyty, QStandardItemModel *model);
    void wypelnijModelZabiegow(QList<Zabieg*> zabiegi, QStandardItemModel *model);

    Termin* utworzTermin(int dzien, int miesiac, int rok, Czas* czas);
    Czas* utworzCzas(int godzina, int minuta, int sekunda);
    Wizyta* utworzWizyte(Pracownik *pracownik, Pacjent *pacjent, Zabieg *zabieg, Termin *termin);

    static Przychodnia *getInstancja();

    bool czyPoprawnyEmail(QString email);
};

#endif // PRZYCHODNIA_H
