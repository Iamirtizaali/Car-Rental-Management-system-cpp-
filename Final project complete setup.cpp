#include <iostream> 
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <sstream>
#include <regex>

using namespace std;

//<---------------------------------------------Declaration of Structures ---------------------->

//The admin data structure
struct admindata {
	int adminID;
	string adminName;
	string adminPassword;
};

//Car data structure
struct cardata {
	int carid; //carid contains the number of cars that are currently registered
	string carname;
	string model; 
	string number;
	string condition;
	string status;
	double perdayRate; //perdayRate contain the amount that is paid per day for car rent
	int carRepairTimes; //this variable contains the no of times the car has been repaired
	double totalIncomeGen; //it contains the total income generated from the car
	cardata() {
		carRepairTimes = 0;
		totalIncomeGen = 0;
	}
};

//Customer Data structure
struct costumerdata {
	int cosid;  //it contains the number of costumers that are registered currently
	string name;
	string address;
	string phoneNum;
	string CNIC;
	int password;
	string costumerstatus;
	int rentedCarID;   //it contains the index of the car that is rented by costumer
	double totalamount; //it contains the total amount that the costumer has paid after registeration
	costumerdata() {
		totalamount = 0;
		costumerstatus = "Available";
		rentedCarID = -1;
	}
};

//Rental Report Section it simply prints the report of the costumer
struct rentalReport {
	int id;
	int pass;
	int days;
	int carID;
	double price;
	string rentTime;
	string ReturnTime;
	string carName;
	string carModel;
	string carNumber;
	rentalReport() {
		days = 0;
		price = 0;
		rentTime = "";
		ReturnTime = "";
		carName = "";
		carModel = "";
		carNumber = "";
	}
};

//Customer report section ...it makes the report of the costumer.
struct costumerReport {
	int id;
	int password;
	string Date;
	int days;
	double amount;

	costumerReport() {
		Date = "0";
		days = 0;
		amount = 0;
	}
};


//<---------------------------------------------Data reading section from files into arrays---------------------->

int* noOfcostumers();
int* noOfCars();
cardata* carpointerdata();
costumerdata* costumerpointer();

//<---------------------------------------------Exit function which read data back into files and ends the program---------------------->

void exitfunction(const cardata car[], const int carsnumber, const costumerdata[], const int);

//<---------------------------------------------Admin Section---------------------->

void adminSide(cardata* carptr, int*, costumerdata* costumerptr, int*);
void adminoptions(cardata* carptr, int*, costumerdata* costumerptr, int*);

//<---------------------------------------------Car Section---------------------->

cardata* addcar(cardata*, int*);
void viewcars(cardata* carptr, int*);
int searchCarData(cardata*, int*);
void updateCarData(cardata*, int*);
cardata* deleteCarData(cardata*, int*);
void printCar(cardata s);

//<---------------------------------------------Customer Section---------------------->

void costumerSide(cardata* car, int* carnumbers, costumerdata* costumer, int* costumernumber);
void costumerOptions(cardata* car, int* carnumbers, costumerdata* costumer, int* costumernumber, int id);
costumerdata* addCostumer(costumerdata*, int*);
void viewcostumer(costumerdata*, int*);
void printCostumer(costumerdata);
void updateCostumerData(costumerdata*, int*);
costumerdata* deleteCostumerData(costumerdata*, int*);
int searchCostumer(costumerdata*, int*);
void changeadminpass();

//<---------------------------------------------Print Report Section---------------------->

void printRenalReport(cardata* car, int* carnumbers, costumerdata* costumer, int* costumernumber, int& id);
void PrintcarReport(cardata* car, int* carsnumber);

//<---------------------------------------------Car rent and return section---------------------->

cardata* rentCar(cardata* car, int* carnumbers, costumerdata* costumer, int* costumernumber, int& id);
cardata* returnCar(cardata* car, int* carnumbers, costumerdata* costumer, int* costumernumber, int& id);

//<---------------------------------------------Current Time Section---------------------->

string timefunction();

//<---------------------------------------------Validation functions section---------------------->

bool validateCarNumber(const string& carNumber);
bool validatePhoneNumber(const string& phoneNumber);
bool validateCNICNumber(const string& CNICNumber);
void validateNum(int& num);

//<---------------------------------------------Beautiful message display section---------------------->

void printWelcomeMessage();
void printCongratulationsCustomer();
void printCongratulationsAdmin();


//<---------------------------------------------Main Function section---------------------->
int main() {
	char choice;
	cardata* carptr = carpointerdata(); //here i have read the car data into a dynamic array and stored the address in carptr by calling carpointerdata function
	costumerdata* costumerptr = costumerpointer(); //here i have read the customer data into a dynamic array and stored the address in customerptr by calling costumerpointer function
	int* costumernumber = noOfcostumers(); //here i have read the no of costumers from file and stored it in dynamic integer and returned the address of it into costumerptr
	int* carsnumber = noOfCars(); //here i have read the no of cars from file and stored it in dynamic integer and returned the address of it into carpointer
	printWelcomeMessage(); 
	do {

		cout << "Enter 'A' if you are an admin." << endl;
		cout << "Enter 'C' if you are a customer. " << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		cout << endl;
	} while (choice != 'a' && choice != 'A' && choice != 'C' && choice != 'c');
	//cout << system("clear");
	system("cls");
	switch (choice) {
	case 'c':
	case 'C':
		// costumer side
		costumerSide(carptr, carsnumber, costumerptr, costumernumber);
		break;
	case 'a':
	case 'A':
		//admin side
		adminSide(carptr, carsnumber, costumerptr, costumernumber);
		break;
	default:
		break;
	}
	return 0;
}

//<------------------------------------Admin section--------------------------------->

