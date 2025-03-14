# 📂 File System Simulator

## 📌 Overview
This is a simple **command-line file system simulator** written in **C++**. It allows users to execute basic file system operations such as creating directories, changing directories, listing contents, creating files, and removing files. The program continuously runs in a loop, processing user input until the `exit` command is issued.

## 🛠 Features
- **mkdir [directory]** → Creates a new directory.
- **ls** → Lists directory contents.
- **cd [directory]** → Changes the current directory.
- **touch [file]** → Creates a new file.
- **rm [file]** → Removes a file.
- **echo "text" > [file]** → Writes content to a file.
- **echo "text" >> [file]** → Appends content to a file.
- **cat [file]** → Displays file content.
- **exit** → Exits the program.

## 📝 How It Works
1. **Create Directories & Files**
   ```sh
   mkdir documents
   touch notes.txt
   ```
2. **Navigate Through Directories**
   ```sh
   cd documents
   ls
   ```
3. **Write & Read File Content**
   ```sh
   echo "Hello, World!" > notes.txt
   cat notes.txt
   ```
4. **Delete Files**
   ```sh
   rm notes.txt
   ```

