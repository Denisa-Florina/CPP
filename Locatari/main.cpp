#include "lab1011.h"
#include <QtWidgets/QApplication>
#include "Locatar.h"
#include "validator.h"
#include <iostream>
#include "FileRepo.h"
#include "Service.h"
#include "ListaNotificare.h"
#include "ui.h"
#include "AppGui.h"

using namespace std;

int main(int argc, char *argv[])
{
	LocatarValidator val;
	FileRepo rep{ "locatari.txt" };
	LocatarService serv{ rep, val };
    ListaNOT list;

    QApplication a(argc, argv);
	AppGui gui{serv, list};
	gui.show();
	/*
    //w.show()
	{

		LocatarValidator val; 
		int cmd;
		cout << "1-RepoFile\n0-RepoProb\n";
		cin >> cmd;

		if (cmd == 0) {
			RepoLab rep{ 0.5f };
			LocatarService serv{ rep, val };
			ListaNOT list;
			//UI ui{ serv, list };
			AppGui ui{ serv,list };
			ui.show();
			//ui.show;
		}
		else {
			FileRepo rep{ "locatari.txt" };
			LocatarService serv{ rep, val };
			ListaNOT list;
			//UI ui{ serv, list };
			AppGui ui{ serv,list };
			ui.show();
			//ui.run();
		}


	}
	*/
    return a.exec();
}
