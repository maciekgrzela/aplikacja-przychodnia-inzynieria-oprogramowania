#include "przychodnia.h"

Przychodnia* Przychodnia::instancja = nullptr;

Przychodnia::Przychodnia() {
    this->dodajPacjenta("Anna", "Nowak", "anowak@email.pl", "609609609", "Długa", 11, 25900, "Kielce");
    this->dodajPacjenta("Jan", "Kowalski", "jkowalsk@email.com", "312312313", "Prosta", 78, 53800, "Wrocław");
    this->dodajPacjenta("Adam", "Urbański", "aurban@domena.eu", "505505501", "Sienkiewicza", 92, 44923, "Poznań");

    this->dodajPracownika("Edward", "Gutkowski", "EG001");
    this->dodajPracownika("Bronisław", "Bielak", "BB001");
    this->dodajPracownika("Daria", "Rafalska", "DR001");

    this->dodajZabieg("Szczepienie ochronne", 30.50, 1.5, "Opis zabiegu szczepienie ochronne");
    this->dodajZabieg("Spirometria", 95.90, 1.5, "Pomiar objętości oraz pojemności płuc");
    this->dodajZabieg("Badanie EKG", 25.99, 2.5, "Badanie mające na celu określenie oceny pracy serca");

    pracownicy.at(0)->dodajKompetencje(zabiegi.at(0));
    pracownicy.at(0)->dodajKompetencje(zabiegi.at(1));
    pracownicy.at(0)->dodajKompetencje(zabiegi.at(2));
    pracownicy.at(1)->dodajKompetencje(zabiegi.at(0));
    pracownicy.at(1)->dodajKompetencje(zabiegi.at(2));
    pracownicy.at(2)->dodajKompetencje(zabiegi.at(0));

    this->ustawManagera("Rafał", "Adamski", "RA001");
}

Przychodnia::~Przychodnia() {}

QList<Pacjent *> Przychodnia::zwrocPacjentow() {
    return pacjenci;
}

QList<Pracownik *> Przychodnia::zwrocPracownikow() {
    return pracownicy;
}

QList<Wizyta *> Przychodnia::zwrocWizyty() {
    return wizyty;
}

QList<Zabieg *> Przychodnia::zwrocZabiegi() {
    return zabiegi;
}

QList<Pacjent *> Przychodnia::zwrocPacjentow(QString kryterium)
{
    QList<Pacjent *> pacjenciKryteria;
    foreach(Pacjent *pacjent, pacjenci){
        if(pacjent->czySpelniaKryteria(kryterium)){
            pacjenciKryteria.append(pacjent);
        }
    }
    return pacjenciKryteria;
}

QList<Pracownik *> Przychodnia::zwrocPracownikow(QString kryterium) {
    QList<Pracownik *> pracownicyKryteria;
    foreach(Pracownik *pracownik, pracownicy){
        if(pracownik->czySpelniaKryteria(kryterium)){
            pracownicyKryteria.append(pracownik);
        }
    }
    return pracownicyKryteria;
}

QList<Zabieg *> Przychodnia::zwrocZabiegi(QString kryterium) {
    QList<Zabieg *> zabiegiKryteria;
    foreach(Zabieg *zabieg, zabiegi){
        if(zabieg->czySpelniaKryteria(kryterium)){
            zabiegiKryteria.append(zabieg);
        }
    }
    return zabiegiKryteria;
}

QList<Zabieg *> Przychodnia::zwrocZabiegiNiedozwoloneDla(Pracownik *pracownik) {
    QList<Zabieg *> zabiegiNiedozwolone;
    foreach(Zabieg *zabieg, zabiegi){
        if(!(pracownik->czyPosiadaKompetencje(zabieg))){
            zabiegiNiedozwolone.append(zabieg);
        }
    }
    return zabiegiNiedozwolone;
}

Manager* Przychodnia::zwrocManagera() {
    return manager;
}

Pracownik* Przychodnia::szukajPracownika(QString imie, QString nazwisko, QString kodLogowania) {
    Pracownik *temp = new Pracownik(imie, nazwisko, kodLogowania);
    Pracownik *pracownik = nullptr;
    QListIterator<Pracownik*> it(pracownicy);
    while(it.hasNext()){
        pracownik = it.next();
        if(*temp == *pracownik){
            return pracownik;
        }
    }
    return nullptr;
}

Pacjent* Przychodnia::szukajPacjenta(QString imie, QString nazwisko, QString email, QString telefon, QString ulica, int numer, int kod, QString miejscowosc) {
    Pacjent *temp = new Pacjent(imie, nazwisko, email, telefon, ulica, numer, kod, miejscowosc);
    Pacjent *pacjent = nullptr;
    QListIterator<Pacjent*> it(pacjenci);
    while(it.hasNext()){
        pacjent = it.next();
        if(*temp == *pacjent){
            return pacjent;
        }
    }
    return nullptr;
}