//this function login the admin and after logging in successfully it calls the other function
void adminSide(cardata* carptr, int* carsnumber, costumerdata* costumerptr, int* costumernumber) {
	string name;
	string password;
	//admindata admdata = { 1,"2","3" };
	admindata admdata;
	ifstream read;
	read.open("admindata.txt");
	int count = 2;
	while (!read.eof())
	{
		//read >> admdata.adminID;
		read.ignore();
		// read >> admdata.adminName;
		 //read >> admdata.adminPassword;
		getline(read, admdata.adminName);
		getline(read, admdata.adminPassword);

		//if (admdata.adminID == id) {
			//found = true;
		cin.ignore(); // Ignore the newline character left in the buffer
		cout << "Enter the name of admin: ";
		getline(cin, name);

		cout << "Enter admin password: ";
		getline(cin, password);
		while ((admdata.adminName != name || admdata.adminPassword != password) && count > 0) {
			cout << "Remaining attempts: " << count << endl;
			cout << "Wrong name or password" << endl;
			cout << "Enter the name of admin: ";
			getline(cin, name);
			cout << "Enter admin password: ";
			getline(cin, password);
			count--;
		}
		//	}
	}
	read.close();
	//if (!found) {
	//	cout << "Wrong ID...\nLogin failed" << endl;
	//	exit(0);
	//}
	if (count == 0) {
		cout << "you have ran out of attepmts" << endl;
		exit(0);
	}
	adminoptions(carptr, carsnumber, costumerptr, costumernumber);
}
//this function displays the admin menu and displays the function according to the choice of admin
void adminoptions(cardata* carptr, int* carsnumber, costumerdata* costumerptr, int* costumernumber) {
	system("cls");
	printCongratulationsAdmin();
	int choice;
	do
	{
		cout << "============================================" << endl;
		cout << "           Welcome to Car Rental            " << endl;
		cout << "============================================" << endl;
		cout << "Enter 1  to Change Password." << endl;
		cout << "Enter 2  to View Cars." << endl;
		cout << "Enter 3  to Add Customers." << endl;
		cout << "Enter 4  to View Customers." << endl;
		cout << "Enter 5  to Update Customer Data." << endl;
		cout << "Enter 6  to Add Car." << endl;
		cout << "Enter 7  to Remove Car." << endl;
		cout << "Enter 8  to Remove Customer." << endl;
		cout << "Enter 9  to Update Car Data." << endl;
		cout << "Enter 10 to Show Customer Report." << endl;
		cout << "Enter 11 to Show Car Report." << endl;
		cout << "Enter 12 to Exit." << endl;
		cout << "============================================" << endl;
		cout << "Enter your choice: "; 
		while (!(cin >> choice)) {
			// Clear the error flag for cin
			cin.clear();

			// Discard the invalid input
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Invalid input.\n Please enter an integer: ";
		}
		validateNum(choice);
		system("cls");
		switch (choice)
		{
		case 1:
			changeadminpass();
			break;
		case 2:
			viewcars(carptr, carsnumber);
			break;
		case 3:
			costumerptr = addCostumer(costumerptr, costumernumber);
			break;
		case 4:
			viewcostumer(costumerptr, costumernumber);
			break;
		case 5:
			updateCostumerData(costumerptr, costumernumber);
			break;
		case 6:
			carptr = addcar(carptr, carsnumber);
			break;
		case 7:
			carptr = deleteCarData(carptr, carsnumber);
			break;
		case 8:
			costumerptr = deleteCostumerData(costumerptr, costumernumber);
			break;
		case 9:
			updateCarData(carptr, carsnumber);
			break;
		case 10:
		{
			int id;

			cout << "Enter the ID of costumer you want to print data: ";

			while (!(cin >> id)) {
				// Clear the error flag for cin
				cin.clear();

				// Discard the invalid input
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << "Invalid input.\n Please enter an integer: ";
			}
			validateNum(id);
			int idx = -1;
			for (int i = 0; i < *costumernumber; i++)
			{
				if (costumerptr[i].cosid == id)
				{
					idx = i;
					break;
				}
			}
			ifstream read;
			read.open(to_string(id) + ".txt");
			if (!read.is_open())
			{
				cout << "No such ID found." << endl;
			}
			else {
				printRenalReport(carptr, carsnumber, costumerptr, costumernumber, id);
			}
			break;
		}
		case 11:
			PrintcarReport(carptr, carsnumber);
			break;
		case 12:
			exitfunction(carptr, *carsnumber, costumerptr, *costumernumber);
			break;
		default:
			cout << "Wrong input!!!" << endl;
			break;
		}
	} while (true);
}
//this function facilitates the user to change its password and stores new password in the file
void changeadminpass() {
	//int id;
	admindata pass;
	admindata newpass;
	cin.ignore();
	//cout << "Enter the id of the password you want to change: ";
	//while (!(cin >> id)) {
	//	// Clear the error flag for cin
	//	cin.clear();

	//	// Discard the invalid input
	//	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	//	cout << "Invalid input.\n Please enter an integer: ";
	//}
	//validateNum(id);
	//cin.ignore();
	cout << "Enter the new password: ";
	getline(cin, newpass.adminPassword);
	ofstream tempFile;
	tempFile.open("temp.txt");
	ifstream read;
	read.open("admindata.txt");
	while (!read.eof()) {
		//read >> pass.adminID;
		read.ignore();
		getline(read, pass.adminName);
		getline(read, pass.adminPassword);
		/*if (pass.adminID != id) {
			tempFile << "\n" << pass.adminID;
			tempFile << "\n" << pass.adminName;
			tempFile << "\n" << pass.adminPassword;
			cout << "Wrong ID So password not changed" << endl;
		}*/
		//else {
			//tempFile << "\n" << pass.adminID;
	//	}
	}
	tempFile << "\n" << pass.adminName;
	tempFile << "\n" << newpass.adminPassword;
	cout << "\n\tData updated successfully" << endl;
	read.close();
	tempFile.close();
	remove("admindata.txt");
	rename("temp.txt", "admindata.txt");
}

