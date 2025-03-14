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
    void echo(const string &filename, const string &content, bool append = false)
    {
        if (currentDir->children.find(filename) == currentDir->children.end())
        {
            cout << "Error: File not found!\n";
            return;
        }

        TrieNode *file = currentDir->children[filename];
        if (!file->isFile)
        {
            cout << "Error: Cannot write to a directory!\n";
            return;
        }

        if (append)
        {
            file->content += "\n" + content;
        }
        else
        {
            file->content = content;
        }

        cout << "Content written to " << filename << endl;
    }
    void cat(const string &filename)
    {
        if (currentDir->children.find(filename) == currentDir->children.end())
        {
            cout << "Error: File not Found\n";
            return;
        }
        TrieNode *file = currentDir->children[filename];
        if (!file->isFile)
        {
            cout << "Error: " << filename << " is a directory!\n";
            return;
        }

        cout << file->content << endl;
    }
};

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
        else if (command == "echo")
        {
            string filename, content, mode;
            cin >> mode >> filename;
            getline(cin, content);

            bool append = (mode == ">>");
            fst.echo(filename, content, append);
        }
        else if (command == "cat")
        {
            string filename;
            cin >> filename;
            fst.cat(filename);
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