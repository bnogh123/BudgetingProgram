// Noghnogh_FinalProject.cpp: The main file for the program
// by Bassem Noghnogh for CIS-2541-NET02
// last edited 5/10/2021

#define NOMINMAX
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "Month.h"
#include "Payment.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

//function prototypes
void addNewMonth(Month*);
void createNewMonthFile(Month);
Month readFileToMonth(string, Payment*, Month&);
int getTotMonths();
void displayAllUtilities(Payment*, int);

namespace dict
{
    string intro = "Hello. Welcome to your finance helper program!",
        readingFiles = "Currently scanning your month files",
        success = "All Successful!",
        error = "Not all files were scanned successfully.",
        menuPrompt = "\nPlease choose from the following menu options\n",
        menu1[] = { "\t1 -- View your payments", "\t2 -- Edit the current month",
        "\t3 -- Add a new month", "\t4 -- Change months", "\t5 -- Exit" },
        menu2[] = { "\t1 -- View this month's payments", "\t2 -- View all utilies",
        "\t3 -- Exit to previous menu" },
        menu3[] = { "\t1 -- Add a payment to this month", "\t2 -- Remove a payment from this month",
        "\t3 -- Edit this month's utilities", "\t4 -- Pay payments from this month", "\t5 -- Exit to previous menu" },
        exit = "Thank you for using the finance helper program!",
        menuExit = "Going back to menu";
};