//<------------------------------------Car section--------------------------------->

//this function enables the user to add a new car
cardata* addcar(cardata* car, int* carnumber) {
	(*carnumber)++;
	// cout << "the address of car array is: " << car << endl << endl;
	cardata* newcar = new cardata[*carnumber];
	for (int i = 0; i < *carnumber - 1; i++)
	{
		newcar[i].carid = car[i].carid;
		newcar[i].carname = car[i].carname;
		newcar[i].model = car[i].model;
		newcar[i].number = car[i].number;
		newcar[i].condition = car[i].condition;
		newcar[i].status = car[i].status;
		newcar[i].perdayRate = car[i].perdayRate;
	}
	int randomnumber;
	srand(time(0));
	randomnumber = 1 + rand() % 100;
	int i = 0;
	while (i < *carnumber)
	{
		if (newcar[i].carid == randomnumber)
		{
			int randomnumber = 1 + rand() % 1000;
			i = 0;
		}
		i++;
	}
	newcar[*carnumber - 1].carid = randomnumber;
	cin.ignore();
	cout << "Enter the name of the car: ";
	getline(cin, newcar[*carnumber - 1].carname);
	cout << "Enter the model of the car: ";
	getline(cin, newcar[*carnumber - 1].model);
	cout << "Enter the number of the car  (Write car number in AAA844 format): ";
	getline(cin, newcar[*carnumber - 1].number);
	while (!validateCarNumber(newcar[*carnumber - 1].number)) {
		cout << "You are entering the car number in wrong format (Write car number in AAA844 format)" << endl;
		cout << "Enter the number of the car: ";
		getline(cin, newcar[*carnumber - 1].number);
	}
	cout << "Enter the condition of the car (Good,Best or Under Maintenance): ";
	getline(cin, newcar[*carnumber - 1].condition);
	while (newcar[*carnumber - 1].condition != "Good" && newcar[*carnumber - 1].condition != "Best" && newcar[*carnumber - 1].condition != "Under Maintenance")
	{
		cout << "Sorry!!! You can only write \"Good\", \"Best\" or \"Under Maintenance\" in this field" << endl;
		cout << "Enter the condition of the car: ";
		getline(cin, newcar[*carnumber - 1].condition);
	}
	cout << "Enter the Status of the car (Available or Rented): ";
	getline(cin, newcar[*carnumber - 1].status);
	while (newcar[*carnumber - 1].status != "Available" && newcar[*carnumber - 1].status != "Rented")
	{
		cout << "You can only write \"Available\" or \"Rented in car status\" ." << endl;
		cout << "Enter the Status of the car: ";
		getline(cin, newcar[*carnumber - 1].status);
	}
	cout << "Enter per day rental rate of the car: ";
	while (!(cin >> newcar[*carnumber - 1].perdayRate)) {
		// Clear the error flag for cin
		cin.clear();

		// Discard the invalid input
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Invalid input.\n Please enter an integer: ";
	}
	//newcar[*carnumber - 1] = car[*carnumber - 1];
	delete[] car;
	car = newcar;
	//newcar = car;
	cout << "Car added successfully" << endl;
	// cout << "\n\nthe address of new car is: " << newcar << endl << endl;
	/* for (int i = 0; i < *carnumber; i++)
	 {
		 cout << "car data--------------\n\n";
		 cout << "Car ID: " << newcar[i].carid << endl;
		 cout << "Car name: " << newcar[i].carname << endl;
		 cout << "Car model: " << newcar[i].model << endl;
		 cout << "Car number: " << newcar[i].number << endl;
		 cout << "Car condtion: " << newcar[i].condition << endl;
		 cout << "Car status: " << newcar[i].status << endl;
	 }*/
	return newcar;
}
//this fucntion allows the user to view cars that are registered
void viewcars(cardata* carptr, int* carsnumber) {

	for (int i = 0; i < *carsnumber; i++)
	{
		printCar(carptr[i]);

	}
}
//this function allows the user to print cars details that are registered
void printCar(cardata s) {
	cout << "\n\t---------------------- Car Data ----------------------" << endl;
	cout << setw(20) << left << "\tCar ID:" << s.carid << endl;
	cout << setw(20) << left << "\tCar Name:" << s.carname << endl;
	cout << setw(20) << left << "\tCar Model:" << s.model << endl;
	cout << setw(20) << left << "\tCar Number:" << s.number << endl;
	cout << setw(20) << left << "\tCar Condition:" << s.condition << endl;
	cout << setw(20) << left << "\tCar Status:" << s.status << endl;
	cout << "\t------------------------------------------------------" << endl;

}
//this function allows the user to print complete car report of any car
void PrintcarReport(cardata* car, int* carsnumber) {
	int id;
	cout << "\n\tEnter Car id want to search : ";
	while (!(cin >> id)) {
		// Clear the error flag for cin
		cin.clear();

		// Discard the invalid input
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Invalid input.\n Please enter an integer: ";
	}
	validateNum(id);
	int idx = -1;
	bool found = false;
	for (int i = 0; i < *carsnumber; i++)
	{
		if (id == car[i].carid)
		{
			idx = i;
			found = true;
			break;
		}
	}
	if (found)
	{
		cout << "\n\t---------------------- Car Data ----------------------" << endl;
		cout << setw(20) << left << "\tCar ID:" << car[idx].carid << endl;
		cout << setw(20) << left << "\tCar Name:" << car[idx].carname << endl;
		cout << setw(20) << left << "\tCar Model:" << car[idx].model << endl;
		cout << setw(20) << left << "\tCar Number:" << car[idx].number << endl;
		cout << setw(20) << left << "\tCar Condition:" << car[idx].condition << endl;
		cout << setw(20) << left << "\tCar Status:" << car[idx].status << endl;
		cout << setw(20) << left << "\tTimes Rented:" << car[idx].carRepairTimes << " times" << endl;
		cout << fixed << setprecision(2); // Set precision for floating-point numbers
		cout << setw(20) << left << "\tRent Rate per Day:" << car[idx].perdayRate << " $" << endl;
		cout << setw(20) << left << "\tTotal Income generated from Car:" << car[idx].totalIncomeGen << " $" << endl;
		cout << "\t------------------------------------------------------" << endl;
	}
	else {
		cout << "car id not found" << endl;
	}
}
//this function allows user to search any car in his inventory
int searchCarData(cardata* car, int* carsnumber) {
	int id;
	cout << "\n\tEnter Car id want to search : ";
	while (!(cin >> id)) {
		// Clear the error flag for cin
		cin.clear();

		// Discard the invalid input
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Invalid input.\n Please enter an integer: ";
	}
	validateNum(id);
	int idx = -1;
	bool found = false;
	for (int i = 0; i < *carsnumber; i++)
	{
		if (id == car[i].carid)
		{
			idx = i;
			found = true;
			break;
		}
	}
	if (found)
	{
		printCar(car[idx]);
	}
	else {
		cout << "car id not found" << endl;
	}
	return idx;
}
//this function allows user to update the data of any car
void updateCarData(cardata* car, int* carsnumber) {
	int id = searchCarData(car, carsnumber);
	cout << "\n\tYou want to update record (y/n) : ";
	char choice;
	cin >> choice;
	if (choice == 'y' || choice == 'Y') {
		cardata newData;
		cout << "\n\tEnter Car name : ";
		cin.get();
		getline(cin, newData.carname);
		cout << "\n\tEnter Car model : ";
		getline(cin, newData.model);
		cout << "\n\tEnter Car number : ";
		getline(cin, newData.number);
		while (!validateCarNumber(newData.number)) {
			cout << "You are entering the car number in wrong format (Write car number in AAA844 format)" << endl;
			cout << "Enter the number of the car: ";
			getline(cin, newData.number);

		}
		cout << "\n\tEnter Car condition : ";
		getline(cin, newData.condition);
		while (newData.condition != "Good" && newData.condition != "Best" && newData.condition != "Under Maintenance")
		{
			cout << "Sorry!!! You can only write \"Good\", \"Best\" or \"Under Maintenance\" in this field" << endl;
			cout << "Enter the condition of the car: ";
			getline(cin, newData.condition);
		}
		cout << "\n\tEnter Car Status : ";
		getline(cin, newData.status);
		while (newData.status != "Available" && newData.status != "Rented")
		{
			cout << "You can only write \"Available\" or \"Rented in car status\" ." << endl;
			cout << "Enter the Status of the car: ";
			getline(cin, newData.status);
		}
		cout << "\n\tEnter per day rental rate: ";
		cin >> newData.perdayRate;
		while (!(cin >> newData.perdayRate)) {
			// Clear the error flag for cin
			cin.clear();

			// Discard the invalid input
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Invalid input.\n Please enter an integer: ";
		}
		car[id].carname = newData.carname;
		car[id].model = newData.model;
		car[id].number = newData.number;
		car[id].condition = newData.condition;
		car[id].status = newData.status;
		car[id].perdayRate = newData.perdayRate;
		cout << "\n\tData updated successfully" << endl;
	}

}
//this function allows user to delete any car
cardata* deleteCarData(cardata* car, int* carsnumber) {
	int id = searchCarData(car, carsnumber);
	if (id != -1)
	{
		cout << "\n\tYou want to delete record (y/n) : ";
		char choice;
		cin >> choice;
		if (choice == 'y' || choice == 'Y') {
			cardata* newcar = new cardata[*carsnumber - 1];
			for (int i = 0, j = 0; i < *carsnumber; i++)
			{
				if (id == i)
				{
					continue;
				}
				newcar[j].carid = car[i].carid;
				newcar[j].carname = car[i].carname;
				newcar[j].model = car[i].model;
				newcar[j].number = car[i].number;
				newcar[j].condition = car[i].condition;
				newcar[j].status = car[i].status;
				newcar[j].perdayRate = car[i].perdayRate;

				j++;
			}
			(*carsnumber)--;
			cout << "\n\tData deleted successfuly";
			delete[] car;
			car = newcar;
			return newcar;
		}
		else
		{
			cout << "Car not deleted." << endl;
		}
	}
	else
	{
		cout << "Car ID not found" << endl;
	}
}

