#include "wizyta.h"

Wizyta::Wizyta(Pacjent *pacjent, Zabieg *zabieg, Pracownik *pracownik, Termin *termin) {
    this->pacjent = pacjent;
    this->zabieg = zabieg;
    this->pracownik = pracownik;
    this->termin = termin;
}

Pacjent *Wizyta::getPacjent() const
{
    return pacjent;
}

void Wizyta::setPacjent(Pacjent *value)
{
    pacjent = value;
}

Zabieg *Wizyta::getZabieg() const
{
    return zabieg;
}

void Wizyta::setZabieg(Zabieg *value)
{
    zabieg = value;
}

Pracownik* Wizyta::getPracownik() const
{
    return pracownik;
}

void Wizyta::setPracownik(Pracownik *value)
{
    pracownik = value;
}

Termin *Wizyta::getTermin() const
{
    return termin;
}

void Wizyta::setTermin(Termin *value)
{
    termin = value;
}

QString Wizyta::getStatus() const
{
    return status;
}

void Wizyta::setStatus(const QString &value)
{
    status = value;
}

bool Wizyta::operator==(Wizyta &inny) {
    return true;
}
