#pragma once
#include <QMessageBox>
#include <QWidget>
#include <QVBoxLayout>
#include <QLayoutItem>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QDebug>
#include <QListWidget>
#include <QTableWidget>
#include <QRadioButton>
#include <QHeaderView>
#include <QSplitter>
#include <qdebug.h>
#include <qmessagebox.h>
#include "validator.h"
#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QStringList>
#include <vector>
#include <QWidget>
#include <QPainter>
#include <QImage>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "ListaNotificare.h"
#include "Locatar.h"
#include "Service.h"
#include <QRandomGenerator>
#include "Observer.h"
#include "MyListModel.h"
#include <QListView>


//clasa pentru Cos Read Only 
class CosReadOnlyGUI : public QWidget, public Observer {
public:
    CosReadOnlyGUI(ListaNOT& list) :listContract{ list } {
        listContract.addObserver(this);
    };
private:
    ListaNOT& listContract; //service filme

    vector<Locatar> locatari = listContract.get_List();

    void paintEvent(QPaintEvent* ev) override
    {
        QPainter p{ this };

        int i = 0;
        for (const auto& f : locatari)
        {
            if (i % 3 == 0)
            {
                // Generez coordonatele aleatoriu pentru pozitia elipsei
                int x = QRandomGenerator::global()->bounded(width() - 100);  // Latimea ferestrei minus latimea elipsei
                int y = QRandomGenerator::global()->bounded(height() - 100); // Inaltimea ferestrei minus inaltimea elipsei

                // Desenez elipsa la poztia aleatoare generata
                p.drawEllipse(x, y, 100, 100);
            }

            if (i % 3 == 1)
            {
                // Generez coordonatele aleatoriu pentru pozitia elipsei
                int x = QRandomGenerator::global()->bounded(width() - 100);  // Latimea ferestrei minus latimea elipsei
                int y = QRandomGenerator::global()->bounded(height() - 100); // Inaltimea ferestrei minus inaltimea elipsei

                // Desenez dreptunghiul la poztia aleatoare generata
                p.drawRect(x, y, 100, 50);
            }

            if (i % 3 == 2)
            {
                // Genereaza coordonate aleatoare pentru varfurile triunghiului
                int x1 = QRandomGenerator::global()->bounded(width() - 100);  // Coordonata x a primului varf
                int y1 = QRandomGenerator::global()->bounded(height() - 100); // Coordonata y a primului varf
                int x2 = QRandomGenerator::global()->bounded(width() - 100);  // Coordonata x a celui de-al doilea varf
                int y2 = QRandomGenerator::global()->bounded(height() - 100); // Coordonata y a celui de-al doilea varf
                int x3 = QRandomGenerator::global()->bounded(width() - 100);  // Coordonata x a celui de-al treilea varf
                int y3 = QRandomGenerator::global()->bounded(height() - 100); // Coordonata y a celui de-al treilea varf

                // Definirea varfurilor triunghiului
                QVector<QPoint> points;
                points << QPoint(x1, y1) << QPoint(x2, y2) << QPoint(x3, y3);

                // Desenez triunghiul cu varfurile date
                p.drawPolygon(points);
            }

            i++;
        }
    }

    void update() override
    {
        locatari = listContract.get_List();
        repaint(); //reincarc LOCATARII dupa operatie
    }
};


//Clasa pentru raport
class MapWindow : public QWidget{
public:
    MapWindow(const map<string, DTOLocatar> mp, QWidget* parent = nullptr)
        : QWidget(parent)
    {
        QTableWidget* tableWidget = new QTableWidget(this);
        tableWidget->setColumnCount(2);

        QStringList headers = { "Tip", "Numar de aparitii"};
        tableWidget->setHorizontalHeaderLabels(headers);

        int row = 0;
        for (const auto& elem : mp) {
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(elem.first)));
            tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(to_string(elem.second.getCount()))));
            ++row;
        }

        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(tableWidget);
    }
};


//Clasa care formeaza o fereastra de tip tabel
//@param locatari - vector<Locatar> pe care il punem in tabel
class TableWindow : public QWidget {
public:
    TableWindow(const std::vector<Locatar>& locatari, QWidget* parent = nullptr)
        : QWidget(parent)
    {
        QTableWidget* tableWidget = new QTableWidget(this);
        tableWidget->setColumnCount(4); 

        QStringList headers = { "Apartament", "Nume Proprietar", "Suprafață", "Tip" };
        tableWidget->setHorizontalHeaderLabels(headers);

        int row = 0;
        for (const auto& locatar : locatari) {
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(locatar.get_apartament())));
            tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(locatar.get_nume_proprietar())));
            tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(locatar.get_suprafata())));
            tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(locatar.get_tip())));
            ++row;
        }

        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(tableWidget);
    }
};