Zabieg* Przychodnia::szukajZabiegu(QString nazwa, double cena, double czasTrwania, QString opis) {
    Zabieg *temp = new Zabieg(nazwa, cena, czasTrwania, opis);
    Zabieg *zabieg = nullptr;
    QListIterator<Zabieg*> it(zabiegi);
    while(it.hasNext()){
        zabieg = it.next();
        if(*temp == *zabieg){
            return zabieg;
        }
    }
    return nullptr;
}

void Przychodnia::dodajPracownika(QString imie, QString nazwisko, QString kodLogowania) {
    Pracownik *tempPracownik = this->szukajPracownika(imie, nazwisko, kodLogowania);
    if(tempPracownik == nullptr){
        Pracownik *pracownik = new Pracownik(imie, nazwisko, kodLogowania);
        pracownik->setHaslo(QCryptographicHash::hash(kodLogowania.toUtf8(), QCryptographicHash::Sha1));
        if(unikalnyKodLogowania(pracownik, kodLogowania)){
            pracownicy.append(pracownik);
        }
    }
}

void Przychodnia::modyfikujPracownika(Pracownik *pracownik, QString imie, QString nazwisko, QString kodLogowania) {
    if(imie.length() != 0 && nazwisko.length() != 0 && kodLogowania.length() != 0){
        if(pracownik != nullptr){
            Pracownik *tempPrac = this->szukajPracownika(imie, nazwisko, kodLogowania);
            if(tempPrac == nullptr && unikalnyKodLogowania(pracownik, kodLogowania)){
                pracownik->modyfikuj(imie, nazwisko, kodLogowania, pracownik->getHaslo());
            }
        }
    }
}

void Przychodnia::usunPracownika(Pracownik *pracownik) {
    Pracownik *temp = nullptr;
    QListIterator<Pracownik*> it(pracownicy);
    int pos=0;
    while(it.hasNext()){
        temp = it.next();
        pos++;
        if(*temp == *pracownik){
            pracownicy.removeAt(pos-1);
            return;
        }
    }
}

void Przychodnia::rozszerzKompetencjePracownika(Pracownik *pracownik, Zabieg *kompetencja) {
    pracownik->dodajKompetencje(kompetencja);
}

void Przychodnia::redukujKompetencjePracownika(Pracownik *pracownik, Zabieg *kompetencja) {
    pracownik->usunKompetencje(kompetencja);
}

void Przychodnia::zmienGodzinyPracyPracownika(Pracownik *pracownik, GodzinyPracy *godzinyPracy) {
    pracownik->ustawGodzinyPracyWDniu(godzinyPracy);
}

void Przychodnia::zmienGodzinyPracyPracownika(Pracownik *pracownik, QString dzienTygodnia, QString godzinaOd, QString godzinaDo) {
    Czas *godzinaOdCzas = new Czas(godzinaOd+":00");
    Czas *godzinaDoCzas = new Czas(godzinaDo+":00");
    pracownik->setGodzinyPracyWDniuTygodnia(dzienTygodnia, godzinaOdCzas, godzinaDoCzas);
}

bool Przychodnia::czyPracownikWykonujeWizyte(Termin *termin, Pracownik *pracownik, double czasTrwaniaWizyty) {
    if(pracownik->czyWykonujeWizyteWDanymTerminie(*termin, this->zwrocWizyty(), czasTrwaniaWizyty)){
        return true;
    }else {
        return false;
    }
}

bool Przychodnia::unikalnyKodLogowania(Pracownik *wykluczony, QString kodLogowania) {
    foreach(Pracownik *pracownik, pracownicy){
        if(pracownik->getKodLogowania() == kodLogowania && !(*pracownik == *wykluczony)){
            return false;
        }
    }
    return true;
}

void Przychodnia::dodajPacjenta(QString imie, QString nazwisko, QString email, QString telefon, QString ulica, int numer, int kod, QString miejscowosc) {
    Pacjent *tempPacjent = this->szukajPacjenta(imie, nazwisko, email, telefon, ulica, numer, kod, miejscowosc);
    if(tempPacjent == nullptr && imie.length() != 0 && nazwisko.length() != 0 && czyPoprawnyEmail(email) && telefon.length() != 0 && ulica.length() != 0 && numer > 0 && kod > 0 && miejscowosc.length() != 0){
        Pacjent *pacjent = new Pacjent(imie, nazwisko, email, telefon, ulica, numer, kod, miejscowosc);
        pacjenci.append(pacjent);
    }
}

