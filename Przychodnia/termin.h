#ifndef TERMIN_H
#define TERMIN_H

#include "czas.h"

class Termin : public Porownywalny<Termin> {
private:
    int dzien;
    int miesiac;
    int rok;
    Czas godzina;
public:
    Termin(int dzien, int miesiac, int rok, Czas godzina);
    int getDzien() const;
    void setDzien(int value);
    int getMiesiac() const;
    void setMiesiac(int value);
    int getRok() const;
    void setRok(int value);
    Czas getGodzina() const;
    void setGodzina(const Czas &value);
    static QString zwrocDzienTygodnia(int dzien, int miesiac, int rok);

    bool operator== (Termin &inny) override;
};

#endif // TERMIN_H
