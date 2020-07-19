#pragma once
#include "Turret.h"
#include <string>
#include <vector>
#include "RepositoryBase.h"


using namespace std;

class Repository : public RepositoryBase
{
	friend class Tests;
	private:
		std::vector<Turret> turrets;

	public:
		Repository();
		void change_fileLocation(string fileName) override;
		void add_to_repository(Turret turret) override;
		void delete_from_repository(string location) override;
		void update_from_repository(Turret turret) override;
		string get_repository_type() override;
		std::vector<Turret> get_all() override;
		int getSize() override;
};

