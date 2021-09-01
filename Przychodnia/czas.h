#ifndef CZAS_H
#define CZAS_H

#include <QString>
#include "porownywalny.h"

class Czas : public Porownywalny<Czas> {
private:
    int godzina;
    int minuta;
    int sekunda;
public:
    Czas();
    Czas(int godzina, int minuta, int sekunda);
    Czas(QString godzinaTekst);
    void modyfikuj(int godzina, int minuta, int sekunda);

    int getGodzina() const;
    void setGodzina(int value);
    int getMinuta() const;
    void setMinuta(int value);
    int getSekunda() const;
    void setSekunda(int value);

    void dodajPolGodziny();

    bool operator== (Czas &inny) override;
    bool operator< (Czas &inny);
    QString toString();
    QString toStringBezSekund();

};

#endif // CZAS_H
