#include "Parser.h"
#include "Engine.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{

Parse p;
Engine e;

bool quit = false;
int choice, choice1;
string PatientID, FirstName, LastName, Gender, Address, Phone, Email;
string PhysicianID, Specialty;
string AppointmentID, Date, StartTime, EndTime, Procedure, Fee;

cout<<"Hospital Database Management System"<<endl;
cout<<"-----------------------------------"<<endl<<endl;
	


	string command = "CREATE TABLE Patient (PatientID INTEGER, FirstName VARCHAR(20), LastName VARCHAR(20), Gender VARCHAR(1), Address VARCHAR(60), Phone VARCHAR(10), Email VARCHAR(40)) PRIMARY KEY (PatientID);";
	p.Tokenize(command);
	p.Begin_Parse();
	e.chooseParser(p.get_tokens());
	command = "CREATE TABLE Physician (PhysicianID INTEGER, FirstName VARCHAR(20), LastName VARCHAR(20), Specialty VARCHAR(20)) PRIMARY KEY (PhysicianID);";
	p.Tokenize(command);
	p.Begin_Parse();
	e.chooseParser(p.get_tokens());
	command = "CREATE TABLE Appointment (AppointmentID INTEGER, PatientID INTEGER, PhysicianID INTEGER, Date VARCHAR(10), StartTime VARCHAR(10), EndTime VARCHAR(10), Procedure VARCHAR(20), Fee VARCHAR(10)) PRIMARY KEY (AppointmentID);";
	p.Tokenize(command);
	p.Begin_Parse();
	e.chooseParser(p.get_tokens());


