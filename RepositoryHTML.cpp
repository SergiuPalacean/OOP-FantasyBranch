#include "RepositoryHTML.h"
#include <regex>
#include <iterator>
#include <algorithm>
#include "Turret.h"
#include <stdio.h>
using namespace std;

vector<Turret> RepositoryHTML::read_from_file()
{
	int counter=1;
	vector<Turret> turrets;
	ifstream read_file;
	read_file.open(this->fileName);
	Turret turret;
	while (!read_file.eof())
	{
		string line;
		read_file >> line;
		if (counter > 16)
		{
			if (line == "<tr>")
			{
				int i = 0;
				while (i < 5)
				{
					read_file >> line;
					switch (i)
					{
					case 0:
					{
						line.erase(0, 4);
						for (int j = 0; j < 5; j++)
							line.pop_back();
						turret.location = line;
						break;
					}
					case 1:
					{
						line.erase(0, 4);
						for (int j = 0; j < 5; j++)
							line.pop_back();
						turret.size = line;
						break;
					}
					case 2:
					{
						line.erase(0, 4);
						for (int j = 0; j < 5; j++)
							line.pop_back();
						turret.auraLevel = stoi(line);
						break;
					}
					case 3:
					{
						line.erase(0, 4);
						for (int j = 0; j < 5; j++)
							line.pop_back();
						turret.separateParts = stoi(line);
						break;
					}
					case 4:
					{
						line.erase(0, 4);
						for (int j = 0; j < 5; j++)
							line.pop_back();
						turret.vision = line;
						break;
					}
					case 5:
						break;
					}
					i++;
				}
				read_file >> line;
				turrets.push_back(turret);
			}
			else
				break;
		}
		counter++;
	}
	read_file.close();
	return turrets;
}

void RepositoryHTML::write_to_file(vector<Turret> turrets)
{
	ofstream write_html;
	write_html.open(this->fileName);
	write_html << "<!DOCTYPE html>" << endl;
	write_html << "<html>" << endl;
	write_html << "<head>" << endl;
	write_html << "<title>Turrets</title>" << endl;
	write_html << "</head>" << endl;
	write_html << "<body>" << endl;
	write_html << "<table border=\"1\">" << endl;
	write_html << "<tr>" << endl;
	write_html << "<td>Location</td>" << endl;
	write_html << "<td>Size</td>" << endl;
	write_html << "<td>AuraLevel</td>" << endl;
	write_html << "<td>SeparateParts</td>" << endl;
	write_html << "<td>Vision</td>" << endl;
	write_html << "</tr>" << endl;
	for (auto& turret : turrets)
	{
		write_html << "<tr>" << endl;
		write_html << "<td>" << turret.get_location() << "</td>" << endl;
		write_html << "<td>" << turret.get_size() << "</td>" << endl;
		write_html << "<td>" << turret.get_auraLevel() << "</td>" << endl;
		write_html << "<td>" << turret.get_separateParts() << "</td>" << endl;
		write_html << "<td>" << turret.get_vision() << "</td>" << endl;
		write_html << "</tr>" << endl;
	}
	write_html << "</table>" << endl;
	write_html << "</body>" << endl;
	write_html << "</html>" << endl;
	write_html.close();
}

string RepositoryHTML::get_repository_type()
{
	return "html";
}
