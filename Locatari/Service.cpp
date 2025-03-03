#include "Service.h"
#include <assert.h>
#include <functional>
#include <algorithm>
#include "LocatarDTO.h"
#include <iostream>
#include <map>
#include "Repo.h"
#include "FileRepo.h"


map<string, DTOLocatar> LocatarService::raport() {
	map<string, DTOLocatar> mp;
	vector<Locatar> l = rep.getAll();

	for (const auto& locatar : l) {
		DTOLocatar d(locatar.get_tip());
		mp[locatar.get_tip()] = d;
	}

	for (const auto& locatar : l) {
		const auto nr = mp[locatar.get_tip()].getCount() + 1;
		DTOLocatar Newval(locatar.get_tip(), nr);
		mp[locatar.get_tip()] = Newval;
	}

	return mp;

}

void LocatarService::Undo() {
	if (undoAction.empty()) {
		throw RepoException{ "Nu mai exista operatii" };
	}
	undoAction.back()->doUndo();

	undoAction.pop_back();
	//rep.saveRepository();
}

void LocatarService::add(string apartament, string nume_proprietar, double suprafata, string tip) {
	Locatar l{ apartament, nume_proprietar, suprafata, tip };
	val.validate(l);
	rep.store(l);
	undoAction.push_back(std::make_unique<UndoAdauga>(l, rep));
	//rep.saveRepository();
}

void LocatarService::sterge(string apartament) {
	undoAction.push_back(std::make_unique<UndoSterge>(rep, rep.find(apartament)));
	rep.sterge(apartament);
	//rep.saveRepository();
}

void LocatarService::modifica(string apartament, string nume) {
	Locatar l = rep.find(apartament);
	rep.modifica(apartament, nume);
	undoAction.push_back(std::make_unique<UndoModifica>(l, rep));
	//rep.saveRepository();
}

const Locatar& LocatarService::cauta(string apartament) {
	return rep.find(apartament);
}

vector<Locatar> LocatarService::filtrareSuprafata(double suprafata) {
	return filtreaza([suprafata](const Locatar& p) noexcept{
		return p.get_suprafata() == suprafata;
		});
}


vector<Locatar> LocatarService::filtrareTip(string tip) {
	return filtreaza([tip](const Locatar& p) {return p.get_tip() == tip;});
}

vector<Locatar> LocatarService::filtreaza(function<bool(const Locatar&)> fct) {
	/*
	vector<Locatar> rez;
	for (const auto& l : rep.getAll()) {
		if (fct(l)) {
			rez.push_back(l);
		}
	}
	return rez;
	*/
	auto locatari = rep.getAll();
	std::vector<Locatar> rez;
	std::copy_if(locatari.begin(), locatari.end(), std::back_inserter(rez), fct);
	return rez;
}

/*
vector<Locatar> LocatarService::generalSort(bool(*maiMicF)(const Locatar&, const Locatar&)) {
	vector<Locatar> v{ rep.getAll() };//fac o copie	
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (!maiMicF(v.at(i), v.at(j))) {
				//interschimbam
				Locatar aux = v.at(i);
				v.at(i) = v.at(j);
				v.at(j) = aux;
			}
		}
	}
	return v;
}
*/

vector<Locatar> LocatarService::sortNume() {
	auto copyAll = rep.getAll();
	std::sort(copyAll.begin(), copyAll.end(), cmpNume);
	return copyAll;
	//return generalSort(cmpNume);
}

vector<Locatar> LocatarService::sortSuprafata() {
	auto copyAll = rep.getAll();
	std::sort(copyAll.begin(), copyAll.end(), cmpSurafata);
	return copyAll;
	//return generalSort(cmpSurafata);
}

vector<Locatar> LocatarService::sortTipSuprafata() {
	/*
	return generalSort([](const Locatar& p1, const Locatar& p2) {
		if (p1.get_tip() == p2.get_tip()) {
			return p1.get_suprafata() < p2.get_suprafata();
		}
		return p1.get_tip() < p2.get_tip();
		});
	*/
	auto copyAll = rep.getAll();
	std::sort(copyAll.begin(), copyAll.end(), cmpTipSurafata);
	return copyAll;
}


