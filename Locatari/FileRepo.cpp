#include <fstream>
#include "FileRepo.h"
#include "Locatar.h"
#include "validator.h"
#include "Service.h"
#include <assert.h>

using namespace std;

void FileRepo::loadRepository() {
    ifstream file(nameFile);
    Locatar locatar;
    while (file >> locatar){
        store(locatar);

    }
}

void FileRepo::saveRepository() {
    std::ofstream ofile(nameFile);
    //if (!ofile.is_open())
    //    throw RepoException("File does not exist\n");
    for (const auto& subject : this->getAll())
    {
        ofile << subject;
    }
    ofile.close();
}


void FileRepo::emptyFile() {
    std::ofstream ofile(nameFile);
    ofile << "";
    ofile.close();
}



void test_FileRepo() {

    FileRepo rep{ "TestFileRepo.txt" };
    LocatarValidator val;
    LocatarService serv{ rep, val };
    assert(rep.getAll().size() == 1);
}