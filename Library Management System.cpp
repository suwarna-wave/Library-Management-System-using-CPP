
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>  
#include <cstdlib>
#include <cstring>
#include <cstdio>

class Book {
private:
    std::string bno;
    std::string bname;
    std::string aname;

public:
    void createBook() {
        std::cout << "\nNEW BOOK ENTRY...\n";
        std::cout << "\nENTER BOOK NO.: ";
        std::cin >> bno;
        std::cout << "\nENTER BOOK NAME: ";
        std::cin.ignore();
        std::getline(std::cin, bname);
        std::cout << "\nENTER AUTHOR NAME: ";
        std::getline(std::cin, aname);
        std::cout << "\n\n\nBook Created..\n";
    }

    void showBook() {
        std::cout << "\nBook Number: " << bno;
        std::cout << "\nBook Name: " << bname;
        std::cout << "\nAuthor Name: " << aname << std::endl;
    }

    void modifyBook() {
        std::cout << "\nBook Number: " << bno;
        std::cout << "\nModify Book Name: ";
        std::cin.ignore();
        std::getline(std::cin, bname);
        std::cout << "Modify Author's Name: ";
        std::getline(std::cin, aname);
    }

    std::string getBookNumber() const {
        return bno;
    }

    void report() const {
        std::cout << std::setw(10) << bno << std::setw(30) << bname << std::setw(30) << aname << std::endl;
    }
};

class Student {
private:
    std::string admno;
    std::string name;
    std::string stbno;
    int token;

public:
    void createStudent() {
        std::cout << "\nNEW STUDENT ENTRY...\n";
        std::cout << "\nEnter The Admission No.: ";
        std::cin >> admno;
        std::cout << "Enter The Student Name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        token = 0;
        stbno = "";
        std::cout << "\n\nStudent Record Created...\n";
    }

    void showStudent() {
        std::cout << "\nAdmission Number: " << admno;
        std::cout << "\nStudent Name: " << name;
        std::cout << "\nNo of Books Issued: " << token;
        if (token == 1) {
            std::cout << "\nBook Number: " << stbno;
        }
        std::cout << std::endl;
    }

    void modifyStudent() {
        std::cout << "\nAdmission No.: " << admno;
        std::cout << "\nModify Student Name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
    }

    std::string getAdmissionNumber() const {
        return admno;
    }

    std::string getStudentBookNumber() const {
        return stbno;
    }

    int getToken() const {
        return token;
    }

    void addToken() {
        token = 1;
    }

    void resetToken() {
        token = 0;
    }

    void getStudentBookNumber(const std::string& t) {
        stbno = t;
    }

    void report() const {
        std::cout << std::setw(10) << admno << std::setw(20) << name << std::setw(10) << token << std::endl;
    }
};

std::fstream fp, fp1;
Book bk;
Student st;

void writeBook() {
    char ch;
    fp.open("book.dat", std::ios::out | std::ios::app);
    do {
        system("clear");
        bk.createBook();
        fp.write(reinterpret_cast<char*>(&bk), sizeof(Book));
        std::cout << "\n\nDo you want to add more records? (y/n): ";
        std::cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void writeStudent() {
    char ch;
    fp.open("student.dat", std::ios::out | std::ios::app);
    do {
        system("clear");
        st.createStudent();
        fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
        std::cout << "\n\nDo you want to add more records? (y/n): ";
        std::cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void displayBook(const std::string& n) {
    std::cout << "\nBOOK DETAILS\n";
    int flag = 0;
    fp.open("book.dat", std::ios::in);
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(Book))) {
        if (bk.getBookNumber() == n) {
            bk.showBook();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0) {
        std::cout << "\n\nBook does not exist\n";
    }
}

void displayStudent(const std::string& n) {
    std::cout << "\nSTUDENT DETAILS\n";
    int flag = 0;
    fp.open("student.dat", std::ios::in);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        if (st.getAdmissionNumber() == n) {
            st.showStudent();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0) {
        std::cout << "\n\nStudent does not exist\n";
    }
}

void modifyBook() {
    std::string n;
    int found = 0;
    system("clear");
    std::cout << "\n\nMODIFY BOOK RECORD...";
    std::cout << "\n\nEnter the book no. ";
    std::cin >> n;
    fp.open("book.dat", std::ios::in | std::ios::out);
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(Book)) && found == 0) {
        if (bk.getBookNumber() == n) {
            bk.showBook();
            std::cout << "\nEnter the new details of the book";
            bk.modifyBook();
            int pos = -1 * sizeof(bk);
            fp.seekp(pos, std::ios::cur);
            fp.write(reinterpret_cast<char*>(&bk), sizeof(Book));
            std::cout << "\n\nRecord Updated\n";
            found = 1;
        }
    }
    fp.close();
    if (found == 0) {
        std::cout << "\n\nRecord Not Found\n";
    }
    std::cin.get();
}

void modifyStudent() {
    std::string n;
    int found = 0;
    system("clear");
    std::cout << "\n\nMODIFY STUDENT RECORD...";
    std::cout << "\n\nEnter the Admission no. ";
    std::cin >> n;
    fp.open("student.dat", std::ios::in | std::ios::out);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student)) && found == 0) {
        if (st.getAdmissionNumber() == n) {
            st.showStudent();
            std::cout << "\nEnter the new details of the student";
            st.modifyStudent();
            int pos = -1 * sizeof(st);
            fp.seekp(pos, std::ios::cur);
            fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
            std::cout << "\n\nRecord Updated\n";
            found = 1;
        }
    }
    fp.close();
    if (found == 0) {
        std::cout << "\n\nRecord Not Found\n";
    }
    std::cin.get();
}