int main()
{
    // initialize variables
    Payment* baseUtility;
    bool isExit = false;
    int input(0);

    // check for total months
    int totMonths = getTotMonths();
    Month* months;

    // print startup message
    cout << dict::readingFiles << endl;
    Sleep(500);

    if (!totMonths) // if no months, create new file
    {
        baseUtility = new Payment[4];
        months = { new Month(1, baseUtility) };
        createNewMonthFile(months[0]);
        cout << "Month 1 file created!" << endl;
        Sleep(500);
    }
    else // if more than one month, dynamically allocate and populate array
    {
        months = new Month[totMonths];
        baseUtility = new Payment[4 * static_cast<unsigned __int64>(totMonths)];

        for (int i = 0; i < totMonths; i++)
        {
            string fileName = "month" + to_string(i + 1) + ".txt";
            readFileToMonth(fileName, baseUtility, months[i]);
            cout << "Month " << to_string(i + 1) << " read successfully!" << endl;
            Sleep(500);
        }

    }
    cout << "------------" << endl;

    // set current month
    Month& currentMonth = (months[totMonths-1]);

    // allocate for next month in case
    Month * nextMonth = new Month(totMonths + 1);

    for (int i = 0; i < 4; i++)
        (*nextMonth).setUtility(i, 0.0);

    // display intro
    cout << dict::intro << endl;
    system("pause");

    while (!isExit)
    {
        // display base menu
        cout << dict::menuPrompt << endl;
        for (string option : dict::menu1)
        {
            Sleep(200);
            cout << option << endl;
        }

        // receive input
        cin >> input;

        switch (input)
        {
        default: // input validation
            cout << "Invalid choice" << endl;
            break;
        case 1: // view your payments
            while (!isExit)
            {
                // display second menu
                cout << dict::menuPrompt << endl;
                for (string option : dict::menu2)
                {
                    Sleep(200);
                    cout << option << endl;
                }

                // receive input
                cin >> input;

                switch (input)
                {
                default: // input validation
                    cout << "Invalid choice" << endl;
                    break;
                case 1: // view current month's payments
                    // have each month print out everything
                    currentMonth.displayAll();
                    break;
                case 2: // view all utilities
                    displayAllUtilities(baseUtility, totMonths);
                    break;
                case 3: // exit back to menu
                    cout << dict::menuExit;
                    Sleep(500);
                    isExit = true;
                    break;
                }

                // clear cin
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                Sleep(500);
            }

            // reset exit flag
            isExit = false;
            break;
        case 2:
            while (!isExit)
            {
                // display third menu
                cout << dict::menuPrompt << endl;
                for (string option : dict::menu3)
                {
                    Sleep(200);
                    cout << option << endl;
                }

                // receive input
                cin >> input;

                switch (input)
                {
                default: // input validation
                    cout << "Invalid choice" << endl;
                    break;
                case 1: // add new payment

                    // prompt
                    cout << "Please enter the details for the Payment you wish to add" << endl;

                    // add new payment to month
                    
                    currentMonth.addOtherPayment();

                    break;
                case 2: // remove payment
                    // check if there are any other payments
                    if (currentMonth.getOtherSize() == 0)
                    {
                        cout << "The current month has no payments other than utilities." << endl
                            << dict::menuExit << endl;
                        Sleep(500);
                        break;
                    }

                    // display options
                    for (int i = 0; i < currentMonth.getOtherSize(); i++)
                    {
                        cout << (i + 1)<< " -- " << currentMonth.getOther(i).getName() << endl;
                    }
                    cout << (currentMonth.getOtherSize() + 1) << " -- exit" << endl;

                    // receive input
                    cin >> input;

                    while (input < 1 || input >(currentMonth.getOtherSize() + 1))
                    {
                        cout << "Invalid input. Please choose from the options above." << endl;
                        cin >> input;
                    }

                    if (input == (currentMonth.getOtherSize() + 1))
                        break;
                    else
                        currentMonth.deleteOther(input-1);
                    break;
                case 3: // edit utility
                    
                    // display options
                    for (int i = 0; i < 4; i++)
                    {
                        cout << "\t" << (i + 1) << " -- Edit ";

                        switch (static_cast<Utility>(i))
                        {
                        case Utility::ELEC:
                            cout << "Electric" << endl;
                            break;
                        case Utility::NTER:
                            cout << "Internet" << endl;
                            break;
                        case Utility::RENT:
                            cout << "Rent" << endl;
                            break;
                        case Utility::WATR:
                            cout << "Water" << endl;
                            break;
                        }

                    }
                    cout << "\t5 -- Exit" << endl;

                    // receive input
                    cin >> input;

                    while (input < 1 || input > 5)
                    {
                        cout << "\nInvalid input. Please choose from the options above." << endl;
                        cin >> input;
                    }

                    if (input != 5)
                    {
                        // initialize variable
                        int input2;
                        string payStat;
                        double cost;

                        // display options
                        cout << "Choose what you would like to edit"
                            << currentMonth.getUtility(input-1).getName() << "?"
                            << endl << "\t1 -- Cost" << endl << "\t2 -- Payment Status"
                            << endl << "\t3 -- Exit" << endl;

                        cin >> input2;

                        while (input2 < 1 || input2 > 3)
                        {
                            cout << "Please choose from the options above" << endl;
                            cin >> input2;
                        }

                        switch (input2)
                        {
                        case 1:
                            
                            // prompt for cost
                            cout << "Cost: ";
                            cin >> cost;

                            while (cost <= 0.0)
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Please enter a positive number\nCost: ";
                                cin >> cost;
                            }

                            // set cost
                            currentMonth.setUtility(input - 1, cost);

                            break;
                        case 2:

                            // prompt for payment status
                            cout << "Is the payment payed(P) or unpayed(U): ";
                            cin >> payStat;

                            while (payStat != "P" && payStat != "p" && payStat != "U" && payStat != "u")
                            {
                                cout << "Please enter \"P\" for payed, or \"U\" for unpayed: ";
                                cin >> payStat;
                            }

                            if (payStat == "P" || payStat == "p")
                                currentMonth.getUtility(input - 1).setPayed();
                            break;
                        }
                    }
                    else
                        break;

                    break;
                case 4: // pay a payment
                    // check if there are any other payments
                    if (currentMonth.getOtherSize() == 0)
                    {
                        cout << "The current month has no payments other than utilities." << endl
                            << dict::menuExit << endl;
                        Sleep(500);
                        break;
                    }

                    cout << "Choose from the following options";

                    // display options
                    for (int i = 0; i < currentMonth.getOtherSize(); i++)
                    {
                        cout << "\t" << (i + 1)<< " -- Pay " << currentMonth.getOther(i).getName() << endl;
                    }
                    cout << (currentMonth.getOtherSize() + 1) << " -- Exit" << endl;

                    // receive input
                    cin >> input;

                    while (input < 1 || input > (currentMonth.getOtherSize() + 1))
                    {
                        cout << "Invalid input. Please choose from the options above." << endl;
                        cin >> input;
                    }
                    
                    if (input == (currentMonth.getOtherSize() + 1))
                        break;
                    else
                        currentMonth.payOther(input-1);

                    break;
                case 5: // exit to menu
                    cout << dict::menuExit;
                    Sleep(500);
                    isExit = true;
                    break;
                }

                // clear cin
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                Sleep(500);
            }

            // reset exit flag
            isExit = false;
            break;
        case 3: // add a new month
            if (totMonths < 12)
            {
                createNewMonthFile(*nextMonth);
                cout << "New month successfully created! Please restart the program." << endl;
                isExit = true;
            }
            else
                cout << "Maximum month files already exist." << endl;

            break;
        case 4: // change current month
            cout << "which month would you like to select?" << endl;
            cin >> input;

            while (input < 1 || input > totMonths)
            {
                cout << "Please choose a valid month number. You can select from " 
                    << totMonths << " months." << endl;
                cin >> input;
            }

            // change current month
            currentMonth = (months[input - 1]);

            // clear cin and break
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        case 5:
            cout << dict::exit << endl;
            isExit = true;

            // clear cin and break
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        Sleep(500);
    }

    // write months to files
    for (int i = 0; i < totMonths; i++)
        createNewMonthFile(months[i]);

    cout << endl << "All successful!";

    // delete months
    delete[] months;
}

