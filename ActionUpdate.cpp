#include "ActionUpdate.h"

ActionUpdate::ActionUpdate(RepositoryBase* repo, Turret oldTurret, Turret newTurret)
{
	this->repo = repo;
	this->oldTurret = oldTurret;
	this->newTurret = newTurret;
}

ActionUpdate::~ActionUpdate()
{
	this->repo = NULL;
}

void ActionUpdate::executeUndo()
{
	this->repo->update_from_repository(this->oldTurret);
}

void ActionUpdate::executeRedo()
{
	this->repo->update_from_repository(this->newTurret);
}
