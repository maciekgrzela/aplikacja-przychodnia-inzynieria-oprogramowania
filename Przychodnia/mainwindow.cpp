#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, bool czyManager, Osoba *zalogowany)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    przychodnia = Przychodnia::getInstancja();
    this->zalogowanoJakoManager = czyManager;
    this->zalogowany = zalogowany;

    this->setWindowTitle("Aplikacja Przychodnia v1.0.0 @ Zalogowano: "+zalogowany->getImie()+" "+zalogowany->getNazwisko());

    this->przygotujInterfejsGraficzny();

    this->wyswietlListePacjentow(przychodnia->zwrocPacjentow(), ui->pacjenciWizytaTableView);
    this->wyswietlListePracownikow(przychodnia->zwrocPracownikow(), ui->pracownicyWizytaTableView);
    this->wyswietlListeZabiegow(przychodnia->zwrocZabiegi(), ui->zabiegiWizytaTableView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::przydzielUprawnieniaDlaPracownika() {
    if(!zalogowanoJakoManager){
        ui->zabiegiBtn->setEnabled(false);
        ui->pracownicyBtn->setEnabled(false);
        ui->kompetencjeBtn->setEnabled(false);
    }
}

void MainWindow::wyswietlListePacjentow(QList<Pacjent *> listaPacjentow, QTableView *viewPacjent) {
    QStandardItemModel *pacjentModel = new QStandardItemModel(viewPacjent);
    pacjentModel->setColumnCount(8);
    pacjentModel->setHorizontalHeaderLabels({"Imię", "Nazwisko", "E-mail", "Telefon", "Ulica", "Numer", "Kod", "Miejscowość"});
    viewPacjent->setModel(pacjentModel);

    przychodnia->wypelnijModelPacjentow(listaPacjentow, pacjentModel);
}

void MainWindow::wyswietlListePracownikow(QList<Pracownik *> listaPracownikow, QTableView *viewPracownik) {
    QStandardItemModel *pracownikModel = new QStandardItemModel(viewPracownik);
    pracownikModel->setColumnCount(3);
    pracownikModel->setHorizontalHeaderLabels({"Imię", "Nazwisko", "Kod logowania"});
    viewPracownik->setModel(pracownikModel);

    przychodnia->wypelnijModelPracownikow(listaPracownikow, pracownikModel);
}

void MainWindow::wyswietlListeZabiegow(QList<Zabieg *> listaZabiegow, QTableView *viewZabieg) {
    QStandardItemModel *zabiegModel = new QStandardItemModel(viewZabieg);
    zabiegModel->setColumnCount(4);
    zabiegModel->setHorizontalHeaderLabels({"Nazwa", "Cena", "Czas trwania", "Opis"});
    viewZabieg->setModel(zabiegModel);

    przychodnia->wypelnijModelZabiegow(listaZabiegow, zabiegModel);
}

void MainWindow::przygotujTabele()
{
    QList<QTableView*> tableViews = findChildren<QTableView*>();
    foreach(QTableView* view, tableViews) {
        view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        view->setSelectionBehavior(QAbstractItemView::SelectRows);
        view->setSelectionMode(QAbstractItemView::SingleSelection);
        view->horizontalHeader()->setStretchLastSection(true);
        view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        view->verticalHeader()->hide();
    }
}

void MainWindow::przygotujInterfejsGraficzny() {
    przydzielUprawnieniaDlaPracownika();
    przygotujTabele();
    ui->menuTab->tabBar()->hide();
    ui->userNameLabel->setText(zalogowany->getImie()+" "+zalogowany->getNazwisko());
    QList<QLineEdit*> lineEdits = ui->godzinyPracownikaGroupBox->findChildren<QLineEdit*>();
    foreach(QLineEdit *line, lineEdits){
        line->setInputMask("99:99");
    }
}

void MainWindow::wypelnijPolaGodzinPracy(QString odGodzina, QString doGodzina) {
    QList<QLineEdit*> lineEdits = ui->godzinyPracownikaGroupBox->findChildren<QLineEdit*>();
    int i = 0;
    foreach(QLineEdit *line, lineEdits){
        if(i%2 == 0){
            line->setText(odGodzina);
        }else {
            line->setText(doGodzina);
        }
        i++;
    }
}

QString MainWindow::godzinaDoPolaTekstowego(QString godzina) {
    qDebug() << "Godz: -------------------------------- " << godzina;
    QString godz = godzina.mid(0, godzina.indexOf(":"));
    qDebug() << "Godzina: "<< godz;
    QString min = godzina.mid(godzina.indexOf(":")+1, godzina.length() - godzina.lastIndexOf(":"));
    qDebug() << "Minuta" << min;
    QString sek = godzina.mid(godzina.lastIndexOf(":")+1);
    qDebug() << "Sekunda" << sek;

    int godzInt = godz.toInt();
    int minInt = min.toInt();
    int sekInt = sek.toInt();

    if(godzInt < 10){
        godz = "0"+godz;
    }
    if(minInt < 10){
        min = "0"+min;
    }
    if(sekInt < 10){
        sek = "0"+sek;
    }
    return godz+""+min;
}

QString MainWindow::usunDodatkoweInfo(QString tekst) {
    tekst.replace(" PLN", "").replace("h", "");
    return tekst;
}

void MainWindow::uaktywnijPrzyciskiGodziny() {
    QList<QToolButton*> btns = ui->godzinyGroupBox->findChildren<QToolButton*>();
    foreach(QToolButton *btn, btns){
        btn->setEnabled(true);
    }
}

void MainWindow::uaktywnijPrzycisk(QToolButton *btn) {
    if(btn->styleSheet().contains("background-color: rgb(0,51,102)")){
        btn->setStyleSheet(btn->styleSheet().replace("rgb(0,51,102)", "rgb(192,19,0)"));
        ui->godzinaWizytyLineEdit->setText(btn->text().mid(0, btn->text().indexOf("-") - 1));
        daneGodziny.append(btn->text().mid(0, btn->text().indexOf(":")).toInt());
        daneGodziny.append(btn->text().mid(btn->text().indexOf(":")+1, btn->text().indexOf("-")-4).toInt());
        daneGodziny.append(0);
    }else {
        btn->setStyleSheet(btn->styleSheet().replace("rgb(192,19,0)", "rgb(0,51,102)"));
        ui->godzinaWizytyLineEdit->setText("");
        daneGodziny.clear();
    }
    if(daneTerminu.length() > 0 && daneZabiegu.length() > 0 && danePacjenta.length() > 0 && danePracownika.length() > 0 && ui->godzinaWizytyLineEdit->text().length() > 0){
        ui->umowWizyteBtn->setEnabled(true);
    }else {
        ui->umowWizyteBtn->setEnabled(false);
    }
}

void MainWindow::on_wizytyBtn_clicked()
{
    ui->menuTab->setCurrentIndex(0);
}

void MainWindow::on_pacjenciBtn_clicked()
{
    this->wyswietlListePacjentow(przychodnia->zwrocPacjentow(), ui->pacjenciTableView);
    ui->menuTab->setCurrentIndex(1);
}

void MainWindow::on_kompetencjeBtn_clicked()
{
    this->wyswietlListePracownikow(przychodnia->zwrocPracownikow(), ui->pracownicyKompetencjeTableView);
    ui->menuTab->setCurrentIndex(2);
}

void MainWindow::on_zabiegiBtn_clicked()
{
    this->wyswietlListeZabiegow(przychodnia->zwrocZabiegi(), ui->zabiegiTableView);
    ui->menuTab->setCurrentIndex(3);
}

void MainWindow::on_pracownicyBtn_clicked()
{
    this->wyswietlListePracownikow(przychodnia->zwrocPracownikow(), ui->pracownicyTableView);
    ui->menuTab->setCurrentIndex(4);
}

void MainWindow::on_ustawieniaBtn_clicked()
{
    ui->menuTab->setCurrentIndex(5);
}

void MainWindow::on_wylogujBtn_clicked() {
    QCoreApplication::quit();
}

void MainWindow::on_szukajPacjenciWizytaBtn_clicked() {
    if(ui->szukajPacjenciWizytaLineEdit->text().length() > 0){
        QList<Pacjent*> pacjenciKryteria = przychodnia->zwrocPacjentow(ui->szukajPacjenciWizytaLineEdit->text());
        this->wyswietlListePacjentow(pacjenciKryteria, ui->pacjenciWizytaTableView);
    }else {
        this->wyswietlListePacjentow(przychodnia->zwrocPacjentow(), ui->pacjenciWizytaTableView);
    }
}

void MainWindow::on_szukajZabiegiWizytaBtn_clicked() {
    if(ui->szukajZabiegiWizytaLineEdit->text().length() > 0){
        QList<Zabieg*> zabiegiKryteria = przychodnia->zwrocZabiegi(ui->szukajZabiegiWizytaLineEdit->text());
        this->wyswietlListeZabiegow(zabiegiKryteria, ui->zabiegiWizytaTableView);
    }else {
        this->wyswietlListeZabiegow(przychodnia->zwrocZabiegi(), ui->zabiegiWizytaTableView);
    }
}

void MainWindow::on_szukajPracownicyWizytaBtn_clicked() {
    if(ui->szukajPracownicyWizytaLineEdit->text().length() > 0){
        QList<Pracownik*> pracownicyKryteria = przychodnia->zwrocPracownikow(ui->szukajPracownicyWizytaLineEdit->text());
        this->wyswietlListePracownikow(pracownicyKryteria, ui->pracownicyWizytaTableView);
    }else {
        this->wyswietlListePracownikow(przychodnia->zwrocPracownikow(), ui->pracownicyWizytaTableView);
    }
}

void MainWindow::on_szukajPacjentaBtn_clicked() {
    if(ui->szukajPacjentaLineEdit->text().length() > 0){
        QList<Pacjent*> pacjenciKryteria = przychodnia->zwrocPacjentow(ui->szukajPacjentaLineEdit->text());
        this->wyswietlListePacjentow(pacjenciKryteria, ui->pacjenciTableView);
    }else {
        this->wyswietlListePacjentow(przychodnia->zwrocPacjentow(), ui->pacjenciTableView);
    }
}

void MainWindow::on_szukajPracownikaKompetencjeBtn_clicked() {
    if(ui->szukajPracownikaKompetencjeLineEdit->text().length() > 0){
        QList<Pracownik*> pracownicyKryteria = przychodnia->zwrocPracownikow(ui->szukajPracownikaKompetencjeLineEdit->text());
        this->wyswietlListePracownikow(pracownicyKryteria, ui->pracownicyKompetencjeTableView);
    }else {
        this->wyswietlListePracownikow(przychodnia->zwrocPracownikow(), ui->pracownicyKompetencjeTableView);
    }
}

void MainWindow::on_szukajZabieguBtn_clicked() {
    if(ui->szukajZabieguLineEdit->text().length() > 0){
        QList<Zabieg*> zabiegiKryteria = przychodnia->zwrocZabiegi(ui->szukajZabieguLineEdit->text());
        this->wyswietlListeZabiegow(zabiegiKryteria, ui->zabiegiTableView);
    }else {
        this->wyswietlListeZabiegow(przychodnia->zwrocZabiegi(), ui->zabiegiTableView);
    }
}

void MainWindow::on_szukajPracownikaBtn_clicked() {
    if(ui->szukajPracownikaLineEdit->text().length() > 0){
        QList<Pracownik*> pracownicyKryteria = przychodnia->zwrocPracownikow(ui->szukajPracownikaLineEdit->text());
        this->wyswietlListePracownikow(pracownicyKryteria, ui->pracownicyTableView);
    }else {
        this->wyswietlListePracownikow(przychodnia->zwrocPracownikow(), ui->pracownicyTableView);
    }
}

void MainWindow::on_dodajPracownikaPracownicyBtn_clicked() {
    przychodnia->dodajPracownika(ui->pracownikImieLineEdit->text(), ui->pracownikNazwiskoLineEdit->text(), ui->pracownikKodLogowaniaLineEdit->text());
    this->wyswietlListePracownikow(przychodnia->zwrocPracownikow(), ui->pracownicyTableView);
}

void MainWindow::on_pracownicyTableView_clicked(const QModelIndex &index) {
    QList<QString> danePracownika;
    for(auto i = 0; i < index.model()->columnCount(); i++){
        danePracownika.append(index.model()->data(index.model()->index(index.row(), i)).toString());
    }
    QList<QLineEdit*> lineEdits = ui->danePracownikaGroupBox->findChildren<QLineEdit*>();
    int i = 0;
    foreach(QLineEdit* line, lineEdits) {
        line->setText(danePracownika.at(i));
        i++;
    }
    i = 0;
    modyfikowanyPracownik = przychodnia->szukajPracownika(danePracownika.at(0), danePracownika.at(1), danePracownika.at(2));
    QList<GodzinyPracy*> godzPracyModyfikowanego = modyfikowanyPracownik->getGodzinyPracy();
    if(godzPracyModyfikowanego.length() > 0){
        lineEdits = ui->godzinyPracownikaGroupBox->findChildren<QLineEdit*>();

        foreach(GodzinyPracy *godz, godzPracyModyfikowanego){
            lineEdits.at(i)->setText(godzinaDoPolaTekstowego(godz->getGodzinaOd()->toString()));
            lineEdits.at(i+1)->setText(godzinaDoPolaTekstowego(godz->getGodzinaDo()->toString()));
            i+=2;
        }
    }
}


void MainWindow::on_modyfikujPracownikaPracownicyBtn_clicked() {
    if(modyfikowanyPracownik != nullptr){
        przychodnia->modyfikujPracownika(modyfikowanyPracownik, ui->pracownikImieLineEdit->text(), ui->pracownikNazwiskoLineEdit->text(), ui->pracownikKodLogowaniaLineEdit->text());
        this->wyswietlListePracownikow(przychodnia->zwrocPracownikow(), ui->pracownicyTableView);
    }
}

void MainWindow::on_pracownikWyczyscBtn_clicked() {
    QList<QLineEdit*> lineEdits = ui->danePracownikaGroupBox->findChildren<QLineEdit*>();
    foreach(QLineEdit* line, lineEdits) {
        line->setText("");
    }
    modyfikowanyPracownik = nullptr;
    ui->pracownicyTableView->clearSelection();
}

void MainWindow::on_usunPracownikaBtn_clicked() {
    if(modyfikowanyPracownik != nullptr){
        przychodnia->usunPracownika(modyfikowanyPracownik);
        this->wyswietlListePracownikow(przychodnia->zwrocPracownikow(), ui->pracownicyTableView);
        on_pracownikWyczyscBtn_clicked();
    }
}

void MainWindow::on_ustawSchemat715_clicked() {
    wypelnijPolaGodzinPracy("07:00", "15:00");
}

void MainWindow::on_ustawSchemat816_clicked()
{
    wypelnijPolaGodzinPracy("08:00", "16:00");
}

void MainWindow::on_ustawSchemat917_clicked()
{
    wypelnijPolaGodzinPracy("09:00", "17:00");
}

void MainWindow::on_ustawSchemat1018_clicked()
{
    wypelnijPolaGodzinPracy("10:00", "18:00");
}

void MainWindow::on_ustawSchemat1119_clicked()
{
    wypelnijPolaGodzinPracy("11:00", "19:00");
}

void MainWindow::on_godzinyPracyWyczyscBtn_clicked() {
    wypelnijPolaGodzinPracy("", "");
    on_pracownikWyczyscBtn_clicked();
}

void MainWindow::on_godzinyPracyZatwierdzBtn_clicked() {
    QList<QString> dniTygodnia;
    dniTygodnia << "Poniedziałek" << "Wtorek" << "Środa" << "Czwartek" << "Piątek";
    if(modyfikowanyPracownik != nullptr){
        QList<QLineEdit*> lineEdits = ui->godzinyPracownikaGroupBox->findChildren<QLineEdit*>();
        int i = 0;
        foreach(QString dzien, dniTygodnia){
            przychodnia->zmienGodzinyPracyPracownika(modyfikowanyPracownik, dzien, lineEdits.at(i)->text(), lineEdits.at(i+1)->text());
            i+=2;
        }
    }
}


void MainWindow::on_zabiegiTableView_clicked(const QModelIndex &index) {
    QList<QString> daneZabiegu;
    for(auto i = 0; i < index.model()->columnCount(); i++){
        daneZabiegu.append(index.model()->data(index.model()->index(index.row(), i)).toString());
    }
    QList<QLineEdit*> lineEdits = ui->daneZabieguGroupBox->findChildren<QLineEdit*>();
    int i = 0;
    foreach(QLineEdit* line, lineEdits) {
        line->setText(usunDodatkoweInfo(daneZabiegu.at(i)));
        i++;
    }
    ui->opisZabiegiLineEdit->setText(daneZabiegu.last());
    modyfikowanyZabieg = przychodnia->szukajZabiegu(daneZabiegu.at(0),usunDodatkoweInfo(daneZabiegu.at(1)).toDouble(),usunDodatkoweInfo(daneZabiegu.at(2)).toDouble(),daneZabiegu.at(3));
}

void MainWindow::on_zabiegiWyczyscBtn_clicked() {
    QList<QLineEdit*> lineEdits = ui->daneZabieguGroupBox->findChildren<QLineEdit*>();
    foreach(QLineEdit* line, lineEdits) {
        line->setText("");
    }
    ui->opisZabiegiLineEdit->setText("");
    modyfikowanyZabieg = nullptr;
    ui->zabiegiTableView->clearSelection();
}

void MainWindow::on_zabiegiUsunBtn_clicked() {
    if(modyfikowanyZabieg != nullptr){
        przychodnia->usunZabieg(modyfikowanyZabieg);
        this->wyswietlListeZabiegow(przychodnia->zwrocZabiegi(), ui->zabiegiTableView);
        on_zabiegiWyczyscBtn_clicked();
    }
}

void MainWindow::on_zabiegiDodajBtn_clicked() {
    przychodnia->dodajZabieg(ui->nazwaZabiegiLineEdit->text(), usunDodatkoweInfo(ui->cenaZabiegiLineEdit->text()).toDouble(), usunDodatkoweInfo(ui->czasZabiegiLineEdit->text()).toDouble(), ui->opisZabiegiLineEdit->toPlainText());
    this->wyswietlListeZabiegow(przychodnia->zwrocZabiegi(), ui->zabiegiTableView);
}

void MainWindow::on_zabiegiModyfikujBtn_clicked() {
    if(modyfikowanyZabieg != nullptr){
        przychodnia->modyfikujZabieg(modyfikowanyZabieg, ui->nazwaZabiegiLineEdit->text(), usunDodatkoweInfo(ui->cenaZabiegiLineEdit->text()).toDouble(), usunDodatkoweInfo(ui->czasZabiegiLineEdit->text()).toDouble(), ui->opisZabiegiLineEdit->toPlainText());
        this->wyswietlListeZabiegow(przychodnia->zwrocZabiegi(), ui->zabiegiTableView);
    }
}


void MainWindow::on_pacjenciWyczyscBtn_clicked() {
    QList<QLineEdit*> lineEdits = ui->danePacjentaGroupBox->findChildren<QLineEdit*>();
    foreach(QLineEdit* line, lineEdits) {
        line->setText("");
    }
    modyfikowanyPacjent = nullptr;
    ui->pacjenciTableView->clearSelection();
}

void MainWindow::on_pacjenciTableView_clicked(const QModelIndex &index) {
    QList<QString> danePacjenta;
    for(auto i = 0; i < index.model()->columnCount(); i++){
        danePacjenta.append(index.model()->data(index.model()->index(index.row(), i)).toString());
    }
    QList<QLineEdit*> lineEdits = ui->danePacjentaGroupBox->findChildren<QLineEdit*>();
    int i = 0;
    foreach(QLineEdit* line, lineEdits) {
        line->setText(danePacjenta.at(i));
        i++;
    }
    modyfikowanyPacjent = przychodnia->szukajPacjenta(danePacjenta.at(0),danePacjenta.at(1),danePacjenta.at(2),danePacjenta.at(3),danePacjenta.at(4),danePacjenta.at(5).toInt(),danePacjenta.at(6).toInt(),danePacjenta.at(7));
}

void MainWindow::on_pacjenciUsunBtn_clicked() {
    if(modyfikowanyPacjent != nullptr){
        przychodnia->usunPacjenta(modyfikowanyPacjent);
        this->wyswietlListePacjentow(przychodnia->zwrocPacjentow(), ui->pacjenciTableView);
        on_pacjenciWyczyscBtn_clicked();
    }
}

void MainWindow::on_modyfikujDanePacjentaBtn_clicked() {
    if(modyfikowanyPacjent != nullptr){
        przychodnia->modyfikujPacjenta(modyfikowanyPacjent, ui->imiePacjenciLineEdit->text(), ui->nazwiskoPacjenciLineEdit->text(), ui->emailPacjenciLineEdit->text(), ui->telefonPacjenciLineEdit->text(), ui->ulicaPacjenciLineEdit->text(), ui->numerPacjenciLineEdit->text().toInt(), ui->kodPacjenciLineEdit->text().toInt(), ui->miejscowoscPacjenciLineEdit->text());
        this->wyswietlListePacjentow(przychodnia->zwrocPacjentow(), ui->pacjenciTableView);
    }
}

void MainWindow::on_pacjenciDodajBtn_clicked() {
    przychodnia->dodajPacjenta(ui->imiePacjenciLineEdit->text(), ui->nazwiskoPacjenciLineEdit->text(), ui->emailPacjenciLineEdit->text(), ui->telefonPacjenciLineEdit->text(), ui->ulicaPacjenciLineEdit->text(), ui->numerPacjenciLineEdit->text().toInt(), ui->kodPacjenciLineEdit->text().toInt(), ui->miejscowoscPacjenciLineEdit->text());
    this->wyswietlListePacjentow(przychodnia->zwrocPacjentow(), ui->pacjenciTableView);
}

void MainWindow::on_pracownicyKompetencjeTableView_clicked(const QModelIndex &index) {
    QList<QString> danePracownika;
    for(auto i = 0; i < index.model()->columnCount(); i++){
        danePracownika.append(index.model()->data(index.model()->index(index.row(), i)).toString());
    }
    QList<QLineEdit*> lineEdits = ui->danePracKompetencjeGroupBox->findChildren<QLineEdit*>();
    int i = 0;
    foreach(QLineEdit* line, lineEdits) {
        line->setText(danePracownika.at(i));
        i++;
    }
    modyfikowanyPracownik = przychodnia->szukajPracownika(danePracownika.at(0), danePracownika.at(1), danePracownika.at(2));
    this->wyswietlListeZabiegow(modyfikowanyPracownik->kompetencjePracownika(), ui->przeglKompetencjiTableView);
    this->wyswietlListeZabiegow(przychodnia->zwrocZabiegiNiedozwoloneDla(modyfikowanyPracownik), ui->rozszKompetencjiTableView);
}

void MainWindow::on_przeglKompetencjiTableView_doubleClicked(const QModelIndex &index) {
    QList<QString> daneZabiegu;
    for(auto i = 0; i < index.model()->columnCount(); i++){
        daneZabiegu.append(index.model()->data(index.model()->index(index.row(), i)).toString());
    }
    Zabieg *nowaKompetencja = przychodnia->szukajZabiegu(daneZabiegu.at(0),usunDodatkoweInfo(daneZabiegu.at(1)).toDouble(),usunDodatkoweInfo(daneZabiegu.at(2)).toDouble(),daneZabiegu.at(3));
    if(modyfikowanyPracownik != nullptr && nowaKompetencja != nullptr){
        modyfikowanyPracownik->usunKompetencje(nowaKompetencja);
    }
    this->wyswietlListeZabiegow(modyfikowanyPracownik->kompetencjePracownika(), ui->przeglKompetencjiTableView);
    this->wyswietlListeZabiegow(przychodnia->zwrocZabiegiNiedozwoloneDla(modyfikowanyPracownik), ui->rozszKompetencjiTableView);
}

void MainWindow::on_rozszKompetencjiTableView_doubleClicked(const QModelIndex &index) {
    QList<QString> daneZabiegu;
    for(auto i = 0; i < index.model()->columnCount(); i++){
        daneZabiegu.append(index.model()->data(index.model()->index(index.row(), i)).toString());
    }
    Zabieg *nowaKompetencja = przychodnia->szukajZabiegu(daneZabiegu.at(0),usunDodatkoweInfo(daneZabiegu.at(1)).toDouble(),usunDodatkoweInfo(daneZabiegu.at(2)).toDouble(),daneZabiegu.at(3));
    if(modyfikowanyPracownik != nullptr && nowaKompetencja != nullptr){
        modyfikowanyPracownik->dodajKompetencje(nowaKompetencja);
    }
    this->wyswietlListeZabiegow(modyfikowanyPracownik->kompetencjePracownika(), ui->przeglKompetencjiTableView);
    this->wyswietlListeZabiegow(przychodnia->zwrocZabiegiNiedozwoloneDla(modyfikowanyPracownik), ui->rozszKompetencjiTableView);
}

void MainWindow::on_pacjenciWizytaTableView_clicked(const QModelIndex &index) {
    danePacjenta.clear();
    for(auto i = 0; i < index.model()->columnCount(); i++){
        danePacjenta.append(index.model()->data(index.model()->index(index.row(), i)).toString());
    }
    ui->danePacjentaLineEdit->setText(danePacjenta.at(0)+" "+danePacjenta.at(1));
    if(daneTerminu.length() > 0 && daneZabiegu.length() > 0 && danePacjenta.length() > 0 && danePracownika.length() > 0 && ui->godzinaWizytyLineEdit->text().length() > 0){
        ui->umowWizyteBtn->setEnabled(true);
    }else {
        ui->umowWizyteBtn->setEnabled(false);
    }
}

void MainWindow::on_zabiegiWizytaTableView_clicked(const QModelIndex &index) {
    daneZabiegu.clear();
    for(auto i = 0; i < index.model()->columnCount(); i++){
        if(i != 0 && i != 3){
            daneZabiegu.append(usunDodatkoweInfo(index.model()->data(index.model()->index(index.row(), i)).toString()));
        }else {
            daneZabiegu.append(index.model()->data(index.model()->index(index.row(), i)).toString());
        }

    }
    ui->daneZabieguLineEdit->setText(daneZabiegu.at(0)+" "+daneZabiegu.at(1));
    if(daneTerminu.length() > 0 && daneZabiegu.length() > 0 && danePacjenta.length() > 0 && danePracownika.length() > 0 && ui->godzinaWizytyLineEdit->text().length() > 0){
        ui->umowWizyteBtn->setEnabled(true);
    }else {
        ui->umowWizyteBtn->setEnabled(false);
    }
}

void MainWindow::on_pracownicyWizytaTableView_clicked(const QModelIndex &index) {
    danePracownika.clear();
    for(auto i = 0; i < index.model()->columnCount(); i++){
        danePracownika.append(index.model()->data(index.model()->index(index.row(), i)).toString());
    }
    ui->danePracownikaLineEdit->setText(danePracownika.at(0)+" "+danePracownika.at(1));
    if(ui->daneTerminuLineEdit->text().length() > 0){
        uaktywnijPrzyciskiGodziny();
    }
    if(daneTerminu.length() > 0 && daneZabiegu.length() > 0 && danePacjenta.length() > 0 && danePracownika.length() > 0 && ui->godzinaWizytyLineEdit->text().length() > 0){
        ui->umowWizyteBtn->setEnabled(true);
    }else {
        ui->umowWizyteBtn->setEnabled(false);
    }
}

void MainWindow::on_calendarWidget_clicked(const QDate &date) {
    ui->daneTerminuLineEdit->setText(QString::number(date.day()) + "." + QString::number(date.month()) + "." + QString::number(date.year()));
    daneTerminu.clear();
    daneTerminu.append(date.day());
    daneTerminu.append(date.month());
    daneTerminu.append(date.year());
    if(ui->danePracownikaLineEdit->text().length() > 0){
        uaktywnijPrzyciskiGodziny();
    }
    if(daneTerminu.length() > 0 && daneZabiegu.length() > 0 && danePacjenta.length() > 0 && danePracownika.length() > 0 && ui->godzinaWizytyLineEdit->text().length() > 0){
        ui->umowWizyteBtn->setEnabled(true);
    }else {
        ui->umowWizyteBtn->setEnabled(false);
    }
}

void MainWindow::on_umowWizyteBtn_clicked() {
    daneTerminu.append(daneGodziny);
    if(przychodnia->umowWizyte(danePacjenta, daneZabiegu, danePracownika, daneTerminu)){
        QMessageBox::information(nullptr, "Sukces", "Pomyślnie wprowadzono wizytę");
    }
    on_wyczyscWizyteBtn_clicked();
}


void MainWindow::on_toolButton_clicked() {
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}

void MainWindow::on_toolButton_2_clicked() {
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}

void MainWindow::on_toolButton_3_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}