//Clasa pentru fereastra listei de asteptare
class ContractGui :public QWidget, public Observer {
public:
    ContractGui(LocatarService& serv, ListaNOT& list) :servContract{ serv }, listContract{ list } {
        listContract.addObserver(this);
        initContractGUI();
        loadDateContract();
        initConectContract();
    }
private:
    LocatarService& servContract;
    ListaNOT& listContract;
    QListWidget* contract_list = new QListWidget;

    //Butoane
    QPushButton* btnAddC = new QPushButton{ "&Adauga" };
    QPushButton* btnGol = new QPushButton{ "&Goleste" };
    QPushButton* btnGen = new QPushButton{ "Genereaza" };
    QPushButton* btnExp = new QPushButton{ "Export" };
    QPushButton* btnExit = new QPushButton{ "&Exit" };

    //Linii
    QLineEdit* txtNume = new QLineEdit;
    QLineEdit* txtTip = new QLineEdit;
    QLineEdit* txtSuprafatat = new QLineEdit;
    QLineEdit* txtApartament = new QLineEdit;
    QLineEdit* txtGen = new QLineEdit;
    QLineEdit* txtExp = new QLineEdit;

    //Initializare fereastra
    void initContractGUI();

    //Actualizam lista
    void loadDateContract();

    //Facem conexiuni
    void initConectContract();

    void update() override
    {
        loadDateContract(); //reincarc LOCATARII dupa operatie
    }
};


//Fereastra principala
class AppGui :public QWidget {
public:
    //Constructorul
    AppGui(LocatarService& serv, ListaNOT& list) :serv{ serv }, list{ list } {
        initGUI();
        loadDate();
        loadDateAPPContract();
        initConect();
    }
private:
    LocatarService& serv;
    ListaNOT& list;
    QListWidget* cos = new QListWidget;
    QListWidget* lst = new QListWidget;
    QHBoxLayout* lyBtnType = new QHBoxLayout;
    QHBoxLayout* ly = new QHBoxLayout{};

    QListView* lst_view = new QListView;
    MyListModel* model;


    QPushButton* btnAddC = new QPushButton{ "&Adauga" };
    QPushButton* btnGen = new QPushButton{ "Genereaza" };


    //Butoane si linii
    QRadioButton* prop = new QRadioButton{ "Nume Proprietar" };
    QRadioButton* sup = new QRadioButton{ "Suprafata" };
    QRadioButton* tipSup = new QRadioButton{ "Tip+Suprafata" };
    QRadioButton* tip = new QRadioButton{ "Tip" };
    QPushButton* btnAdd = new QPushButton{ "&Adauga" };
    QPushButton* btnUndo = new QPushButton{ "&Undo" };
    QPushButton* btnC = new QPushButton{ "&Cauta" };
    QPushButton* btnRap = new QPushButton{ "&Raport" };
    QPushButton* btnSort = new QPushButton{ "&Sort" };
    QPushButton* btnF = new QPushButton{ "&Filtreaza" };
    QPushButton* btnAfiseaza = new QPushButton{ "Afiseaza" };
    QPushButton* btnLst = new QPushButton{ "Cos-CRUD" };
    QPushButton* btnLst2 = new QPushButton{ "Cos-ReadOnly" };
    QPushButton* btnExit = new QPushButton{ "&Exit" }; 
    QPushButton* btnSterge  = new QPushButton{ "&Sterge" };
    QPushButton* btnStergeC = new QPushButton{ "&Sterge" };
    QPushButton* btnMod = new QPushButton{ "&Modifica" };
    QLineEdit* txtNume = new QLineEdit;
    QLineEdit* txtTip = new QLineEdit;
    QLineEdit* txtSuprafatat = new QLineEdit;
    QLineEdit* txtApartament = new QLineEdit;
    QLineEdit* txtGen = new QLineEdit;

    //Initializare conexiuni
    void initConect();

    //Actualizam lista
    void loadDate();

    //Initializam fereastra
    void initGUI();

    void reloadList(const vector<Locatar>& all);

    //Initializez fereastra pentru genuri
    void handleTypeButtonClicked(const std::string& type);

    void loadDateAPPContract();

};