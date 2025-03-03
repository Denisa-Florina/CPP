#include "Repo.h"
#include <assert.h>
#include <iostream>
#include <vector>
#include <exception>

using std::ostream;
using std::stringstream;

void LocatarRepo::store(const Locatar& Lnew) {
	if (exist(Lnew)) {
		throw RepoException("Apartament deja inchiriat");
	}

	locatari.push_back(Lnew);
}

void LocatarRepo::sterge(string apartament) {
	int index = 0;
	bool gasit=false;
	for (auto& locatar : locatari) {
		if (locatar.get_apartament() == apartament) {
			gasit = true;
			break;
		}
		index++;
	}

	if (gasit == true) {
		locatari.erase(locatari.begin() + index);
		return;
	}
	else {
		throw RepoException("Nu exista locatar cu apartament: " + apartament);
	}
}

void LocatarRepo::modifica(string apartament, string nume) {
	bool found = false; 
	for (auto& locatar : locatari) { 
		if (locatar.get_apartament() == apartament) { 
			locatar.set_nume_proprietar(nume); 
			found = true; 
			break; 
		}
	}

	if (!found) { 
		throw RepoException("Nu exista locatar cu apartament: " + apartament); 
	}
}

const vector<Locatar>& LocatarRepo::getAll() {
	return locatari;
}

bool LocatarRepo::exist(const Locatar& Lnew) {
	try {
		find(Lnew.get_apartament());
		return true;
	}
	catch (RepoException&) {
		return false;
	}
}


const Locatar& LocatarRepo::find(string apartament){
	auto it = std::find_if(locatari.begin(), locatari.end(), [&](const Locatar& p) {
		return p.get_apartament() == apartament;
		});

	if (it != locatari.end()) {
		return *it;
	}

	throw RepoException("Nu exista locatar cu apartament: " + apartament);
}


const Locatar& RepoAbstract::find(string apartament) {
	auto it = std::find_if(locatari.begin(), locatari.end(), [&](const Locatar& p) {
		return p.get_apartament() == apartament;
		});

	if (it != locatari.end()) {
		return *it;
	}

	throw RepoException("Nu exista locatar cu apartament: " + apartament);
}

void RepoAbstract::store(const Locatar& Lnew) {
	if (exist(Lnew)) {
		throw RepoException("Apartament deja inchiriat");
	}

	locatari.push_back(Lnew);
}

void RepoAbstract::sterge(string apartament) {
	int index = 0;
	bool gasit = false;
	for (auto& locatar : locatari) {
		if (locatar.get_apartament() == apartament) {
			gasit = true;
			break;
		}
		index++;
	}

	if (gasit == true) {
		locatari.erase(locatari.begin() + index);
		return;
	}
	else {
		throw RepoException("Nu exista locatar cu apartament: " + apartament);
	}
}

void RepoAbstract::modifica(string apartament, string nume) {
	bool found = false;
	for (auto& locatar : locatari) {
		if (locatar.get_apartament() == apartament) {
			locatar.set_nume_proprietar(nume);
			found = true;
			break;
		}
	}

	if (!found) {
		throw RepoException("Nu exista locatar cu apartament: " + apartament);
	}
}

const vector<Locatar>& RepoAbstract::getAll() {
	return locatari;
}

bool RepoAbstract::exist(const Locatar& Lnew) {
	try {
		find(Lnew.get_apartament());
		return true;
	}
	catch (RepoException&) {
		return false;
	}
}





void RepoLab::store(const Locatar& Lnew) {
	//srand(time(nullptr));
	int randomNumber = rand();
	float rn = static_cast<float>(randomNumber) / RAND_MAX;
	if (rn < this->prob) {
		throw RepoException("\nBad luck!\n");
	}
	else {
		//locatari.push_back(Lnew);
		RepoAbstract::store(Lnew);

	}
}

void RepoLab::sterge(string apartament) {
	//srand(time(nullptr));
	int randomNumber = rand();
	float rn = static_cast<float>(randomNumber) / RAND_MAX;
	if (rn < this->prob) {
		throw RepoException("\nBad luck!\n");
	}
	else {
		/*
		int index = 0;
		bool gasit = false;
		for (auto& locatar : locatari) {
			if (locatar.get_apartament() == apartament) {
				gasit = true;
				break;
			}
			index++;
		}

		if (gasit == true) {
			locatari.erase(locatari.begin() + index);
			return;
		}
		else {
			throw RepoException("Nu exista locatar cu apartament: " + apartament);
		}
		*/
		RepoAbstract::sterge(apartament);
	}
}

