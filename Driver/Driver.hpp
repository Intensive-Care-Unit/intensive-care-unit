#include "Hospital.hpp"
#include "State.hpp"
#include "DriverHelperFunctions.hpp"
#include <ctime>
// Gets the role, doctor or director
std::string selectRole();
// Prints all units in the hospital
void printUnits();
// Allows the user to choose a unit from the menu
int getUnitIndexFromUser();
// Select a unit
int selectUnitDoctor();
int selectUnitDirector();
// Prints the patients in a table
void printPatients(int unitIndex);
// This function lets the user decide on whether to select the use by its name or id
void optionsOnPatientSelection(int unitIndex);
// After selecting a patient by its ID or NAME, this function selects
void managePatient(uint64_t id, int unitIndex);
// Runs on a separate thread, checks for a new measurement from the UPDATE function in care unit and patient
void checkNewMeasurement(Patient* p);
char quitThread ='\0'; // Global variable used to check if the user wants the quit the separate thread of excution

// These two functions return a boolean on whether a given patient exists or not
bool patientExists(uint64_t id, int unitIndex);
bool patientExists(std::string& name, int unitIndex);

// Clears the terminal
void clear() {
    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
    #elif defined (__APPLE__)
        system("clear");
    #endif
}

// Convert epoch time to normal time
tm* epochTimeToHumanTime(time_t epochTime){
    time_t et = epochTime;
	return gmtime(&et);
}


// Returns an int to be used as role (0 means doctor 1 means director)
std::string selectRole() {
    // Print the roles in table
    VariadicTable<std::string, std::string> vt({"Role 0", "Role 1"}, 15);
    vt.addRow("Doctor", "Director");
    vt.print(std::cout);

    // Role selection
    std::string role = "-1";
    do {
        std::cout << "Select a role > ";
        std::cin >> role; 
    } while (role != "1" && role != "0");
    return role;
}

// Allows the user to choose a unit from the menu
int getUnitIndexFromUser() {
        Hospital* h = State::getHospital();
        std::vector<CareUnit> units = h->getUnits();
        // Get the input from the user
        int unitNum = -1;
        do {
            std::cout << "Select from [0-" << units.size()-1 << "] for unit: ";
            std::cin >> unitNum;

        } while (unitNum > units.size()-1 || unitNum < 0);

        return (unitNum);
}

// Function to print all the units in the hospital
void printUnits () {
    Hospital *h = State::getHospital();
    VariadicTable<int, std::string, int> vt({"Index","Unit Name", "Size"}, 15);
    std::vector<CareUnit> units = h->getUnits();
    for (int i = 0; i < units.size(); i++) {
        std::string capitalizedUnitName = units[i].getServiceName();
        capitalizedUnitName[0] = toupper(capitalizedUnitName[0]);
        vt.addRow(i, capitalizedUnitName, units[i].getPatientsCount());
    }
    vt.print(std::cout);
}

// Returns an int: index to the unit in the CareUnits vector in hospital
int selectUnitDoctor() {
    // Printing units Table
    std::cout << "Please select a unit: " << std::endl;
    printUnits();
    return getUnitIndexFromUser();
}

// Returns an int: index to the unit in the CareUnits vector in hospital
int selectUnitDirector() {
    // Printing units Table
    std::cout << "Current Units: " << std::endl;
    printUnits();
    int selectedUnitIndex = -1;

    std::string choice = "1";
    while (choice == "1") {
        std::cout << "1- Add unit       2- Select unit\n>";
        std::cin >> choice;
        while (choice != "1" && choice != "2") {
            std::cout << "Please type a valid number > ";
            std::cin >> choice;
        }

        if (choice == "2") {
            clear();
            printUnits();
            selectedUnitIndex = getUnitIndexFromUser();
        } else {
            std::string unitName;
            std::cout << "[Adding Unit] Please type the new unit's name: ";
            std::cin >> std::ws;
            std::getline(std::cin, unitName);
            State::getHospital()->addUnit(unitName);
        }
    }
    return selectedUnitIndex;
}

// Runs on a separate thread, checks for a new measurement from the UPDATE function in care unit and patient
void checkNewMeasurement(Patient* p) {
    using namespace std::literals::chrono_literals;
    while (quitThread == '\0') {
        auto m = *p->getHistory().back();
        auto humanTime = epochTimeToHumanTime(m.getTime());
        std::cout << printDouble((double)m.getHeartRate(),2,20)       << " | "
            << printDouble((double)m.getBloodPressure().first, 2,20)     << " | "
            << printDouble((double)m.getBloodPressure().second,2,20) << " | " 
            << humanTime->tm_hour << ":" << humanTime->tm_min << ":" << humanTime->tm_sec << " GMT" <<"\n";

        std::this_thread::sleep_for(1s);
    }
}

// Prints the patients in a table
void printPatients(int unitIndex) {
    Hospital* h = State::getHospital();
    auto patients = h->getUnits()[unitIndex].getPatients();
    std::cout << "There are " << patients.size() << " patients in this unit." << std::endl;
    int counter = 0;

    VariadicTable<uint64_t, std::string, int, int, std::string> vt({"ID", "Name", "Age", "Weight", "Gender"}, 15);

    for (const auto& p: patients) {
        if (!p.second.isDeleted())
            vt.addRow(p.second.getId(), p.second.getName(), p.second.getAge(), p.second.getWeight(), (char)p.second.getGender() == 'f' ? "Female" : "Male");
    }

    vt.print(std::cout);
}

