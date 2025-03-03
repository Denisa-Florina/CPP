#pragma once
#include "Locatar.h"
#include "Repo.h"
#include <iostream>
#include <sstream>
#include "validator.h"
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "LocatarDTO.h"
#include "FileRepo.h"
#include "Undo.h"

using std::vector;
using std::function;
using std::stringstream;

class LocatarService
{
private:
	RepoAbstract& rep;
	LocatarValidator& val;
	vector<unique_ptr<ActiuneUndo>> undoAction;
	//vector<vector<Locatar>> undoL;


	/*
	Functie generala de filtrare
	fct - poate fi o functie
	fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
	returneaza doar locatarii care trec de filtru (fct(locatar)==true)
	*/
	vector<Locatar> filtreaza(function<bool(const Locatar&)> fct);


	/*
	 Functie de sortare generala
	 maiMareF - functie care compara 2 Locatar, verifica daca are loc relatia mai mare
			  - poate fi orice functe (in afara clasei) care respecta signatura (returneaza bool are 2 parametrii Locatar)
			  - poate fi functie lambda (care nu capteaza nimic in capture list)
	 returneaza o lista sortata dupa criteriu dat ca paramatru
	*/
	vector<Locatar> generalSort(bool(*maiMicF)(const Locatar&, const Locatar&));
public:
	LocatarService(RepoAbstract& rep, LocatarValidator& val) noexcept: rep{ rep }, val{val} {}
	//nu permitem copii
	LocatarService(const LocatarService& ot) = delete;
	LocatarService() = default;

	void Undo();
	//adaugam un element
	void add(string apartament, string nume_proprietar, double suprafata, string tip);

	//stergem un element dupa apartament
	//@param apartament - apartamentul locatarlui
	void sterge(string apartament);

	//modificam un element dupa apartament
	//@param apartament - apartamentul locatarlui
	//@param nume - numele noulu proprietar
	void modifica(string apartament, string nume);

	//cautam un element dupa apartament
	//@param apartament - apartamentul locatarlui
	//@return Locatarul cu apartamentul respectiv
	const Locatar& cauta(string apartament);

	/*
	returneaza doar locatarii cu suprafata egala cu cea data
	*/
	vector<Locatar> filtrareSuprafata(double suprafata);


	/*
	returneaza doar locatarii cu tipul egal cu cel dat
	*/
	vector<Locatar> filtrareTip(string tip);

	map<string, DTOLocatar> raport();

	/*
	Sorteaza dupa Nume
	*/
	vector<Locatar> sortNume();

	/*
	Sorteaza dupa Suprafata
	*/
	vector<Locatar> sortSuprafata();

	/*
	Sorteaza dupa tip+suprafata
	*/
	vector<Locatar> sortTipSuprafata();

	//Returneaza vectorul de locatari
	const vector<Locatar>& getAll() noexcept {
		return rep.getAll();
	}
};

//teste
void testAdd();
void testStergeServ();
void testModificaServ();
void testCautaServ();
void testFiltrareSuprafata();
void testFiltrareTip();
void testSortNume();
void testSortSuprafata();
void testSortTipSuprafata();
void test_raport();
void test_undo();