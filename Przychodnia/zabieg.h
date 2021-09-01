#ifndef ZABIEG_H
#define ZABIEG_H

#include <QString>
#include <QStandardItemModel>
#include "porownywalny.h"

class Zabieg : public Porownywalny<Zabieg> {
private:
    QString nazwa;
    double cena;
    double czasTrwania;
    QString opis;
public:
    Zabieg(QString nazwa, double cena, double czasTrwania, QString opis);
    void modyfikuj(QString nazwa, double cena, double czasTrwania, QString opis);

    QString getNazwa() const;
    void setNazwa(const QString &value);
    double getCena() const;
    void setCena(double value);
    double getCzasTrwania() const;
    void setCzasTrwania(double value);
    QString getOpis() const;
    void setOpis(const QString &value);

    bool operator== (Zabieg &inny) override;
    void wypelnijModel(QStandardItemModel *model, int index);

    bool czySpelniaKryteria(QString kryterium);
};

#endif // ZABIEG_H
