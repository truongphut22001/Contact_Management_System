#pragma once
#include<iostream>
#include<vector>
#include<math.h>
#include<list>
#include <conio.h>
#include<algorithm>
#include<stack>
#include<fstream> 

using namespace std;

class contact{
private:
	char fName[50];
	char lName[50];
	char address[50];
	char email[50];
	long long phNo;
public:
	void createContact(){
		cout<<"Enter your first name: ";
		cin>>fName;
		cout<<"Enter your last name: ";
		cin>>lName;
		cout<<"Enter phone: ";
		cin>>phNo;
		cout<<"Enter address: ";
		cin>>address;
		cout<<"Enter email: ";
		cin>>email;
	}

	void showContact(){
		cout<< "Name: " << fName << " " << lName <<endl ;
		cout<< "Address: " << address <<endl;
		cout<< "Email: " << email <<endl;
		cout<< "Phone Number: " << phNo << endl;

	}

	void writeOnFile(){
		char ch;
		ofstream f1;
		f1.open("CMS.dat",ios:: binary | ios::app); //append

		
		do{
		createContact();
		f1.write(reinterpret_cast<char*>(this), sizeof(*this));
		
		// chua hieu

		cout<< "Do you have next data ? (y/n)" << endl;
		cin>> ch;
		} while(ch == 'y');

		cout<< "Contact has been successfully added !"<< endl;
		f1.close();



	}

	void readFromFile(){
		ifstream f2;
		f2.open("CMS.dat", ios:: binary);
		
		cout<< "***************" << endl;
		cout<< "LIST OF CONTACT" << endl;
		cout<< "***************" << endl;

		while(!f2.eof()){ //eof la end of file

			if(f2.read(reinterpret_cast<char*>(this), 
			sizeof(*this))){
				showContact();

			} 

			f2.close();

		}
	}

	void searchOnFile(){
		ifstream f3;
		long long phone;
		cout<< "Enter phone no.";
		cin >> phone;
		f3.open("CMS.dat", ios::binary);

		while (!f3.eof())
		{
			if(f3.read(reinterpret_cast<char*>(this),
			sizeof(*this))){
				if(phone == phNo){
					showContact();
					return;
				}
			}
		}
		cout<< "No contacts found !"<< endl;

		f3.close();
	}

	void deleteFromFile(){
		long long phone;
		int count = 0;
		ifstream f5;
		ofstream f4;
		

		f5.open("DMS.dat", ios::binary);
		f4.open("temp.dat", ios::binary);

		cout<< "Enter phone number to delete: " << endl;
		cin >> phone;

		while(!f5.eof()){
			if(f5.read(reinterpret_cast<char*>(this),sizeof(*this))){
				if(phNo != phone){
					f4.write(reinterpret_cast<char*>(this),sizeof(*this));

				}
				else count = 1;
			}
		}
		f5.close();
		f4.close();
		remove("CMS.dat");
		rename("temp.dat", "CMS.dat");
		count==1?
		cout<< "Contact deleted" <<endl:

		cout<< "Contact not found" << endl;

	}

	void editContact(){
		long long phone;
		fstream f6;
		cout<< "Edit contact"<< endl;
		cout<< "************" << endl;
		cout<< "Enter phone number you want to edit" << endl;
		cin >> phone;

		f6.open("CMS.dat", ios::binary | ios::out| ios:: in);
		
		while(!f6.eof()){
			if(f6.read(reinterpret_cast<char*>(this),sizeof(*this))){
				if(phone == phNo){
					cout<< "Enter new record" << endl;
					createContact();

					int pos = -1*sizeof(*this);
					f6.seekp(pos, ios::cur);
					f6.write(reinterpret_cast<char*>(this), sizeof(*this));
					cout<< "Contact successfully updated !" <<endl;
					return;


				}
			}
		}
		cout<< "No contact found !" <<endl;
		f6.close();

	}




};

int main() {
    system("cls");
	system("Color 3F"); // Color XY, X: background color, Y: text color;
	cout<< "Welcome to my Contact Management System" << endl;
	getch();
	while(1){
		contact c1;
		int choice;
		system("cls");
		system("Color 03");

		cout<< "CONTACT MANAGEMENT SYSTEM" <<endl;
		cout<< "MAIN MENU" << endl;
		cout<< "*******************************" <<endl;
		cout<< "[1] Add new contact"<<endl;
		cout<< "[2] List all contacts" << endl;
		cout<< "[3] Search a contact" << endl;
		cout<< "[4] Delete a contact" << endl;
		cout<< "[5] Edit a contact" << endl;
		cout<< "[0] Exit" <<endl;
		cout<< "*******************************" <<endl;
		cout<< "Enter your choice: " <<endl;
		cin >> choice;
		switch(choice){
			case 1:
			system("cls");
			c1.writeOnFile();
			break;

			case 2:
			system("cls");
			c1.readFromFile();
			break;

			case 3:
			c1.searchOnFile();
			break;

			case 4:
			c1.deleteFromFile();
			break;

			case 5:
			c1.editContact();
			break;

			case 0:
			cout<< "Thanks for using my contact management system !" << endl;
			exit(0);
			break;

			default:
			continue;

		}

		int opt;
		cout<< "...Enter your choice:" << endl;
		cout<< "[1] Main menu" << endl;
		cout<< "[0] Exit" << endl;
		cin >> opt;

		switch(opt){
			case 0:
			cout<< "Thanks for using my contact management system !" << endl;
			exit(0);
			break;

			default:
			continue;

		}
	}


    return 0;
}