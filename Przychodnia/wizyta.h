#ifndef WIZYTA_H
#define WIZYTA_H

#include <QString>
#include "pacjent.h"
#include "termin.h"
#include "porownywalny.h"
#include "zabieg.h"

class Pracownik;

class Wizyta : public Porownywalny<Wizyta> {
private:
    Pacjent *pacjent;
    Zabieg *zabieg;
    Pracownik *pracownik;
    Termin *termin;
    QString status;
public:
    Wizyta(Pacjent *pacjent, Zabieg *zabieg, Pracownik *pracownik, Termin *termin);
    void modyfikuj(Pacjent *pacjent, Zabieg *zabieg, Pracownik *pracownik);

    QString getStatus() const;
    void setStatus(const QString &value);

    bool operator== (Wizyta &inny) override;

    Pacjent *getPacjent() const;
    void setPacjent(Pacjent *value);
    Zabieg *getZabieg() const;
    void setZabieg(Zabieg *value);
    Pracownik *getPracownik() const;
    void setPracownik(Pracownik *value);
    Termin *getTermin() const;
    void setTermin(Termin *value);
};

#endif // WIZYTA_H