void deleteStudent() {
    std::string n;
    int flag = 0;
    system("clear");
    std::cout << "\n\n\n\tDELETE STUDENT...";
    std::cout << "\n\nEnter the Admission no.: ";
    std::cin >> n;
    fp.open("student.dat", std::ios::in | std::ios::out);
    std::fstream fp2;
    fp2.open("temp.dat", std::ios::out);
    fp.seekg(0, std::ios::beg);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        if (st.getAdmissionNumber() != n) {
            fp2.write(reinterpret_cast<char*>(&st), sizeof(Student));
        } else {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("temp.dat", "student.dat");
    if (flag == 1) {
        std::cout << "\n\n\tRecord Deleted..\n";
    } else {
        std::cout << "\n\nRecord not Found\n";
    }
    std::cin.get();
}

void deleteBook() {
    std::string n;
    int flag = 0;
    system("clear");
    std::cout << "\n\n\n\tDELETE BOOK...";
    std::cout << "\n\nEnter the Book no.: ";
    std::cin >> n;
    fp.open("book.dat", std::ios::in | std::ios::out);
    std::fstream fp2;
    fp2.open("Temp.dat", std::ios::out);
    fp.seekg(0, std::ios::beg);
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(Book))) {
        if (bk.getBookNumber() != n) {
            fp2.write(reinterpret_cast<char*>(&bk), sizeof(Book));
        } else {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("book.dat");
    rename("Temp.dat", "book.dat");
    if (flag == 1) {
        std::cout << "\n\n\tRecord Deleted...\n";
    } else {
        std::cout << "\n\nRecord not Found\n";
    }
    std::cin.get();
}

void displayAllStudents() {
    system("clear");
    fp.open("student.dat", std::ios::in);
    if (!fp) {
        std::cout << "File Could Not Be Open";
        std::cin.get();
        return;
    }
    std::cout << "\n\n\t\tStudent List\n\n";
    std::cout << "==================================================================\n";
    std::cout << "\tAdmission No." << std::setw(10) << "Name" << std::setw(20) << "Book Issued\n";
    std::cout << "==================================================================\n";
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        st.report();
    }
    fp.close();
    std::cin.get();
}

void displayAllBooks() {
    system("clear");
    fp.open("book.dat", std::ios::in);
    if (!fp) {
        std::cout << "File Could Not Be Open";
        std::cin.get();
        return;
    }
    std::cout << "\n\n\t\tBook List\n\n";
    std::cout << "==================================================================\n";
    std::cout << "\tBook No." << std::setw(20) << "Book Name" << std::setw(25) << "Book Author\n";
    std::cout << "==================================================================\n";
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(Book))) {
        bk.report();
    }
    fp.close();
    std::cin.get();
}

void bookIssue() {
    std::string sn, bn;
    int found = 0, flag = 0;
    system("clear");
    std::cout << "\n\nBOOK ISSUE...\n";
    std::cout << "\n\tEnter Admission no.: ";
    std::cin >> sn;
    fp.open("student.dat", std::ios::in | std::ios::out);
    fp1.open("book.dat", std::ios::in | std::ios::out);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student)) && found == 0) {
        if (st.getAdmissionNumber() == sn) {
            found = 1;
            if (st.getToken() == 0) {
                std::cout << "\n\tEnter The Book No.: ";
                std::cin >> bn;
                while (fp1.read(reinterpret_cast<char*>(&bk), sizeof(Book)) && flag == 0) {
                    if (bk.getBookNumber() == bn) {
                        flag = 1;
                        st.addToken();
                        st.getStudentBookNumber(bk.getBookNumber());
                        int pos = -1 * sizeof(st);
                        fp.seekg(pos, std::ios::cur);
                        fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
                        std::cout << "\n\n\tBook Issued Successfully\n\n Please Note The Book Issue Date On Backside Of Your Book And Return Book Within 15 Days, Otherwise Fine Of 15 Rs Per Day\n";
                    }
                }
                if (flag == 0) {
                    std::cout << "Book No. Does Not Exists\n";
                }
            } else {
                std::cout << "You Have Not Returned The Last Book\n";
            }
        }
    }
    if (found == 0) {
        std::cout << "Student Record Not Exists...\n";
    }
    std::cin.get();
    fp.close();
    fp1.close();
}

