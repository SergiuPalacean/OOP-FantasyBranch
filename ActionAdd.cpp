#include "ActionAdd.h"

ActionAdd::ActionAdd(RepositoryBase* repository, Turret turret)
{
	this->repository = repository;
	this->addedTurret = turret;
}

void ActionAdd::executeUndo()
{
	this->repository->delete_from_repository(this->addedTurret.get_location());
}

void ActionAdd::executeRedo()
{
	this->repository->add_to_repository(this->addedTurret);
}

ActionAdd::~ActionAdd()
{
	this->repository = NULL;
}


