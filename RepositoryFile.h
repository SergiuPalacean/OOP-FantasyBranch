#pragma once
#include <string>
#include "Turret.h"
#include <vector>
#include "RepositoryBase.h"
using namespace std;

class RepositoryFile : public RepositoryBase
{
	friend class Tests;
private:
	virtual vector<Turret> read_from_file()=0;
	virtual void write_to_file(vector<Turret> turrets)=0;
public:
	void change_fileLocation(string fileName) override;
	void add_to_repository(Turret turret) override;
	void delete_from_repository(string location) override;
	void update_from_repository(Turret turret) override;
	vector<Turret> get_all() override;
	int getSize() override;
};

