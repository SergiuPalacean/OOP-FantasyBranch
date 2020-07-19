#pragma once
#include "RepositoryFile.h"
class RepositoryCSV : public RepositoryFile
{
	private:
		vector<Turret> read_from_file() override;
		void write_to_file(vector<Turret> turrets) override;
	public:
		string get_repository_type() override;
};