void testAdd() {
	FileRepo rep{"Test.txt"};
	LocatarValidator val;
	LocatarService serv{ rep, val };
	serv.add("A", "B", 123, "c");
	const auto& locatari = serv.getAll();
	assert(locatari.size() == 1);
	rep.emptyFile();
}

void testStergeServ() {
	FileRepo rep{ "Test.txt" };
	LocatarValidator val;
	LocatarService serv{ rep, val };
	serv.add("A", "B", 11, "c");
	serv.sterge("A");
	const auto& locatari = rep.getAll();
	assert(locatari.size() == 0);
	rep.emptyFile();
}

void testModificaServ() {
	FileRepo rep{ "Test.txt" };
	LocatarValidator val;
	LocatarService serv{ rep, val };
	serv.add("A", "B", 10, "c");
	serv.modifica("A", "C");
	const auto& locatari = rep.getAll();
	assert(locatari[0].get_nume_proprietar() == "C");
	rep.emptyFile();
}

void testCautaServ() {
	FileRepo rep{ "Test.txt" };
	LocatarValidator val;
	LocatarService serv{ rep, val };
	serv.add("A", "B", 78, "c");
	const auto& locatar = serv.cauta("A");
	assert(locatar.get_apartament() == "A");
	rep.emptyFile();
}

void testFiltrareSuprafata() {
	FileRepo rep{ "Test.txt" };
	LocatarValidator val;
	LocatarService serv{ rep, val };
	serv.add("A", "B", 90, "c");
	serv.add("B", "C", 156, "d");
	const auto& rez = serv.filtrareSuprafata(90);
	assert(rez.size() == 1);
	assert(rez[0].get_apartament() == "A");
	rep.emptyFile();
}

void testFiltrareTip() {
	FileRepo rep{ "Test.txt" };
	LocatarValidator val;
	LocatarService serv{ rep, val };
	serv.add("A", "B", 133, "c");
	serv.add("B", "C", 180, "c");
	const auto& rez = serv.filtrareTip("c");
	assert(rez.size() == 2);
	rep.emptyFile();
}

void testSortNume() {
	FileRepo rep{ "Test.txt" };
	LocatarValidator val;
	LocatarService serv{ rep, val };
	serv.add("B", "C", 19, "c");
	serv.add("A", "B", 45, "c");
	const auto& rez = serv.sortNume();
	assert(rez[0].get_apartament() == "A");
	rep.emptyFile();
}

void testSortSuprafata() {
	FileRepo rep{ "Test.txt" };
	LocatarValidator val;
	LocatarService serv{ rep, val };
	serv.add("B", "C", 150, "c");
	serv.add("A", "B", 123, "c");
	const auto& rez = serv.sortSuprafata();
	assert(rez[0].get_apartament() == "A");
	rep.emptyFile();
}

void testSortTipSuprafata() {
	FileRepo rep{ "Test.txt" };
	LocatarValidator val;
	LocatarService serv{ rep, val };
	serv.add("B", "C", 123, "d");
	serv.add("C", "C", 124, "d");
	serv.add("A", "B", 150, "c");
	const auto& rez = serv.sortTipSuprafata();
	assert(rez[0].get_apartament() == "A");
	rep.emptyFile();
}

void test_raport() {
	FileRepo rep{ "Test.txt" };
	LocatarValidator val;
	LocatarService serv{ rep, val };
	serv.add("B", "C", 123, "d");
	serv.add("C", "C", 124, "d");
	serv.add("A", "B", 150, "c"); 
	serv.raport();
	rep.emptyFile();
}

void test_undo() {
	FileRepo rep{ "Test.txt" };
	LocatarValidator val;
	LocatarService serv{ rep, val };
	serv.add("B", "C", 123, "d");
	serv.Undo();
	try {
		serv.Undo();
		assert(false);
	}
	catch (RepoException& ex) {
		assert(true);
	}
	serv.add("B", "C", 123, "d");
	serv.modifica("B", "A");
	assert(serv.getAll().size() == 1);
	serv.Undo();
	assert(serv.getAll().size() == 1);
	serv.sterge("B");
	assert(serv.getAll().size() == 0);
	serv.Undo();
	assert(serv.getAll().size() == 1);
	rep.emptyFile();
}
