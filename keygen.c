#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include<Windows.h>

#define keyLength 16

unsigned char GetRand() {
	//Quick and dirty way to generate characters to start with within printable range 0 -> 127 to prevent any overflows.

	return (rand() % 128); //returns a char between 0 and 127 (inclusive).
}

char* KeyGen() {

	unsigned char keygen[keyLength];
	srand((unsigned int)time(NULL)); //seed generation

	// The 1st + 3rd == 2nd + 4th characters
	for (int i = 0; i < 4; i++)
		keygen[i] = GetRand();

	unsigned char key13 = keygen[0] + keygen[2];
	unsigned char key24 = keygen[1] + keygen[3];
	char  diff1234 = key13 - key24;

	if (diff1234 > 0)
		keygen[1] = keygen[1] + (unsigned char) diff1234;
	if (diff1234 < 0) {
		diff1234 = -diff1234;
		keygen[0] = keygen[0] + diff1234;
	}
	  key13 = keygen[0] + keygen[2];
	  key24 = keygen[1] + keygen[3];
	  diff1234 = key13 - key24;

	//same rules as the first 4 characters
	for (int i = 4; i < 8; i++) // 4,5,6,7
		keygen[i] = keygen[i - 4];
	
	// The sum of 9th and 10th characters == 11th character.
	keygen[10] = GetRand();
	while (keygen[10] % 2 != 0)	//make sure its even to avoid remainder and quotient problems
		keygen[10] = GetRand();
	keygen[8] = keygen[10] / 2;
	keygen[9] = keygen[10] / 2;

	//12th character must be 0x40.
	keygen[11] = '@';

	//13th character must be between 0x5A and 0x61
	keygen[12] = '[';

	//14th character must be between 0x7A and 0x7F
	keygen[13] = '{';

	//15th character must be more than 0x7A.
	keygen[14] = '{';

	//16th character is XOR-ed with the 15th characters and the result must be 0x17
	keygen[15] = '{' ^ 0x17;


	printf("random ress: %s\n", keygen);
	return keygen;
}



int main(){
	HANDLE hDataFile = CreateFileW(L"C:\\Windows\\SysWOW64\\eLearnRE#5.dat", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hDataFile == INVALID_HANDLE_VALUE) {	//If file doesn't exist
		//create it
		 hDataFile = CreateFileW(L"C:\\Windows\\SysWOW64\\eLearnRE#5.dat", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hDataFile == INVALID_HANDLE_VALUE)
			return 1;
	}

	char* charsToWrite;
	DWORD bytesWrote;

	charsToWrite = KeyGen();
	WriteFile(hDataFile, charsToWrite, keyLength, &bytesWrote, NULL);

	CloseHandle(hDataFile);
	return 0;
}
