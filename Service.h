#pragma once
#include "Repo.h"
#include "Turret.h"
#include <string>
#include <vector>
#include "RepositoryBase.h"
#include "Action.h"
#include "ActionAdd.h"
#include "ActionRemove.h"
#include <memory>

using namespace std;

class Service
{
	friend class Tests;
	private:
		RepositoryBase* repository;
		int current_mode;
		string path;
		vector<unique_ptr<Action>> undo_stack;
		vector<unique_ptr<Action>> redo_stack;


	public:
		Service(RepositoryBase* repository);
		Service();
		~Service();
		void change_mode(string mode);
		void add_from_service(string location, string size, int auraLevel, int separateParts, string vision);
		void update_from_service(string location, string new_size, int new_auraLevel, int new_separateParts, string new_vision);
		void delete_from_service(string location);
		vector<Turret> get_all_service();
		void change_fileLocation(string filePath);
		void undo();
		void redo();
		string repository_type();
};




