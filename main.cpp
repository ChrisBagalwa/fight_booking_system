#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Declaration
string welcome();
void print_seats(string flight[]);
void populate_seats();
bool validate_flight(string a);
bool validate_seat(string a, int b);
bool validate_book(string a);
void print_ticket(string passenger[], int i);

string flights [5][52];
string passengers [4][250];

int main()
{
    string seat, flight, book = "y";
    int int_flight, p = 0, j = 0;
    int seat_number, seat_price;
    populate_seats();
    // While Book is 'Y' Display the available departure times
    while (book == "y" || book == "Y")
        {
            passengers[p][0] = (welcome());
            // Display available time for flights
            cout << "\nThe available travel times for flights are:" << endl;
            cout << "   Depart\tArrive" << endl;

            for (int i = 0; i < 5; i++)
                {
                    if (flights[i][51] != "50")
                        {
                    cout << i + 1 << ". " << flights[i][0] << endl;
                    }
                    else if (j < 4){
                        j++;
                    }
                    else
                        {
                        cout << "\nAll flights are booked" << endl;
                        return 0;
                    }
            }
            // prompt the user to choose a preferred departure time (option 1 -5).
            cout << "Choose the time by enetering the option number from the displayed list:" << endl;
            do
                {
                cin >> flight;
            }
            while(!validate_flight(flight));
            // Display available seats
            cout << "\nThe available seats for the time selected are as follows:" << endl;

            int_flight = stoi(flight) - 1;
            print_seats(flights[int_flight]);
            // Prompt the user to to enter seat number
            cout << "Please Key in a seat number to chose a seat (eg:A2)" << endl;

            do
                {
                cin >> seat;
            }
            while (!validate_seat(seat, int_flight));

            for (int i = 0; i < 51; i++)
                {
                // If any seats have already been booked for that time,
                // the booked seats should be indicated and displayed using �**�
                if (flights[int_flight][i] == seat)
                {
                    flights[int_flight][i] = "**";
                    seat_number = i;
                    break;
                }
            }
            // The front four rows are considered as �First Class�
            if (seat_number < 25)
                {
                // First class travel ticket is 20% more costly than the economy class (R1920.00)
                seat_price = 1920;
                passengers[p][4] = "First class";
            }
            else
            {
                // The cost for economy class is fixed at R1600.00
                seat_price = 1600;
                passengers[p][4] = "Economy class";
            }
            passengers[p][1] = flight;
            passengers[p][2] = seat;
            passengers[p][3] = to_string(seat_price);

            flights[int_flight][51] = to_string(stoi(flights[int_flight][51]) + 1);
            // Display ticket details
            print_ticket(passengers[p], int_flight);
            // Ask user if their would like to book another flight
            cout << "\nDo you want to make another booking (Y/N)?" ;
            do
                {
                cin >> book;
                cin.get();
            }while(!validate_book(book));

            p++;
            cout << endl;
        }

        for (int i = 0; i < 5; i++)
            {
            // Display number of Bookings made
            cout << "Number of bookings made for " << flights[i][0].substr(0,5);
            cout << ": " << flights[i][51] << endl;
        }
    return 0;
}
// Define welcome function
string welcome()
{
    string passenger;
    // Welcome the user to the fligh booking system
    cout << "Welcome to the Chris's Flight Booking System\n" << endl;
    // Prompt the user to enter full name
    cout << "Enter Full Name" << endl;

    getline(cin,passenger);

    return passenger;
}

// Define print_seat function
void print_seats(string flight[])
{
    // Display flight class
    int k = 0;
    cout << "First class(1920.00)" << endl;
    for (int j = 0; j < 9; j++){
        if (k == 24){
            cout << "Economy class(1600.00)" << endl;
        }
        cout << "|";
        for (int i = 0; i < 3; i++)
            {
            cout << flight[k+1] << "|";
            k++;

                if (k > 49)
                    {
                    cout << endl;
                    return;
            }
        }

        cout << "----";

        for (int i = 0; i < 3; i++)
            {
            cout << "|" << flight[k+1];
            k++;
        }
        cout << "|" << endl;
    }
}
// Define populate_seats function
void populate_seats()
{
    flights[0][0] = "07:00\t09:30";
    flights[1][0] = "09:00\t11:30";
    flights[2][0] = "11:00\t13:30";
    flights[3][0] = "13:00\t15:30";
    flights[4][0] = "15:00\t17:30";

    for (int a = 0; a < 5; a++)
        {
        int b = 0;
        for (int i = 17; i < 26; i++)
        {
            for ( int j = 1; j < 7; j++)
            {
                if (i == 25 && j > 2)
                    {
                    break;
                }
                string seat = char('0' + i) + to_string(j);
                flights[a][b+1] = seat;

                b++;
            }
            flights[a][b+1] = "0";
        }
    }
}
// Define print_ticket function display ticket details
void print_ticket(string passenger[], int i)
{
    int name = passenger[0].length();
    cout << "****************************" << endl;
    cout << "Travel Ticket for FLIGHT " << i + 1 << endl;
    cout << "****************************" << endl;

    cout << left << setw(15) << "Name " << ": " << passenger[0];
    cout << setw(13) << "" << "Travel Ticket Class " << ": " << passenger[4] << endl;

    cout << setw(31 + name) << "" << setw(20) << "Seat No." << ": " << passenger[2] << endl;

    cout << setw(15) << "Departure" << ": " << setw(13 + name) << "Johannesburg";
    cout << setw(20) << "Departure Time" << ": " << flights[i][0].substr(0,5) << endl;

    cout << setw(15) << "Destination" << ": " << setw(13 + name) << "Cape Town";
    cout << setw(20) << "Arrival Time" << ": " << flights[i][0].substr(6,10) << endl;

    cout << "\n**************************" << endl;
    cout << "Amount: R" << passenger[3] << endl;
    cout << "Thank you for booking with COS 1511 Booking System." << endl;
    cout << "Your travel agent is Damian Jacobs" << endl;
    cout << "****************************" << endl;
}
// Define validate_flight function
bool validate_flight(string a)
{
    // The option selected should be validated for 1-5
    for (int i = 1; i < 6; i++)
        {
        if (a == to_string(i))
        {
            return true;
        }
    }
    cout << "Incorrect option! Please choose from 1-5." << endl;
    return false;
}
// Define validate_seat function
bool validate_seat(string a, int b)
{
    for (int i = 0; i < 51; i++)
        {
        if (flights[b][i] == a)
            {
            return true;
        }
    }
    // If the seat is already booked, Prompt the user to input another seat number
    cout << "Sorry the seat is taken. Please choose a seat that is available" << endl;
    return false ;
}

bool validate_book(string a){
    while(a != "y" && a != "n" & a != "Y" && a != "N")
        {
        // Prompt the user to enter valid option
        cout << "Enter a valid option: Y/N:";
        return false;
    }
    return true;
}
