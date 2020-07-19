#include "Validator.h"

#include <string>
using namespace std;

void Validator::validate(Turret turret)
{
	string errors = "";
	if (turret.get_location() == "")
		errors += "Invalid location\n";
	if (turret.get_size() == "")
		errors += "Invalid size\n";
	if (turret.get_auraLevel() < 0)
		errors += "Invalid aura\n";
	if (turret.get_separateParts() < 1)
		errors += "Invalid parts\n";
	if (turret.get_vision() == "")
		errors += "Invalid vision\n";
	if (errors.size() > 0)
		throw ValidationError(errors);
}
