#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Person {
protected:
    string first_name, last_name, cnic_no, dob;
    string father_first_name, father_last_name;
    string religion, poi;
    string pob, nationality, gender;

public:
    void setName(string fn, string ln) {
        first_name = fn;
        last_name = ln;
    }

    void setFatherName(string ffn, string fln) {
        father_first_name = ffn;
        father_last_name = fln;
    }

    void setCNIC(string cnic) {
        cnic_no = cnic;
    }

    void setReligion(string r) {
        religion = r;
    }

    void setNationality(string n) {
        nationality = n;
    }

    void setDOB(string d) {
        dob = d;
    }

    void setGender(string g) {
        gender = g;
    }

    void setPlaceofBirth(string p) {
        pob = p;
    }

    void setPlaceofIssue(string p) {
        poi = p;
    }

    string getCNIC() {
        return cnic_no;
    }
};

class Passport : public Person {
private:
    string pass_number;
    string doi, doe;

public:
    void setPassportNumber(string p) {
        pass_number = p;
    }

    void setDateofIssue(string d) {
        doi = d;
    }

    void setDOE(string d) {
        doe = d;
    }

    string getFullData() {
        return pass_number + "\n" + first_name + "\n" + last_name + "\n" + nationality + "\n" + dob + "\n" +
               cnic_no + "\n" + gender + "\n" + father_first_name + " " + father_last_name + "\n" + doi + "\n" +
               poi + "\n" + doe + "\n---";
    }

    void saveToFile() {
        ofstream outFile("passport_data.txt", ios::app);
        if (!outFile) {
            cout << "Error: Could not open file for writing.\n";
            return;
        }
        outFile << getFullData() << endl;
        outFile.close();
    }

    static void loadAllFromFile() {
        ifstream inFile("passport_data.txt");
        if (!inFile) {
            cout << "Error: No records found.\n";
            return;
        }

        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }

    static void findByPassportNumber(string pnum) {
        ifstream inFile("passport_data.txt");
        if (!inFile) {
            cout << "Error: No records found.\n";
            return;
        }

        string line;
        bool found = false;

        while (getline(inFile, line)) {
            string pass, fn, ln, nat, dob, cnic, gen, fname, doi, poi, doe, dash;

            pass = line;
            getline(inFile, fn);
            getline(inFile, ln);
            getline(inFile, nat);
            getline(inFile, dob);
            getline(inFile, cnic);

            if (pass == pnum) {
                found = true;
                getline(inFile, gen);
                getline(inFile, fname);
                getline(inFile, doi);
                getline(inFile, poi);
                getline(inFile, doe);
                getline(inFile, dash);

                cout << "\nPassport Number: " << pass << endl;
                cout << "Name: " << fn << " " << ln << endl;
                cout << "Nationality: " << nat << endl;
                cout << "DOB: " << dob << endl;
                cout << "CNIC: " << cnic << endl;
                cout << "Gender: " << gen << endl;
                cout << "Father Name: " << fname << endl;
                cout << "Date of Issue: " << doi << endl;
                cout << "Place of Issue: " << poi << endl;
                cout << "Expiry Date: " << doe << endl;
                break;
            } else {
                // Skip rest of this record (11 lines: 10 fields + "---")
                for (int i = 0; i < 11; i++) getline(inFile, line);
            }
        }

        if (!found) {
            cout << "No record found for Passport Number: " << pnum << endl;
        }

        inFile.close();
    }
};

void addPassport() {
    Passport p;
    string pass_no, fname, lname, nat, dob, cnic, gender, ffname, flname, doi, poi, doe;

    cout << "Passport Number: ";
    getline(cin, pass_no);
    p.setPassportNumber(pass_no);

    cout << "First Name: ";
    getline(cin, fname);
    cout << "Last Name: ";
    getline(cin, lname);
    p.setName(fname, lname);

    cout << "Nationality: ";
    getline(cin, nat);
    p.setNationality(nat);

    cout << "Date of Birth: ";
    getline(cin, dob);
    p.setDOB(dob);

    cout << "CNIC Number: ";
    getline(cin, cnic);
    p.setCNIC(cnic);

    cout << "Gender: ";
    getline(cin, gender);
    p.setGender(gender);

    cout << "Father First Name: ";
    getline(cin, ffname);
    cout << "Father Last Name: ";
    getline(cin, flname);
    p.setFatherName(ffname, flname);

    cout << "Place of Issue: ";
    getline(cin, poi);
    p.setPlaceofIssue(poi);

    cout << "Date of Issue: ";
    getline(cin, doi);
    p.setDateofIssue(doi);

    cout << "Expiry Date: ";
    getline(cin, doe);
    p.setDOE(doe);

    p.saveToFile();
}

int main() {
    while (true) {
        string option;
        cout << "\n===== Passport System Menu =====\n";
        cout << "1. Add New Passport\n";
        cout << "2. Show All Records\n";
        cout << "3. Find Record by Passport Number\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        getline(cin, option);

        if (option == "1") {
            addPassport();
        } else if (option == "2") {
            Passport::loadAllFromFile();
        } else if (option == "3") {
            string pnum;
            cout << "Enter Passport Number: ";
            getline(cin, pnum);
            Passport::findByPassportNumber(pnum);
        } else if (option == "4") {
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
