//SOFTWARE DEVELOPMENTS FUNCDAMENTALS-2
//PROJECT ON CAR RENTAL SYSTEM
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
#include<windows.h>
using namespace std;
// Car structure
struct Car {
    string make;
    string model;
    int year;
    string color;
    int rentalStatus;
    int rentalDays;
    float rentalCost;
};
double price;
string fname,lname,add1,num,em;
int carNumber;
int flag=0,flag1=0;
//class of whole Car Rental System which contains functions,constructors etc.
class project
{
public:
   //constructor
   project()
   {
    price=0.0;
    fname=" ";
    lname=" ";
    add1=" ";
    num=" ";
    em=" ";
   }
    //function to check valid username and password
    bool checkLoginCredentials(const string& username, const string& password) {
    ifstream infile("users.txt");
    string storedUsername, storedPassword;

    while (infile >> storedUsername >> storedPassword) {
        if (username == storedUsername && password == storedPassword) {
            infile.close();
            return true;
        }
    }

    infile.close();
    return false;
}
//function to register a new user
void registerUser(const string& username, const string& password) {
    ofstream outfile("users.txt", ios::app);
    outfile << username << " " << password << endl;
    outfile.close();
    cout << "User registered successfully!" << endl;
}
//function to input personal details
void personal_details()
{   system ("cls");
cout<<"\nPlease provide the following details to complete your Order!!\n";
cout<<"\nFirst Name : ";
cin>>fname;
cout<<"\nLast Name : ";
cin>>lname;
cout<<"\nBilling Address : ";
cin>>add1;
cout<<"Contact Number : ";
cin>>num;
cout<<"Email id: ";
cin>>em;
}

void addCar(vector<Car>& cars, const string& make, const string& model, int year, const string& color, int rentalStatus, int rentalDays, float rentalCost) 
{
    Car car;
    car.make = make;
    car.model = model;
    car.year = year;
    car.color = color;
    car.rentalStatus = rentalStatus;
    car.rentalDays = rentalDays;
    car.rentalCost = rentalCost;

    cars.push_back(car);
}

// Function to read the car data from the file
vector<Car> readCarsFromFile() {
    vector<Car> cars;
    ifstream infile("cars.txt");
    string line;
    while (getline(infile, line)) {
        Car car;
        car.make = line;
        getline(infile, line);
        car.model = line;
        getline(infile, line);
        car.year = stoi(line);
        getline(infile, line);
        car.color = line;
        getline(infile, line);
        car.rentalStatus = stoi(line);
        getline(infile, line);
        car.rentalDays = stoi(line);
        getline(infile, line);
        car.rentalCost = stof(line);
        cars.push_back(car);
    }
    infile.close();
    return cars;
}

// Function to write the car data to the file
void writeCarsToFile(vector<Car> cars) {
    ofstream outfile("cars.txt");
    for (auto car : cars) {
        outfile << car.make << endl;
        outfile << car.model << endl;
        outfile << car.year << endl;
        outfile << car.color << endl;
        outfile << car.rentalStatus << endl;
        outfile << car.rentalDays << endl;
        outfile << car.rentalCost << endl;
    }
    outfile.close();
}
// Function to display the main menu
void displayMainMenu() {
    cout << "CAR RENTAL SYSTEM" << endl;
    cout << "1. View available cars" << endl;
    cout << "2. Rent a car" << endl;
    cout << "3. Return a car" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to display the available cars
void displayAvailableCars(vector<Car> cars) 
{
    cout << "CAR RENTAL SYSTEM - AVAILABLE CARS" << endl;
    cout << "==============================================================================================================================================" << endl;

    cout<<"SNO"<<setw(18)<<"BRAND"<<setw(18)<<"MODEL"<<setw(18)<<"YEAR"<<setw(18)<<"COLOR"<<setw(18)<<"RENTAL STATUS"<<setw(18)<<"RENTAL DAYS"<<setw(18)<<"RENTAL COST";
    cout<<endl;
      int i=0;
    for ( auto& car : cars) {
    cout <<i+1<<setw(18)<< car.make <<setw(18)<<car.model<<setw(18)<<car.year<<setw(18)<<car.color<<setw(18)<<(car.rentalStatus == 1 ? "Rented" : "Available")<<setw(18)<<car.rentalDays<<setw(18)<<car.rentalCost<<endl;
     i++;
  
}

}
// Function to rent a car
void rentCar(vector<Car>& cars) {
    displayAvailableCars(cars);
    cout << "Enter the car number you want to rent: ";
    
    cin >> carNumber;
    carNumber--;
    if (carNumber < 0 || carNumber >= cars.size()) {
        cout << "Invalid car number!" << endl;
        return;
    }
    if (cars[carNumber].rentalStatus == 1) {
        cout << "This car is already rented!" << endl;
        return;
    }
    cout << "Enter the number of days you want to rent the car: ";
    int rentalDays;
    cin >> rentalDays;
    cars[carNumber].rentalStatus = 1;
    cars[carNumber].rentalDays = rentalDays;
    cars[carNumber].rentalCost = rentalDays * cars[carNumber].rentalCost;
    price=cars[carNumber].rentalCost;
    flag=cars[carNumber].rentalStatus;
}
// Function to return a car
void returnCar(vector<Car>& cars) {
    cout << "CAR RENTAL SYSTEM - RETURN A CAR" << endl;
    cout << "==========================================================================================================================================" << endl;
    displayAvailableCars(cars);
    cout << "Enter the car number you want to return: ";
    int carNumber;
    cin >> carNumber;
    carNumber--;
    if (carNumber < 0 || carNumber >= cars.size()) {
        cout << "Invalid car number!" << endl;
        return;
    }
    if (cars[carNumber].rentalStatus == 0) {
        cout << "This car is not rented!" << endl;
        return;
    }
    int rentalDays = cars[carNumber].rentalDays;
    float rentalCost = cars[carNumber].rentalCost;
    float totalCost = rentalDays * rentalCost;
    cout << "Rental Details:" << endl;
    cout << "Make: " << cars[carNumber].make << endl;
    cout << "Model: " << cars[carNumber].model << endl;
    cout << "Rental Days: " << rentalDays << endl;
    cout << "Rental Cost per day: " << rentalCost << endl;
    cout << "Total Cost: " << totalCost << endl;
    cout << "Are you sure you want to return this car? (Y/N): ";
    char choice;
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        cars[carNumber].rentalStatus = 0;
        cars[carNumber].rentalDays = 0;
        cout << "Car returned successfully!" << endl;
    } else {
        cout << "Return canceled." << endl;
    }
    flag1=cars[carNumber].rentalStatus;
}
// Function for the admin menu
void adminMenu(vector<Car>& cars,int choice) {

    switch (choice) {
        case 1: {
            system("cls");
            Car car;
            cout << "Enter the make of the car: ";
            cin >> car.make;
            cout << "Enter the model of the car: ";
            cin >> car.model;
            cout << "Enter the year of the car: ";
            cin >> car.year;
            cout << "Enter the color of the car: ";
            cin >> car.color;
            cout << "Enter the rental cost per day of the car: ";
            cin >> car.rentalCost;
            car.rentalStatus = 0;
            car.rentalDays = 0;
            cars.push_back(car);
            writeCarsToFile(cars);
            cout << "New car added successfully!" << endl;
            break;
        }
        case 2: {
            system("cls");
            displayAvailableCars(cars);
            cout << "\n\n\nEnter the car number you want to remove: ";
            int carNumber;
            cin >> carNumber;
            carNumber--;
            if (carNumber < 0 || carNumber >= cars.size()) {
                cout << "Invalid car number!" << endl;
                break;
            }
            if (cars[carNumber].rentalStatus == 1) {
                cout << "This car is rented and cannot be removed!" << endl;
                break;
            }
            cars.erase(cars.begin() + carNumber);
            writeCarsToFile(cars);
            cout << "Car removed successfully!" << endl;
            break;
        }
        case 3: {
            system("cls");
            displayAvailableCars(cars);
            break;
        }
        case 4: {
            system("cls");
            cout <<"\n\n\n"<<setw(70)<<"RENTED CARS" << endl;
            cout << "=========================================================================================================================================================" << endl;
            for (int i = 0; i < cars.size(); i++) {
                if (cars[i].rentalStatus == 1) {
                    cout << i + 1 << ". " << cars[i].make << " " << cars[i].model << ", " << cars[i].color << ", " << cars[i].year << ", rented for " << cars[i].rentalDays << " days, total cost $" << cars[i].rentalDays * cars[i].rentalCost << endl;
                }
            }
            cout << endl;
            break;
        }
        case 5: {
            system("cls");
            cout <<"\n\n\n"<<setw(70)<<"Logged out successfully!" << endl;
            break;
        }
        default: {
            system("cls");
            cout <<"\n\n\n"<<setw(70)<<"Invalid choice!" << endl;
            break;
        }
    }
}

//function to calculate the total amount
void billingSystem(double totalAmount, double discount) {
    cout<<"Congrats you are eligible for a discount of 8%"<<endl;
  double amountAfterDiscount = ((100-discount)/100)*totalAmount;
  double tax = amountAfterDiscount * 0.10;
  double amountWithTax = amountAfterDiscount + tax;

  cout << "Total Amount: " << totalAmount << endl;
  cout << "Discount: " << discount << endl;
  cout << "Amount After Discount: " << amountAfterDiscount << endl;
  cout << "Tax (10%): " << tax << endl;
  cout << "Amount with Tax: " << amountWithTax << endl;

  cout<<"\n"<<setw(70)<<"We hope you had a wonderful experience!!"<<endl;
}

//function to display the bill
void BILLDISPLAY(vector<Car>& cars)
{   system ("cls");
    cout<<"\n\n\n"<<setw(70)<<"CAR RENTAL\n"<<setw(70)<<+"SYSTEM";
    cout<<"\n\nName : " <<fname<<" "<<lname;
    cout<<"\nBilling Address : "<<add1;
    cout<<"\nContact Number : "<<num;
    cout<<"\nEmail id: "<<em;
    cout<<"\n\n\n----------------------------------------------------------------------------------------------------------------\n\n\n";

    cout<<"Car Rented : "<<cars[carNumber].model<<endl;
    cout<<"\nCategory : "<<cars[carNumber].make<<endl;
    cout<<"\nRegistration Year : "<<cars[carNumber].year<<endl;
    cout<<"\nDuration Rented : "<<cars[carNumber].rentalDays<<endl;

    cout<<"\n\n\n----------------------------------------------------------------------------------------------------------------\n\n\n";
}
//function to give the delivery details
void delivery()
{
    cout<<"Press D for Delivery "<<endl;
    cout<<"Press T for Takeaway"<<endl;
    char delivery;
    cin>>delivery;
    if(delivery=='D')
    {
        cout<<"Your Car will be delivered at your home within 2 working days"<<endl;
        cout<<"\n\n----------------------------------------------------------------------------------------------------------------\n\n";}
        else if(delivery=='T'){
        cout<<"You can get you Car within 2 days of booking date"<<endl;
        cout<<"You can collect your your car from our office"<<endl;
        cout<<"Office Address= Green Park,"<<endl<<"Near Shipra Mall,"<<endl<< "Sector 59 Noida"<<endl;
        cout<<"\n\n----------------------------------------------------------------------------------------------------------------\n\n";}
        else
        cout<<"Invalid Input";


}
//function to handle the payment mode
void paymentmode()
{
    string st;
    cout<<"\n\n----------------------------------------------------------------------------------------------------------------\n\n";
    cout<<"Payment Mode-Card/Cash"<<endl;
    cin>>st;
    cout<<"Your Payment has been received"<<endl;
    cout<<"\n\n----------------------------------------------------------------------------------------------------------------\n\n";
}
//EXIT function
void exit()
{
    cout<<"\n\n----------------------------------------------------------------------------------------------------------------\n\n";
    cout<<"Thank You for Visting Us"<<endl;
    cout<<"Hope you have a great drive ahead"<<endl;
}
};

