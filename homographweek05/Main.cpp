#include <string>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;


bool homograph(string file1, string file2);
//bool nonHomograph(char file1[], char file2[]);
string canon(vector<string> file);
stack<string> reverseStack(stack<string> stringStack);


int main()
{
	vector<string> filePath1;
	vector<string> filePath2;
	string file1;
	string file2;

	cout << "Specify the first filename: ";
	cin >> file1;
	filePath1.push_back(file1);
	cout << "Specify the second filename: ";
	cin >> file2;
	filePath2.push_back(file2);

	file1 = canon(filePath1);
	file2 = canon(filePath2);

	if (homograph(file1, file2))
		cout << "The filepaths are homographs.\n";
	else
		cout << "The filepaths are non-Homographs.\n";

	return 0;
}

bool homograph(string file1, string file2) {

	if (file1 === file2)
		return true;
	else
		return false;
}

string canon(vector<string> file) {
	stack<string> currentFileString;

	for (vector<string>::iterator iter = file.begin(); iter != file.end(); iter++)
	{
		if (iter == file.begin())
		{
			bool colon = (*iter).find(":") != std::string::npos; //found out what npos was here https://www.geeksforgeeks.org/stringnpos-in-c-with-examples/

			if (*iter == "/" || colon)
			{
				currentFileString = stack<string>();
			}
		}

		if (*iter == "..") 
		{
			currentFileString.pop();
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
			currentFileString.push(*iter);     
		}
	}

	stack<string> reversedStack = reverseStack(currentFileString);
	string filePathName = "";

	while (!reversedStack.empty())
	{
		if (reversedStack.top() == "/")
		{
			reversedStack.pop();
			continue;
		}

		if (filePathName == "")
		{
			filePathName += reversedStack.top();
		}
		else
		{
			filePathName = filePathName + "/" + reversedStack.top();
		}

		reversedStack.pop();
	}

	return filePathName;
}

stack<string> reverseStack(stack<string> stringStack)
{
	stack<string> reversedStack;

	while (!stringStack.empty())
	{
		reversedStack.push(stringStack.top());
		stringStack.pop();
	}

	return reversedStack;
}