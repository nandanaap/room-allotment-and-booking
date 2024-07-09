#include <iostream>
#include <limits>
#include <cstring>
#include <ctime>


using namespace std;

const int MAX_ROOMS = 3;
const char* ROOM_NAMES[MAX_ROOMS] = {"Workspace", "Lab", "Meetings"};
const int ROOM_CAPACITY[MAX_ROOMS] = {40, 10, 20}; // Example capacities for each room
const int ROOM_NUMBERS[MAX_ROOMS] = {1, 2, 3}; // Room numbers for Meetings, Lab, Workspace

const int MAX_AREAS = 5;
const char* AREA_NAMES[MAX_AREAS] = {"Stuff Area", "Kitchen Area", "Coffee Area", "Break Area", "Lean Area"};
const int AREA_CAPACITY[MAX_AREAS] = {15,20, 20,10,30}; // Example capacities for each room
const int AREA_NUMBERS[MAX_AREAS] = {4, 5, 6, 7, 8}; // Room numbers for other areas

class RoomBookingSystem {
private:
    struct Room {
        char roomName[20];
        char host[50];
        char phoneNumber[11]; // New field for phone number
        char startTime[6];  // HH:MM format
        char endTime[6];    // HH:MM format
        int chairCapacity;
        int roomNumber;
    };

    Room rooms[MAX_ROOMS];  // Array of rooms
    int roomCount;          // Number of currently available rooms

public:
    RoomBookingSystem() {
        roomCount = 0;
    }

    void bookRoom();
    void setHost();
    void setStartTime();
    void setEndTime();
    void setChairCapability();
    void defineRoomNames();
    bool isValidTimeFormat(const char* time);
    bool isValidPhoneNumber(const char* phoneNumber);
    bool isRoomAvailable(int roomNumber);
    void displayRoomOptions();
    void displayRoomDetails();
    int getRoomChoice();
    void displaydate();
};

bool RoomBookingSystem::isValidTimeFormat(const char* time) {
    // Check if time is in HH:MM format
    if (strlen(time) != 5)
        return false;

    if (time[2] != ':')
        return false;

    int hour = (time[0] - '0') * 10 + (time[1] - '0');
    int minute = (time[3] - '0') * 10 + (time[4] - '0');

    if (hour < 0 || hour > 23 || minute < 0 || minute > 59)
        return false;

    return true;
}

bool RoomBookingSystem::isValidPhoneNumber(const char* phoneNumber) {
    // Check if phone number is 10 digits
    if (strlen(phoneNumber) != 10)
        return false;

    // Check if all characters are digits
    for (int i = 0; i < 10; ++i) {
        if (!isdigit(phoneNumber[i]))
            return false;
    }

    return true;
}

bool RoomBookingSystem::isRoomAvailable(int roomNumber) {
    for (int i = 0; i < roomCount; ++i) {
        if (rooms[i].roomNumber == roomNumber)
            return false; 
             // Room is already booked
    }
    return true;  // Room is available
}

void RoomBookingSystem::displayRoomOptions() {
    cout << "Available rooms for booking:\n";
    for (int i = 0; i < MAX_ROOMS; ++i) {
        cout << i + 1 << ". " << ROOM_NAMES[i] << " (Capacity: " << ROOM_CAPACITY[i] << ", Room No: " << ROOM_NUMBERS[i] << ")\n";
    }
    /*cout<<"Room for informal discussion :"<<endl;
    for (int i = 0; i < MAX_AREAS; ++i) {
        cout << i + 4 << ". " << AREA_NAMES[i] << " (Capacity: " << AREA_CAPACITY[i] << ", Room No: " <<AREA_NUMBERS [i] << ")\n";
    }*/
}

int RoomBookingSystem::getRoomChoice() {
    int choice;
    displayRoomOptions();
    cout << "Enter the room number to book: ";
    cin >> choice;

    if(choice < 1 || choice > MAX_ROOMS)
    {
        cout << "Invalid choice. Please enter a number between 1 and " << MAX_ROOMS << ": ";
        cin >> choice;
    }

    return choice - 1;
}

void RoomBookingSystem::bookRoom() {
    if (roomCount >= MAX_ROOMS) {
        cout << "No rooms available for booking.\n";
        return;
    }

    Room newRoom;

    cout << "Enter host's name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(newRoom.host, 50);

    int roomChoice = getRoomChoice();
    strcpy(newRoom.roomName, ROOM_NAMES[roomChoice]);
    newRoom.chairCapacity = ROOM_CAPACITY[roomChoice];
    newRoom.roomNumber = ROOM_NUMBERS[roomChoice];

    cout << "Enter phone number (10 digits): ";
    cin >> newRoom.phoneNumber;

    while (!isValidPhoneNumber(newRoom.phoneNumber)) {
        cout << "Invalid phone number format. Please enter 10 digits: ";
        cin >> newRoom.phoneNumber;
    }

    cout << "Enter start time (HH:MM): ";
    cin >> newRoom.startTime;

    while (!isValidTimeFormat(newRoom.startTime)) {
        cout << "Invalid start time format. Use HH:MM format: ";
        cin >> newRoom.startTime;
    }

    cout << "Enter end time (HH:MM): ";
    cin >> newRoom.endTime;

    while (!isValidTimeFormat(newRoom.endTime)) {
        cout << "Invalid end time format. Use HH:MM format: ";
        cin >> newRoom.endTime;
    }

    rooms[roomCount++] = newRoom;

    cout << "Room booked successfully! Room Number: " << newRoom.roomNumber << "\n";
}

