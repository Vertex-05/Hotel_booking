#pragma once
#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED
#include<iostream>
#include<string>
#include <vector>
#include<fstream>
#include<map>
#include<sstream>
#include<algorithm>
using namespace std;

char getValidCharInput(const string& prompt, const string& options) {
	char input;
	while (true) {
		cout << prompt;
		cin >> input;
		if (options.find(input) != string::npos && cin.peek() == '\n') {
			break;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Please try again.\n";
	}
	return input;
}

class Room {
protected:
	double finalprice;
	double baseprice;
	int capacity;
	vector <string> amenities;
	string roomtype;
	int numguest;
	static map<pair<string, string>, double> priceMap; // Static price table

	static void loadPriceMap() {
		if (!priceMap.empty()) return; // Already loaded, no need to reload
		ifstream file("hotel_room.csv");
		if (!file.is_open()) {
			cerr << "Unable to open file 'hotel_room.csv'!\n";
			exit(EXIT_FAILURE);
		}

		vector<string> types;
		string line, type;
		getline(file, line); // Read the header row
		stringstream headerStream(line);
		getline(headerStream, type, ','); // Skip the first column of the header
		while (getline(headerStream, type, ',')) {
			types.push_back(type);
		}

		while (getline(file, line)) {
			stringstream rowStream(line);
			string hotelName;
			getline(rowStream, hotelName, ',');

			for (size_t i = 0; i < types.size(); ++i) {
				string priceStr;
				getline(rowStream, priceStr, ',');
				if (!priceStr.empty()) {
					double price = stod(priceStr);
					priceMap[{hotelName, types[i]}] = price;
				}
			}
		}
		file.close();
	}
	/***************************************************************************************
		*    Title: c++ reading csv file
		*    Author: kbyun
		*    Date: Nov 12, 2013
		*    Availability: https://stackoverflow.com/questions/19936483/c-reading-csv-file
		***************************************************************************************/

public:
	Room() = default;
	void calcPrice(const string& hotelname) {
		loadPriceMap();
		auto key = make_pair(hotelname, roomtype);
		if (priceMap.find(key) == priceMap.end()) {
			cerr << "Error: No price found for hotel '" << hotelname
				<< "' and room type '" << roomtype << "'!\n";
			return ; // Return a special value or throw an exception
		}
		baseprice = priceMap[key];
		finalprice += baseprice;

		
	}

	void addAmenityPrice(double amount) {
		finalprice += amount;
	}

	int getCapacity() { return capacity; }
	double getPrice() { return finalprice; }
	int getNumGuest() { return numguest; }
	void setNumGuest(int n) { numguest = n; }
	void printAmenities() {
		cout << "The Amenities for " << roomtype <<": \n";
		for (int i = 0;i < amenities.size();i++) {
			cout << amenities[i] << " ;";
		}
		cout << endl;
	}
	virtual void printRoomDetails(const string& hotelname) {
		cout << "\n*************************************************************\n";
		cout << "Room type: " << roomtype << endl;
		cout << "Room capacity: " << capacity << endl;
		printAmenities();
		calcPrice(hotelname);
		cout << "Room price(RM/day): " << finalprice << endl;
		cout << "*************************************************************\n";

	}
	void printroomtypedetails(const string& hotelname) {
		cout << "\n*************************************************************\n";
		cout << "Standard: \n";
		roomtype = "standard";
		calcPrice(hotelname);
		cout << "The price: " << finalprice << "RM/day" << endl;
		cout << "The capacity: 2\n";
		cout << "Amenities: WI_FI; Parking; Telephone; laundry; Roomcleaning\n";
		
		
		cout << "\nDeluxe: \n";
		roomtype = "deluxe";
		finalprice = 0;
		calcPrice(hotelname);
		cout << "The price(without added amenities): " << finalprice << "RM/day" << endl;
		cout << "The capacity: 3\n";
		cout << "Amenities can be added: \n";
		cout << "a: Add Mini Bar\n";
		cout << "b: Add Coffee Maker\n";
		cout << "c: Add Both Mini Bar and Coffee Maker\n";
		cout << "d: No additional amenities\n";

		cout << "\nSuite: \n";
		roomtype = "suite";
		finalprice = 0;
		calcPrice(hotelname);
		cout << "The price(without added amenities): " << finalprice << "RM/day" << endl;
		cout << "The capacity: 5\n";
		cout << "Amenities can be added: \n";
		cout << "a: Add Luxury Linens and Pillows\n";
		cout << "b: Add Private Butler Service\n";
		cout << "c: Add Both Luxury Linens and Pillows and Private Butler Service\n";
		cout << "*************************************************************\n";
		roomtype = "";
	}
};


// Define the static variable outside the class
map<pair<string, string>, double> Room::priceMap;

#endif // !ROOM_H_INCLUDED