#pragma once
#include "Action.h"
#include "Turret.h"
#include "RepositoryBase.h"

class ActionAdd : public Action
{
	public:
		ActionAdd(RepositoryBase* repository, Turret turret);
		void executeUndo() override;
	    void executeRedo() override;
		~ActionAdd();
	private:
		Turret addedTurret;
		RepositoryBase* repository;
};

