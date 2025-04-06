#pragma once
#ifndef SUITE_H_INCLUDED
#define SUITE_H_INCLUDED
#include "Room.h"
class Suite :public Room {
public:
	Suite() {
		roomtype = "suite";
		capacity = 5;
		amenities = { "WI_FI","Parking","Telephone","laundry","Roomcleaning" ,"Mini Bar","Coffee Maker" };
	}
	void AddAmenities() {
		const std::string prompt =
			"Please choose additional amenities:\n"
			"a: Add Luxury Linens and Pillows\n"
			"b: Add Private Butler Service\n"
			"c: Add Both Luxury Linens and Pillows and Private Butler Service\n"
			"d: No additional amenities\n"
			"Your choice: ";
		char choose = getValidCharInput(prompt, "abcd");
		if (choose == 'd') {
			cout << "Thank you for booking! Enjoy your stay!\n";
			return;
		}
		else if (choose == 'a') {
			amenities.push_back("Luxury Linens and Pillows");
			cout << "Amenity successfully added! Enjoy your stay!\n";
			addAmenityPrice(30.00);
		}
		else if (choose == 'b') {
			amenities.push_back("Private Butler Service");
			cout << "Amenity successfully added! Enjoy your stay!\n";
			addAmenityPrice(30.00);
		}
		else {
			amenities.push_back("Luxury Linens and Pillows");
			amenities.push_back("Private Butler Service");
			cout << "Amenity successfully added! Enjoy your stay!\n";
			addAmenityPrice(30.00);
		}
	}
};
#endif // !SUITE_H_INCLUDED