//<-----------------------Costumer Section------------------------------------------->

//this function allows user to add new costumer to its inventory
costumerdata* addCostumer(costumerdata* costumer, int* costumernumber) {
	(*costumernumber)++;
	costumerdata* newcostumer = new costumerdata[*costumernumber];
	for (int i = 0; i < *costumernumber - 1; i++)
	{
		newcostumer[i].cosid = costumer[i].cosid;
		newcostumer[i].name = costumer[i].name;
		newcostumer[i].address = costumer[i].address;
		newcostumer[i].phoneNum = costumer[i].phoneNum;
		newcostumer[i].CNIC = costumer[i].CNIC;
		newcostumer[i].password = costumer[i].password;
		newcostumer[i].costumerstatus = costumer[i].costumerstatus;
		newcostumer[i].totalamount = costumer[i].totalamount;
	}
	cin.ignore();
	cout << "Enter the name of the costumer: ";
	getline(cin, newcostumer[*costumernumber - 1].name);
	cout << "Enter the address of the costumer: ";
	getline(cin, newcostumer[*costumernumber - 1].address);
	cout << "Enter the phone number of the costumer: ";
	getline(cin, newcostumer[*costumernumber - 1].phoneNum);
	while (!validatePhoneNumber(newcostumer[*costumernumber - 1].phoneNum))
	{
		cout << "Wrong Phone number!!! The phone number should start from 0 and there should be 11 digits." << endl;
		cout << "Enter the phone number of the costumer: ";
		getline(cin, newcostumer[*costumernumber - 1].phoneNum);
	}
	cout << "Enter the CNIC: ";
	getline(cin, newcostumer[*costumernumber - 1].CNIC);
	while (!validateCNICNumber(newcostumer[*costumernumber - 1].CNIC))
	{
		cout << "Your CNIC should have 13 digits." << endl;
		cout << "Enter the CNIC: ";
		getline(cin, newcostumer[*costumernumber - 1].CNIC);

	}
	cout << "Enter the status of costumer (Available or Rented): ";
	getline(cin, newcostumer[*costumernumber - 1].costumerstatus);
	while (newcostumer[*costumernumber - 1].costumerstatus != "Available" && newcostumer[*costumernumber - 1].costumerstatus != "Rented")
	{
		cout << "You can only write \"Available\" or \"Rented in costumer status\" ." << endl;
		cout << "Enter the Status of the car: ";
		getline(cin, newcostumer[*costumernumber - 1].costumerstatus);
	}
	// costumerID += 10;
	srand(time(0));
	int pass = 1 + rand() % 100000;
	int randomnumber = 1 + rand() % 1000;
	int i = 0;
	while (i<*costumernumber)
	{
		if (newcostumer[i].cosid==randomnumber)
		{
	    int randomnumber = 1 + rand() % 1000;
		i = 0;
		}
		i++;
	}
	newcostumer[*costumernumber - 1].password = pass;
	newcostumer[*costumernumber - 1].cosid = randomnumber;
	cout << "\n--------------------------------------------" << endl;
	cout << "  Customer Registration Successful" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "Customer ID: " << randomnumber << endl;
	cout << "Password: " << newcostumer[*costumernumber - 1].password << endl;
	cout << "--------------------------------------------\n" << endl;

	ofstream write;
	write.open(to_string(newcostumer[*costumernumber - 1].cosid) + ".txt");
	write << "\n" << newcostumer[*costumernumber - 1].cosid;
	write << "\n" << newcostumer[*costumernumber - 1].password;
	write.close();
	delete[] costumer;
	costumer = newcostumer;
	return newcostumer;
}
//this function allows user to view registered costumers.
void viewcostumer(costumerdata* costumer, int* costumernumber) {

	for (int i = 0; i < *costumernumber; i++)
	{
		printCostumer(costumer[i]);
	}
}
//this function prints the details of all the costumers
void printCostumer(costumerdata s) {
	cout << "\n\t---------------------- Customer Data ----------------------" << endl;
	cout << setw(20) << left << "\tCustomer ID:" << s.cosid << endl;
	cout << setw(20) << left << "\tName:" << s.name << endl;
	cout << setw(20) << left << "\tAddress:" << s.address << endl;
	cout << setw(20) << left << "\tPhone Number:" << s.phoneNum << endl;
	cout << setw(20) << left << "\tCNIC:" << s.CNIC << endl;
	cout << setw(20) << left << "\tPassword:" << s.password << endl;
	cout << "\t-------------------------------------------------------------" << endl;
}
//this function allows user to search for any registered costumer and return the index of it.
int searchCostumer(costumerdata* costumer, int* costumernumber) {
	int id;
	cout << "\n\tEnter Customer id want to search : ";
	while (!(cin >> id)) {
		// Clear the error flag for cin
		cin.clear();

		// Discard the invalid input
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Invalid input.\n Please enter an integer: ";
	}
	validateNum(id);
	int idx;
	bool found = false;
	for (int i = 0; i < *costumernumber; i++)
	{
		if (costumer[i].cosid == id)
		{
			found = true;
			idx = i;
			break;
		}
	}
	if (found)
	{
		printCostumer(costumer[idx]);
	}
	return idx;
}
//this function allows the user to update the data of any costumer
void updateCostumerData(costumerdata* costumer, int* costumernumber) {
	int id = searchCostumer(costumer, costumernumber);
	cout << "\n\tYou want to update record (y/n) : ";
	char choice;
	cin >> choice;
	if (choice == 'y' || choice == 'Y') {
		costumerdata newData;
		cin.ignore();
		cout << "Enter the name of the costumer: ";
		getline(cin, newData.name);
		cout << "Enter the address of the costumer: ";
		getline(cin, newData.address);
		cout << "Enter the phone number of the costumer: ";
		getline(cin, newData.phoneNum);
		while (!validatePhoneNumber(newData.phoneNum))
		{
			cout << "Wrong Phone number!!! The phone number should start from 0 and there should be 11 digits." << endl;
			cout << "Enter the phone number of the costumer: ";
			getline(cin, newData.phoneNum);
		}
		cout << "Enter the CNIC: ";
		getline(cin, newData.CNIC);
		while (!validateCNICNumber(newData.CNIC))
		{
			cout << "Your CNIC should have 13 digits." << endl;
			cout << "Enter the CNIC: ";
			getline(cin, newData.CNIC);

		}
		costumer[id].name = newData.name;
		costumer[id].address = newData.address;
		costumer[id].phoneNum = newData.phoneNum;
		costumer[id].CNIC = newData.CNIC;
		cout << "\n\tData updated successfully" << endl;
	}
}
//this function allows user to delete any costumer from its data
costumerdata* deleteCostumerData(costumerdata* costumer, int* costumernumber) {
	int id = searchCostumer(costumer, costumernumber);
	if (id != -1)
	{
		cout << "\n\tYou want to delete record (y/n) : ";
		char choice;
		cin >> choice;
		if (choice == 'y' || choice == 'Y') {
			(*costumernumber)--;
			costumerdata* newcostumer = new costumerdata[*costumernumber];
			for (int i = 0, j = 0; i < *costumernumber + 1; i++)
			{
				if (i == id) {
					ifstream read;
					//read.open(costumer[i].cosid + ".txt");
					remove((to_string(costumer[i].cosid) + ".txt").c_str());
					cout << "Record deleted successfully" << endl;
					continue;
				}
				newcostumer[j].cosid = costumer[i].cosid;
				newcostumer[j].name = costumer[i].name;
				newcostumer[j].address = costumer[i].address;
				newcostumer[j].phoneNum = costumer[i].phoneNum;
				newcostumer[j].CNIC = costumer[i].CNIC;
				newcostumer[j].password = costumer[i].password;
				j++;
			}

			delete[]    costumer;
			costumer = newcostumer;
			return newcostumer;
		}
		else {
			cout << "\n\tRecord not deleted";
			return costumer;
		}
	}
	else
	{
		cout << "Wrong ID...Record not deleted" << endl;
	}
}
//this function allows costumer to login by providing its id and password
void costumerSide(cardata* car, int* carnumbers, costumerdata* costumer, int* costumernumber) {
	int id, password;
	int fileid, filepassword;
	cout << "Enter the ID provided by the admin: ";
	while (!(cin >> id)) {
		// Clear the error flag for cin
		cin.clear();

		// Discard the invalid input
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Invalid input.\n Please enter an integer: ";
	}
	validateNum(id);
	int idx = -1;
	for (int i = 0; i < *costumernumber; i++)
	{
		if (costumer[i].cosid == id)
		{
			idx = i;
			break;
		}
	}
	ifstream read;
	read.open(to_string(id) + ".txt");
	if (!read.is_open())
	{
		cout << "No such ID found." << endl;
	}
	else {
		int count = 2;
		cout << "Enter your password: ";
		cin >> password;
		read >> fileid;
		read >> filepassword;
		read.close();
		while ((password != filepassword) && count > 0) {
			cout << "Remaining attempts: " << count << endl;
			cout << "Wrong name or password" << endl;
			cout << "Enter your password: ";
			cin >> password;
			count--;
			if (count == 0)
			{
				exit(0);
			}
		}
		cout << "\n-------------------------------------------------------" << endl;
		cout << "  Successfully Logged In" << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "Welcome back, " << costumer[idx].name << "!" << endl;
		cout << "You are now logged in and ready to explore our services." << endl;
		cout << "-------------------------------------------------------\n" << endl;
		costumerOptions(car, carnumbers, costumer, costumernumber, id);
	}
}
//this function displays the menu to the costumer and customer can perform the operation of its own choice.
void costumerOptions(cardata* car, int* carnumbers, costumerdata* costumer, int* costumernumber, int id) {
	printCongratulationsCustomer();
	int choice;
	do
	{
		cout << "======================================" << endl;
		cout << "        Car Rental Management        " << endl;
		cout << "======================================" << endl;
		cout << "Enter 1 to Rent Cars." << endl;
		cout << "Enter 2 to Return Cars." << endl;
		cout << "Enter 3 to View Available Cars." << endl;
		cout << "Enter 4 to View Rental Report." << endl;
		cout << "Enter 5 to Exit." << endl;
		cout << "======================================" << endl;
		cout << "Enter your choice: "; 
		while (!(cin >> choice)) {
			// Clear the error flag for cin
			cin.clear();

			// Discard the invalid input
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Invalid input.\n Please enter an integer: ";
		}
		validateNum(choice);
		system("cls");
		switch (choice)
		{
		case 1:
			car = rentCar(car, carnumbers, costumer, costumernumber, id);
			break;
		case 2:
			car = returnCar(car, carnumbers, costumer, costumernumber, id);
			break;
		case 3:
			viewcars(car, carnumbers);
			break;
		case 4:
			printRenalReport(car, carnumbers, costumer, costumernumber, id);
			break;
		case 5:
			exitfunction(car, *carnumbers, costumer, *costumernumber);
			break;
		default:
			break;
		}
	} while (true);
}

