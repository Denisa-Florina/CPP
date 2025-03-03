#pragma once
#include "Locatar.h"
#include "Repo.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;

};

class UndoAdauga :public ActiuneUndo {
	Locatar loc_add;
	RepoAbstract& rep;
public:
	UndoAdauga(const Locatar& loc, RepoAbstract& rep) :rep{ rep }, loc_add(loc) {};
	void doUndo() override {
		rep.sterge(loc_add.get_apartament());
	}
};

class UndoSterge :public ActiuneUndo {
	Locatar loc_read;
	RepoAbstract& repo;
public:
	UndoSterge(RepoAbstract& repo, const Locatar& locatar) :repo{ repo }, loc_read(locatar) {};
	void doUndo() override {
		repo.store(loc_read);
	}
};

class UndoModifica :public ActiuneUndo {
	Locatar loc_add;
	RepoAbstract& repo;
public:
	UndoModifica(const Locatar& loc, RepoAbstract& repo) :repo{ repo }, loc_add(loc) {};
	void doUndo() override {
		repo.modifica(loc_add.get_apartament(),loc_add.get_nume_proprietar());
	}
};