
#include "validator.h"
#include <assert.h>
#include <sstream>


void LocatarValidator::validate(const Locatar& p) {
	vector<string> msgs;
	if (p.get_suprafata() < 0) msgs.push_back("Suprafata negativa!!!");
	if (p.get_tip().size() == 0) msgs.push_back("Tip vid!!!");
	if (p.get_nume_proprietar().size() == 0) msgs.push_back("Nume proprietar vid!!!");
	if (p.get_apartament().size() == 0) msgs.push_back("Apartament vid!!!");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}

void testValidator() {
	LocatarValidator v; 
	Locatar p{ "","",-1,""};
	try {
		v.validate(p);
	}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);
	}
}