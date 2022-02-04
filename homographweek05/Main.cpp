#include <cstring>
#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

bool homograph(string file1, string file2);
string canon(vector<string> filePath);
stack<string> reverseStack(stack<string> stringStack);
vector<string> stringToVector(string file);
string getCurrentPath(stack<string>& pathVector);

int main()
{
	string file1 = "/home/user/secret/password.txt";
	string file2 = "./../secret/password.txt";
/*
	cout << "Specify the first filename: ";
	cin >> (file1);

	cout << "Specify the second filename: ";
	cin >> file2;
*/
	if (homograph(file1, file2))
		cout << "The filepaths are homographs.\n";
	else
		cout << "The filepaths are non-Homographs.\n";

	return 0;
}

bool homograph(string file1, string file2) {
	
	vector<string> filePath1 = stringToVector(file1);
	vector<string> filePath2 = stringToVector(file2);
	
	file1 = canon(filePath1);
	file2 = canon(filePath2);

	if (file1.compare(file2) == 0) {
		return true;
	}
	else {
		return false;
	}
}

string canon(vector<string> filePath) {
	stack<string> currentFileString;
	
	for (vector<string>::iterator iter = filePath.begin(); iter != filePath.end(); iter++)
	{
		if (iter == filePath.begin())
		{
			bool foundColon = (*iter).find(":") != std::string::npos;

			// if we are at the beginning of a path / - for unix C: - for windows - we don't want a current working directory.
			if (*iter == "/" || foundColon)
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

vector<string> stringToVector(string file)
{
	vector<string> newVector;
	stringstream str_strm(file);
	string parsed;

	while (getline(str_strm, parsed, '/'))
	{
		if (parsed == "" || parsed == " ")
			continue;

		newVector.push_back(parsed);
	}


	return newVector;
}

string getCurrentPath(stack<string>& pathVector)
{
	// this uses the std::filesystem library to get the current working directory path
	path currentPath = current_path();
	path::iterator currentPathIter;

	string currentPathString = currentPath.generic_string();

	for (currentPathIter = currentPath.begin(); currentPathIter != currentPath.end(); currentPathIter++)
	{
		pathVector.push((*currentPathIter).generic_string());
	}

	return currentPathString;
}
