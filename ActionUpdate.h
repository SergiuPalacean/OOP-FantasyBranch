#pragma once
#include "Action.h"
#include "RepositoryBase.h"
#include "Turret.h"

class ActionUpdate : public Action
{
public:
	ActionUpdate(RepositoryBase* repo, Turret oldTurret, Turret newTurret);
	~ActionUpdate();
	void executeUndo() override;
	void executeRedo() override;

private:
	Turret oldTurret;
	Turret newTurret;
	RepositoryBase* repo;
};

