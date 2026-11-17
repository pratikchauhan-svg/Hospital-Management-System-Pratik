
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

// Safe Integer Input
int getInt(string msg) {
    int x;
    cout << msg;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Enter again: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return x;
}

// Safe String Input
string getString(string msg) {
    string s;
    cout << msg;
    getline(cin, s);
    return s;
}

// Base Class
class Person {
protected:
    int id, age;
    string name;

public:
    void input() {
        id = getInt("Enter ID: ");
        name = getString("Enter Name: ");
        age = getInt("Enter Age: ");
    }

    virtual void display() {
        cout << "ID: " << id << "\nName: " << name
             << "\nAge: " << age << endl;
    }
};

// Patient Class
class Patient : public Person {
    string disease, gender;

public:
    void registerPatient() {
        input();
        gender = getString("Enter Gender: ");
        disease = getString("Enter Disease: ");

        ofstream f("patients.txt", ios::app);
        f << id << "|" << name << "|" << age
          << "|" << gender << "|" << disease << endl;

        cout << "Patient Registered Successfully!\n";
    }

    void viewPatients() {
        ifstream f("patients.txt");
        string s;

        cout << "\n--- Patient Records ---\n";
        while (getline(f, s))
            cout << s << endl;
    }

    void searchPatient() {
        int n = getInt("Enter Patient ID: ");
        string s;
        bool found = false;

        ifstream f("patients.txt");

        while (getline(f, s)) {
            size_t p = s.find('|');

            if (p != string::npos && stoi(s.substr(0, p)) == n) {
                cout << s << endl;
                found = true;
                break;
            }
        }

        if (!found)
            cout << "Patient Not Found!\n";
    }
};

// Doctor Class
class Doctor : public Person {
    string specialization;

public:
    void addDoctor() {
        input();
        specialization = getString("Enter Specialization: ");

        ofstream f("doctors.txt", ios::app);
        f << id << "|" << name << "|" << age
          << "|" << specialization << endl;

        cout << "Doctor Added Successfully!\n";
    }

    void viewDoctors() {
        ifstream f("doctors.txt");
        string s;

        cout << "\n--- Doctor Records ---\n";
        while (getline(f, s))
            cout << s << endl;
    }
};

// Appointment Class
class Appointment {
public:
    void book() {
        int p = getInt("Enter Patient ID: ");
        int d = getInt("Enter Doctor ID: ");
        string date = getString("Enter Date: ");

        ofstream f("appointments.txt", ios::app);
        f << p << "|" << d << "|" << date << endl;

        cout << "Appointment Booked!\n";
    }

    void view() {
        ifstream f("appointments.txt");
        string s;

        cout << "\n--- Appointments ---\n";
        while (getline(f, s))
            cout << s << endl;
    }
};

// Billing Class
class Billing {
public:
    void generateBill() {
        int id = getInt("Enter Patient ID: ");

        float c, m;

        cout << "Consultation Charges: ";
        while (!(cin >> c)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter valid charges: ";
        }

        cout << "Medicine Charges: ";
        while (!(cin >> m)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter valid charges: ";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nTotal Bill: Rs. " << c + m << endl;

        ofstream f("bills.txt", ios::app);
        f << id << "|" << c << "|" << m << "|" << c + m << endl;
    }
};

// Hospital Class
class Hospital {
    Patient p;
    Doctor d;
    Appointment a;
    Billing b;

public:
    void menu() {
        int ch;

        do {
            cout << "\n===== HOSPITAL MANAGEMENT SYSTEM =====\n";
            cout << "1. Register Patient\n";
            cout << "2. View Patients\n";
            cout << "3. Add Doctor\n";
            cout << "4. View Doctors\n";
            cout << "5. Book Appointment\n";
            cout << "6. View Appointments\n";
            cout << "7. Generate Bill\n";
            cout << "8. Search Patient\n";
            cout << "9. Exit\n";

            ch = getInt("Enter Choice: ");

            switch (ch) {
                case 1: p.registerPatient(); break;
                case 2: p.viewPatients(); break;
                case 3: d.addDoctor(); break;
                case 4: d.viewDoctors(); break;
                case 5: a.book(); break;
                case 6: a.view(); break;
                case 7: b.generateBill(); break;
                case 8: p.searchPatient(); break;
                case 9: cout << "Thank You!\n"; break;
                default: cout << "Invalid Choice!\n";
            }

        } while (ch != 9);
    }
};

int main() {
    Hospital h;
    h.menu();
    return 0;
}