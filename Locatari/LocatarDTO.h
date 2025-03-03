#pragma once
#include <iostream>

using namespace std;

class DTOLocatar {
private:
	string tip;
	int count;
public:
	DTOLocatar(string tip, int count) : tip{ tip }, count{ count }{}

	DTOLocatar(string tip) : tip{ tip }, count{ 0 } {}

	DTOLocatar() : tip{ "" }, count{ 0 } {}

	string getTip() const {
		return tip;
	}

	int getCount() const noexcept {
		return count;
	}

};