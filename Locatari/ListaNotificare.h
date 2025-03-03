#pragma once

#include "Locatar.h"

#include <vector>
#include <random>
#include <fstream>
#include <algorithm>
#include "Observer.h"

using std::vector;
using std::shuffle;

class ListaNOT: public Observable{
private:
	vector<Locatar> ListaNot;
public:
	//goleste lista
    void empty_list() noexcept;

	//adauga apartamentul in lista
	//param l - Locatar
	//aruncam eroare daca apartamentul este deja in lista
    void add_apartament(const Locatar& l);

	//genereaza apartamente random din vector
	//nr_apt-nr de apartamente pe care vrem sa le adaugam
	//memory-vectorul din care selectam random Locatari
    void generate_apartamente(int nr_apt, const vector<Locatar>& memory);

	//exporta lista intr-un html 
	//name_file-numele fisierului in care exportam lista
    void export_list(const string& name_file);

	//returneaza lista
    const vector<Locatar>& get_List();


	void sterge(string apartament);

	//cauta un apartament
	//apartament-apartamentul pe care il cautam
	//return true-daca l-am gasit
	//return false-daca nu l-am gasit
    int search_apartament(const string& apartament);

};

/*
Folosit pentru a semnala situatii exceptionale care pot aparea in listaNOT
*/
class ListaException {
	string msg;
public:
	ListaException(string m) :msg{ m } {}

	string getMessage() {
		return msg;
	}

};

//teste
void test_adauga();
void test_sterge();
void test_generate();
void test_export();
void test_export2();