#include "RepositoryCSV.h"
#include <regex>
#include <iterator>
#include <algorithm>
#include "Turret.h"
using namespace std;


vector<Turret> RepositoryCSV::read_from_file()
{
	vector<Turret> turrets;
	ifstream read_file;
	read_file.open(this->fileName);
	Turret turret;
	while (!read_file.eof())
	{
		string line;
		read_file >> line;


		regex re(",");
		sregex_token_iterator first{ line.begin(), line.end(), re, -1 };
		sregex_token_iterator last;
		vector<string> parameters{ first, last };

		if (parameters.size() < 5)
			break;
		turret.location = parameters[0];
		turret.size = parameters[1];
		turret.auraLevel = stoi(parameters[2]);
		turret.separateParts = stoi(parameters[3]);
		turret.vision = parameters[4];
		turrets.push_back(turret);
	}
	read_file.close();
	return turrets;
}

void RepositoryCSV::write_to_file(vector<Turret> turrets)
{
	ofstream write_csv;
	write_csv.open(this->fileName);
	for (auto& turret : turrets)
	{
		write_csv << turret.get_location() << "," << turret.get_size() << "," << turret.get_auraLevel() << "," << turret.get_separateParts() << "," << turret.get_vision() << endl;
	}
	write_csv.close();
}

string RepositoryCSV::get_repository_type()
{
	return "csv";
}
