#include <stdio.h>
#include <sstream> // For breaking down input into tokens
#include <iostream>
#include <vector>

using namespace std;
void executecommand(const vector<string> &commands)
{
    if (commands.empty())
    {
        return;
    }

    string command = commands[0];
    if (command == "mkdir" || command == "cd" || command == "touch" || command == "rm")
    {
        if (commands.size() < 2)
        {
            cout << "Error: Missing argument for " << command << endl;
            return;
        }
    }
    if (command == "mkdir")
    {
        cout << "Creating a new director named: " << commands[1] << endl;
    }
    else if (command == "ls")
    {
        cout << "Listing all directories present: " << endl;
    }
    else if (command == "cd")
    {
        cout << "Changing directory to: " << commands[1] << endl;
    }
    else if (command == "touch")
    {
        cout << "Creating new file named: " << commands[1] << endl;
    }
    else if (command == "exit")
    {
        cout << "Exiting...." << endl;
        exit(0);
    }
    else if (command == "rm")
    {
        cout << "Removing: " << commands[1] << endl;
    }
    else
    {
        cout << "Invalid Command: " << command << endl;
    }
}
int main()
{
    string input;
    while (true)
    {
        cout << ">>";
        getline(cin, input);
        istringstream ss(input);
        vector<string> commands;
        string token;
        while (ss >> token)
        {
            commands.push_back(token);
        }
        executecommand(commands);
    }

    return 0;
}