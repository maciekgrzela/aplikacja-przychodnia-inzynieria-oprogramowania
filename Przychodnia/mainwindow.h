#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QStandardItemModel>
#include <QTableView>
#include <QMessageBox>
#include <QButtonGroup>
#include <QToolButton>

#include "przychodnia.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, bool czyManager = false, Osoba *zalogowany = nullptr);
    ~MainWindow();

    void przydzielUprawnieniaDlaPracownika();
    void wyswietlListePacjentow(QList<Pacjent*> listaPacjentow, QTableView *viewPacjent);
    void wyswietlListePracownikow(QList<Pracownik*> listaPracownikow, QTableView *viewPracownik);
    void wyswietlListeZabiegow(QList<Zabieg*> listaZabiegow, QTableView *viewZabieg);

    void przygotujTabele();
    void przygotujInterfejsGraficzny();
    void wypelnijPolaGodzinPracy(QString odGodzina, QString doGodzina);

    QString godzinaDoPolaTekstowego(QString godzina);
    QString usunDodatkoweInfo(QString tekst);

    void wprowadzGodzineDoTerminu(QString godzina);

    void uaktywnijPrzyciskiGodziny();
    void uaktywnijPrzycisk(QToolButton *btn);


private slots:
    void on_wizytyBtn_clicked();
    void on_pacjenciBtn_clicked();
    void on_kompetencjeBtn_clicked();
    void on_zabiegiBtn_clicked();
    void on_pracownicyBtn_clicked();
    void on_ustawieniaBtn_clicked();
    void on_wylogujBtn_clicked();
    void on_modyfikujDanePacjentaBtn_clicked();
    void on_szukajPacjenciWizytaBtn_clicked();
    void on_szukajZabiegiWizytaBtn_clicked();
    void on_szukajPracownicyWizytaBtn_clicked();
    void on_szukajPacjentaBtn_clicked();
    void on_szukajPracownikaKompetencjeBtn_clicked();
    void on_szukajZabieguBtn_clicked();
    void on_szukajPracownikaBtn_clicked();
    void on_dodajPracownikaPracownicyBtn_clicked();
    void on_pracownicyTableView_clicked(const QModelIndex &index);
    void on_modyfikujPracownikaPracownicyBtn_clicked();
    void on_pracownikWyczyscBtn_clicked();
    void on_usunPracownikaBtn_clicked();
    void on_ustawSchemat715_clicked();
    void on_ustawSchemat816_clicked();
    void on_ustawSchemat917_clicked();
    void on_ustawSchemat1018_clicked();
    void on_ustawSchemat1119_clicked();
    void on_godzinyPracyWyczyscBtn_clicked();
    void on_godzinyPracyZatwierdzBtn_clicked();
    void on_zabiegiTableView_clicked(const QModelIndex &index);
    void on_zabiegiWyczyscBtn_clicked();
    void on_zabiegiUsunBtn_clicked();
    void on_zabiegiDodajBtn_clicked();
    void on_zabiegiModyfikujBtn_clicked();
    void on_pacjenciWyczyscBtn_clicked();
    void on_pacjenciTableView_clicked(const QModelIndex &index);
    void on_pacjenciUsunBtn_clicked();
    void on_pacjenciDodajBtn_clicked();
    void on_pracownicyKompetencjeTableView_clicked(const QModelIndex &index);
    void on_przeglKompetencjiTableView_doubleClicked(const QModelIndex &index);
    void on_rozszKompetencjiTableView_doubleClicked(const QModelIndex &index);
    void on_pacjenciWizytaTableView_clicked(const QModelIndex &index);
    void on_zabiegiWizytaTableView_clicked(const QModelIndex &index);
    void on_pracownicyWizytaTableView_clicked(const QModelIndex &index);
    void on_calendarWidget_clicked(const QDate &date);

    void on_toolButton_clicked();
    void on_toolButton_2_clicked();
    void on_toolButton_3_clicked();
    void on_toolButton_4_clicked();
    void on_toolButton_5_clicked();
    void on_toolButton_6_clicked();
    void on_toolButton_7_clicked();
    void on_toolButton_8_clicked();
    void on_toolButton_9_clicked();
    void on_toolButton_10_clicked();
    void on_toolButton_11_clicked();
    void on_toolButton_12_clicked();
    void on_toolButton_13_clicked();
    void on_toolButton_14_clicked();
    void on_toolButton_15_clicked();
    void on_toolButton_16_clicked();
    void on_toolButton_17_clicked();
    void on_toolButton_18_clicked();
    void on_toolButton_19_clicked();
    void on_toolButton_20_clicked();
    void on_toolButton_21_clicked();
    void on_toolButton_22_clicked();
    void on_toolButton_23_clicked();

    void on_umowWizyteBtn_clicked();

    void on_wyczyscWizyteBtn_clicked();

private:
    Ui::MainWindow *ui;
    Przychodnia *przychodnia;
    bool zalogowanoJakoManager;
    Osoba *zalogowany;
    Pracownik *modyfikowanyPracownik;
    Zabieg *modyfikowanyZabieg;
    Pacjent *modyfikowanyPacjent;
    QButtonGroup *godzinyPrzyciski;
    QList<QString> danePacjenta;
    QList<QString> danePracownika;
    QList<QString> daneZabiegu;
    QList<int> daneTerminu;
    QList<int> daneGodziny;
};
#endif // MAINWINDOW_H
