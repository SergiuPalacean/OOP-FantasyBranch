#pragma once
#include "Repo.h"
#include "Turret.h"
#include <string>
#include <vector>
#include "RepositoryFile.h"
#include "RepositoryBase.h"
#include "RepositoryCSV.h"
#include "RepositoryHTML.h"
#include "Subject.h"
#include "Action.h"
#include "ActionAdd.h"
#include "ActionRemove.h"
#include "ActionUpdate.h"
#include <memory>


class ServiceWatchMan : public Subject
{
	friend class Tests;

private:
	int current_mode;
	int current_index_for_next;
	RepositoryBase* repository_turrets;
	RepositoryBase* repository_activated_turrets;
	string path;
	string pathCopy;
	vector<unique_ptr<Action>> undo_stack;
	vector<unique_ptr<Action>> redo_stack;

public:
	ServiceWatchMan();
	ServiceWatchMan(RepositoryBase* repository_turrets);
	~ServiceWatchMan();
	void change_mode(string mode);
	void delete_from_service_watchman(string location);
	void update_from_service_watchman(string location, string size, int auraLevel, int separateParts, string vision);
	std::vector<Turret> get_all_criteria(string size, int separateParts);
	std::vector<Turret> get_all_activated_turrets();
	int next();
	void save(string location);
	void change_path(string Path);
	void save_to_format(string path);
	string repository_type();
	int get_index();
	void open();
	void undo();
	void redo();
};

