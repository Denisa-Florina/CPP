#include "Locatar.h"
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

string Locatar::get_tip() const{
	return tip;
}

string Locatar::get_apartament() const{
	return apartament;
}

string Locatar::get_nume_proprietar() const{
	return nume_proprietar;
}

double Locatar::get_suprafata() const noexcept{
	return suprafata;
}

void Locatar::set_nume_proprietar(string nume_nou) {
	nume_proprietar = nume_nou;
}

void Locatar::set_apartament(string apt) {
    apartament = apt;
}

void Locatar::set_suprafata(double sup) {
    suprafata = sup;
}

void Locatar::set_tip(string tp) {
    tip = tp;
}

bool cmpNume(const Locatar& p1, const Locatar& p2) {
	return p1.get_nume_proprietar() < p2.get_nume_proprietar();
}

bool cmpSurafata(const Locatar& p1, const Locatar& p2) noexcept{
	return p1.get_suprafata() < p2.get_suprafata();
}


bool cmpTipSurafata(const Locatar& p1, const Locatar& p2) noexcept {
	if (p1.get_tip() == p2.get_tip())
		return p1.get_suprafata() < p2.get_suprafata();
	else
		return p1.get_tip() < p2.get_tip();
}

/*
bool Locatar::operator==(const Locatar& other) {
	return this->apartament == other.apartament;
}


bool Locatar::operator!=(const Locatar& other) {
	return !operator==(other);
}
*/

vector<string> splitInput(const string& inputString, char delimitator)
{
    std::vector<string> splited;
    std::stringstream stream(inputString);
    std::string curent;
    while (std::getline(stream, curent, delimitator))
    {
        splited.push_back(curent);
    }
    return splited;
}
std::istream& operator>>(std::istream& inputStream, Locatar& subject)
{
    std::string line;
    std::getline(inputStream, line);
    std::vector<string> objects = splitInput(line, ',');
    if (objects.size() != 4)
        return inputStream;
    subject.set_apartament(objects[0]);
    subject.set_nume_proprietar(objects[1]);
    subject.set_suprafata(std::stoi(objects[2]));
    subject.set_tip(objects[3]);
    return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const Locatar& subject)
{
    outputStream << subject.get_apartament() << "," << subject.get_nume_proprietar() << "," << subject.get_suprafata() << "," << subject.get_tip() << "\n";
    return outputStream;
}