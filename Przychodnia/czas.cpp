#include "czas.h"
#include <QtMath>

Czas::Czas() {
    this->godzina = 0;
    this->minuta = 0;
    this->sekunda = 0;
}

Czas::Czas(int godzina, int minuta, int sekunda) {
    this->godzina = godzina;
    this->minuta = minuta;
    this->sekunda = sekunda;
}

Czas::Czas(QString godzinaTekst) {
    if(godzinaTekst.length() == 8 && godzinaTekst.count(":") == 2
            && godzinaTekst.at(2) == ":"
            && godzinaTekst.at(5) == ":"){
        QString godzina;
        godzina.push_back(godzinaTekst.at(0));
        godzina.push_back(godzinaTekst.at(1));
        this->godzina = godzina.toInt();
        QString minuta;
        minuta.push_back(godzinaTekst.at(3));
        minuta.push_back(godzinaTekst.at(4));
        this->minuta = minuta.toInt();
        QString sekunda;
        sekunda.push_back(godzinaTekst.at(6));
        sekunda.push_back(godzinaTekst.at(7));
        this->sekunda = sekunda.toInt();
    }else {
        this->godzina = 0;
        this->minuta = 0;
        this->sekunda = 0;
    }
}

int Czas::getMinuta() const
{
    return minuta;
}

void Czas::setMinuta(int value)
{
    minuta = value;
}

int Czas::getSekunda() const
{
    return sekunda;
}

void Czas::setSekunda(int value)
{
    sekunda = value;
}

void Czas::dodajPolGodziny() {
    this->godzina = (this->godzina + (this->minuta + 30) / 60) % 24;
    this->minuta = (this->minuta + 30) % 60;
}

bool Czas::operator==(Czas &inny)
{
    if(this->godzina == inny.godzina){
        if(this->minuta == inny.minuta){
            if(this->sekunda == inny.sekunda){
                return true;
            }
        }
    }
    return false;
}

bool Czas::operator<(Czas &inny) {
    if(this->godzina < inny.godzina){
        return true;
    }else {
        if(this->minuta < inny.minuta){
            return true;
        }else {
            if(this->sekunda < inny.sekunda){
                return true;
            }else {
                return false;
            }
        }
    }
}

QString Czas::toString() {
    return QString::number(getGodzina())+":"+QString::number(getMinuta())+":"+QString::number(getSekunda());
}

QString Czas::toStringBezSekund() {
    return QString::number(getGodzina())+":"+QString::number(getMinuta());
}

int Czas::getGodzina() const {
    return godzina;
}

void Czas::setGodzina(int value)
{
    godzina = value;
}
