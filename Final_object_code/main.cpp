#include "Room.h"
#include "Standard.h"
#include "Suite.h"
#include "Deluxe.h"
#include "User.h"
#include "Booking.h"
#include "Hotel.h"
#include "Destination.h"


void displayRoomTypes();
void bookRoom(User& user1);

int main() {

	cout << "Welcome to Booking Travel Application!\n";
	char isLogin = getValidCharInput("a.Log in\nb.Exit\nPlease make a selection: ", "ab");
	if (isLogin == 'b') {
		cout<< "Thank you for using Booking Travel Application. Goodbye!\n";
		return 0;
	}

	User user1;
	if (user1.Login()) {
		while (true) {

			cout << "\nMain selection menu:\n";
			cout << "a.Display room types\n";
			cout << "b.Book room\n";
			cout << "c.View room booking\n";
			cout << "d.Exit\n";
			char choice = getValidCharInput("Enter your choice: ", "abcd");
			if (choice == 'd') {
				break;
			}else if (choice == 'a') {// display room type
				displayRoomTypes();
			}else if (choice == 'b') {
				bookRoom(user1);
			}else if (choice == 'c') {
				user1.viewUserBooking();
			}
		}
	}
	return 0;
}

void displayRoomTypes() {
	cout << "\nPlease choose your destination: \n";
	cout << "a.NewYork\nb.London\nc.Paris\nd.Tokyo\ne.Sydney\n";
	char dest_choice = getValidCharInput("Enter your choice: ", "abcde");
	Destination dest1(dest_choice);
	dest1.listHotels();

	char hotel_char_choice = getValidCharInput("Enter your choice: ", "12345");
	int hotel_choice = hotel_char_choice - '0'; // Convert char to integer
	cout << "a.Standard\nb.Deluxe\nc.Suite\n";
	Room room1;
	room1.printroomtypedetails(dest1.getHotels()[hotel_choice - 1].getHotelname());
}

void bookRoom(User& user1) {
reBooking:
	cout << "\nPlease choose your destination: \n";
	cout << "a.NewYork\nb.London\nc.Paris\nd.Tokyo\ne.Sydney\n";
	char dest_choice = getValidCharInput("Enter your choice: ", "abcde");
	Destination dest1(dest_choice);
	dest1.listHotels();

	char hotel_char_choice = getValidCharInput("Enter your choice: ", "12345");
	int hotel_choice = hotel_char_choice - '0'; // Convert char to integer
	string hotel_Name = dest1.getHotels()[hotel_choice - 1].getHotelname();

	cout << "a.Standard\nb.Deluxe\nc.Suite\n";
	Room* room1 = nullptr;
	char roomtype_choice = getValidCharInput("Enter your choice: ", "abc");
	cout << "\n";

	if (roomtype_choice == 'a') {
		room1 = new Standard;
		room1->printRoomDetails(hotel_Name);
	}
	else if (roomtype_choice == 'b') {
		Deluxe deluxe1;
		deluxe1.AddAmenities();
		room1 = &deluxe1;
		room1->printRoomDetails(hotel_Name);
	}
	else if (roomtype_choice == 'c') {
		Suite suite1;
		suite1.AddAmenities();
		room1 = &suite1;
		room1->printRoomDetails(hotel_Name);
	}

	int numGuest = getValidatedIntInput("\nPlease enter the number of persons : ", 1, room1->getCapacity());
	room1->setNumGuest(numGuest);
	int numRooms = getValidatedIntInput("Please enter the number of room : ", 1, 10);

	Booking booking1;
	cout << "Please enter the check in date: \n";
	booking1.setDate('a');
	cout << "\nPlease enter the check out date: \n";
	booking1.setDate('b');
	booking1.setNumRoom(numRooms);
	booking1.setDest(dest_choice);
	booking1.setHotel(hotel_Name);
	booking1.setuserID(user1.getUserID());
	booking1.setDays();
	booking1.calcSubtotal(room1);
	booking1.printBooking();

	cout << "a.Credit card\nb.E-wallet\nc.Cash on delivery\n";
	char pay_choice = getValidCharInput("Enter your choice: ", "abc");
	booking1.setMethod(pay_choice);

	char confirm_choice = getValidCharInput("\nPlease confirm the booking(y/n): ", "yn");
	if (confirm_choice == 'n') {
		booking1.subCurrentID();
		goto reBooking;
	}

	booking1.saveBooking("Bookings.csv");
	cout << "\nSuccessfully saved!\n";
}
