# Chapter 4: What the operating system provides

## Features

- Named file handling
    - Up to 8 characters in length
    - Com is command line file, ASM is assembly file
    - The leading dash represents a directory label, and is not a real file
- To create a file use the SAVE command
- DIR lists the files
- ? is a wildcard, * is any number of characters
- **As long as you use the same file handler routines, you can parse wildcards and other options**
- The PIP command is used to send a file to a logical device
- **Logical devices are assigned to physical devices, so the programmer doesn't have to worry about physical devices**
