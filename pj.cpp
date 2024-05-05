#include <string>
#include <iostream>
#include <cstring>
#include "SHA1.hpp"
#include "SHA1.hpp"
using namespace std;
#include <fstream>

//Save information in the file of chaindata.txt
//Information include users' name, ID, Password and specific hash value
void File(string Name, string ID, string Password, string HashValue)
{
    ofstream ofs;
    ofs.open("chaindata.txt",ios::out | ios::app);
    ofs << "Name:" << endl;
    ofs << Name << endl;
    ofs << "ID:" << endl;
    ofs << ID << endl;
    ofs << "Password:" << endl;
    ofs << Password << endl;
    ofs << "Hash Value: " << endl;
    ofs << HashValue << endl;
    ofs.close();
    cout << "Data are successfully stored in chaindata.txt." << endl;
}

//Read and print the whole data stored in chaindata.txt
void ReadFile()
{
    ifstream ifs;
    ifs.open("chaindata.txt", ios::in);
    if (!ifs.is_open())
    {
        cout << "The file cannot be opened." << endl;
        return;
    }
    char buf[1024] = {0};
    while(ifs >> buf)
    {
        cout << buf << endl;
    }
    ifs.close();
}

//Find the content of a specific line
string ContentsOfLine(int SpecificLine) //找出其中一行的内容
{
    int i = 0;
    string Content;
    fstream ifs;
    ifs.open("chaindata.txt", ios::in);
    while(getline(ifs, Content) && i < SpecificLine - 1)
    {
        i++;
    }
    ifs.close();
    return Content;
}

//Find the number of lines in chaindata.txt
int NumberOfLines()
{
    ifstream ifs;
    int Lines = 0; //大写的Lines
    string buf;
    ifs.open("chaindata.txt", ios::in);
    while(getline(ifs, buf, '\n'))
    {
        Lines++;
    }
    ifs.close();
    return Lines;
}

//Save the latest hash value
void CompareFile(string HashValue)
{
    ofstream ofs;
    ofs.open("comparefile.txt",ios::trunc);
    ofs << "Hash value: " << endl;
    ofs << HashValue << endl;
    ofs.close();
}

//Read the comparefile.txt for checking integrity
string ReadCompareFile()
{
    int k = 0;
    string Confirm;
    ifstream ifs;
    ifs.open("comparefile.txt", ios::in);
    while(getline(ifs, Confirm) && k < 1)
    {
        k++;
    }
    ifs.close();
    return Confirm;
}

int main()
{
    //Provide a menu to ask users to select a function
    cout << "MENU" << endl;
    cout << "\t1.Addition of New Block" << endl;
    cout << "\t2.Display Chain Data" << endl;
    cout << "\t3.Check Integrity" << endl;
    int choice = 0;
    cout << "Enter your choice: ";
    cin >> choice;

    string Name, ID, Password, PreviousHashValue, HashValue;

    if (choice == 1) //Addition of a new block
    {
        //Ask users to input their information that need to be stored
        cout << "Name: ";
        cin >> Name;
        cout << "ID: ";
        cin >> ID;
        cout << "Password: ";
        cin >> Password;
        //Generate the hash value by inputting a random string including letters and numbers
        string Number;
        cout << "Please enter a random string(consist of letters and numbers): ";
        cin >> Number;
        string input(Number);
        SHA1 checksum;
        checksum.update(input);
        char hash[41];
        strcpy(hash, checksum.final().c_str());
        //Use File function to transmit information to chaindata.txt
        File(Name, ID, Password, hash);
        //Use comparefile function to transmit the latest hash vlaue to comparefile.txt9
        CompareFile(hash);
    }
    else if(choice == 2)
    {
        //Display the chain data by numerous ways
        cout << "Display Chain Data By" << endl;
        cout << "\t1.block number" << endl;
        cout << "\t2.the data of the whole chain" << endl;
        int choice2 = 0;
        cout << "Please enter your choice: ";
        cin >> choice2;
        if (choice2 == 1) //by block number
        {
            //Information about which block the user wants to view
            int BlockNumber = 0;
            cout << "Please enter the block number: ";
            cin >> BlockNumber;
            //Read and print the data of a particular block
            int Line1, Line2, Line3, Line4, Line5, Line6, Line7, Line8, Line9 = 0;
            int LineList[9] = {Line1, Line2, Line3, Line4, Line5, Line6, Line7, Line8, Line9};
            if (BlockNumber == 1) //"Previous hash value" does not exit in the first block, therefore, no need to print that out
            {
                for (int i = 0; i < 9; i++) //A block consist of 8 lines (without previous hash value)
                {
                    LineList[i] = (BlockNumber - 1) * 8 + i; //"(BlockNumber - 1) * 8 + i" find the lines of a particular block
                }
                string receive;
                for (int j = 1; j < 9; j++)
                {
                    receive = ContentsOfLine(LineList[j]);
                    cout << receive << endl;
                }
            }
            else if (BlockNumber > 1)
            {
                string PreviousHashValue;
                PreviousHashValue = ContentsOfLine((BlockNumber - 1) * 8); // "(BlockNumber - 1) * 8" is the number of line where stored the previous hash value 
                cout << "Previous hash value: " << endl;
                cout << PreviousHashValue << endl;

                for (int i = 0; i < 9; i++)
                {
                    LineList[i] = (BlockNumber - 1) * 8 + i;
                }
                string receive;
                for (int j = 1; j < 9; j++)
                {
                    receive = ContentsOfLine(LineList[j]);
                    cout << receive << endl;
                }
            }
        }
        else if (choice2 == 2) //by the data of the whole chain
        {
            ReadFile();
        }
    }
    else if(choice == 3) //Check integrity
    {
        //Find the number of lines in chaindata.txt == the number of last line in chaindata.txt
        int lines;
        lines = NumberOfLines();
        //Find the latest hash value that stored in the last line of chaindata.txt
        string LastHashValue;
        LastHashValue = ContentsOfLine(lines);
        //Find the hash value that stored in comparefile.txt
        string Confirm;
        Confirm = ReadCompareFile();
        //The latest hash value stored in chaindata.txt and the hash value stored in comparefile.txt should be the same
        if (LastHashValue == Confirm)
        {
            cout << "The Chain data has not been modified." << endl;
        }
        else if (LastHashValue != Confirm)
        {
            cout << "The Chain data has been modified." << endl;
        }

    }
    return 0;
}

