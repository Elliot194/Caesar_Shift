// Auther: Elliot Rihan
// Created: 27/11/18
// Last Modified Date: 08/12/18
// Description: C++ program to decrypt a message encrypted with a Caesar Shift
// Caesar_Shift.cpp : This file contains the 'main' functions.

//#include "stdafx.h"
#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <bitset>
#include <cstdlib>
using namespace std;

ifstream inputFile;
string encryptedBinary;
string encryptedMessage;
string message;
string letter;
char yesOrNo;
// V5 CurentWorkingBranch Everything working 
void cinYesOrNo(string yNQuestion)
{ // cinYesOrNo is used to get input of Y or N from user 
	do {
		cout << yNQuestion << "[Y/N] --> ";
		cin >> yesOrNo;
	} while (!cin.fail() && yesOrNo != 'y' && yesOrNo != 'n' && yesOrNo != 'Y' && yesOrNo != 'N');
}

void openEncryptedFile()
{ // openEncryptedFile is used to open Binary file 
	inputFile.open("encrypted.bin");
	getline(inputFile, encryptedBinary);
	inputFile.close();
	cinYesOrNo("Would you like to print Encrypted Binary? ");
	if (yesOrNo == 'Y' || yesOrNo == 'y')
	{
		cout << "Encrypted Binary\n" << encryptedBinary << "\n";
	}
}

void saveFile(string tempEncryptedMessage)
{ // saveFile uses ofstream to save decrypted message to .txt
	message = tempEncryptedMessage;
	ofstream decryptedMessage("caesar_decrypted.txt");
	decryptedMessage << message;
	decryptedMessage.close();
	cout << "Message has been saved\n";
	cout << "Application will close\n";
	exit(0);
}

void binaryToAlpha()
{ // binaryToAlpha used bitset <8> to read binary file 8 bits at a time 
  // and add the character to the string encryptedMessage 
	istringstream eB(encryptedBinary);
	bitset<8> nm;
	while (eB >> nm)
	{
		encryptedMessage = encryptedMessage + char(nm.to_ulong());
	}
	cout << "\nThis is the Encrypted Message\n" << encryptedMessage << "\n";
}

void decriptCeaser(string encryptedMessage)
{
	string tempEncryptedMessage = encryptedMessage;
	int messageLength = (int)tempEncryptedMessage.length();
	for (int shift = 1; shift < 26; shift++)
	{ // this for loop runs thru the possible shifts
		for (int i = 0; i < messageLength; i++)
		{ // this for loop changes the character in the tempEncryptedMessage string
			if (isalpha(tempEncryptedMessage[i]))
			{// isalpha is an built in method to check if a character is in alphabet 
				if (tempEncryptedMessage[i] == 'z')
				{ // this loops back to start of alphabet without it alphabet becomes symbols 
					tempEncryptedMessage[i] = 'a';
				}
				else if (tempEncryptedMessage[i] == 'Z')
				{
					tempEncryptedMessage[i] = 'A';
				}
				else
				{
					tempEncryptedMessage[i]++;
				}
			}
		}
		cout << "\nShift Attempt: " << shift << "\n\n" << tempEncryptedMessage;
		cinYesOrNo("\n\nIs this this correct Shift Key? ");
		if (yesOrNo == 'Y' || yesOrNo == 'y')
		{
			cinYesOrNo("Are you sure? ");
			if (yesOrNo == 'Y' || yesOrNo == 'y')
			{
				cout << "Okay message will be saved to caesar_decrypted.txt file\n";
				saveFile(tempEncryptedMessage);
			}
		}
	} // If the user doesnt select a shift offers to run again or close
	cout << "ERROR: You should have found the correct key\n";
	cinYesOrNo("Would you like try again? ");
	if (yesOrNo == 'Y' || yesOrNo == 'y')
	{
		system("CLS");
		decriptCeaser(encryptedMessage);
	}
	else if (yesOrNo == 'N' || yesOrNo == 'n')
	{
		cout << "Okay decrypter will close";
	}
}

int main()
{
	cout << "\t\t\t\t\tCaesar Shift decrypter from Binary file \n\n";
	openEncryptedFile();
	binaryToAlpha();
	decriptCeaser(encryptedMessage);
}