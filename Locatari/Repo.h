#pragma once
#include "Locatar.h"
#include <vector>
#include <string>
#include <ostream>
#include <map>

using std::vector;
using std::string;
using std::ostream;


using namespace std;


class RepoAbstract {
public:
	vector<Locatar> locatari;
	//RepoAbstract() = default;
	virtual ~RepoAbstract() = default;

	virtual void store(const Locatar& Lnew);

	virtual const Locatar& find(string apartament);

	virtual const vector<Locatar>& getAll();

	virtual void sterge(string apartament);

	virtual void modifica(string apartament, string nume);

	virtual bool exist(const Locatar& Lnew);
};



class RepoLab : public RepoAbstract {
public:
	map<int, Locatar> all_map;
	float prob;
	vector<Locatar> locatari;


	RepoLab(float prob) : prob{ prob } {}
	//nu permitem copierea de obiecte
	/*
	* Salvare oferta
	*
	* @param oferta: obiect de tip Oferta
	* arunca exceptie daca mai exista o oferta cu aceeasi denumire si destinatie
	*/
	void store(const Locatar& Lnew);

	const Locatar& find(string apartament) override;

	virtual const vector<Locatar>& getAll();

	virtual void sterge(string apartament) override;

	virtual void modifica(string apartament, string nume);

	bool exist(const Locatar& Lnew);
	//ostream& operator<<(ostream& out, const exception& ex);

};




class LocatarRepo:public RepoAbstract{
private:
	vector<Locatar> locatari;

public:
	LocatarRepo() = default;
	//nu permitem copierea de obiecte
	LocatarRepo(const LocatarRepo& ot) = delete;


	/*
	metoda privata verifica daca exista deja p in repository
	*/
	bool exist(const Locatar& Lnew);

	/*
	Salvare locatar
	arunca exceptie daca mai exista un locatar cu acelasi apartament
	*/
	virtual void store(const Locatar& Lnew);

	/*
	Sterge locatar
	arunca exceptie daca nu exista un locatar cu acel apartament
	*/
	virtual void sterge(string apartament);

	/*
	Modifica locatar
	arunca exceptie daca nu exista un locatar cu acel apartament
	*/
	virtual void modifica(string apartament, string nume);

	/*
	Cauta
	arunca exceptie daca nu exista locatar
	*/
	const Locatar& find(string apartament);

	/*
	returneaza toti locatarii
	*/
	virtual const vector<Locatar>& getAll();

};


/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class RepoException {
	string msg;
public:
	RepoException(string m) :msg{ m } {}

	string getMessage() {
		return msg;
	}

};


//teste
void testStore();
void testCauta();
void testSterge();
void testModifica();
void testFind();
void test_Prob();