void RepoLab::modifica(string apartament, string nume) {

	//srand(time(nullptr));
	int randomNumber = rand();
	float rn = static_cast<float>(randomNumber) / RAND_MAX;

	if (rn < this->prob) {
		throw RepoException("\nBad luck!\n");
	}
	else {
		/*
		bool found = false;
		for (auto& locatar : locatari) {
			if (locatar.get_apartament() == apartament) {
				locatar.set_nume_proprietar(nume);
				found = true;
				break;
			}
		}

		if (!found) {
			throw RepoException("Nu exista locatar cu apartament: " + apartament);
		}
		*/
		RepoAbstract::modifica(apartament, nume);
	}
}

const vector<Locatar>& RepoLab::getAll() {
	//for (auto i : all_map)
	//	locatari.push_back(i.second);
	return RepoAbstract::getAll();
}

bool RepoLab::exist(const Locatar &p) {

	//srand(time(nullptr));
	int randomNumber = rand();
	float rn = static_cast<float>(randomNumber) / RAND_MAX;

	if (rn < prob) {
		throw RepoException("Bad luck!");
	}
	else {
		RepoAbstract::exist(p);
	}
	/*
	try {
		find(p.get_apartament());
		return true;
	}
	catch (RepoException&) {
		return false;
	}
	*/
}


const Locatar& RepoLab::find(string apartament) {
	//locatari = getAll();
	
	//srand(time(nullptr));
	int randomNumber = rand();
	float rn = static_cast<float>(randomNumber) / RAND_MAX;

	if (rn < prob) {
		throw RepoException("Bad luck!");
	}
	else {
		/*
		auto it = std::find_if(locatari.begin(), locatari.end(), [&](const Locatar& p) {
			return p.get_apartament() == apartament;
			});

		if (it != locatari.end()) {
			return *it;
		}

		throw RepoException("Nu exista locatar cu apartament: " + apartament);
		*/
		RepoAbstract::find(apartament);
	}
}

void test_Prob() {
	RepoLab rep{ 1 };
	try {
		rep.store({ "D","B", 45, "c" });
	}
	catch(RepoException& ve){
		assert(true);
	}
	try {
		rep.sterge("D");
	}
	catch (RepoException& ve) {
		assert(true);
	}
	try {
		rep.modifica("D", "B");
	}
	catch (RepoException& ve) {
		assert(true);
	}
	try {
		rep.find("D");
	}
	catch (RepoException& ve) {
		assert(true);
	}
}

void testStore() {
	LocatarRepo rep;
	Locatar p{ "A","B", 34, "c" };
	rep.store(p);
	const auto& locatari = rep.getAll();
	assert(locatari.size() == 1);
	try {
		rep.store(p);
		//assert(false);
	}
	catch (RepoException& a) {
		a.getMessage();
		assert(true);
	}
	rep.store({ "D","B", 45, "c" });
	rep.store({ "E","B", 43, "c" });
	rep.store({ "N","B", 56, "c" });
	rep.store({ "I","B", 45, "c" });
	assert(locatari.size() == 5);
}

void testSterge() {
	LocatarRepo rep;
	rep.store({ "A", "B", 523, "C" });
	rep.store({ "B", "B", 523, "C" });
	rep.sterge("A");
	const auto& locatari = rep.getAll();
	assert(locatari.size() == 1);
	try {
		rep.sterge("A");
		assert(false); 
	}
	catch (const RepoException&) {
		assert(true); 
	}
}

void testModifica() {
	LocatarRepo rep;
	rep.store({ "A", "B", 12, "C" });
	rep.modifica("A", "D");
	const auto& locatari = rep.getAll();
	assert(locatari[0].get_nume_proprietar() == "D");
	try {
		rep.modifica("B", "E");
		assert(false); 
	}
	catch (const RepoException&) {
		assert(true); 
	}
}

void testCauta() {
	LocatarRepo rep;
	rep.store(Locatar{ "a","a",4,"a"});
	rep.store(Locatar{ "b","b",4,"b"});

	auto p = rep.find("a");
	assert(p.get_apartament() == "a");

	//arunca exceptie daca nu gaseste
	try {
		rep.find("c");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
}

void testFind() { 
	LocatarRepo rep;
	rep.store({ "A", "B", 13, "C" });
	const auto& locatar = rep.find("A");
	assert(locatar.get_apartament() == "A");
	try {
		rep.find("B");
		assert(false); 
	}
	catch (const RepoException&) {
		assert(true); 
	}
}