void createNewMonthFile(Month newMonth)
{
    // initialize variables
    string monthFileName = "month" + to_string(newMonth.getMonthNum()) + ".txt";
    Payment toWrite;
    ifstream monthFileTest(monthFileName);

    // check and delete existing file
    if (monthFileTest)
    {
        char* monthFileNameChar = new char[monthFileName.size() + 1];
        monthFileName.copy(monthFileNameChar, monthFileName.size() + 1);
        remove(monthFileNameChar);
        delete[] monthFileNameChar;
    }
    
    // create new file
    ofstream monthFile(monthFileName);

    monthFile << newMonth.getMonthNum() << "/"
        << newMonth.getTotMonths() << endl;

    for (int i = 0; i < 4; i++)
    {
        // get payment
        toWrite = newMonth.getUtility(i);

        // decide which utility it is
        switch (static_cast<Utility>(i))
        {
        default:
            break;
        case Utility::ELEC:
            monthFile << "Electricity";
            break;
        case Utility::NTER:
            monthFile << "Internet";
            break;
        case Utility::RENT:
            monthFile << "Rent";
            break;
        case Utility::WATR:
            monthFile << "Water";
            break;
        }

        // write the rest
        monthFile << ": $" << fixed << setprecision(2) << toWrite.getCost();
        if (toWrite.isPayed())
            monthFile << " (Payed)" << endl;
        else
            monthFile << " (Unpayed)" << endl;
    }

    if (newMonth.getOtherSize())
    {
        for (int entry = 0; entry < newMonth.getOtherSize(); entry++)
        {
            // get Payment
            toWrite = newMonth.getOther(entry);

            // write the rest
            monthFile << toWrite.getName() << ": $" << fixed << setprecision(2) << toWrite.getCost();
            if (toWrite.isPayed())
                monthFile << " (Payed)" << endl;
            else
                monthFile << " (Unpayed)" << endl;
        }
    }


    // close file
    monthFile.close();
}

