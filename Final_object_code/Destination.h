#pragma once
#ifndef DESTINATION_H_INCLUDED
#define DESTINATION_H_INCLUDED
#include "Hotel.h"

class Destination {
private:
	string dest;
	vector <Hotel> Hotels;
	char dest_choice;
	void setHotels() {
		multimap<string, string> hotelmap;
		string rowhotel, line, destination;

		ifstream file("dest_hotel.csv");
		if (!file.is_open()) {
			cerr << "Unable to open file 'dest_hotel.csv'!\n";
			exit(EXIT_FAILURE);
		}

		// ��ȡ�ļ����ݲ���� multimap
		getline(file, line); // ����������
		while (getline(file, line)) {
			stringstream rowstream(line);
			if (getline(rowstream, destination, ',') && getline(rowstream, rowhotel, ',')) {
				hotelmap.insert({ destination, rowhotel });
			}
		}

		file.close();

		// ������Ŀ��Ŀ�ĵ���صľƵ�
		auto range = hotelmap.equal_range(dest); // ֻ����ָ����Ŀ�ĵ�
		Hotels.clear(); // ��յ�ǰ�Ƶ��б���ֹ�ۻ�����
		for (auto i = range.first; i != range.second; ++i) {
			Hotels.push_back(Hotel(i->second));
		}
	}



public:
	Destination() = default;
	Destination(char c) {
		dest_choice = c;
		setdest(c);
		setHotels();
	}
	void setdest(char c) {
		if (c == 'a') {
			dest = "NewYork";
		}if (c == 'b') {
			dest = "London";
		}if (c == 'c') {
			dest = "Paris";
		}if (c == 'd') {
			dest = "Tokyo";
		}if (c == 'e') {
			dest = "Sydney";
		}
	}
	vector <Hotel> getHotels() { return Hotels; }
	void listHotels() {
		cout << "\n*************************************************************\n";
		cout << "The destination: " << dest << endl;
		cout << "The hotels can be chosen: \n\n";
		for (int m = 0; m < Hotels.size();m++) {
			cout << m + 1<<") ";
			Hotels[m].printHotel();
			cout << endl;
		}
		cout << "*************************************************************\n";
	}
};
#endif // !DESTINATION_H_INCLUDED