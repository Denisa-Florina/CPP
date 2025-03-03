#pragma once
#include "Repo.h"

class FileRepo : public LocatarRepo {
private:
	string nameFile;
public:
    void loadRepository();
    void saveRepository();
    void emptyFile();
    FileRepo(const string& name) : LocatarRepo(), nameFile{ name } { loadRepository(); };

    void setPath(const string& name) {
        this->nameFile = name;
    }

    ~FileRepo() override=default;


	void store(const Locatar& o) override {
		LocatarRepo::store(o);
		saveRepository();
	}

	void sterge(string apartament) override {
		LocatarRepo::sterge(apartament);
		saveRepository();
	}

	void modifica(string apartament, string nume) override {
		LocatarRepo::modifica(apartament, nume);
		saveRepository();
	}

	const Locatar& find(string apartament) override {
		return LocatarRepo::find(apartament);
	}

	bool exist(const Locatar& o) override {
		bool ret = LocatarRepo::exist(o);
		return ret;	
	}

};
void test_FileRepo();