//<-----------------------Rent and return Car Section------------------------------------------->

//this function allows user to rent any car of its own choice if the costumer has not rented any car 
cardata* rentCar(cardata* car, int* carnumbers, costumerdata* costumer, int* costumernumber, int& id) {
	costumerReport report;
	int myid = searchCarData(car, carnumbers);
	char choice;
	int idx = -1;
	for (int i = 0; i < *costumernumber; i++)
	{
		if (costumer[i].cosid == id)
		{
			idx = i;
			break;
		}
	}
	if (car[myid].condition == "Under Maintenance")
	{
		cout << "Sorry!!! The car is under maintenance and that's why you cannot rent it." << endl;
		return car;
	}
	if (car[myid].status == "Rented")
	{
		cout << "Sorry!!! The car is rented and that's why you cannot rent it." << endl;
		return car;
	}
	if (costumer[idx].costumerstatus == "Rented")
	{
		cout << "Sorry!!! You have already rented a car and that's why you cannot rent more cars." << endl;
		return car;
	}
	if (myid == -1)
	{
		cout << "Sorry!!! You have entered the wrong ID." << endl;
		return car;
	}
	if (myid != -1 && car[myid].status != "Rented" && costumer[idx].costumerstatus != "Rented" || car[myid].condition != "Under Maintenance")
	{
		cout << "Enter (Y/y) to rent this car: ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
		{
			if (costumer[idx].costumerstatus != "Rented") {
				cout << "Enter the number of Days for which you want to rent this car: ";
				while (!(cin >> report.days)) {
					// Clear the error flag for cin
					cin.clear();

					// Discard the invalid input
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					cout << "Invalid input.\n Please enter an integer: ";
				}
				validateNum(report.days);
				car[myid].status = "Rented";
				car[myid].carRepairTimes++;
				costumer[idx].rentedCarID = car[myid].carid;
				report.amount = (car[myid].perdayRate * report.days);
				costumer[idx].costumerstatus = "Rented";
				costumer[idx].totalamount += report.amount;
				car[myid].totalIncomeGen += report.amount;
				ofstream write;
				write.open(to_string(id) + ".txt", ios::app);
				write << "\n" << car[myid].carid;
				write << "\n" << car[myid].carname;
				write << "\n" << car[myid].model;
				write << "\n" << car[myid].number;
				write << "\n" << timefunction();
				cout << "=======================================================" << endl;
				cout << "                 Rental Report                       =" << endl;
				cout << "=======================================================" << endl;
				cout << " Rented Car Id:          " << setw(20) << car[myid].carid << " =" << endl;
				cout << " Rented Car Name:        " << setw(20) << car[myid].carname << " =" << endl;
				cout << " Rented Car Model:       " << setw(20) << car[myid].model << " =" << endl;
				cout << " Rented Car Number Plate: " << setw(20) << car[myid].number << " =" << endl;
				cout << " Total Rent paid:        " << setw(20) << report.amount << " =" << endl;
				cout << "=======================================================" << endl;
				cout << "=   Car Rented Successfully                           =" << endl;
				cout << "=======================================================" << endl;
				cout << "= Thank you for choosing our car rental service!        =" << endl;
				cout << "= Enjoy your ride and have a safe journey!              =" << endl;
				cout << "=========================================================" << endl;	write << "\n" << report.days;
				write << "\n" << report.amount;
				write.close();
			}
		}
	}

	return car;
}
//this function allows the user to return the car that he has registered.
cardata* returnCar(cardata* car, int* carnumbers, costumerdata* costumer, int* costumernumber, int& id) {
	costumerReport report;
	int idx = -1;
	for (int i = 0; i < *costumernumber; i++)
	{
		if (costumer[i].cosid == id)
		{
			idx = i;
			break;
		}
	}
	cout << "Enter the id of the car you want to return." << endl;
	int myid = searchCarData(car, carnumbers);
	if (myid == -1 || car[myid].carid != costumer[idx].rentedCarID)
	{
		cout << "Sorry you are entering wrong ID of Car" << endl;
	}
	else
	{
		char choice;
		cout << "Enter Y/y to return the car: " << endl;
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
		{
			car[myid].status = "Available";

			ofstream write;
			write.open(to_string(id) + ".txt", ios::app);
			write << "\n" << timefunction();
			costumer[idx].costumerstatus = "Available";
			costumer[idx].rentedCarID = -1;
			write.close();
			cout << "\n-------------------------------------------------------" << endl;
			cout << "  Car Returned Successfully" << endl;
			cout << "-------------------------------------------------------" << endl;
			cout << "Thank you for returning the car!" << endl;
			cout << "We hope you had a great experience with our rental service." << endl;
			cout << "-------------------------------------------------------\n" << endl;

		}
	}

	return car;
}

