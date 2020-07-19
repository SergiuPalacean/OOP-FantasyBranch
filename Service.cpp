#include "Service.h"
#include <exception>
#include "Error.h"
#include "Validator.h"
#include <iostream>
#include "ActionUpdate.h"

const int modeDefault = -1;
const int modeA = -2;
const int modeB = -3;

using namespace std;

Service::Service(RepositoryBase* repository)
{
	this->repository = repository;
	this->current_mode = modeDefault;
}

Service::Service()
{
	this->repository = NULL;
	this->current_mode = modeDefault;
}

Service::~Service()
{
	this->repository = NULL;
}


void Service::change_mode(string mode)
{
	if (mode == "A")
		this->current_mode = modeA;
	else if (mode == "B")
		this->current_mode = modeB;
}

void Service::add_from_service(string location, string size, int auraLevel, int separateParts, string vision)
{
	if (this->current_mode == modeA)
	{
		if (this->repository != NULL)
		{
			Turret turret(location, size, auraLevel, separateParts, vision);
			Validator validator;
			validator.validate(turret);
			unique_ptr<ActionAdd> action = make_unique<ActionAdd>(this->repository, turret);
			this->undo_stack.push_back(move(action));
			this->repository->add_to_repository(turret);
			this->redo_stack.clear();
		}
	}
	else
	{
		throw ServiceError("You don't have permission to take this action. Consider changing to mode A\n");
	}
}

void Service::update_from_service(string location, string new_size, int new_auraLevel, int new_separateParts, string new_vision)
{
	if (this->current_mode == modeA)
	{
		if (this->repository != NULL)
		{
			Turret turret(location, new_size, new_auraLevel, new_separateParts, new_vision);
			Validator validator;
			validator.validate(turret);
			Turret updated_turret;
			for (auto& turret : this->repository->get_all())
			{
				if (turret.get_location() == location)
				{
					updated_turret = turret;
				}
			}
			unique_ptr<ActionUpdate> action = make_unique<ActionUpdate>(this->repository, updated_turret, turret);
			this->undo_stack.push_back(move(action));
			this->repository->update_from_repository(turret);
			this->redo_stack.clear();
		}
	}
	else
	{
		throw ServiceError("You don't have permission to take this action. Consider changing to mode A\n");
	}
}

void Service::delete_from_service(string location)
{
	if (this->current_mode == modeA)
	{
		if (this->repository != NULL)
		{
			vector<Turret> turrets = this->repository->get_all();
			Turret removed_turret;
			for (auto& turret : turrets)
			{
				if (turret.get_location() == location)
				{
					removed_turret = turret;
				}
			}
			unique_ptr<ActionRemove> action = make_unique<ActionRemove>(this->repository, removed_turret);
			this->undo_stack.push_back(move(action));
			this->repository->delete_from_repository(location);
			this->redo_stack.clear();
		}
	}
	else
	{
		throw ServiceError("You don't have permission to take this action. Consider changing to mode A\n");
	}
}

vector<Turret> Service::get_all_service()
{
	if (this->current_mode == modeA)
	{
		
		if (this->repository != NULL)
		{
			return this->repository->get_all();
		}
	}
	else
	{
		throw ServiceError("You don't have permission to take this action. Consider changing to mode A\n");
	}
}

void Service::change_fileLocation(string filePath)
{
	this->repository->change_fileLocation(filePath);
}

void Service::undo()
{
	if (this->undo_stack.size() > 0)
	{
		unique_ptr<Action> action = move(this->undo_stack.back());
		action->executeUndo();
		this->redo_stack.push_back(move(action));
		this->undo_stack.pop_back();
	}
	else
		throw ServiceError("No more undos\n");
}

void Service::redo()
{
	if (this->redo_stack.size() > 0)
	{
		unique_ptr<Action> action = move(this->redo_stack.back());
		action->executeRedo();
		this->undo_stack.push_back(move(action));
		this->redo_stack.pop_back();
	}
	else
		throw ServiceError("No more redos\n");
}

string Service::repository_type()
{
	return this->repository->get_repository_type();
}








