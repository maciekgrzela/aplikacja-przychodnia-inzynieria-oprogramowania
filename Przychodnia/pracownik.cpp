#include "pracownik.h"

Pracownik::Pracownik(QString imie, QString nazwisko, QString kodLogowania) {
    this->imie = imie;
    this->nazwisko = nazwisko;
    this->kodLogowania = kodLogowania;

    QList<QString> dniTygodnia;
    dniTygodnia << "Poniedziałek" << "Wtorek" << "Środa" << "Czwartek" << "Piątek";
    foreach(QString dzien, dniTygodnia){
        Czas *godzinaOd = new Czas(), *godzinaDo = new Czas();
        GodzinyPracy* godziny = new GodzinyPracy(dzien, godzinaOd, godzinaDo);
        godzinyPracy.append(godziny);
    }
}

void Pracownik::modyfikuj(QString imie, QString nazwisko, QString kodLogowania, QByteArray haslo) {
    this->setImie(imie);
    this->setNazwisko(nazwisko);
    this->setKodLogowania(kodLogowania);
    this->setHaslo(haslo);
}

QByteArray Pracownik::getHaslo() const
{
    return haslo;
}

void Pracownik::setHaslo(const QByteArray &value)
{
    haslo = value;
}

QList<GodzinyPracy*> Pracownik::getGodzinyPracy() const
{
    return godzinyPracy;
}

void Pracownik::setGodzinyPracy(const QList<GodzinyPracy*> &value)
{
    godzinyPracy = value;
}

GodzinyPracy *Pracownik::godzinyPracyWDniuTygodnia(QString dzienTygodnia) {
    QList<GodzinyPracy*> listaGodzinPracy = this->getGodzinyPracy();
    foreach(GodzinyPracy *godzinaPracy, listaGodzinPracy){
        if(godzinaPracy->getDzienTygodnia() == dzienTygodnia){
            return godzinaPracy;
        }
    }
}

void Pracownik::setGodzinyPracyWDniuTygodnia(QString dzienTygodnia, Czas *godzinaOd, Czas *godzinaDo) {
    GodzinyPracy *godzinyPracy = new GodzinyPracy(dzienTygodnia, godzinaOd, godzinaDo);
    foreach(GodzinyPracy *godzina, this->godzinyPracy){
        if(godzina->getDzienTygodnia() == godzinyPracy->getDzienTygodnia()){
            godzina->setGodzinaOd(godzinaOd);
            godzina->setGodzinaDo(godzinaDo);
        }
    }
}

QList<Zabieg *> Pracownik::kompetencjePracownika() {
    return kompetencje;
}

bool Pracownik::czyPosiadaKompetencje(Zabieg *zabieg) {
    QListIterator<Zabieg*> it(kompetencje);
    Zabieg *temp = nullptr;
    while(it.hasNext()){
        temp = it.next();
        if(*temp == *zabieg){
            return true;
        }
    }
    return false;
}

void Pracownik::dodajKompetencje(Zabieg *zabieg) {
    if(zabieg != nullptr){
        bool czyJuzPosiada = this->czyPosiadaKompetencje(zabieg);
        if(!czyJuzPosiada){
            kompetencje.append(zabieg);
        }
    }
}

void Pracownik::usunKompetencje(Zabieg *zabieg) {
    if(zabieg != nullptr){
        bool czyPosiada = this->czyPosiadaKompetencje(zabieg);
        if(czyPosiada){
            kompetencje.removeAll(zabieg);
        }
    }
}


bool Pracownik::operator==(Pracownik &inny) {
    if(this->getImie() == inny.getImie() &&
       this->getNazwisko() == inny.getNazwisko() &&
       this->getKodLogowania() == inny.getKodLogowania()){
        return true;
    }
    return false;
}

void Pracownik::wypelnijModel(QStandardItemModel *model, int index) {
    QStandardItem *itemImie = new QStandardItem(this->getImie());
    QStandardItem *itemNazwisko = new QStandardItem(this->getNazwisko());
    QStandardItem *itemEmail = new QStandardItem(this->getKodLogowania());

    model->setItem(index, 0, itemImie);
    model->setItem(index, 1, itemNazwisko);
    model->setItem(index, 2, itemEmail);
}

void Pracownik::ustawGodzinyPracyWDniu(GodzinyPracy *godzinyPracy) {
    if(godzinyPracy != nullptr){
        QString dzienTygodnia="";
        QList<GodzinyPracy*> godziny = this->getGodzinyPracy();
        QListIterator<GodzinyPracy*> it(godziny);
        int pos=0;
        while(it.hasNext()){
            pos++;
            GodzinyPracy *temp = it.next();
            dzienTygodnia=temp->getDzienTygodnia();
            if(dzienTygodnia == godzinyPracy->getDzienTygodnia()){
                godziny.removeAt(pos);
                godziny.append(godzinyPracy);
                this->setGodzinyPracy(godziny);
            }
        }
    }
}

bool Pracownik::czyWykonujeWizyteWDanymTerminie(Termin termin, QList<Wizyta*> wizyty, double czasTrwaniaWizyty) {
    Wizyta *wizyta = nullptr;
    QListIterator<Wizyta*> it(wizyty);
    int iloscZajBlokGodzinowych = (double)czasTrwaniaWizyty / (double)0.5;
    for(int i = 0; i < iloscZajBlokGodzinowych; i++){
        while(it.hasNext()){
            wizyta = it.next();
            Termin *terminWizyty=wizyta->getTermin();
            Pracownik *pracownikWykonujacyWizyte = wizyta->getPracownik();
            if(this == pracownikWykonujacyWizyte && termin == *terminWizyty){
                return true;
            }
        }
        it.toFront();
        termin.getGodzina().dodajPolGodziny();
    }
    return false;
}

bool Pracownik::czySpelniaKryteria(QString kryterium) {
    if(kryterium.length() > 0){
        if(this->getImie().contains(kryterium) || this->getNazwisko().contains(kryterium) ||
           this->getKodLogowania().contains(kryterium)){
            return true;
        }
    }
    return false;
}

void Pracownik::wyswietlDane()
{
    qDebug() << this->getImie() << this->getNazwisko() << this->getKodLogowania();
}

QString Pracownik::getKodLogowania() const
{
    return kodLogowania;
}

void Pracownik::setKodLogowania(const QString &value)
{
    kodLogowania = value;
}
