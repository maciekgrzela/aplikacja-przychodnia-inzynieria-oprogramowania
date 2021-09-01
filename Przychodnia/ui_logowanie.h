/********************************************************************************
** Form generated from reading UI file 'logowanie.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGOWANIE_H
#define UI_LOGOWANIE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Logowanie
{
public:
    QFrame *frame;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QLabel *label_4;
    QVBoxLayout *verticalLayout;
    QLineEdit *kodLogowaniaLineEdit;
    QLineEdit *hasloLineEdit;
    QPushButton *zalogujBtn;
    QPushButton *zamknijBtn;
    QLabel *wrongLoginDataLabel;

    void setupUi(QDialog *Logowanie)
    {
        if (Logowanie->objectName().isEmpty())
            Logowanie->setObjectName(QStringLiteral("Logowanie"));
        Logowanie->resize(432, 300);
        Logowanie->setStyleSheet(QStringLiteral(""));
        frame = new QFrame(Logowanie);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 0, 190, 300));
        frame->setStyleSheet(QStringLiteral("background-color: rgb(0,51,102);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(43, 175, 103, 23));
        QFont font;
        font.setFamily(QStringLiteral("Fira Sans Light"));
        font.setPointSize(14);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral("color: rgb(255,255,255);"));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(62, 100, 61, 61));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/icons/img_rc/calendar-7.png")));
        label_2->setScaledContents(true);
        groupBox = new QGroupBox(Logowanie);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(212, 80, 201, 101));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(23, 30, 159, 50));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_2->addWidget(label_3);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_2->addWidget(label_4);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        kodLogowaniaLineEdit = new QLineEdit(layoutWidget);
        kodLogowaniaLineEdit->setObjectName(QStringLiteral("kodLogowaniaLineEdit"));

        verticalLayout->addWidget(kodLogowaniaLineEdit);

        hasloLineEdit = new QLineEdit(layoutWidget);
        hasloLineEdit->setObjectName(QStringLiteral("hasloLineEdit"));
        hasloLineEdit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(hasloLineEdit);


        horizontalLayout->addLayout(verticalLayout);

        zalogujBtn = new QPushButton(Logowanie);
        zalogujBtn->setObjectName(QStringLiteral("zalogujBtn"));
        zalogujBtn->setGeometry(QRect(260, 260, 75, 23));
        zalogujBtn->setAutoFillBackground(false);
        zalogujBtn->setStyleSheet(QLatin1String("background-color: rgb(40,167,69);\n"
"color: rgb(255,255,255);\n"
"border: none;"));
        zalogujBtn->setAutoDefault(false);
        zalogujBtn->setFlat(true);
        zamknijBtn = new QPushButton(Logowanie);
        zamknijBtn->setObjectName(QStringLiteral("zamknijBtn"));
        zamknijBtn->setGeometry(QRect(340, 260, 75, 23));
        zamknijBtn->setAutoFillBackground(false);
        zamknijBtn->setStyleSheet(QLatin1String("background-color: rgb(220,53,69);\n"
"color: rgb(255,255,255);\n"
"border: none;"));
        zamknijBtn->setAutoDefault(false);
        zamknijBtn->setFlat(true);
        wrongLoginDataLabel = new QLabel(Logowanie);
        wrongLoginDataLabel->setObjectName(QStringLiteral("wrongLoginDataLabel"));
        wrongLoginDataLabel->setGeometry(QRect(187, 0, 251, 41));
        QFont font1;
        font1.setFamily(QStringLiteral("Fira Sans Light"));
        font1.setPointSize(10);
        wrongLoginDataLabel->setFont(font1);
        wrongLoginDataLabel->setStyleSheet(QLatin1String("background-color: rgb(220,53,69);\n"
"color: rgb(255,255,255);"));
        wrongLoginDataLabel->setAlignment(Qt::AlignCenter);
        wrongLoginDataLabel->raise();
        frame->raise();
        groupBox->raise();
        zalogujBtn->raise();
        zamknijBtn->raise();

        retranslateUi(Logowanie);

        QMetaObject::connectSlotsByName(Logowanie);
    } // setupUi

    void retranslateUi(QDialog *Logowanie)
    {
        Logowanie->setWindowTitle(QApplication::translate("Logowanie", "Aplikacja Przychodnia v1.0.0", Q_NULLPTR));
        label->setText(QApplication::translate("Logowanie", "Przychodnia", Q_NULLPTR));
        label_2->setText(QString());
        groupBox->setTitle(QApplication::translate("Logowanie", "Zaloguj si\304\231", Q_NULLPTR));
        label_3->setText(QApplication::translate("Logowanie", "Kod:", Q_NULLPTR));
        label_4->setText(QApplication::translate("Logowanie", "Has\305\202o:", Q_NULLPTR));
        zalogujBtn->setText(QApplication::translate("Logowanie", "Zaloguj", Q_NULLPTR));
        zamknijBtn->setText(QApplication::translate("Logowanie", "Zamknij", Q_NULLPTR));
        wrongLoginDataLabel->setText(QApplication::translate("Logowanie", "<html><head/><body><p><span style=\" font-weight:600;\">B\305\202\304\205d: </span>Niepoprawne dane logowania</p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Logowanie: public Ui_Logowanie {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGOWANIE_H
