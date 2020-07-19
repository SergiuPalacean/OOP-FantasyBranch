#include "RepositoryText.h"

vector<Turret> RepositoryText::read_from_file()
{
	vector<Turret> turrets;
	ifstream read_file;
	read_file.open(this->fileName);
	Turret turret;
	while (read_file >> turret)
	{
		turrets.push_back(turret);
	}
	read_file.close();
	return turrets;
}

void RepositoryText::write_to_file(vector<Turret> turrets)
{
	ofstream write_file;
	write_file.open(this->fileName);
	for (auto& i : turrets)
	{
		write_file << i;
	}
	write_file.close();
}

string RepositoryText::get_repository_type()
{
	return "text";
}