void Przychodnia::modyfikujPacjenta(Pacjent *pacjent, QString imie, QString nazwisko, QString email, QString telefon, QString ulica, int numer, int kod, QString miejscowosc) {
    if(imie.length() != 0 && nazwisko.length() != 0 && czyPoprawnyEmail(email) && telefon.length() != 0 && ulica.length() != 0 && numer > 0 && kod > 0 && miejscowosc.length() != 0){
        if(pacjent != nullptr){
            Pacjent *tempPac = this->szukajPacjenta(imie, nazwisko, email, telefon, ulica, numer, kod, miejscowosc);
            if(tempPac == nullptr){
                pacjent->modyfikuj(imie, nazwisko, email, telefon, ulica, numer, kod, miejscowosc);
            }
        }
    }
}

void Przychodnia::usunPacjenta(Pacjent *pacjent) {
    Pacjent *temp = nullptr;
    QListIterator<Pacjent*> it(pacjenci);
    int pos=0;
    while(it.hasNext()){
        temp = it.next();
        pos++;
        if(*temp == *pacjent){
            pacjenci.removeAt(pos-1);
            return;
        }
    }
}

bool Przychodnia::umowWizyte(QList<QString> danePacjenta, QList<QString> daneZabiegu, QList<QString> danePracownika, QList<int> daneTerminu) {
    if(danePacjenta.length() == 8 && daneZabiegu.length() == 4 && danePracownika.length() == 3 && daneTerminu.length() == 6){
        Pacjent *pacjent = szukajPacjenta(danePacjenta.at(0),danePacjenta.at(1), danePacjenta.at(2), danePacjenta.at(3), danePacjenta.at(4), danePacjenta.at(5).toInt(), danePacjenta.at(6).toInt(), danePacjenta.at(7));
        if(pacjent != nullptr){
            Pracownik *pracownik = szukajPracownika(danePracownika.at(0), danePracownika.at(1), danePracownika.at(2));
            if(pracownik != nullptr){
                Zabieg *zabieg = szukajZabiegu(daneZabiegu.at(0), daneZabiegu.at(1).toDouble(), daneZabiegu.at(2).toDouble(), daneZabiegu.at(3));
                Czas *czasRozpoczeciaWizyty = this->utworzCzas(daneTerminu.at(3), daneTerminu.at(4), daneTerminu.at(5));
                bool pracownikPosiadaKompetencje = pracownik->czyPosiadaKompetencje(zabieg);
                if(czasRozpoczeciaWizyty != nullptr && pracownikPosiadaKompetencje){
                    GodzinyPracy *godzinyPracy = pracownik->godzinyPracyWDniuTygodnia(Termin::zwrocDzienTygodnia(daneTerminu.at(0), daneTerminu.at(1), daneTerminu.at(2)));
                    if(*czasRozpoczeciaWizyty < *godzinyPracy->getGodzinaDo() && *godzinyPracy->getGodzinaOd() < *czasRozpoczeciaWizyty){
                        Termin *termin = this->utworzTermin(daneTerminu.at(0), daneTerminu.at(1), daneTerminu.at(2), czasRozpoczeciaWizyty);
                        if(termin != nullptr){
                            bool czyZajety = czyPracownikWykonujeWizyte(termin, pracownik, daneZabiegu.at(2).toDouble());
                            if(!czyZajety){
                                Wizyta *wizyta = this->utworzWizyte(pracownik, pacjent, zabieg, termin);
                                wizyta->setStatus("Umówiona");
                                wizyty.append(wizyta);
                                return true;
                            }else {
                                //QMessageBox::information(nullptr, "Pracownik zajęty", "W danym terminie pracownik już wykonuje zabieg");
                            }
                        }else {
                            //QMessageBox::information(nullptr, "Nieprawidłowy termin", "Wprowadzono nieprawidłowy termin zabiegu");
                        }
                    }else {
                        //QMessageBox::information(nullptr, "Nieprawidłowy godzina", "Wskazana godzina nie mieści się w godzinach pracy pracownika");
                    }
                }else {
                    //QMessageBox::information(nullptr, "Brak kompetencji", "Pracownik nie posiada kompetencji aby wykonywać ten zabieg");
                }
            }else {
                //QMessageBox::information(nullptr, "Nieprawidłowy pracownik", "Wprowadzono nieprawidłowe dane pracownika");
            }
        }else {
            //QMessageBox::information(nullptr, "Nieprawidłowy pacjent", "Wprowadzono nieprawidłowe dane pacjenta");
        }
    }else {
        //QMessageBox::information(nullptr, "Bład", "Wprowadzone dane są niekompletne");
    }
    return false;
}