Month readFileToMonth(string fileName, Payment* baseUtility, Month& newMonth)
{
    // try to open named file
    ifstream monthFile(fileName);
    string toRead;

    // if file open was successful, read
    if (monthFile)
    {
        // get first line which has month number and total months
        getline(monthFile, toRead);
        newMonth.setMonth(stoi(toRead.substr(0, toRead.find("/"))), baseUtility);

        // populate utilities
        for (int i = 0; i < 4; i++)
        {
            // assume all utilities are payed
            bool allPayed = true;

            // get next line
            getline(monthFile, toRead);

            // populate each utility with cost
            try
            {
                newMonth.setUtility(i, stod(toRead.substr(toRead.find("$") + 1, toRead.find("("))));
            }
            catch (const std::exception&)
            {
                // report error
                cerr << "Utilities were not formatted correctly";
                exit(-2);
            }

            string payedStatus = toRead.substr(toRead.find("("), toRead.size());

            // check if utility is payed
            if (payedStatus == "(Unpayed)"
                || payedStatus[1] == 'U')
            {
                allPayed = false;
            }
            else if (!(payedStatus == "(Payed)")
                && !(payedStatus[1] == 'P'))
            {
                cerr << "Utilities were not formatted correctly";
                exit(-2);
            }

        }

        // populate other payments
        while (getline(monthFile, toRead) && toRead != "")
        {
            //initalize variables
            Payment nextPay;

            // get next line
            string payedStatus = toRead.substr(toRead.find("("), toRead.size());

            // parse for payment name
            nextPay.setName(toRead.substr(0, toRead.find(":")));

            // populate other payment with cost
            try
            {
                nextPay.setCost(stod(toRead.substr(toRead.find("$") + 1, toRead.find("("))));
            }
            catch (const std::exception&)
            {
                // report error
                cerr << "Other Payments were not formatted correctly";
                exit(-2);
            }

            // check if utility is payed
            if (payedStatus == "(Payed)"
                || payedStatus[1] == 'P')
            {
                nextPay.setPayed();
            }
            else if (!(payedStatus == "(Unpayed)")
                && !(payedStatus[1] == 'U'))
            {
                cerr << "Other Payments were not formatted correctly";
                exit(-2);
            }

            //add payment to month
            newMonth.addOtherPayment(nextPay);
        };
    }
    else
    {
        // report error
        cerr << "File did not open";
        exit(-2);
    }

    // close file
    monthFile.close();

    // return month
    return newMonth;
}

int getTotMonths()
{
    // try to open named file
    ifstream monthFile("month1.txt");
    string toRead;
    int totMonths;

    // if file open was successful, read for total months
    if (monthFile)
    {
        // get first line which has month number and total months
        getline(monthFile, toRead);

        // get total months
        totMonths = stoi(toRead.substr(toRead.find("/") + 1, toRead.size()));
    }
    else
    {
        // set total months to zero flag
        totMonths = 0;
    }

    // close file
    monthFile.close();

    // return
    return totMonths;
}

void displayAllUtilities(Payment* base, int totmonths)
{
    // initialize variables
    string utility;
    double totals[4] = { 0.0, 0.0, 0.0, 0.0 };

    // increment totals
    for (int i = 0; i < (totmonths * 4); i++)
    {
        switch (static_cast<Utility>(i % 4))
        {
        case Utility::RENT:
            totals[0]+= base[i].getCost();
            break;
        case Utility::ELEC:
            totals[1] += base[i].getCost();
            break;
        case Utility::WATR:
            totals[2] += base[i].getCost();
            break;
        case Utility::NTER:
            totals[3] += base[i].getCost();
            break;
        }
    }

    // print out header
    cout << setw(10) << "Utility"
        << setw(10) << "Total"
        << setw(10) << "Average" << endl
        << setw(10) << "-------"
        << setw(10) << "-----"
        << setw(10) << "-------" << endl;

    // print out totals
    for (int i = 0; i < 4; i++)
    {
        switch (static_cast<Utility>(i))
        {
        case Utility::ELEC:
            utility = "Electric";
            break;
        case Utility::NTER:
            utility = "Internet";
            break;
        case Utility::RENT:
            utility = "Rent";
            break;
        case Utility::WATR:
            utility = "Water";
            break;
        }

        cout << setw(10) << utility
            << setw(10) << totals[i]
            << setw(10) << (totals[i] / totmonths) << endl;
    }

}
