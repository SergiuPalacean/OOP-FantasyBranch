#include "ActionRemove.h"

ActionRemove::ActionRemove(RepositoryBase* repository, Turret turret)
{
	this->repository = repository;
	this->removedTurret = turret;
}

void ActionRemove::executeUndo()
{
	this->repository->add_to_repository(this->removedTurret);
}

void ActionRemove::executeRedo()
{
	this->repository->delete_from_repository(this->removedTurret.get_location());
}

ActionRemove::~ActionRemove()
{
	this->repository = NULL;
}
