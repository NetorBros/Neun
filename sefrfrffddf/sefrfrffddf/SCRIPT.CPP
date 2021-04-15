#include <stdlib>
#include "script.h"
#Include "money.h"
#include "LIBPS.H";

void main()
{
	Ped ped;
	Weapon weapon;

	int ammo = 3500;

	WEAPON::ADD_AMMO_TO_PED(ped, 0x1B06D571, ammo);



	while (true)
	{
		
		WAIT(0);
	}

	void ScriptMain()
	{
		srand(GetTickCount());
		main();
	}

}