//<-----------------------Print Report Section------------------------------------------->

//this function displays the complete rental report along with history of that costumer
void printRenalReport(cardata* car, int* carnumbers, costumerdata* costumer, int* costumernumber, int& id) {
	rentalReport report;
	char choice;
	int idx = -1;
	for (int i = 0; i < *costumernumber; i++)
	{
		if (costumer[i].cosid == id)
		{
			idx = i;
			break;
		}
	}
	cout << "Enter Y/y to print your rental report history: " << endl;
	cin >> choice;
	if (choice == 'Y' || choice == 'y')
	{
		ifstream read;
		read.open(to_string(id) + ".txt");
		read >> report.id;
		read >> report.pass;

		while (!read.eof())
		{
			int carID;
			read >> carID;
			read.ignore();
			getline(read, report.carName);
			getline(read, report.carModel);
			getline(read, report.carNumber);
			getline(read, report.rentTime);
			read >> report.days;
			read >> report.price;
			read.ignore();
			getline(read, report.ReturnTime);
			cout << "************************************" << endl;
			cout << "         CAR RENTAL REPORT          " << endl;
			cout << "************************************" << endl;

			cout << setw(20) << left << "Car rented Name:" << report.carName << endl;
			cout << setw(20) << left << "Car rented Model:" << report.carModel << endl;
			cout << setw(20) << left << "Car rented Number:" << report.carNumber << endl;
			cout << setw(20) << left << "Car rented at:" << report.rentTime << endl;
			cout << setw(20) << left << "Car rented for " << report.days << " days" << endl;
			cout << setw(20) << left << "Car rent paid:" << report.price << endl;
			cout << setw(20) << left << "Car returned at:" << report.ReturnTime << endl;

			cout << "************************************" << endl;
		}
		cout << "Total amount spent: " << costumer[idx].totalamount << endl;
	}
}

