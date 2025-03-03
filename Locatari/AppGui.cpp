#include "AppGui.h"
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
#include "Service.h"
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
#include <set>
#include "ListaNotificare.h"

//Initializare fereastra din lista de notificare
void ContractGui::initContractGUI() {
    setWindowTitle("Lista de notificare");
    QPalette pallete = QPalette();

    QHBoxLayout* ly = new QHBoxLayout{};
    setLayout(ly);
    ly->addWidget(contract_list);

    //Boxuri
    auto stg = new QVBoxLayout;
    auto form = new QFormLayout;
    auto lyBtnn = new QHBoxLayout;
    auto lyBtnR = new QHBoxLayout;
    auto lyBtn = new QHBoxLayout;

    //Adaugam linile
    form->addRow("Apartament", txtApartament);
    form->addRow("Nume Proprietar", txtNume);
    form->addRow("Suprafata", txtSuprafatat);
    form->addRow("Tip", txtTip);
    form->addRow("Numarul de apartamente generate", txtGen);
    form->addRow("Numele fisierului pentru export", txtExp);

    //Adaugam butoanele
    lyBtnn->addWidget(btnAddC);
    lyBtnn->addWidget(btnGol);
    lyBtnn->addWidget(btnGen);
    lyBtnn->addWidget(btnExp);
    lyBtnn->addWidget(btnExit);

    //Adaugam layout-urile
    stg->addLayout(form);
    stg->addLayout(lyBtnn);
    stg->addLayout(lyBtn);
    ly->addLayout(stg);
}

//Actualizam lista din lista de notificare
void ContractGui::loadDateContract() {
    contract_list->clear();
    vector<Locatar> all = listContract.get_List();
    for (const auto& pr : all) {
        contract_list->addItem(QString::fromStdString(pr.get_apartament() + " " + pr.get_nume_proprietar() + " " + pr.get_tip() + " " + to_string(pr.get_suprafata())));
    }
}

//Facem conexiuni pentru lista de notificare
void ContractGui::initConectContract() {

    QObject::connect(btnExit, &QPushButton::clicked, [&]() {
        qDebug() << "Exit buton apasat";
        QMessageBox::information(nullptr, "Info", "Va multumim, o zi buna!");
        close();
        });

    QObject::connect(btnAddC, &QPushButton::clicked, [&]() {
        auto nume = txtNume->text();
        auto tip = txtTip->text();
        auto suprafata = txtSuprafatat->text();
        auto apartament = txtApartament->text();
        const Locatar l = Locatar(apartament.toStdString(), nume.toStdString(), stod(suprafata.toStdString()), tip.toStdString());
        try {
            listContract.add_apartament(l);
            loadDateContract();
            qDebug() << "Locatar adaugat in lista cu succes";
        }
        catch (ListaException& ve) {
            QMessageBox::information(nullptr, "Info", ve.getMessage().c_str());
        }
        catch (ValidateException& ex) {
            //QMessageBox::information(nullptr, "Info", ex);
        }
        });

    QObject::connect(btnGol, &QPushButton::clicked, [&]() {
        listContract.empty_list();
        qDebug() << "Lista de notificare a fost golita cu succes!";
        loadDateContract();
        });

    QObject::connect(btnGen, &QPushButton::clicked, [&]() {
        auto gen = txtGen->text();
        listContract.generate_apartamente(stod(gen.toStdString()), servContract.getAll());
        qDebug() << "Lista de notificare a generat locatari cu succes!";
        loadDateContract();
        });

    QObject::connect(btnExp, &QPushButton::clicked, [&]() {
        auto exp = txtExp->text();
        listContract.export_list(exp.toStdString());
        qDebug() << "Lista de notificare a fost exportata cu succes!";
        });

}