QList<Wizyta *> Przychodnia::zwrocWizyty(Pracownik pracownik, Termin termin) {
    Wizyta *temp = nullptr;
    QList<Wizyta*> wszystkie = this->zwrocWizyty();
    QList<Wizyta*> wykonywane;
    QListIterator<Wizyta*> it(wszystkie);
    while(it.hasNext()){
        temp = it.next();
        if(*temp->getPracownik() == pracownik && *temp->getTermin() == termin){
            wykonywane.append(temp);
        }
    }
    return wykonywane;
}

void Przychodnia::ustawManagera(QString imie, QString nazwisko, QString kodLogowania) {
    this->manager = new Manager(imie, nazwisko, kodLogowania);
    this->manager->setHaslo(QCryptographicHash::hash(kodLogowania.toUtf8(), QCryptographicHash::Sha1));
}

void Przychodnia::dodajZabieg(QString nazwa, double cena, double czasTrwania, QString opis) {
    Zabieg *zabiegTemp = this->szukajZabiegu(nazwa, cena, czasTrwania, opis);
    if(zabiegTemp == nullptr){
        Zabieg *zabieg = new Zabieg(nazwa, cena, czasTrwania, opis);
        zabiegi.append(zabieg);
    }
}

void Przychodnia::modyfikujZabieg(Zabieg *zabieg, QString nazwa, double cena, double czasTrwania, QString opis) {
    if(nazwa.length() != 0 && cena >= 0 && czasTrwania >= 0.5 && opis.length() != 0){
        if(zabieg != nullptr){
            Zabieg *tempZab = this->szukajZabiegu(nazwa, cena, czasTrwania, opis);
            if(tempZab == nullptr){
                zabieg->modyfikuj(nazwa, cena, czasTrwania, opis);
            }
        }
    }
}

void Przychodnia::usunZabieg(Zabieg *zabieg) {
    Zabieg *temp = nullptr;
    QListIterator<Zabieg*> it(zabiegi);
    int pos=0;
    while(it.hasNext()){
        temp = it.next();
        pos++;
        if(*temp == *zabieg){
            zabiegi.removeAt(pos-1);
            return;
        }
    }
}

void Przychodnia::wypelnijModelPacjentow(QList<Pacjent *> listaPacjentow, QStandardItemModel *modelPacjent) {
    foreach(Pacjent *pacjent, listaPacjentow){
        int index = modelPacjent->rowCount();
        modelPacjent->setRowCount(index+1);
        pacjent->wypelnijModel(modelPacjent, index);
    }
}

void Przychodnia::wypelnijModelPracownikow(QList<Pracownik *> listaPracownikow, QStandardItemModel *modelPracownik) {
    foreach(Pracownik *pracownik, listaPracownikow){
        int index = modelPracownik->rowCount();
        modelPracownik->setRowCount(index+1);
        pracownik->wypelnijModel(modelPracownik, index);
    }
}

void Przychodnia::wypelnijModelZabiegow(QList<Zabieg *> listaZabiegow, QStandardItemModel *modelZabieg) {
    foreach(Zabieg *zabieg, listaZabiegow){
        int index = modelZabieg->rowCount();
        modelZabieg->setRowCount(index+1);
        zabieg->wypelnijModel(modelZabieg, index);
    }
}

Termin* Przychodnia::utworzTermin(int dzien, int miesiac, int rok, Czas *czas) {
    if((dzien >= 1 && dzien <= 31) && (miesiac >= 1 && miesiac <= 12) && (rok >= 2000 && rok <= 2050)){
        Termin* termin = new Termin(dzien, miesiac, rok, *czas);
        return termin;
    }else {
        return nullptr;
    }
}

Czas* Przychodnia::utworzCzas(int godzina, int minuta, int sekunda) {
    if((godzina >= 7 && godzina <= 19) && (minuta >= 0 && minuta <= 59) && (sekunda >= 0 && sekunda <= 59)){
        Czas *czas = new Czas(godzina, minuta, sekunda);
        return czas;
    }else {
        return nullptr;
    }
}

Wizyta* Przychodnia::utworzWizyte(Pracownik *pracownik, Pacjent *pacjent, Zabieg *zabieg, Termin *termin) {
    Wizyta *wizyta = new Wizyta(pacjent, zabieg, pracownik, termin);
    return wizyta;
}

Przychodnia* Przychodnia::getInstancja() {
    if(instancja == nullptr){
        instancja = new Przychodnia();
    }
    return instancja;
}

bool Przychodnia::czyPoprawnyEmail(QString email) {
    if(email.indexOf('@') > -1 && email.count('@') == 1 && email.indexOf('.') > -1 && email.count('.') >= 1) {
        return true;
    }else {
        return false;
    }
}