// After selecting a patient by its ID or NAME, this function selects
void managePatient(uint64_t id, int unitIndex) {
    clear();
    Hospital* h = State::getHospital();
    Patient& p = h->getUnits()[unitIndex].getPatient(id);
    // Print patients info in table
    VariadicTable<uint64_t, std::string, int, int, std::string> vt({"ID", "Name", "Age", "Weight (kg)", "Gender"}, 15);
    vt.addRow(p.getId(), p.getName(), p.getAge(), p.getWeight(),(char)p.getGender() == 'f' ? "Female" : "Male");
    vt.print(std::cout);

    int option = -1;
    do {
        std::cout << "Please select an option:\n1- Release patient    2- Move to critical unit     3- See measures\n> ";
        std::cin >> option;
    } while (option > 3 || option < 1);


    if (option == 3) {
        auto his = p.getHistory();
        // Printing the history in a table
        // VariadicTable<int, int, int> vt({"Heart Pulses", "Systolic ", "Diastolic"}, 15);
        std::cout << center("Pulses (bpm)",20)       << " | "
        << center("Systolic (mmHg)",20)     << " | "
        << center("Diastolic (mmHg)",20)
        << center("Date",20) << "\n";
        for(std::list<Measurement*>::iterator hisIter = his.begin(); hisIter != his.end(); hisIter++) {
            Measurement m = **hisIter;
            auto humanTime = epochTimeToHumanTime(m.getTime());
            // vt.addRow( (int)m.getHeartRate(), (int)m.getBloodPressure().first , (int)m.getBloodPressure().second);

             std::cout << printDouble((int)m.getHeartRate(),2,20)       << " | "
                      << printDouble((int)m.getBloodPressure().first, 2,20)     << " | "
                      << printDouble((int)m.getBloodPressure().first, 2,20) << " | " 
                      << humanTime->tm_hour << ":" << humanTime->tm_min << ":" << humanTime->tm_sec << " GMT" << "\n";
        }
        // vt.print(std::cout);

        // Running the function that gets a new measurment on a new thread
        std::thread checkThread(checkNewMeasurement, &p);
        // std::cin >> std::ws;
        // std::getline(std::cin, quitThread);
        std::cin >> quitThread;
        checkThread.join();

    } else if (option == 2) {
        p.moveToCritical();
        std::cout << "Patient [" << p.getId() << " | " << p.getName() << "] moved to critical unit.\n";
    } else if (option == 1) {
        h->getUnits()[unitIndex].removePatient(p.getId());
        std::cout << "Patient [" << p.getId() << " | " << p.getName() << "] removed.\n";
    }


    if (option == 3) {
        std::cout << "\n\n1- Quit  2- Prev\n>";

        int decision = -1;
        do {
            std::cin >> decision;
        } while (decision != 1 && decision != 2);

        if (decision == 2){
            managePatient(id, unitIndex);
        }
    } else {
        std::cout << "\n\n1- Quit  2- Patients Menu \n>";

        int decision = -1;
        do {
            std::cin >> decision;
        } while (decision != 1 && decision != 2);

        if (decision == 2){
            printPatients(unitIndex);
            optionsOnPatientSelection(unitIndex);
        }
    }
}

// This function lets the user decide on whether to select the patient by its name or id
void optionsOnPatientSelection(int unitIndex) {
    Hospital* h = State::getHospital();
    // Getting the desired option from the user
    std::cout << "A- Select Patient by Id    B- Select Patient by Name" << std::endl;
    std::string option = "";
    do {    
        std::cout << "> ";
        std::cin >> option;
    } while (option != "a" && option != "A" && option != "b" && option != "B");


    if (option == "a" || option == "A") {
        std::cout << "Please input the id > ";
        uint64_t curId;
        std::cin >> curId;
        
        while (!patientExists(curId, unitIndex)) {
            std::cout << "Please input a valid id > ";
            std::cin >> curId;
        }
        managePatient(curId, unitIndex);

    } else if (option == "b" || option == "B") {
        std::cout << "Please input the name \n> ";
        std::string name;
        std::cin >> std::ws;
        std::getline(std::cin, name);

        while (!patientExists(name, unitIndex)) {
            std::cout << "Please input a valid name > ";
            std::cin >> std::ws;
            std::getline(std::cin, name);
        }

        uint64_t id = h->getUnits()[unitIndex].getPatient(name).getId();
        std::cout << id << " - " << name << std::endl;
        managePatient(id, unitIndex);
    }
}

// These two functions return a boolean on whether a given patient exists or not
bool patientExists(uint64_t id, int unitIndex) {
    return State::getHospital()->getUnits()[unitIndex].hasPatient(id);
}
bool patientExists(std::string& name, int unitIndex) {
    return State::getHospital()->getUnits()[unitIndex].hasPatient(name);
}

void Driver() {
    while (true) {
        std::string selectedRole = selectRole();
        clear();
        // Returns an int: index to the unit in the CareUnits vector in hospital
        int selectedUnit = selectedRole == "0" ? selectUnitDoctor() : selectUnitDirector();
        clear();
        printPatients(selectedUnit) ;
        optionsOnPatientSelection(selectedUnit) ;
        clear();
    } 
}