//<-----------------------Current time Section------------------------------------------->

//this function takes the current time from the library and return the current time as string
string timefunction() {
	// Get the current time
	time_t currentTime;
	time(&currentTime);

	//// Convert the current time to a string
	//char timeBuffer[26];
	//ctime_s(timeBuffer, sizeof(timeBuffer), &currentTime);
	//string timeString = timeBuffer;
	//// ctime includes a newline character at the end, so you may want to remove it
	//timeString.pop_back();

	// Alternatively, you can use std::put_time to format the time as a string
	tm timeInfo;
	localtime_s(&timeInfo, &currentTime);
	stringstream ss;
	ss << put_time(&timeInfo, "%Y-%m-%d %H:%M:%S");
	string formattedTimeString = ss.str();

	// Print the results
	return formattedTimeString;
}

//<-----------------------Data reading from files into dynamic arrays Section------------------------------------------->

//these funtions read the data from files into dynamic arrays and then returns the addresses of that arrays
cardata* carpointerdata() {

	ifstream read;
	read.open("id.txt");
	int carnumber;
	read >> carnumber;
	read.close();
	read.open("car.txt");
	cardata* cararray;
	cararray = new cardata[carnumber];
	for (int i = 0; i < carnumber; i++)
	{
		read >> cararray[i].carid;
		read.ignore();
		getline(read, cararray[i].carname);
		getline(read, cararray[i].model);
		getline(read, cararray[i].number);
		getline(read, cararray[i].condition);
		getline(read, cararray[i].status);
		read >> cararray[i].perdayRate;
		read >> cararray[i].carRepairTimes;
		read >> cararray[i].totalIncomeGen;
	}
	read.close();
	return cararray;
}
costumerdata* costumerpointer()
{
	ifstream read;
	read.open("cosid.txt");
	int costumerNumber;
	int costumerID;
	read >> costumerID;
	// costumerID = costumerID / 10;
	read.close();
	read.clear();
	costumerdata* costumer;
	costumer = new costumerdata[costumerID];
	read.open("costumer.txt");
	for (int i = 0; i < costumerID; i++)
	{
		read >> costumer[i].cosid;
		read.ignore();
		getline(read, costumer[i].name);
		getline(read, costumer[i].address);
		getline(read, costumer[i].phoneNum);
		getline(read, costumer[i].CNIC);
		read >> costumer[i].password;
		read.ignore();
		getline(read, costumer[i].costumerstatus);
		read >> costumer[i].rentedCarID;
		read >> costumer[i].totalamount;
	}
	read.close();
	return costumer;
}
int* noOfCars() {
	int number;
	ifstream read;
	read.open("id.txt");
	read >> number;
	int* carnumber = new int(number);
	return carnumber;
}
int* noOfcostumers() {
	int number;
	ifstream read;
	read.open("cosid.txt");
	read >> number;
	// number = number / 10;
	int* costumernumber = new int(number);
	return costumernumber;
};



