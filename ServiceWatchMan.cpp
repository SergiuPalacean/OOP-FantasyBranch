#include "ServiceWatchMan.h"
#include <exception>
#include "Error.h"
#include <stdlib.h>

const int modeDefault = -1;
const int modeA = -2;
const int modeB = -3;

using namespace std;

ServiceWatchMan::ServiceWatchMan()
{
	this->repository_turrets = NULL;
	this->repository_activated_turrets = NULL;
	this->current_index_for_next = 0;
	this->current_mode = modeDefault;
}

ServiceWatchMan::ServiceWatchMan(RepositoryBase* repository_turrets)
{
	this->repository_turrets = repository_turrets;
	this->repository_activated_turrets = NULL;
	this->current_index_for_next = 0;
	this->current_mode = modeDefault;
}

ServiceWatchMan::~ServiceWatchMan()
{
	delete this->repository_activated_turrets;
	this->repository_turrets = NULL;
}

void ServiceWatchMan::change_mode(string mode)
{
	if (mode == "A")
		this->current_mode = modeA;
	else if (mode == "B")
		this->current_mode = modeB;
}

void ServiceWatchMan::delete_from_service_watchman(string location)
{
	if (this->repository_activated_turrets != NULL)
	{
		for (auto& i : this->repository_activated_turrets->get_all())
			if (i.get_location() == location)
			{
				this->repository_activated_turrets->delete_from_repository(location);
				this->notify();
				unique_ptr<ActionRemove> action = make_unique<ActionRemove>(this->repository_activated_turrets, i);
				this->undo_stack.push_back(move(action));
				this->redo_stack.clear();
			}
	}
}

void ServiceWatchMan::update_from_service_watchman(string location, string size, int auraLevel, int separateParts, string vision)
{
	if (this->repository_activated_turrets != NULL)
	{
		for (auto& turret : this->repository_activated_turrets->get_all())
			if (turret.get_location() == location)
			{ 
				Turret newTurret(location, size, auraLevel, separateParts, vision);
				unique_ptr<ActionUpdate> action = make_unique<ActionUpdate>(this->repository_activated_turrets, turret, newTurret);
				this->repository_activated_turrets->update_from_repository(newTurret);
				this->notify();
				this->undo_stack.push_back(move(action));
				this->redo_stack.clear();
			}
	}
}

vector<Turret> ServiceWatchMan::get_all_criteria(string size, int separateParts)
{
	if (this->current_mode == modeB)
	{
		if (this->repository_activated_turrets != NULL)
		{
			vector<Turret> all_turrets = this->repository_turrets->get_all();
			vector<Turret> all_turrets_criteria;
			for (auto& i : all_turrets)
			{
				if ((i).get_size() == size && (i).get_separateParts() >= separateParts)
					all_turrets_criteria.push_back((i));
			}
			return all_turrets_criteria;
		}
	}
	else
	{
		throw ServiceWatchmenError("You don't have permission to take this action. Consider changing to mode B\n");
	}
}

vector<Turret> ServiceWatchMan::get_all_activated_turrets()
{
		if (this->repository_activated_turrets != NULL)
		{
			vector<Turret> all_turrets = this->repository_activated_turrets->get_all();
			return all_turrets;
		}
}

int ServiceWatchMan::next()
{
	if (this->current_mode == modeB)
	{
		if (this->repository_turrets != NULL)
		{
			if (this->current_index_for_next == this->repository_turrets->get_all().size())
			{
				this->current_index_for_next = 0;
				return this->current_index_for_next;
			}
			this->current_index_for_next++;
			return this->current_index_for_next;
		}
	}
	else
	{
		throw ServiceWatchmenError("You don't have permission to take this action. Consider changing to mode B\n");
	}
}

void ServiceWatchMan::save(string location)
{
	if (this->current_mode == modeB)
	{
		if (this->repository_activated_turrets != NULL)
		{
			vector<Turret> turrets = this->repository_turrets->get_all();
			for (auto& i : turrets)
			{
				if ((i).get_location() == location)
				{
					this->repository_activated_turrets->add_to_repository((i));
					this->notify();
					unique_ptr<ActionAdd> action = make_unique<ActionAdd>(this->repository_activated_turrets, i);
					this->undo_stack.push_back(move(action));
					this->redo_stack.clear();
					return;
				}
			}
			throw ServiceWatchmenError("You mispelled the location of the turret\n");
		}
	}
	else
	{
		throw ServiceWatchmenError("You don't have permission to take this action. Consider changing to mode B\n");
	}
}

void ServiceWatchMan::change_path(string Path)
{
	this->repository_turrets->change_fileLocation(Path);
}

void ServiceWatchMan::save_to_format(string path)
{
	if (path.back() == 'v')
	{
		this->path = path;
		this->pathCopy = path;
		this->repository_activated_turrets = new RepositoryCSV;
		this->repository_activated_turrets->change_fileLocation(path);
	}
	else if (path.back() == 'l')
	{
		this->path = path;
		this->pathCopy = path;
		this->repository_activated_turrets = new RepositoryHTML;
		this->repository_activated_turrets->change_fileLocation(path);
	}
}

string ServiceWatchMan::repository_type()
{
	return this->repository_activated_turrets->get_repository_type();
}

int ServiceWatchMan::get_index()
{
	return this->current_index_for_next;
}

void ServiceWatchMan::open()
{
	system(this->pathCopy.c_str());
}

void ServiceWatchMan::undo()
{
	if (this->undo_stack.size() > 0)
	{
		unique_ptr<Action> action = move(this->undo_stack.back());
		action->executeUndo();
		this->notify();
		this->redo_stack.push_back(move(action));
		this->undo_stack.pop_back();
	}
	else
		throw ServiceError("No more undos\n");
}

void ServiceWatchMan::redo()
{
	if (this->redo_stack.size() > 0)
	{
		unique_ptr<Action> action = move(this->redo_stack.back());
		action->executeRedo();
		this->notify();
		this->undo_stack.push_back(move(action));
		this->redo_stack.pop_back();
	}
	else
		throw ServiceError("No more redos\n");
}