//Initializare conexiuni pentru fereastra principala
void AppGui::initConect() {
    QObject::connect(btnStergeC, &QPushButton::clicked, [&]() {
        auto apartament = txtApartament->text();
        try {
            list.sterge(apartament.toStdString());
            loadDateAPPContract();
            qDebug() << "Locatar sters cu succes";
        }
        catch (ListaException& ve) {
            QMessageBox::information(nullptr, "Info", ve.getMessage().c_str());
        }
        });

    QObject::connect(btnGen, &QPushButton::clicked, [&]() {
        auto gen = txtGen->text();
        list.generate_apartamente(stod(gen.toStdString()), serv.getAll());
        loadDateAPPContract();
        qDebug() << "Lista de notificare a generat locatari cu succes!";
        });

    QObject::connect(btnAddC, &QPushButton::clicked, [&]() {
        auto nume = txtNume->text();
        auto tip = txtTip->text();
        auto suprafata = txtSuprafatat->text();
        auto apartament = txtApartament->text();
        const Locatar l = Locatar(apartament.toStdString(), nume.toStdString(), stod(suprafata.toStdString()), tip.toStdString());
        try {
            list.add_apartament(l);
            loadDateAPPContract();
            qDebug() << "Locatar adaugat in lista cu succes";
        }
        catch (ListaException& ve) {
            QMessageBox::information(nullptr, "Info", ve.getMessage().c_str());
        }
        });

    QObject::connect(btnExit, &QPushButton::clicked, [&]() {
        int s = 7;
        qDebug() << "Exit buton apasat" << "dfdf" << "\n" << s;
        QMessageBox::information(nullptr, "Info", "Va multumim, o zi buna!");
        close();
        });

    QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
        auto nume = txtNume->text();
        auto tip = txtTip->text();
        auto suprafata = txtSuprafatat->text();
        auto apartament = txtApartament->text();
        try {
            serv.add(apartament.toStdString(), nume.toStdString(), stod(suprafata.toStdString()), tip.toStdString());
            loadDate();
            reloadList(serv.getAll());
            qDebug() << "Locatar adaugat cu succes";
        }
        catch (RepoException& ve) {
            QMessageBox::information(nullptr, "Info", ve.getMessage().c_str());
            
        }
        catch (ValidateException& ex) {
            //QMessageBox::information(nullptr, "Info", ex);
        }
        });

    QObject::connect(btnSterge, &QPushButton::clicked, [&]() {
        auto apartament = txtApartament->text();
        try {
            serv.sterge(apartament.toStdString());
            loadDate();
            reloadList(serv.getAll());
            qDebug() << "Locatar sters cu succes";
        }
        catch (RepoException& ve) {
            QMessageBox::information(nullptr, "Info", ve.getMessage().c_str());
        }
        });

    QObject::connect(btnMod, &QPushButton::clicked, [&]() {
        auto apartament = txtApartament->text();
        auto nume = txtNume->text();
        try {
            serv.modifica(apartament.toStdString(), nume.toStdString());
            loadDate();
            reloadList(serv.getAll());
            qDebug() << "Locatar modificat cu succes";
        }
        catch (RepoException& ve) {
            QMessageBox::information(nullptr, "Info", ve.getMessage().c_str());
        }
        });

    QObject::connect(btnLst, &QPushButton::clicked, [&]() {
        //informatii
        ContractGui* conctr = new ContractGui(serv, list);
        conctr->setWindowTitle("Lista de notificare");
        conctr->resize(800, 300);
        conctr->show();
        });

    QObject::connect(btnLst2, &QPushButton::clicked, [&]() {
        //informatii
        CosReadOnlyGUI* conctract = new CosReadOnlyGUI(list);
        conctract->setWindowTitle("Lista de notificare");
        conctract->resize(800, 600);
        conctract->show();
        });

    QObject::connect(btnSort, &QPushButton::clicked, [&]() {
        //sortare
        if (prop->isChecked()) {
            vector<Locatar> loc = serv.sortNume();
            TableWindow* tableWindow = new TableWindow(loc);
            tableWindow->setWindowTitle("Tabel locuitori sortati dupa nume proprietar");
            tableWindow->resize(400, 300);
            tableWindow->show();
        }
        else
            if (sup->isChecked()) {
                vector<Locatar> loc = serv.sortSuprafata();
                TableWindow* tableWindow = new TableWindow(loc);
                tableWindow->setWindowTitle("Tabel locuitori sortati dupa suprafata");
                tableWindow->resize(500, 300);
                tableWindow->show();
            }
            else
                if (tipSup->isChecked()) {
                    vector<Locatar> loc = serv.sortTipSuprafata();
                    TableWindow* tableWindow = new TableWindow(loc);
                    tableWindow->setWindowTitle("Tabel locuitori sortati dupa tip+suprafata");
                    tableWindow->resize(500, 300);
                    tableWindow->show();
                }
                else {
                    QMessageBox::information(nullptr, "Info", "Criterul de sortare este invalid sau lipseste!");
                }


        });

    QObject::connect(btnAfiseaza, &QPushButton::clicked, [&]() {
        TableWindow* tableWindow = new TableWindow(serv.getAll());
        tableWindow->setWindowTitle("Tabel locuitori");
        tableWindow->resize(500, 300);
        tableWindow->show();
        });

    QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
        try {
            serv.Undo();
            loadDate();
            reloadList(serv.getAll());
            qDebug() << "Undo efectuat cu succes!";
        }
        catch (RepoException& ve) {
            QMessageBox::information(nullptr, "Info", ve.getMessage().c_str());
        }
        });

    QObject::connect(btnF, &QPushButton::clicked, [&]() {
        if (tip->isChecked()) {
            auto tip = txtTip->text();
            TableWindow* tableWindow = new TableWindow(serv.filtrareTip(tip.toStdString()));
            tableWindow->setWindowTitle("Tabel locuitori filtrati dupa tip");
            tableWindow->resize(500, 300);
            tableWindow->show();
        }
        else
            if (sup->isChecked()) {
                auto suprafata = txtSuprafatat->text();
                TableWindow* tableWindow = new TableWindow(serv.filtrareSuprafata(stod(suprafata.toStdString())));
                tableWindow->setWindowTitle("Tabel locuitori filtrati dupa suprafata");
                tableWindow->resize(500, 300);
                tableWindow->show();
            }
            else {
                QMessageBox::information(nullptr, "Info", "Criterul de filtrare este invalid sau lipseste!");
            }
        });

    QObject::connect(btnC, &QPushButton::clicked, [&]() {
        try {
            auto apartament = txtApartament->text();
            Locatar l = serv.cauta(apartament.toStdString());
            qDebug() << "Apartamentul a fost gasit!";
            vector<Locatar> loc;
            loc.push_back(l);

            TableWindow* tableWindow = new TableWindow(loc);
            tableWindow->setWindowTitle("Apartamentul cautat");
            tableWindow->resize(500, 100);
            tableWindow->show();

            
        }
        catch (RepoException& ve) {
            QMessageBox::information(nullptr, "Info", ve.getMessage().c_str());
        }
        });

    QObject::connect(btnRap, &QPushButton::clicked, [&]() {
        map<string, DTOLocatar> mp = serv.raport();
        MapWindow* tableWindow = new MapWindow(mp);
        tableWindow->setWindowTitle("Raport");
        tableWindow->resize(300, 200);
        tableWindow->show();
        });
}