/*
	string command = "OPEN Patient;";
	p.Tokenize(command);
	p.Begin_Parse();
	e.chooseParser(p.get_tokens());
	command = "OPEN Physician;";
	p.Tokenize(command);
	p.Begin_Parse();
	e.chooseParser(p.get_tokens());
	command = "OPEN Appointment;";
	p.Tokenize(command);
	p.Begin_Parse();
	e.chooseParser(p.get_tokens());

*/
while(!quit)
{

	cout<<"Operations on..."<<endl<<endl;
	cout<<"1. Patient"<<endl;
	cout<<"2. Physician"<<endl;
	cout<<"3. Appointment"<<endl;
	cout<<"4. Quit"<<endl<<endl;
	cout<<"Enter a number: ";
	cin>>choice;
	cout<<endl<<endl;

	switch(choice)
	{
	case 1:
		cout<<"1. Add patient"<<endl;
		cout<<"2  Remove patient"<<endl;
		cout<<"3. List all patients"<<endl;
		cout<<"4. Search for a patient"<<endl;
		cout<<"Enter a number to choose an operation: ";
		cin>>choice1;
		cout<<endl<<endl;
		switch(choice1)
		{
		case 1:
			cout<<"Enter an 8-digit PatientID: ";
			cin>>PatientID;
			cout<<endl<<"Enter the patient's first name: ";
			cin>>FirstName;
			cout<<endl<<"Enter the patient's last name: ";
			cin>>LastName;
			cout<<endl<<"Enter the patient's gender (either M or F): ";
			cin>>Gender;
			cout<<endl<<"Enter the patient's address: ";
			cin.ignore();
			getline (cin,Address);
			cout<<Address;
			cout<<endl<<"Enter the patient's phone number: ";
			cin>>Phone;
			cout<<endl<<"Enter the patient's email: ";
			cin>>Email;
			command = "INSERT INTO Patient VALUES FROM ("+PatientID+", \""+FirstName+"\", \""+LastName+"\", \""+Gender+"\", \""+Address+"\", \""+Phone+"\", \""+Email+"\");";	
			p.Tokenize(command);
			p.Begin_Parse();
			e.chooseParser(p.get_tokens());
			break;
		case 2:
			cout<<"Enter the PatientID of the patient you want to delete: ";
			cin>>PatientID;
			command = "DELETE FROM Patient WHERE (PatientID == "+PatientID+");";
			cout<<endl;
			p.Tokenize(command);
			p.Begin_Parse();
			e.chooseParser(p.get_tokens());
			break;
		case 3:
			command = "SHOW Patient;";
			p.Tokenize(command);
			p.Begin_Parse();
			e.chooseParser(p.get_tokens());
			break;
		case 4:
			cout<<"Enter the PatientID of the patient you want to search for: ";
			cin>>PatientID;
			command = "temp <- select (PatientID == "+PatientID+") Patient;";
			p.Tokenize(command);
			p.Begin_Parse();
			e.chooseParser(p.get_tokens());
			cout<<endl;
			command = "SHOW temp;";
			p.Tokenize(command);
			p.Begin_Parse();
			e.chooseParser(p.get_tokens());
			break;	
		default: 
			cout<<"INVALID INPUT"<<endl<<endl;
		}


		break;
	case 2:
		cout<<"1. Add physician "<<endl;
		cout<<"2. Remove physician"<<endl;
		cout<<"3. List all physcians"<<endl;		
		cout<<"4. List physicians by specialty"<<endl;
		cout<<"5. Search physician by PhysicianID"<<endl;
		cout<<"Enter a number to choose an operation: ";
		cin>>choice1;
		cout<<endl;
		switch(choice1)
		{
		case 1:
			cout<<"Enter the physician's PhysicianID: ";
			cin>>PhysicianID;
			cout<<"Enter the physician's first name: ";
			cin>>FirstName;
			cout<<"Enter the physician's last name: ";
			cin>>LastName;
			cout<<"Enter the physician's specialty: ";
			cin>>Specialty;
			command = "INSERT INTO Physician VALUES FROM ("+PhysicianID+", \""+FirstName+"\", \""+LastName+"\", \""+Specialty+"\");";	
			p.Tokenize(command);
			p.Begin_Parse();
			e.chooseParser(p.get_tokens());
			break;
		case 2:
			cout<<"Enter the PhysicianID of the physician you want to delete: ";
			cin>>PhysicianID;
			command = "DELETE FROM Physician WHERE (PhysicianID == "+PhysicianID+");";
			cout<<endl;
			p.Tokenize(command);
			p.Begin_Parse();
			e.chooseParser(p.get_tokens());
			break;
		case 3:
			command = "SHOW Physician;";
			p.Tokenize(command);
			p.Begin_Parse();
			e.chooseParser(p.get_tokens());
			break;
		case 4:
			cout<<"Enter the specialty of the physicans you want to list: ";
			cin>>Specialty;
			command = "temp <- select (Specialty == \""+Specialty+"\") Physician;";
			p.Tokenize(command);
			p.Begin_Parse();
			e.chooseParser(p.get_tokens());
			cout<<endl;
			command = "SHOW temp;";
			p.Tokenize(command);
			p.Begin_Parse();
			e.chooseParser(p.get_tokens());
			break;	
		case 5:
			cout<<"Enter the PhysicianID of the physician you want to search for: ";
			cin>>PhysicianID;
			command = "temp <- select (PhysicianID == "+PhysicianID+") Physician;";
			p.Tokenize(command);
			p.Begin_Parse();
			e.chooseParser(p.get_tokens());
			cout<<endl;
			command = "SHOW temp;";
			p.Tokenize(command);
			p.Begin_Parse();
			e.chooseParser(p.get_tokens());
			break;		
		default:
			cout<<"INVALID INPUT"<<endl<<endl;
		}	
		break;
	case 3:
		cout<<"1. Create appointment"<<endl;
		cout<<"2. Reschedule appointment"<<endl;
		cout<<"3. Cancel appointment"<<endl;
		cout<<"4. List all appointments for a certain date"<<endl;
		cout<<"Enter a number to choose an operation: ";
		cin>>choice1;
		switch(choice1)
		{
		case 1:
		       cout<<"Enter an 8-digit AppointmentID: ";
	      		cin>>AppointmentID;
	 		cout<<"Enter an 8-digit PatientID: ";
			cin>>PatientID;
			cout<<"Enter an 8-digit PhysicianID: ";
			cin>>PhysicianID;
			cout<<"Enter the date for the appointment: ";
			cin>>Date;	
			cout<<"Enter the start time for the appointment: ";
			cin>>StartTime;
			cout<<"Enter the end time for the appointment: ";
			cin>>EndTime;
			cout<<"Enter the procedure for the appointment: ";
			cin>>Procedure;
			cout<<"Enter the fee for the appointment: ";
			cin>>Fee;
			command = "INSERT INTO Appointment VALUES FROM ("+AppointmentID+", "+PatientID+", "+PhysicianID+", \""+Date+"\", \""+StartTime+"\", \""+EndTime+"\", \""+Procedure+"\", \""+Fee+"\");";	
			cout<<command;
			p.Tokenize(command);
			p.Begin_Parse();
			e.chooseParser(p.get_tokens());
	
			break;
		case 2:
			cout<<"Enter AppointmentID: ";
			cin>>AppointmentID;
			cout<<"Enter new date for appointment: ";
			cin>>Date;
			cout<<"Enter new start time for the appointment: ";
			cin>>StartTime;
			cout<<"Enter new end time for the appointment: ";
			cin>>EndTime;
			command = "UPDATE Appointment SET Date = \""+Date+"\" WHERE AppointmentID == "+AppointmentID+";";
			cout<<command;
			p.Tokenize(command);
			p.Begin_Parse();
			e.chooseParser(p.get_tokens());
			break;
		case 3:
			cout<<"Enter the AppointmentID of the appointment you want to delete: ";
			cin>>AppointmentID;
			command = "DELETE FROM Appointment WHERE (AppointmentID == "+AppointmentID+");";
			cout<<endl;
			p.Tokenize(command);
			p.Begin_Parse();
			e.chooseParser(p.get_tokens());
			break;
		case 4:
			cout<<"Enter the date of the appointments you want to list: ";
			cin>>Date;
			command = "temp <- select (Date == "+Date+") Appointment;";
			p.Tokenize(command);
			p.Begin_Parse();
			e.chooseParser(p.get_tokens());
			cout<<endl;
			command = "SHOW temp;";
			p.Tokenize(command);
			p.Begin_Parse();
			e.chooseParser(p.get_tokens());
			break;		
		
		default:
			cout<<"INVALID INPUT"<<endl<<endl;
			break;
		}
	break;	
	case 4:
		command = "WRITE Patient;";
		p.Tokenize(command);
		p.Begin_Parse();
		e.chooseParser(p.get_tokens());
		command = "WRITE Physician;";
		p.Tokenize(command);
		p.Begin_Parse();
		e.chooseParser(p.get_tokens());
		command = "WRITE Appointment;";
		p.Tokenize(command);
		p.Begin_Parse();
		e.chooseParser(p.get_tokens());
		quit = true;
		break;
	default:
		cout<<"INVALID INPUT"<<endl<<endl;
		break;
	}

}
return 0;
}
