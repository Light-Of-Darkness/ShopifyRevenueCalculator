// ShopifyCalculateRevenue.cpp : 
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <limits>
#include <sstream>

using namespace std;

void main (int argc, char *argv[])
{
	string filename;
	if (argc > 2)
	{
		//incorrect usage, commandline should 
		cout << "usage: " << argv[0] << " <filename>\n";
	}
	else
	{
		if (argc == 1)
		{
			cout << "Enter the filename of the .csv file containing your orders" << endl;
			cin.clear();
			getline(cin, filename);
		}
		else
		{
			filename = argv[1];
		}
		ifstream csv(filename);
		string line;
		string token; 
		double subtotal = 0;
		double shipping = 0;
		double taxes = 0;
		bool bankMade = false;
		bool holyShip = false;
		bool countryFunded = false;
		if (csv.is_open())
		{
			csv.clear();
			//skip past the first line that has the headers
			getline(csv, line);
			csv.clear();
			while (getline(csv, line))
			{
				//create the stringstream to start tokenizing
				stringstream tokenizer(line);
				//split the line into tokens separated by commas
				//skip to the subtotal token
				for (int i = 0; i < 9; i++)
				{
					getline(tokenizer, token, ',');
				}
				//token now has the subtotal token
				//check if the subtotal in revenue is above the maximum number that can be stored by a float
				if (numeric_limits<double>::max() - atof(token.c_str()) < subtotal)
				{
					bankMade = true;
				}
				else
					subtotal += atof(token.c_str());
				//get the shipping cost of the order
				getline(tokenizer, token, ',');
				//check if the total shipping cost is above the maximum number that can be stored by a float
				if (numeric_limits<double>::max() - atof(token.c_str()) < shipping)
				{
					holyShip = true;
				}
				else
					shipping += atof(token.c_str());
				//get the taxes of the order
				getline(tokenizer, token, ',');
				//check if the total tax is above the maximum number that can be stored by a float
				if (numeric_limits<double>::max() - atof(token.c_str()) < taxes)
				{
					countryFunded = true;
				}
				else
					taxes += atof(token.c_str());
				//revenue, shipping and taxes gotten, go to next line
				//clear input
				csv.clear();
			}
			if (bankMade)
				printf("Total revenue: at least $%.2f. Maybe more.\n", numeric_limits<double>::max);
			else
				printf("Total revenue: $%.2f\n", subtotal);
			if (holyShip)
				printf("Total shipping costs: at least $%.2f.", numeric_limits<double>::max);
			else
				printf("Total shipping costs: %.2f\n", shipping);
			if (countryFunded)
				printf("Total taxes paid: at least $%.2f", numeric_limits<double>::max);
			else
				printf("Total taxes paid: $%.2f\n", taxes);
		}
		else
			cout << "Unable to open file" << endl;
		//allow user to read output before the console closes
		system("PAUSE");
	}
}

