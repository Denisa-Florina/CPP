#pragma once
#include <string>
#include <iostream>

extern int __empty_global_delete_locatar;

using std::string;
using std::cout;


class Locatar{
private:
	std::string apartament;
	std::string nume_proprietar;
	double suprafata;
	std::string tip;
public:
	//geteri pentru clasa Locatar
	string get_tip() const;
	string get_apartament() const;
	string get_nume_proprietar() const;
	double get_suprafata() const noexcept;

	//seteri pentru clasa Locatar
	void set_nume_proprietar(string nume_nou);
	void set_apartament(string apt);
	void set_suprafata(double sup);
	void set_tip(string tp);


	Locatar() = default;

	Locatar(string apartament, string nume_proprietar, double suprafata, string tip) :apartament{ apartament }, nume_proprietar{ nume_proprietar }, suprafata{ suprafata }, tip{ tip } {
		//this->apartament = apartament;
	}

	//permitem copii
	Locatar(const Locatar& ot) :apartament{ ot.apartament }, nume_proprietar{ ot.nume_proprietar }, suprafata{ ot.suprafata }, tip{ ot.tip } {
		cout << "!!!\n";	
	}

	//Locatar& operator=(const Locatar& other);
	bool operator==(const Locatar& other);
	bool operator!=(const Locatar& other);
	friend std::istream& operator>> (std::istream& input, Locatar& subject);

};

/*
Compara dupa tip
returneaza true daca p1.tip e mai mic decat p2.tip
*/
bool cmpNume(const Locatar& p1, const Locatar& p2);

/*
Compara dupa suprafata
returneaza true daca p1.suprafata e mai mic decat p2.suprafata
*/
bool cmpSurafata(const Locatar& p1, const Locatar& p2) noexcept;

/*
Compara dupa tip si suprafata
*/
bool cmpTipSurafata(const Locatar& p1, const Locatar& p2) noexcept;

std::ostream& operator<<(std::ostream& outputStream, const Locatar& subject);