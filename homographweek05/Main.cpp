#include <iostream>
#include <cstring>
#include <filesystem>
#include <vector>
#include <sstream>
#include <map>
#include <stdlib.h>

using namespace std;
using namespace std::filesystem;

string prompt1(string file1);
string prompt2(string file2);
vector<string> stringConverter(string fileName);
string canonicalizer(vector<string> filePath);
bool homograph(string filePath1, string filePath2);
void allPathsCheck(string filePath1, string filePath2);
void testcase1();
void testcase2();
void testcase3();
void manualResults(bool answer);
void displayComparison(string file1, string file2);

string prompt1(string file1)
{	
	cout << "Enter the first file path: ";
	cin >> file1;

	return file1;
}

string prompt2(string file2)
{
	cout << "Enter the second file path: ";
	cin >> file2;

	return file2;
}


vector<string> stringConverter(string fileName)
{
	vector<string> outputVector;
	stringstream stream(fileName);
	string parsed;

	if (fileName.find(":") != std::string::npos)
	{

		while (getline(stream, parsed, '\\'))
		{
			if (parsed == "" || parsed == " ")
				continue;

			outputVector.push_back(parsed);
		}
	}
	else
	{
		while (getline(stream, parsed, '/'))
		{
			if (parsed == "" || parsed == " ")
				continue;

			outputVector.push_back(parsed);
		}
	}

	return outputVector;
}

string canonicalizer(vector<string> filePath)
{
	vector<string> vectFilePath = filePath;
	map<int, string> filekey;
	int count = 0;
	string fileString = " ";
	for (vector<string>::iterator iter = vectFilePath.begin(); iter != vectFilePath.end(); iter++)
	{
		count++;

		if (iter == vectFilePath.begin())
		{
			bool colon = (*iter).find(":") != std::string::npos;

			if (*iter == "/" || colon)
			{
				filekey = map<int, string>();
			}
		}

		if (*iter == "..") 
		{
			filekey.erase(count);
		}
		else if (*iter == ".") 
		{
			continue;
		}
		else if (*iter == "/")
		{
			continue;
		}
		else
		{
			filekey.emplace(count, *iter);      
		}
	}

	map<int, string>::iterator it = filekey.begin();

	while (it != filekey.end())
	{
		fileString = it->second;

		it++;
	}

	return fileString;
}

bool homograph(string filePath1, string filePath2)
{
	vector<string> fileVector1 = stringConverter(filePath1);

	vector<string> fileVector2 = stringConverter(filePath2);

	string fileCanon1 = canonicalizer(fileVector1);
	string fileCanon2 = canonicalizer(fileVector2);


	if (fileCanon1.compare(fileCanon2) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void allPathsCheck(string filePath1, string filePath2)
{
	bool answer = homograph(filePath1, filePath2);
	manualResults(answer);
	cout << endl;
	testcase1();
	cout << endl;
	testcase2();
	cout << endl;
	testcase3();
	cout << endl;
}

void testcase1() //non-homographs
{
	string filepath1 = " /home/user/cse453/";
	string filepath2 = "../user/../password.txt";

	displayComparison(filepath1, filepath2);
	bool answer = homograph(filepath1, filepath2);

	manualResults(answer);

}

void testcase2() //non-homographs
{
	string filepath1 = "/home/user/cse453/";
	string filepath2 = " /../../secret/password.txt";

	displayComparison(filepath1, filepath2);
	bool answer = homograph(filepath1, filepath2);

	manualResults(answer);

}

void testcase3() //homographs
{	

	string filepath1 = "./../home/test.cpp";
	string filepath2 = "/root/desktop/home/test.cpp";

	displayComparison(filepath1, filepath2);
	bool answer = homograph(filepath1, filepath2);

	manualResults(answer);

}

void testcase4() //homographs
{
	string filepath1 = "/home/user/secret/password.txt";
	string filepath2 = " ./../secret/password.txt";

	displayComparison(filepath1, filepath2);
	bool answer = homograph(filepath1, filepath2);
	
	manualResults(answer);

}

void manualResults(bool answer)
{
	if (answer == true)
	{
		cout << "These paths are homographs.\n";
	}
	else
	{
		cout << "These paths are not homographs.\n";
	}
}

void displayComparison(string file1, string file2)
{
	cout << "The following file paths are being tested for homograph comparison:\n";
	cout << "\t First filepath: " << file1 << endl;
	cout << "\t Second filepath: " << file2 << endl;

}

int main() 
{
	string file1;
	string file2;
	char userInput[2];
	bool answer = true;

	cout << "Menu Options\n";
	cout << "\t M (Manual Input)\n";
	cout << "\t N (Testcase 1)\n";
	cout << "\t O (Testcase 2)\n";
	cout << "\t P (Testcase 3)\n";
	cout << "\t R (Testcase 4)\n";
	cout << "\t A (All paths check)\n";
	cout << "\t Q (Quit)\n";
	cout << "Input: ";
	do {
		cin.getline(userInput, 2);
		
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			continue;
			}

		if (isalpha(userInput[0]))
			userInput[0] = toupper(userInput[0]);
		
		if (isdigit(userInput[0]))
			continue;

		switch (userInput[0])
		{
		case 'M':
			file1 = prompt1(file1);
			file2 = prompt2(file2);
			answer = homograph(file1, file2);
			manualResults(answer);
			break;
		case 'N':
			testcase1();
			break;
		case 'O':
			testcase2();
			break;
		case 'P':
			testcase3();
			break;
		case 'R':
			testcase4();
			break;
		case 'A':
			file1 = prompt1(file1);
			file2 = prompt2(file2);
			allPathsCheck(file1, file2);
			break;
		case 'Q':
			break;
		default:
			cout << "Menu Options\n";
			cout << "\t M (Manual Input)\n";
			cout << "\t N (Testcase 1)\n";
			cout << "\t O (Testcase 2)\n";
			cout << "\t P (Testcase 3)\n";
			cout << "\t R (Testcase 4)\n";
			cout << "\t A (All paths check)\n";
			cout << "\t Q (Quit)\n";
			cout << "Input: ";
			break;
		}

	} while (userInput[0] != 'q' && userInput[0] != 'Q');

	return 0;
}
