#include "Repo.h"

#include <string.h>
#include <stdexcept>
#include <exception>
#include "Error.h"
using namespace std;


Repository::Repository()
{
	this->turrets.clear();
}

void Repository::change_fileLocation(string fileName)
{
	this->fileName = fileName;
}



void Repository::add_to_repository(Turret turret)
{
	if (this->turrets.size() == 0)
		this->turrets.push_back(turret);
	else 
	{
		for (auto& i : this->turrets)
		{
			if ((i).get_location()==turret.get_location())
			{
				throw RepositoryError("Location already on the map\n");
			}
		}
		this->turrets.push_back(turret);
	}
}

void Repository::delete_from_repository(string location)
{
	auto i = this->turrets.begin();
	int counter = 0, is_deleted=0;
	while (i != this->turrets.end())
	{
		if (location.find((*i).get_location()) == 0)
		{
			is_deleted = 1;
			this->turrets.erase(i);
			return;
		}
		counter++;
		i++;
	}
	if(is_deleted==0)
		throw RepositoryError("Could not remove location because it does not belong to the map\n");
}


void Repository::update_from_repository(Turret turret)
{

	this->delete_from_repository(turret.get_location());
	this->add_to_repository(turret);
}

string Repository::get_repository_type()
{
	return "memory";
}

vector<Turret> Repository::get_all()
{
	vector<Turret> all_turret;
	all_turret = this->turrets;
	return all_turret;
}

int Repository::getSize()
{
	return this->turrets.size();
}
