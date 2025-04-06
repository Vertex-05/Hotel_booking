#pragma once
#ifndef HOTEL_H_INCLUDED
#define HOTEL_H_INCLUDED
#include "Room.h"
using namespace std;
#include <string>
class Hotel {
private:
	string hotelname;
	double avgCost;
	void calcAvgCost() {
		map<string, double> AvgCostmap;
		string rowhotel, line, dest, coststr;

		ifstream file("dest_hotel.csv");
		if (!file.is_open()) {
			cerr << "Unable to open file 'dest_hotel.csv'!\n";
			exit(EXIT_FAILURE);
		}
		//read the avgCost map
		getline(file, line);
		while (getline(file, line)) {
			stringstream rowstream(line);
			if (getline(rowstream, dest, ',') && getline(rowstream, rowhotel, ',') && getline(rowstream, coststr, ',')) {
				double cost = stod(coststr);
				AvgCostmap[rowhotel] = cost;
			}
		}

		file.close();
		auto key = hotelname;
		avgCost = AvgCostmap[key];
	}
public:
	Hotel() = default;
	Hotel(string n) {
		hotelname = n;
		calcAvgCost();
	}
	void sethotelname(string h) { hotelname = h;calcAvgCost(); }
	string getHotelname() { return hotelname; }
	double getAvgCost() { return avgCost; }
	void printHotel() {
		cout << "The hotel name: " << hotelname << endl;
		cout << "The average cost of " << hotelname << " is RM" << avgCost << endl;
	}
};

#endif // !HOTEL_H_INCLUDED