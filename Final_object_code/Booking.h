#pragma once
#ifndef BOOKING_H_INCLUDED
#define BOOKING_H_INCLUDED
#include "Room.h"
#include "Date.h"
#include <ctime>
using namespace std;

int getValidatedIntInput(const string& prompt, int minVal, int maxVal) {
	int input;
	while (true) {
		cout << prompt;
		cin >> input;
		if (!cin.fail() && cin.peek() == '\n' && input >= minVal && input <= maxVal) {
			break;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Please enter a valid number(" << minVal << " - " << maxVal << ").\n";

	}
	return input;
}

class Booking {
private:
	Date check_out;
	Date check_in;
	int Days = 0;
	double subtotal = 0.0;
	double taxes = 0.0;
	double totalAmt= 0.0;
	string paymethod;
	int bookingid = 0;
	int Numroom;
	string userID;
	static int currentID;
	string dest;
	string hotel;
	
	//calclute days
	void calcTaxes() {
		taxes = 0.10 * subtotal;
	}
	void calctotalAmt() {
		totalAmt = subtotal + taxes;
	}
	void calcDays() {
		Days = check_out.calculateDateDifference(check_in);
	}

	static void loadMaxIDFromFile() {
		ifstream file("Bookings.csv");
		if (!file.is_open()) {
			currentID = 0;
			cerr << "Unable to open file 'Bookings.csv'!\n";
			exit(EXIT_FAILURE);
		}
		
		string line;
		int maxID = 0;

		while (getline(file, line)) {
			stringstream ss(line);
			string id_str, temp;
			getline(ss, id_str, ',');
			try {
				int id = stoi(id_str); // Attempt to convert the string id_str to an integer id
				maxID = max(maxID, id); // Update maxID to the current maximum value
			}
			catch (...) {
				continue; // If the conversion fails, skip the line and proceed to the next one
			}	
		}

		currentID = maxID;
		file.close();
	}
	/***************************************************************************************
*    Title: Extracting Maximum ID from CSV File
*    Author: Adapted from techniques discussed in public programming forums
*    Date: Dec 27, 2024
*    Availability: https://stackoverflow.com/questions/19936483/c-reading-csv-file
***************************************************************************************/

	static int generateID() {
		loadMaxIDFromFile();
		return ++currentID;
	}
	

public:
	Booking() {
		bookingid = generateID();
	}
	
	Booking(Date out, Date in, Room* Room_ptr,string userid,string d,string h) 
		: check_out(out), check_in(in), bookingid(generateID()),userID(userid),dest(d),hotel(h) {
		calcDays();
		calcSubtotal(Room_ptr);
		calcTaxes();
		calctotalAmt();
	}

	void calcSubtotal(Room* Room_ptr) {
		subtotal = ((1 + (Room_ptr->getNumGuest() - 1) * 0.5) * (Room_ptr->getPrice()) * Days * Numroom);
		calcTaxes();
		calctotalAmt();
	}
	static void subCurrentID() { currentID--; }
	void setNumRoom(int n) { Numroom = n; }
	int getNumRoom() { return Numroom; }
	double getSubtotal() const{return subtotal;}
	double getTaxes()const { return taxes; }
	double gettotalAmt()const { return totalAmt; }
	int getBookingid()const { return bookingid; }
	void setBookingid() { bookingid = currentID; }
	string getPaymethod() { return paymethod; }
	void setuserID(string uid) { userID = uid; }
	string getuserID() { return userID; }
	void setDays() { calcDays(); }
	int getDays() { calcDays(); return Days; }
	void setHotel(string h) { hotel = h; }
	string getHotel() { return hotel; }
	string getDest() { return dest; }
	
	void setDest(char c) {
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

	void setMethod(char c) {
		if (c == 'a') {
			paymethod = "Credit card";
		}
		else if (c == 'b') {
			paymethod = "e-wallet";
		}
		else {
			paymethod = "cash on delivery";
		}
	}
	
	void setDate(char choice_in_out ) {
		Date date1;
		int d, m, y;
		bool status = true;

		y = getValidatedIntInput("Please enter the year: ", 2024, 2026);
		
		date1.setYear(y);


		cout << "Please enter the month: ";
		cin >> m;

		while (status) {

			try {
				date1.setMonth(m);
				status = false;
			}
			catch (Date::Invalid_month)
			{
				cout << "Invalid Input! Please enter the month again: ";
				cin >> m;
			}
		}

		status = true;
		cout << "Please enter the day: " ;
		cin >> d;
		while (status) {

			try {
				date1.setDay(d);
				status = false;
			}
			catch (Date::Invalid_day)
			{
				cout << "Invalid Input! Please enter the day again: ";
				cin >> d;
			}
			catch (Date::Invalid_day_leap_year)
			{
				cout << "Leap Year! Invalid Input! Please enter the day again:" ;
				cin >> d;
			}

		}
		if (choice_in_out == 'a') {
			check_in = date1;
		}
		else if (choice_in_out == 'b') {
			check_out = date1;
		}

	}
	
	
	void printBooking() {
		cout << "\n*************************************************************\n";
		cout << "BookingID: " << bookingid << endl;
		cout << "UserID: " << userID << endl;
		cout << "Destination: " << dest << endl;
		cout << "Hotel: " << hotel << endl;
		cout << "The number of room: " << Numroom << endl;
		cout << "Check_in: ";
		check_in.printDate();
		cout << "Check_out: ";
		check_out.printDate();
		cout << "Days stayed: " << getDays() << endl;
		cout << "Subtotal: RM" << subtotal << endl;
		cout << "Taxes: RM" << taxes << endl;
		cout << "Total amount: RM" << totalAmt << endl;
		cout << "*************************************************************\n";
	}
	void saveBooking(const string filename) {
		ofstream file(filename, ios::app);

		if (!file.is_open()) {
			cout << "Error: Could not open the transaction file for writing!" << endl;
			return;
		}

		file.seekp(0, ios::end);
		if (file.tellp() == 0) {
			file << "BookingID,UserID,Destination,Hotel,Check_in,Check_out,StayedDays,Subtotal,Taxes,TotalAmount,PayMethod\n";
		}

		file << bookingid << ","
			<< userID << ","
			<<dest<<","
			<<hotel<<","
			<<Numroom<<","
			<< check_in.getYear() << "-" << check_in.getMonth() << "-" << check_in.getDay() << ","
			<< check_out.getYear() << "-" << check_out.getMonth() << "-" << check_out.getDay() << ","
			<< getDays() << ","
			<<subtotal<<","
			<<taxes<<","
			<< totalAmt << ","
			<<paymethod<<"\n";
		file.close();
	}
	
};

int Booking::currentID = 0;

#endif // !BOOKING_H_INCLUDED
