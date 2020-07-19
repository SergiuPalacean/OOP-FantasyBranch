#pragma once

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class Turret
{
	friend class Tests;
	friend class RepositoryCSV;
	friend class RepositoryHTML;
	private:
		string location;
		string size;
		int auraLevel;
		int separateParts;
		string vision;

	public:
		Turret(string location, string size, int auraLevel, int separateParts, string vision);
		Turret(const Turret& turret);
		Turret();
		string get_location() const;
		string get_size() const;
		int get_auraLevel() const;
		int get_separateParts() const;
		string get_vision() const;
		void set_size(string newSize);
		void set_auraLevel(int newAuraLevel);
		void set_separateParts(int newSeparateParts);
		void set_vision(string newVision);
		Turret& operator=(const Turret &turret);
		bool operator==(const Turret& turret);
		friend ostream& operator<<(ostream& out_stream, const Turret& turret);
		friend istream& operator>>(istream& in_stream, Turret& turret);
};