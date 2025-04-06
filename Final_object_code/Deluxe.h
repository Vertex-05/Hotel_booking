#pragma once
#ifndef DELUXE_H_INCLUDED
#define DELUXE_H_INCLUDED
#include "Room.h"
class Deluxe :public Room {
public:
	Deluxe() {
		capacity = 3;
		roomtype = "deluxe";
		amenities = { "WI_FI","Parking","Telephone","laundry","Roomcleaning" };
	}
	void AddAmenities() {
		const string prompt =
			"Please choose additional amenities:\n"
			"a: Add Mini Bar\n"
			"b: Add Coffee Maker\n"
			"c: Add Both Mini Bar and Coffee Maker\n"
			"d: No additional amenities\n"
			"Your choice: ";
		char choose = getValidCharInput(prompt, "abcd");
		if (choose == 'd') {
			cout << "Thank you for booking! Enjoy your stay!\n";
			return;
		}
		else if (choose == 'a') {
			amenities.push_back("Mini Bar");
			cout << "Amenity successfully added! Enjoy your stay!\n";
			addAmenityPrice(10.00);
		}
		else if (choose == 'b') {
			amenities.push_back("Coffee Maker");
			cout << "Amenity successfully added! Enjoy your stay!\n";
			addAmenityPrice(10.00);
		}
		else {
			amenities.push_back("Mini Bar");
			amenities.push_back("Coffee Maker");
			cout << "Amenity successfully added! Enjoy your stay!\n";
			addAmenityPrice(20.00);
		}
	}
};
#endif // !DELUXE_H_INCLUDED
