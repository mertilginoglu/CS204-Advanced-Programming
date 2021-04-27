#include <iostream>
#include <string>
#include <istream>
using namespace std;

unsigned char Encrypt(unsigned char var, unsigned char keyVar) //Includes both P and XOR with the key operations
{
	//Getting the values of indexes by using and operations.
	unsigned char ind1 = var & 0x01; 
	unsigned char ind2 = var & 0x02;
	unsigned char ind3 = var & 0x04;
	unsigned char ind4 = var & 0x08;
	unsigned char ind5 = var & 0x10;
	unsigned char ind6 = var & 0x20;
	unsigned char ind7 = var & 0x40;
	unsigned char ind8 = var & 0x80;

	//Permuting them according to the function P.
	ind1 = (ind1 << 2);
	ind2 = (ind2 >> 1);
	ind3 = (ind3 << 1);
	ind4 = (ind4 >> 2);
	ind5 = (ind5 << 2);
	ind6 = (ind6 >> 1);
	ind7 = (ind7 << 1);
	ind8 = (ind8 >> 2);

	//ORing permuted indexes.
	unsigned char result = ind1 | ind2 | ind3 | ind4 | ind5 | ind6 | ind7 | ind8;
	//XOR with the key.
	result = result ^ keyVar;
	return result;
}

int main()
{
	string key, plaintext;
	cout << "*** Welcome to the Simple Data Encryption Application ***" << endl;
	cout << "Please enter the encryption key: ";
	getline(cin, key);
	cout << "Please enter the plaintext to be encrypted: ";
	while(getline(cin, plaintext))
	{
		cout << "Ciphertext: ";
		for(int i = 0; i < plaintext.length(); i++) //Using for loop to use encryption function.
		{
			unsigned char output = Encrypt(plaintext.at(i), key.at(i % key.length())); //Taking mod of key incase if key is shorter than plain text.
			cout << hex << (int) output;
		}
		cout << dec << endl << endl << "Please enter the plaintext to be encrypted: ";
	}
	return 0;
}