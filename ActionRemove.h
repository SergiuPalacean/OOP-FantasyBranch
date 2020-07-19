#pragma once
#include "Action.h"
#include "Turret.h"
#include "RepositoryBase.h"


class ActionRemove : public Action
{
public:
	ActionRemove(RepositoryBase* repository, Turret turret);
	void executeUndo() override;
	void executeRedo() override;
	~ActionRemove();
private:
	Turret removedTurret;
	RepositoryBase* repository;
};