int main()
{   
    project ob;
    vector<Car> cars1;
    system("cls");
    cout<<"\n\n----------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "                                                                     OM SAI TOURS AND TRAVELS                                                                      " << endl;  
    cout << "                                                                       (Car Renting Shop)                                                                          " << endl;
     cout<<"----------------------------------------------------------------------------------------------------------------------------------------------\n";
    char choice;
    bool loginSuccessful=false;
    while(loginSuccessful==false)
    {
    cout << "Do you have an account? (Y/N): ";
    cin >> choice;
    if (choice == 'N'||choice=='n') {
        string newUsername, newPassword,cpassword;
        cout << "Enter a username: ";
        cin >> newUsername;
        cout << "Enter a password: ";
        cin >> newPassword;
        cout << "Confirm password:";
        cin>> cpassword;
        if (newPassword != cpassword)
           cout << "New password and confirm password should be same!"<<endl ;
         while (newPassword != cpassword)
        {
            cout << "Enter new password:";
            cin >> newPassword;
            cout << "Confirm password:";
            cin >> cpassword;
            if (newPassword != cpassword)
                cout << "New password and confirm password should be same!"<<endl;
            cout << endl;
        } 
        ob.registerUser(newUsername, newPassword);
               loginSuccessful = ob.checkLoginCredentials(newUsername, newPassword);
    if (loginSuccessful==true) {
         system("cls");
        cout << "\n\n\n"<<setw(70)<<"Login successful! You are now logged in." << endl;
        cout<<"\n\n\n----------------------------------------------------------------------------------------------------------------\n\n\n";}
        // Continue with the rest of the car rental system functionality
    }
     else if(choice=='Y'||choice=='y'){
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
     
            loginSuccessful = ob.checkLoginCredentials(username, password);
    if (loginSuccessful==true) {
        system("cls");
        cout << "\n\n\n"<<setw(70)<<"Login successful! You are now logged in." << endl;
                cout<<"\n\n\n----------------------------------------------------------------------------------------------------------------\n\n\n";}
        // Continue with the rest of the car rental system functionality
        else
        cout<<"Incorrect Credentials"<<endl;
     }
     else
     {
        cout<<"Invallid Input"<<endl;
     }
    }

    // Example data
    ob.addCar(cars1, "Toyota", "Corolla", 2020, "Blue", 0, 0,3000);
    ob.addCar(cars1, "Honda", "Civic", 2019, "Silver", 0, 0, 10000);
    ob.addCar(cars1, "Ford", "Mustang", 2021, "Red", 1, 5, 12000);
    ob.addCar(cars1, "Chevrolet", "Camaro", 2018, "Yellow", 0, 0,13000);
    ob.addCar(cars1, "BMW", "X5", 2022, "Black", 0, 0,20000);
    ob.addCar(cars1, "Toyota", "Inova", 2022, "Blue", 0, 0, 10000);
    ob.addCar(cars1, "Honda", "City", 2019, "Black", 0, 0, 8000);
    ob.addCar(cars1, "Audi", "R7", 2012, "Violet", 1, 5, 25000);
    ob.addCar(cars1, "Hyundai", "i20", 2018, "Green", 0, 0, 4000);
    ob.addCar(cars1, "BMW", "X4", 2022, "Grey", 1, 10, 15000);

    cout << "You are" << endl;
    cout << "Choose C for Customer" << endl;
    cout << "A for Admin" << endl;
    char ch = ' ';
    cin >> ch;
    switch (ch)
    {
        case 'C':
            system("cls");
            cout <<"\n\n\n"<<setw(70)<<"You've chosen Customer" << endl;
            cout<<"\n\n\n-----------------------------------------------------------------------------------------------------------------------\n\n\n";
            break;
        case 'A':
            system("cls");
            cout <<"\n\n\n"<<setw(70)<<"You've chosen Admin" << endl;
            cout<<"\n\n\n-----------------------------------------------------------------------------------------------------------------------\n\n\n";
            break;
    }
    char ch1;
    int choice1=0;
    if (ch == 'A'||ch=='a')
        {  
            while(choice1!=5)
            {
                cout << "ADMIN MENU" << endl;
             cout << "1. Add a new car" << endl;
             cout << "2. Remove a car" << endl;
             cout << "3. View all cars" << endl;
             cout << "4. View rented cars" << endl;
              cout << "5. Logout" << endl;
                cout<<"Enter you choice"<<endl;
                cin >> choice1;
                ob.adminMenu(cars1,choice1);}}
        else
        if(ch=='C'||ch=='c')
        {
        while(ch1!='4'){
         ob.displayMainMenu();
        cin>>ch1;
        switch(ch1)
        {
            case '1':
            system("cls");
            ob.displayAvailableCars(cars1);
            break;

            case '2':
            system("cls");
            ob.rentCar(cars1);
            if(flag==1)
            {ob.personal_details();
            ob.BILLDISPLAY(cars1);
            ob.billingSystem(price,8);
            ob.paymentmode();
            ob.delivery();}
            break;

            case '3':
            system("cls");
            ob.returnCar(cars1);
            ob.displayAvailableCars(cars1);
            break;  

            case '4':
            ob.exit();
            break;

            default:
            cout<<"Invalid Choice"<<endl;  
        }
    }
 }
 system("cls");
cout<<"\n\n\n\n"<<setw(70)<<"MADE BY:"<<endl;
cout<<"Priyam Nandi - 22102088"<<endl;
cout<<"Chirag Sahu - 22102092"<<endl;
cout<<"Shruti Tanya - 22102084"<<endl;
cout<<"Preyerna Srivastava - 22102105"<<endl;
    return 0;
}

