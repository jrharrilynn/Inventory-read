//-----------------------------------------------------------//
//CS 215 - 011–Lab7
//-----------------------------------------------------------// 
//Author: Jason Harrison
//Date:   03/29/2020
//Description: this applicatrion writes a nice report for users to see their inventory and information regardining it



#include <iostream>;
#include <iomanip>;
#include <fstream>;
#include <string>;
#include <sstream>>;
using namespace std;


const int MAX_PRODUCTS = 10;
//creates a structure called prod that has a name, a proce, and an inventory
struct prod {
	string Name;
	double Price;
	int inStock;
	float totalValue;
};

//------------------------------------------------------
//					readInventory
//------------------------------------------------------
int readInventory(prod P[], int numProducts) {
	//sets integer "i" to 0
	int i=0;

	//opens the "inventory.txt" file
	ifstream prodList;
	prodList.open("inventory.txt");

	// it it doesnt, open, tell the user
	if (prodList.fail()) {
		cout << "Unable to open input file"<<endl;
		numProducts = 0;
	}

	//if it does, read the lines and assign them to this loops respective Prod elements
	else {
		 while(P[i].Price!=-1&&i<MAX_PRODUCTS){
			 prodList >> P[i].Price;
			 prodList >> P[i].inStock;
			 prodList >> P[i].Name;
			 
			 //if the price is -1(sentinal value), it stops and assigns i to numProducts
			 if (P[i].Price == -1)
				 numProducts = i;

			 //if not, it adds 1 to i
			 else
				 ++i;
		};

		 //closes the prodlist file
		prodList.close();
		cout << "Inventory read" << endl;
	}
	
	//returns numProducts to be used as an int
	return numProducts;
}

//------------------------------------------------------
//					totalValue
//------------------------------------------------------

float totalValue(prod P[], int numProducts) {
	//initializes totalPrice as 0
	double totalPrice=0;

	//counts through the array of Prods, adds the value for this loops price elements multiplies by stock element, adds that to total price
	for (int i = 0; i < numProducts; i++) {
		P[i].totalValue = P[i].Price * P[i].inStock;
		totalPrice = totalPrice+P[i].totalValue;
	}

	//returns total price to be used as a float
	return totalPrice;
};


//--------------------------------------------------
//					sort
//--------------------------------------------------
void sort(prod P[], int& numProducts) {

	//nested for loops to sort smallest to largest
	for (int i = 0; i < numProducts - 1; i++) {
		for (int j = i + 1; j < numProducts; j++) {
			
			//compares the first letters of the P[i].Names ascii values
			if (P[i].Name[0] > P[j].Name[0]) {
				string t = P[i].Name;
				P[i].Name = P[j].Name;
				P[j].Name = t;
			};

			//if the first letters are the same, compares the second letters
			if (P[i].Name[0] == P[j].Name[0]) {
				if (P[i].Name[1] > P[j].Name[1]) {
					string t = P[i].Name;
					P[i].Name = P[j].Name;
					P[j].Name = t;
				};
			};

			//if the first and second letters are the same, it compares the third letters
			if (P[i].Name[1] == P[j].Name[1] && P[i].Name[0] == P[j].Name[0]) {
				if (P[i].Name[2] > P[j].Name[2]) {
					string t = P[i].Name;
					P[i].Name = P[j].Name;
					P[j].Name = t;
				};
			};

			//if the first, second, and third letters are the same, it compares the 4th letters
			if (P[i].Name[2] == P[j].Name[2] && P[i].Name[1] == P[j].Name[1] && P[i].Name[0] == P[j].Name[0]) {
				if (P[i].Name[3] > P[j].Name[3]) {
					string t = P[i].Name;
					P[i].Name = P[j].Name;
					P[j].Name = t;
				};
			};
						
					
				
			

		};
	};
};

		




	
				


void writeReport(prod P[], int& numProducts) {

	//calls the totalvalue function and sets total Price equal to it
	float totalPrice= totalValue(P, numProducts);

	//opens the report.txt file to write
	ofstream fout;
	fout.open("report.txt");

	//if it fails, cout the message
	if (fout.fail()) {
		cout << "Unable to open output file\n";
	}

	//if it doesn't fail it writes the report
	else {
		fout << "+------------------------------+\n"
			 << "|      Current Inventory       |\n"
			 << "+------------------------------+\n"
			 << "NAME                  PRICE   # \n"
			 << "-------------------- ------- ---\n";
		for (int i = 0; i < numProducts; i++) {
			fout << setw(21) << left << P[i].Name << "$ ";
			fout << setw(5) << right << setprecision(2) << fixed << P[i].Price;
			fout << setw(4) << right << P[i].inStock << endl;
			
		}
		fout << "+--------------------------------+\n"
			 << "Number of Products:    " << numProducts << endl;
		fout << "Inventory total Value: " << setprecision(2) << fixed << totalPrice << endl;
			
		cout << "Report written to file.\n";
	}
	
}



//--------------------------------------------------------
//						main
//--------------------------------------------------------
int main() {

	//initializes numProducts to 0
	int numProducts=0;

	//initializes totalPrice to 0
	float totalPrice = 0;

	//initializes Prod P for size MAX_PRODUCTS
	prod P[MAX_PRODUCTS];

	//sets numProducts=to readInventory, and calls the function
	numProducts=readInventory(P,numProducts);

	//calls the sort function
	sort(P,numProducts);

	//calls the write report function
	writeReport(P, numProducts);

	system("pause");
	return 0;

}
