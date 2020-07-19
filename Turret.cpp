#include "Turret.h"
#include <string.h>
#include <stdlib.h>
#include <regex>
#include <iterator>
#include <algorithm>
#include <QDebug>


Turret::Turret(string location, string size, int auraLevel, int separateParts, string vision)
{
	this->location = location;
	this->size = size;
	this->auraLevel = auraLevel;
	this->separateParts = separateParts;
	this->vision = vision;
}

Turret::Turret(const Turret& turret)
{
	this->location = turret.location;
	this->size = turret.size;
	this->auraLevel = turret.auraLevel;
	this->separateParts = turret.separateParts;
	this->vision = turret.vision;
}

Turret::Turret()
{
	this->auraLevel = -1;
	this->separateParts = -1;
	this->location = "";
	this->size = "";
	this->vision = "";
}


string Turret::get_location() const
{
	return this->location;
}

string Turret::get_size() const
{
	return this->size;
}

int Turret::get_auraLevel() const
{
	return this->auraLevel;
}

int Turret::get_separateParts() const
{
	return this->separateParts;
}

string Turret::get_vision() const
{
	return this->vision;
}

void Turret::set_size(string newSize)
{
	this->size = newSize;
}

void Turret::set_auraLevel(int newAuraLevel)
{
	this->auraLevel = newAuraLevel;
}

void Turret::set_separateParts(int newSeparateParts)
{
	this->separateParts = newSeparateParts;
}

void Turret::set_vision(string newVision)
{
	this->vision = newVision;
}

Turret& Turret::operator=(const Turret& turret)
{
	if (this == &turret)
		return *this;
	
	this->location = turret.location;
	this->size = turret.size;
	this->auraLevel = turret.auraLevel;
	this->separateParts = turret.separateParts;
	this->vision = turret.vision;
	return *this;
}

bool Turret::operator==(const Turret& turret)
{
	return this->location==turret.location;
}

ostream& operator<<(ostream& out_stream, const Turret& turret)
{
	out_stream << turret.get_location() << ", " << turret.get_size() << ", " << turret.get_auraLevel() << ", " << turret.get_separateParts() << ", " << turret.get_vision()<<"\n";
	return out_stream;
}

istream& operator>>(istream& in_stream, Turret& turret)
{
	string line;
	getline(in_stream, line);
	regex re(", ");
	sregex_token_iterator first{ line.begin(), line.end(), re, -1 };
	sregex_token_iterator last;
	vector<string> parameters{ first, last };
	if (parameters.size() < 5)
		return in_stream;
	else
	{
		turret.location = parameters[0];
		turret.size = parameters[1];
		turret.auraLevel = stoi(parameters[2]);
		turret.separateParts = stoi(parameters[3]);
		turret.vision = parameters[4];
	}
	
	return in_stream;
}