void MainWindow::on_toolButton_4_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}

void MainWindow::on_toolButton_5_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}

void MainWindow::on_toolButton_6_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}

void MainWindow::on_toolButton_7_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}

void MainWindow::on_toolButton_8_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}

void MainWindow::on_toolButton_9_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}

void MainWindow::on_toolButton_10_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}

void MainWindow::on_toolButton_11_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}

void MainWindow::on_toolButton_12_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}

void MainWindow::on_toolButton_13_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}

void MainWindow::on_toolButton_14_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}

void MainWindow::on_toolButton_15_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}

void MainWindow::on_toolButton_16_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}
void MainWindow::on_toolButton_17_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}
void MainWindow::on_toolButton_18_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}
void MainWindow::on_toolButton_19_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}
void MainWindow::on_toolButton_20_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}
void MainWindow::on_toolButton_21_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}
void MainWindow::on_toolButton_22_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}
void MainWindow::on_toolButton_23_clicked()
{
    QToolButton *btn = (QToolButton*)sender();
    uaktywnijPrzycisk(btn);
}

void MainWindow::on_wyczyscWizyteBtn_clicked() {
    daneZabiegu.clear();
    daneGodziny.clear();
    daneTerminu.clear();
    danePacjenta.clear();
    danePracownika.clear();
    ui->pacjenciWizytaTableView->clearSelection();
    ui->pracownicyWizytaTableView->clearSelection();
    ui->zabiegiWizytaTableView->clearSelection();
    ui->calendarWidget->clearFocus();
    ui->daneTerminuLineEdit->setText("");
    ui->daneZabieguLineEdit->setText("");
    ui->danePacjentaLineEdit->setText("");
    ui->danePracownikaLineEdit->setText("");
    ui->godzinaWizytyLineEdit->setText("");
    QList<QToolButton*> tbtns = ui->godzinyGroupBox->findChildren<QToolButton*>();
    foreach(QToolButton *tb, tbtns){
        tb->setStyleSheet(tb->styleSheet().replace("rgb(192,19,0)", "rgb(0,51,102)"));
        tb->setEnabled(false);
    }
}
