#ifndef PRZEDSIEBIORSTWO_H
#define PRZEDSIEBIORSTWO_H

#include <QString>

class Przedsiebiorstwo {
private:
    QString nazwa;
    QString branza;
    QString email;
    QString adres;
    int kod;
    QString miejscowosc;
    QString wojewodztwo;
    QString kraj;
    QString nip;
    Przedsiebiorstwo* instancja;
    Przedsiebiorstwo();
public:
    Przedsiebiorstwo* getInstancja();
    void modyfikuj(QString nazwa, QString branza, QString email, QString adres, int kod, QString miejscowosc, QString wojewodztwo, QString kraj, QString nip);

    QString getNazwa() const;
    void setNazwa(const QString &value);

    QString getBranza() const;
    void setBranza(const QString &value);

    QString getEmail() const;
    void setEmail(const QString &value);

    QString getAdres() const;
    void setAdres(const QString &value);

    int getKod() const;
    void setKod(int value);

    QString getMiejscowosc() const;
    void setMiejscowosc(const QString &value);

    QString getWojewodztwo() const;
    void setWojewodztwo(const QString &value);

    QString getKraj() const;
    void setKraj(const QString &value);

    QString getNip() const;
    void setNip(const QString &value);
};

#endif // PRZEDSIEBIORSTWO_H