void bookDeposit() {
    std::string sn, bn;
    int found = 0, flag = 0, day, fine;
    system("clear");
    std::cout << "\n\nBOOK DEPOSIT...\n";
    std::cout << "\n\tEnter Admission no. Of Student: ";
    std::cin >> sn;
    fp.open("student.dat", std::ios::in | std::ios::out);
    fp1.open("book.dat", std::ios::in | std::ios::out);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student)) && found == 0) {
        if (st.getAdmissionNumber() == sn) {
            found = 1;
            if (st.getToken() == 1) {
                while (fp1.read(reinterpret_cast<char*>(&bk), sizeof(Book)) && flag == 0) {
                    if (bk.getBookNumber() == st.getStudentBookNumber()) {
                        flag = 1;
                        bk.showBook();
                        std::cout << "\n\n Book Deposited In No. Of Days: ";
                        std::cin >> day;
                        if (day > 15) {
                            fine = (day - 15) * 1;
                            std::cout << "\n\n Fine = " << fine << "\n";
                        }
                        st.resetToken();
                        int pos = -1 * sizeof(st);
                        fp.seekg(pos, std::ios::cur);
                        fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
                        std::cout << "\n\n\tBook Deposited Successfully\n";
                    }
                }
                if (flag == 0) {
                    std::cout << "Book No. Does Not Exists\n";
                }
            } else {
                std::cout << "No Book Issued\n";
            }
        }
    }
    if (found == 0) {
        std::cout << "Student Record Not Exists...\n";
    }
    std::cin.get();
    fp.close();
    fp1.close();
}

void start() {
    system("clear");
    std::cout << "\n\n\n\tLIBRARY\n";
    std::cout << "\tMANAGEMENT\n";
    std::cout << "\tSYSTEM\n";
    std::cout << " \n  by: Voyagers\n";
    std::cin.get();
	
}

void adminMenu() {
    int ch2;
    do {
        system("clear");
        std::cout << "\n\n\n\tADMINISTRATOR MENU\n";
        std::cout << "\n\t1.CREATE STUDENT RECORD\n";
        std::cout << "\n\t2.DISPLAY ALL STUDENT RECORD\n";
        std::cout << "\n\t3.DISPLAY SPECIFIC STUDENT RECORD\n";
        std::cout << "\n\t4.MODIFY STUDENT RECORD\n";
        std::cout << "\n\t5.DELETE STUDENT RECORD\n";
        std::cout << "\n\t6.CREATE BOOK\n";
        std::cout << "\n\t7.DISPLAY ALL BOOKS\n";
        std::cout << "\n\t8.DISPLAY SPECIFIC BOOK\n";
        std::cout << "\n\t9.MODIFY BOOK RECORD\n";
        std::cout << "\n\t10.DELETE BOOK RECORD\n";
        std::cout << "\n\t11.BACK TO MAIN MENU\n";
        std::cout << "\n\tPLEASE ENTER YOUR CHOICE (1-11): ";
        std::cin >> ch2;
        switch (ch2) {
            case 1:
                writeStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3: {
                std::string num;
                system("clear");
                std::cout << "\n\n\t Please enter admission no.: ";
                std::cin >> num;
                displayStudent(num);
                break;
            }
            case 4:
                modifyStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                writeBook();
                break;
            case 7:
                displayAllBooks();
                break;
            case 8: {
                std::string num;
                system("clear");
                std::cout << "\n\n\tPlease enter book no.: ";
                std::cin >> num;
                displayBook(num);
                break;
            }
            case 9:
                modifyBook();
                break;
            case 10:
                deleteBook();
                break;
            case 11:
                return;
            default:
                std::cout << "Invalid choice\n";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    } while (ch2 != 11);
}

int main() {
    char ch;
    start();
    do {
        system("clear");
        std::cout << "\n\n\n\t MAIN MENU\n";
        std::cout << "\n\t1 BOOK ISSUE\n";
        std::cout << "\n\t2 BOOK DEPOSIT\n";
        std::cout << "\n\t3 ADMINISTRATOR MENU\n";
        std::cout << "\n\t4 EXIT\n";
        std::cout << "\n\tPLEASE SELECT YOUR OPTION (1-4): ";
        std::cin >> ch;
        switch (ch) {
            case '1':
                bookIssue();
                break;
            case '2':
                bookDeposit();
                break;
            case '3':
                adminMenu();
                break;
            case '4':
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "INVALID CHOICE\n";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    } while (ch != '4');

    return 0;
}