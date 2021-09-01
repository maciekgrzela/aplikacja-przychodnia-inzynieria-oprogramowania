#include <QtTest/QtTest>
#include "przychodnia.h"
#include "pracownik.h"
#include "termin.h"
#include "czas.h"


class TestMain : public QObject {
    Q_OBJECT
private slots:
    void posiadanieKompetencji();
    void godzinyPracyWDniuTygodnia();
    void wykonanieWizytyWTerminie();
    void zwrocenieDniaTygodnia();
    void szukaniePracownika();
    void dodanieCzasu();
};

void TestMain::posiadanieKompetencji() {
    Pracownik *pracownik = new Pracownik("Kasia", "Półtorak", "KP001");
    Zabieg *zabieg = new Zabieg("Szczepienie", 50.0, 0.25, "Szczepienie");
    Zabieg *zabieg2 = new Zabieg("Wizyta kontrolna", 100.0, 0.5, "Wizyta kontrolna - opis");
    Zabieg *zabieg3 = new Zabieg("Badanie krwi", 20.99, 0.2, "Pobranie krwi");

    QCOMPARE(pracownik->czyPosiadaKompetencje(zabieg), false);
    QCOMPARE(pracownik->czyPosiadaKompetencje(zabieg2), false);
    QCOMPARE(pracownik->czyPosiadaKompetencje(zabieg3), false);

    pracownik->dodajKompetencje(zabieg);
    pracownik->dodajKompetencje(zabieg2);
    pracownik->dodajKompetencje(zabieg3);

    QCOMPARE(pracownik->czyPosiadaKompetencje(zabieg), true);
    QCOMPARE(pracownik->czyPosiadaKompetencje(zabieg2), true);
    QCOMPARE(pracownik->czyPosiadaKompetencje(zabieg3), true);
}

void TestMain::godzinyPracyWDniuTygodnia() {
    Pracownik *pracownik = new Pracownik("Patrycja", "Cieśla", "PC001");
    Czas *czas = new Czas(7,0,0);
    Czas *czas2 = new Czas(15,0,0);
    pracownik->setGodzinyPracyWDniuTygodnia("Poniedziałek", czas, czas2);
    Czas *czas3 = new Czas(21,0,0);
    pracownik->setGodzinyPracyWDniuTygodnia("Wtorek", czas, czas3);


    QCOMPARE(pracownik->godzinyPracyWDniuTygodnia("Poniedziałek")->getDzienTygodnia(), QString("Poniedziałek"));
    QCOMPARE(pracownik->godzinyPracyWDniuTygodnia("Poniedziałek")->getGodzinaOd()->toString(), QString("7:0:0"));
    QCOMPARE(pracownik->godzinyPracyWDniuTygodnia("Poniedziałek")->getGodzinaDo()->toString(), QString("15:0:0"));

    QCOMPARE(pracownik->godzinyPracyWDniuTygodnia("Wtorek")->getDzienTygodnia(), QString("Wtorek"));
    QCOMPARE(pracownik->godzinyPracyWDniuTygodnia("Wtorek")->getGodzinaOd()->toString(), QString("7:0:0"));
    QCOMPARE(pracownik->godzinyPracyWDniuTygodnia("Wtorek")->getGodzinaDo()->toString(), QString("21:0:0"));
}

void TestMain::wykonanieWizytyWTerminie() {
    Czas czas(15,0,0);
    Termin *termin = new Termin(11,1,2020, czas);
    Termin *termin2 = new Termin(12,1,2020, czas);
    Pracownik *pracownik = new Pracownik("Kasia", "Półtorak", "KP001");
    Zabieg *zabieg = new Zabieg("Szczepienie", 50.0, 0.5, "Szczepienie");
    Pacjent *pacjent = new Pacjent("Anna", "Nowak", "anowak@mail.com", "609609609", "Nowa", 10, 23233, "Wrocław");
    Wizyta *wizyta = new Wizyta(pacjent, zabieg, pracownik, termin);
    QList<Wizyta*> wizyty;
    wizyty.append(wizyta);
    QCOMPARE(pracownik->czyWykonujeWizyteWDanymTerminie(*termin, wizyty, 0.5), true);
    QCOMPARE(pracownik->czyWykonujeWizyteWDanymTerminie(*termin2, wizyty, 0.5), false);
}

void TestMain::zwrocenieDniaTygodnia() {
    QCOMPARE(Termin::zwrocDzienTygodnia(11,1,2020), QString("Sobota"));
    QCOMPARE(Termin::zwrocDzienTygodnia(12,1,2020), QString("Niedziela"));
    QCOMPARE(Termin::zwrocDzienTygodnia(13,1,2020), QString("Poniedziałek"));
    QCOMPARE(Termin::zwrocDzienTygodnia(13,12,1927), QString("Wtorek"));
    QCOMPARE(Termin::zwrocDzienTygodnia(15,4,2087), QString("Wtorek"));
    QCOMPARE(Termin::zwrocDzienTygodnia(10,1,2020), QString("Piątek"));
}

void TestMain::szukaniePracownika() {
    Przychodnia *przychodnia = Przychodnia::getInstancja();

    QCOMPARE(przychodnia->szukajPracownika("Janusz", "Biernat", "JB001"), nullptr);
    QCOMPARE(przychodnia->szukajPracownika("Bronisław", "Bielak", "BB001")->getImie(), QString("Bronisław"));
    QCOMPARE(przychodnia->szukajPracownika("Bronisław", "Bielak", "BB001")->getNazwisko(), QString("Bielak"));
    QCOMPARE(przychodnia->szukajPracownika("Edward", "Gutkowski", "EG001")->getKodLogowania(), QString("EG001"));
}

void TestMain::dodanieCzasu() {
    Czas *czas = new Czas(14, 57, 22);
    Czas *czas2 = new Czas(12, 28,56);
    Czas *czas3 = new Czas(23, 52, 48);
    Czas *czas4 = new Czas(11, 17, 56);

    czas->dodajPolGodziny();
    czas2->dodajPolGodziny();
    czas3->dodajPolGodziny();
    czas4->dodajPolGodziny();

    QCOMPARE(czas->getGodzina(), 15);
    QCOMPARE(czas->getMinuta(), 27);
    QCOMPARE(czas->getSekunda(), 22);

    QCOMPARE(czas2->getGodzina(), 12);
    QCOMPARE(czas2->getMinuta(), 58);
    QCOMPARE(czas2->getSekunda(), 56);

    QCOMPARE(czas3->getGodzina(), 0);
    QCOMPARE(czas3->getMinuta(), 22);
    QCOMPARE(czas3->getSekunda(), 48);

    QCOMPARE(czas4->getGodzina(), 11);
    QCOMPARE(czas4->getMinuta(), 47);
    QCOMPARE(czas4->getSekunda(), 56);
}

QTEST_MAIN(TestMain)
#include "TestMain.moc"
