#include "RepositoryFile.h"
#include <iostream>
#include <fstream>
#include "Error.h"


void RepositoryFile::change_fileLocation(string fileName)
{
	this->fileName = fileName;
}

void RepositoryFile::add_to_repository(Turret turret)
{
	vector<Turret> turrets = this->read_from_file();
	if (turrets.size() == 0)
		turrets.push_back(turret);
	else
	{
		for (auto& i : turrets)
		{
			if ((i).get_location() == turret.get_location())
			{
				throw RepositoryError("Location already on the map\n");
			}
		}
		turrets.push_back(turret);
	}

	this->write_to_file(turrets);
}

void RepositoryFile::delete_from_repository(string location)
{
	vector<Turret> turrets = this->read_from_file();

	auto i = turrets.begin();
	int counter = 0, is_deleted = 0;
	while (i != turrets.end())
	{
		if (location.find((*i).get_location()) == 0)
		{
			is_deleted = 1;
			turrets.erase(i);
			this->write_to_file(turrets);
			return;
		}
		counter++;
		i++;
	}
	if (is_deleted == 0)
		throw RepositoryError("Could not remove location because it does not belong to the map\n");
}

void RepositoryFile::update_from_repository(Turret turret)
{
	this->delete_from_repository(turret.get_location());
	this->add_to_repository(turret);
}

vector<Turret> RepositoryFile::get_all()
{
	return this->read_from_file();
}

int RepositoryFile::getSize()
{
	vector<Turret> turrets=this->read_from_file();
	return turrets.size();
}