//Actualizam lista
void AppGui::loadDate() {
    lst->clear();
    vector<Locatar> all = serv.getAll();
    for (const auto& pr : all) {
        lst->addItem(QString::fromStdString(pr.get_apartament() + " " + pr.get_nume_proprietar() + " " + pr.get_tip() + " " + to_string(pr.get_suprafata())));
    }
}

void AppGui::reloadList(const vector<Locatar>& all) {
    model->set(all);
}

//Initializam fereastra
void AppGui::initGUI() {
    //design 
    setWindowTitle("Locatari");
    resize(800, 300);
    QPalette pallete = QPalette();
    pallete.setColor(QPalette::Window, QColor(210, 60, 120));
    setAutoFillBackground(true);
    setPalette(pallete);

    //Boxuri
    
    auto stg = new QVBoxLayout;
    auto form = new QFormLayout;
    auto lyBtnn = new QHBoxLayout;
    auto lyBtnR = new QHBoxLayout;
    auto lyBtn = new QHBoxLayout;
    auto lyBtnType = new QHBoxLayout;
    auto lyBtnList = new QVBoxLayout;
    auto form2 = new QFormLayout;
    


    //Adaugam widget-urile pentru fiecare box
    form->addRow("Apartament", txtApartament);
    form->addRow("Nume Proprietar", txtNume);
    form->addRow("Suprafata", txtSuprafatat);
    form->addRow("Tip", txtTip);


    lyBtnn->addWidget(btnAdd);
    lyBtnn->addWidget(btnSterge);
    lyBtnn->addWidget(btnMod);
    lyBtnn->addWidget(btnC);
    lyBtnn->addWidget(btnUndo);


    lyBtnR->addWidget(prop);
    lyBtnR->addWidget(sup);
    lyBtnR->addWidget(tip);
    lyBtnR->addWidget(tipSup);


    stg->addLayout(form);
    stg->addWidget(new QLabel("Alegeti un criteriu pentru sortare sau filtrare!"));
    stg->addLayout(lyBtnR);
    stg->addLayout(lyBtnn);

    std::map<std::string, DTOLocatar> raport = serv.raport();
    for (const auto& entry : raport) {
        const std::string& tip = entry.first;
        QPushButton* typeButton = new QPushButton(QString::fromStdString(tip));
        lyBtnType->addWidget(typeButton);

        // Conectează fiecare buton la slot-ul de afișare a locatarilor pentru tipul respectiv
        QObject::connect(typeButton, &QPushButton::clicked, [this, tip]() {
            handleTypeButtonClicked(tip);
            });
    }

    lyBtn->addWidget(btnSort);
    lyBtn->addWidget(btnAfiseaza);
    lyBtn->addWidget(btnF);
    lyBtn->addWidget(btnRap);
    lyBtn->addWidget(btnExit);



    lyBtnList->addWidget(new QLabel("Lista de notificare:"));
    form2->addRow("Numarul generare", txtGen);
    lyBtnList->addLayout(form2);
    lyBtnList->addWidget(btnLst);
    lyBtnList->addWidget(btnLst2);
    lyBtnList->addWidget(btnAddC);
    lyBtnList->addWidget(btnStergeC);
    lyBtnList->addWidget(btnGen);

    model = new MyListModel{ serv.getAll() };
    lst_view->setModel(model);

    //Setam layout-urile
    setLayout(ly);
    ly->addWidget(lst_view);
    stg->addLayout(lyBtn);
    stg->addLayout(lyBtnType);
    ly->addLayout(stg);
    ly->addLayout(lyBtnList);

}

//Actualizam cosul
void AppGui::loadDateAPPContract() {
    cos->clear();
    vector<Locatar> all = list.get_List();
    for (const auto& pr : all) {
        cos->addItem(QString::fromStdString(pr.get_apartament() + " " + pr.get_nume_proprietar() + " " + pr.get_tip() + " " + to_string(pr.get_suprafata())));
    }
}

// Slot to handle button click
void AppGui::handleTypeButtonClicked(const std::string& type) {
    TableWindow* tableWindow = new TableWindow(serv.filtrareTip(type));
    tableWindow->setWindowTitle(QString::fromStdString("Apartamente de tip: " + type));
    tableWindow->resize(500, 300);
    tableWindow->show();
}