void RoomBookingSystem::setHost() {
    int roomNumber;
    cout << "Enter the room number to set the host: ";
    cin >> roomNumber;

    for (int index = 0; index < roomCount; ++index) {
        if (rooms[index].roomNumber == roomNumber) {
            cout << "Enter new host name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.getline(rooms[index].host, 50);
            cout << "Host name updated for room " << rooms[index].roomName << ".\n";
            return;
        }
    }

    cout << "Room number " << roomNumber << " not found.\n";
}

void RoomBookingSystem::setStartTime() {
    int roomNumber;
    cout << "Enter the room number to set start time: ";
    cin >> roomNumber;

    for (int index = 0; index < roomCount; ++index) {
        if (rooms[index].roomNumber == roomNumber) {
            cout << "Enter new start time (HH:MM): ";
            cin >> rooms[index].startTime;

            while (!isValidTimeFormat(rooms[index].startTime)) {
                cout << "Invalid start time format. Use HH:MM format: ";
                cin >> rooms[index].startTime;
            }

            cout << "Start time updated for room " << rooms[index].roomName << ".\n";
            return;
        }
    }

    cout << "Room number " << roomNumber << " not found.\n";
}

void RoomBookingSystem::setEndTime() {
    int roomNumber;
    cout << "Enter the room number to set end time: ";
    cin >> roomNumber;

    for (int index = 0; index < roomCount; ++index) {
        if (rooms[index].roomNumber == roomNumber) {
            cout << "Enter new end time (HH:MM): ";
            cin >> rooms[index].endTime;

            while (!isValidTimeFormat(rooms[index].endTime)) {
                cout << "Invalid end time format. Use HH:MM format: ";
                cin >> rooms[index].endTime;
            }

            cout << "End time updated for room " << rooms[index].roomName << ".\n";
            return;
        }
    }

    cout << "Room number " << roomNumber << " not found.\n";
}

void RoomBookingSystem::setChairCapability() {
    int roomNumber;
    cout << "Enter the room number to set chair capacity: ";
    cin >> roomNumber;

    for (int index = 0; index < roomCount; ++index) {
        if (rooms[index].roomNumber == roomNumber) {
            cout << "Enter new chair capacity: ";
            cin >> rooms[index].chairCapacity;
            if(rooms[index].chairCapacity>100){
                cout<<"max limit exceeded!"<<endl;
                rooms[index].chairCapacity=ROOM_CAPACITY[index];
            }
            else{
            cout << "Chair capacity updated for room " << rooms[index].roomName << ".\n";
            }
            return;
        }
    }

    cout << "Room number " << roomNumber << " not found.\n";
}

void RoomBookingSystem::defineRoomNames() {
    cout << "\n\t\t\t----------Room Numbers---------- \t\t\t\n";
    for (int i = 0; i < MAX_ROOMS; ++i) {
        cout << ROOM_NAMES[i] << ": Room No. " << ROOM_NUMBERS[i] << "\n";
    }
    for (int i = 0; i < MAX_AREAS; ++i) {
        cout << AREA_NAMES[i] << ": Room No. " << AREA_NUMBERS[i] << "\n";
    }
}

void RoomBookingSystem::displayRoomDetails() {
    if (roomCount == 0) {
        cout << "No rooms have been booked yet.\n";
        return;
    }

    cout << "\n\t\t\t******* Booked Room Details *******\t\t\t\n";
    for (int i = 0; i < roomCount; ++i) {
        cout << "Room Name: " << rooms[i].roomName << "\n";
        cout << "Host Name: " << rooms[i].host<< "\n";
        cout << "Phone Number: " << rooms[i].phoneNumber << "\n";
        cout << "Start Time: " << rooms[i].startTime << "\n";
        cout << "End Time: " << rooms[i].endTime << "\n";
        cout << "Chair Capacity: " << rooms[i].chairCapacity << "\n";
        cout << "Room Number: " << rooms[i].roomNumber << "\n\n";
    }
}
void RoomBookingSystem::displaydate(){
   time_t tt; 
  
    // Declaring variable to store return value of 
    // localtime() 
    struct tm* ti; 
  
    // Applying time() 
    time(&tt); 
  
    // Using localtime() 
    ti = localtime(&tt); 
  
    cout << "Today's Day Date Time is = "
         << asctime(ti); 
    
}


int main() {
    RoomBookingSystem booking;
    cout<<endl<<"************************************************"<<endl;
    cout<<endl<<"--------WELCOME TO ROOM BOOKING SYSTEM----------"<<endl;
    cout<<endl<<"************************************************"<<endl;

    int choice;
    do {
        cout<<"----------MAIN MENU----------"<<endl;
        booking.displaydate();
        cout << "\n1. Book a room";
        cout << "\n2. Set the host";
        cout << "\n3. Set the start time";
        cout << "\n4. Set the end time";
        cout << "\n5. Set the chair booking capability";
        cout << "\n6. Define the room names";
        cout << "\n7. Display details";
        cout << "\n0. Exit\n";

        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                booking.bookRoom();
                break;
            case 2:
                booking.setHost();
                break;
            case 3:
                booking.setStartTime();
                break;
            case 4:
                booking.setEndTime();
                break;
            case 5:
                booking.setChairCapability();
                break;
            case 6:
                booking.defineRoomNames();
                break;
            case 7:
                booking.displayRoomDetails();
                break;
            case 0:
                cout << "loging out\n";
                break;
            default:
                cout << "Invalid Choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
