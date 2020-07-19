#pragma once
#include <string>
#include <vector>
#include "Turret.h"

class RepositoryBase
{
	friend class Tests;
protected:
	std::string fileName;

public:
	virtual void change_fileLocation(std::string fileName)=0;
	virtual void add_to_repository(Turret turret)=0;
	virtual void delete_from_repository(string location)=0;
	virtual void update_from_repository(Turret turret)=0;
	virtual string get_repository_type() = 0;
	virtual std::vector<Turret> get_all()=0;
	virtual int getSize()=0;
};


