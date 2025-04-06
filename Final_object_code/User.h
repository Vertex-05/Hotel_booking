#pragma once
#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#include"Booking.h"
#include<unordered_map>
string getValidStringInput(const string& prompt, const vector<string>& validvactor) {
	string input;
	while (true) {
		cout << prompt;
		cin >> input;
		if (find(validvactor.begin(), validvactor.end(), input) != validvactor.end()) {
			break;
		}
		cout << "Invalid input. Please enter again.\n";
	}
	return input;
}
class User {
private:
	string username;
	string password;
	string email;
	string userID;
	static int currentID;
	vector <string>usernames;
	unordered_map<string, string>credentials;
	void loadsystem(const string& filename) {
		ifstream file(filename);
		if (!file.is_open()) {
			cerr << "Failed to open file: " << filename << endl;
			return;
		}
		string line, name, password, id;
		getline(file, line);// Skip the first line
		while (getline(file, line)) {
			stringstream rowStream(line);
			if (getline(rowStream, id, ',') && getline(rowStream, name, ',') && getline(rowStream, password, ',')) {
				usernames.push_back(name);
				credentials[name] = password;
			}
		}
		file.close();
	}
	
	

public:
	User() = default;
	User(string n, string p, string e) {
		username = n;
		password = p;
		email = e;
	}

	string getUserID() {
		string filename = "Users.csv";
		ifstream file(filename);
		if (!file.is_open()) {
			cerr << "Failed to open file: " << filename << endl;
			return "";
		}
		string line, name, id;
		getline(file, line);// Skip the first line
		while (getline(file, line)) {
			stringstream rowStream(line);
			if (getline(rowStream, id, ',') && getline(rowStream, name, ',')) {
				if (username == name) {
					return id;
				}
			}
		}
		file.close();
		cout << "No user ID was found!\n";
		return "";
	}
	bool Login() {
		loadsystem("Users.csv");
		int loginTimes = 0;

		username = getValidStringInput("Please enter your username: ", usernames);
		while (loginTimes < 5) {
			cout << "Please enter your password: ";
			string input_password;
			cin >> input_password;
			if (input_password == credentials[username]) {
				cout << "Successful login!\n ";
				cout << "Hello, " << username << "!" << endl;
				return true;
			}
			cout << "Incorrect password, please enter agagin.\n";
			loginTimes++;
		}
		cout << "You have entered the wrong password five times.\nPlease try again later!\n";
		return false;
	}
	void printUserinfo() {
		cout << "Username: " << username << endl;
		cout << "Email: " << email << endl;
	}

	void viewUserBooking() {
		string filename = "Bookings.csv";
		ifstream file(filename);
		string line;
		userID = getUserID();
		
		if (file.is_open()) {
			cout << "Booking history for user: " << username << endl;
			getline(file, line);
			bool hasBookings = false;
			
			while (getline(file, line)) {
				hasBookings = true;
				stringstream ss(line);
				string bookingid, storeduserid, Destination, Hotel,NumRoom, Check_in, Check_out, Day_stayed, Subtotal, Taxes, Total_amount,payMethod;

				getline(ss, bookingid, ',');
				getline(ss, storeduserid, ',');
				getline(ss, Destination, ',');
				getline(ss, Hotel, ',');
				getline(ss, NumRoom, ',');
				getline(ss, Check_in, ',');
				getline(ss, Check_out, ',');
				getline(ss, Day_stayed, ',');
				getline(ss, Subtotal, ',');
				getline(ss, Taxes, ',');
				getline(ss, Total_amount, ',');
				getline(ss, payMethod, ',');

				if (storeduserid == userID) {
					cout << "\n*************************************************************\n";
					cout << "BookingID: " << bookingid << endl;
					cout << "UserID: " << userID << endl;
					cout << "Destination: " << Destination << endl;
					cout << "Hotel: " << Hotel << endl;
					cout << "NumRoom: " << NumRoom << endl;
					cout << "Check_in: " << Check_in << endl;
					cout << "Check_out: " << Check_out << endl;
					cout << "Days stayed: " << Day_stayed << endl;
					cout << "Subtotal: " << Subtotal << endl;
					cout << "Taxes: " << Taxes << endl;
					cout << "Total amount: " << Total_amount << endl;
					cout << "Pay Method: " << payMethod << endl;
					cout << "*************************************************************\n";
				}
			}
			if (!hasBookings) {
				cout << "No bookings found for the user: " << userID << endl;
			}
			file.close();
		}
		else {
			cout << "Unable to open booking file. \n";
		}
	}
};
#endif // !USER_H_INCLUDED
