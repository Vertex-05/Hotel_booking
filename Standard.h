#pragma once
#ifndef STANDARD_H_INCLUDED
#define STARDAND_H_INCLUDED
#include "Room.h"
#include<fstream>
#include<sstream>

class Standard :public Room {
public:
	Standard() {
		capacity = 2;
		amenities = { "WI_FI","Parking","Telephone","laundry","Roomcleaning" };
		roomtype = "standard";
	}

};
#endif // !STANDARD_H_INCLUDED