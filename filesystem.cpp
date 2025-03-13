#include <stdio.h>
#include <sstream> // For breaking down input into tokens
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class TrieNode
{
public:
    unordered_map<string, TrieNode *> children;
    bool isFile;
    string content;
    TrieNode() : isFile(false), content("") {}
};

class FileSystemTrie
{
private:
    TrieNode *root;
    TrieNode *currentDir;

public:
    FileSystemTrie()
    {
        root = new TrieNode();
        currentDir = root;
    }

    // Create a new directory
    void mkdir(const string &dirname)
    {
        if (currentDir->children.find(dirname) == currentDir->children.end())
        {
            currentDir->children[dirname] = new TrieNode();
            cout << "Directory created: " << dirname << endl;
        }
        else
        {
            cout << "Error: Directory already exists.\n";
        }
    }
    // List all files
    void ls()
    {
        for (auto &entry : currentDir->children)
        {
            cout << entry.first << (entry.second->isFile ? " [File]" : " [Dir]") << " ";
        }
        cout << endl;
    }

    void cd(const string &dir)
    {
        if (dir == "..")
        {
            // have to go above the chain
            cout << "GOING UP!!" << endl;
            return;
        }
        if (currentDir->children.find(dir) != currentDir->children.end() && !currentDir->children[dir]->isFile)
        {
            currentDir = currentDir->children[dir];
            cout << "Moved to " << dir << endl;
        }
        else
        {
            cout << "Error! Directory Not Found!!";
        }
    }
    void touch(const string &filename, const string &content = "")
    {
        if (currentDir->children.find(filename) == currentDir->children.end())
        {
            currentDir->children[filename] = new TrieNode();
            currentDir->children[filename]->isFile = true;
            currentDir->children[filename]->content = content;
            cout << "File created: " << filename << endl;
        }
        else
        {
            cout << "File already exists";
        }
    }
    void rm(const string &filename)
    {
        auto iter = currentDir->children.find(filename);
        if (iter != currentDir->children.end() && iter->second->isFile)
        {
            delete iter->second;
            currentDir->children.erase(iter);
            cout << "File deleted: " << filename << endl;
        }
        else
        {
            cout << "Error!! File not found or its a directory!" << endl;
        }
    }
};

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

void startCli()
{
    FileSystemTrie fst;
    string command, arg;
    while (true)
    {
        cout << ">>";
        cin >> command;
        if (command == "mkdir")
        {
            cin >> arg;
            fst.mkdir(arg);
        }
        else if (command == "ls")
        {
            fst.ls();
        }
        else if (command == "cd")
        {
            cin >> arg;
            fst.cd(arg);
        }
        else if (command == "touch")
        {
            cin >> arg;
            fst.touch(arg);
        }
        else if (command == "exit")
        {
            break;
        }
        else if (command == "rm")
        {
            cin >> arg;
            fst.rm(arg);
        }
        else
        {
            cout << "Unknown command!" << endl;
        }
    }
};

int main()
{
    startCli();

    return 0;
}