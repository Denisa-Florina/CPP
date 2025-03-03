#pragma once
#include "Locatar.h"
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::ostream;


/*
Folosit pentru a semnala situatii exceptionale care pot aparea in validari
*/
class ValidateException {
	vector<string> msgs;
public:
	ValidateException(const vector<string>& errors) :msgs{ errors } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class LocatarValidator {
public:
	//valideaza un locatar
	//arunca erori daca datele nu sunt valide
	void validate(const Locatar& l);
};

//teste
void testValidator();