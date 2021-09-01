#include "termin.h"

Termin::Termin(int dzien, int miesiac, int rok, Czas godzina) {
    this->dzien = dzien;
    this->miesiac = miesiac;
    this->rok = rok;
    this->godzina = godzina;
}

int Termin::getMiesiac() const
{
    return miesiac;
}

void Termin::setMiesiac(int value)
{
    miesiac = value;
}

int Termin::getRok() const
{
    return rok;
}

void Termin::setRok(int value)
{
    rok = value;
}

Czas Termin::getGodzina() const
{
    return godzina;
}

void Termin::setGodzina(const Czas &value)
{
    godzina = value;
}

QString Termin::zwrocDzienTygodnia(int dzien, int miesiac, int rok) {
    static int t[] = {0,3,2,5,0,3,5,1,4,6,2,4};
    rok -= miesiac < 3;
    int dzienTygodnia = (rok+ rok/4 - rok/100 + rok/400 + t[miesiac-1] + dzien) % 7;
    switch(dzienTygodnia){
        case 0: return "Niedziela";
        case 1: return "Poniedziałek";
        case 2: return "Wtorek";
        case 3: return "Środa";
        case 4: return "Czwartek";
        case 5: return "Piątek";
        case 6: return "Sobota";
    }
}

bool Termin::operator==(Termin &inny) {
    if(this->getRok() == inny.getRok() &&
       this->getMiesiac() == inny.getMiesiac() &&
       this->getDzien() == inny.getDzien() &&
       this->getGodzina() == inny.godzina){
        return true;
    }
    return false;
}

int Termin::getDzien() const
{
    return dzien;
}

void Termin::setDzien(int value)
{
    dzien = value;
}