//<-----------------------Exit function Section------------------------------------------->

//this function reads the complete data back into the file and then ends the program
void exitfunction(const cardata car[], const  int carsnumber, const  costumerdata costumer[], const int costumernumber) {
	int n = 1;
	ofstream write;
	write.open("car.txt");
	for (int i = 0; i < carsnumber; i++)
	{
		write << "\n" << car[i].carid;
		write << "\n" << car[i].carname;
		write << "\n" << car[i].model;
		write << "\n" << car[i].number;
		write << "\n" << car[i].condition;
		write << "\n" << car[i].status;
		write << "\n" << car[i].perdayRate;
		write << "\n" << car[i].carRepairTimes;
		write << "\n" << car[i].totalIncomeGen;
	}
	write.close();
	write.clear();
	write.open("id.txt");
	write << carsnumber;
	write.close();

	write.clear();
	//costumer data reading into the file
	write.open("costumer.txt");
	for (int i = 0; i < costumernumber; i++)
	{
		write << "\n" << costumer[i].cosid;
		write << "\n" << costumer[i].name;
		write << "\n" << costumer[i].address;
		write << "\n" << costumer[i].phoneNum;
		write << "\n" << costumer[i].CNIC;
		write << "\n" << costumer[i].password;
		write << "\n" << costumer[i].costumerstatus;
		write << "\n" << costumer[i].rentedCarID;
		write << "\n" << costumer[i].totalamount;
	}
	write.close();
	write.clear();
	write.open("cosid.txt");
	write << costumernumber;
	write.clear();
	write.close();
	cout << "\n\tData save to file" << endl;
	exit(0);
}


//<-----------------------Validation functions Section------------------------------------------->

//these functions simply validates the inputs 
bool validateCarNumber(const string& carNumber) {
	// Define the regular expression pattern for the car number format
	regex pattern("[A-Z]{3}[0-9]{3}");

	// Use regex_match to check if the input matches the pattern
	return regex_match(carNumber, pattern);
}
bool validatePhoneNumber(const string& phoneNumber) {
	// Define the regular expression pattern for the phone number format
	regex pattern("0[0-9]{10}");

	// Use regex_match to check if the input matches the pattern
	return regex_match(phoneNumber, pattern);
}
bool validateCNICNumber(const string& CNICNumber) {
	// Define the regular expression pattern for the phone number format
	regex pattern("[0-9]{13}");

	// Use regex_match to check if the input matches the pattern
	return regex_match(CNICNumber, pattern);
}
void validateNum(int& num) {
	while (num < 0)
	{
		cout << "Negative input is not accepted." << endl;
		cout << "Enter the input again: ";
		cin >> num;
	}
}

//the function to display the message CAR RENTAL SYSTEM
void printWelcomeMessage() {
	string message = "WELCOME TO CAR RENTAL SYSTEM";

	for (int i = 0; i < 40; ++i) {
		cout << "*";
	}
	cout << endl;

	for (int i = 0; i < 3; ++i) {
		cout << "*";
		for (int j = 0; j < 38; ++j) {
			if (i == 1 && j >= 2 && j < 2 + message.length()) {
				cout << message[j - 2];
			}
			else {
				cout << " ";
			}
		}
		cout << "*" << endl;
	}

	for (int i = 0; i < 40; ++i) {
		cout << "*";
	}
	cout << endl;
}
//the function to display the message of logging in as admin
void printCongratulationsAdmin() {
	string message = "Congratulations! You are logged in as Admin";

	for (int i = 0; i < 48; ++i) {
		cout << "*";
	}
	cout << endl;

	for (int i = 0; i < 3; ++i) {
		cout << "*";
		for (int j = 0; j < 46; ++j) {
			if (i == 1 && j >= 2 && j < 2 + message.length()) {
				cout << message[j - 2];
			}
			else {
				cout << " ";
			}
		}
		cout << "*" << endl;
	}

	for (int i = 0; i < 48; ++i) {
		cout << "*";
	}
	cout << endl;
}
//the function to display the message of logging in as customer
void printCongratulationsCustomer() {
	string message = "Congratulations! You are logged in as Customer";

	for (int i = 0; i < 50; ++i) {
		cout << "*";
	}
	cout << endl;

	for (int i = 0; i < 3; ++i) {
		cout << "*";
		for (int j = 0; j < 48; ++j) {
			if (i == 1 && j >= 2 && j < 2 + message.length()) {
				cout << message[j - 2];
			}
			else {
				cout << " ";
			}
		}
		cout << "*" << endl;
	}

	for (int i = 0; i < 50; ++i) {
		cout << "*";
	}
	cout << endl;
}