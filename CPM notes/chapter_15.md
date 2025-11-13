# Chapter 15: The File Control Block

*This chapter covers file access via the File Control Block. After completing it, we will have a full understanding of CP/M and be ready to write our own programs.*

## Getting to know the FCB

- Our disk accesses will use the giant hook at location 5.
- The FCB is a 33-byte block of RAM that contains information about a file, and workspace that the ystem uses to perform write operations.
- The TFCB (transient file control block) is located at 005ch through 007ch. It is created by CP/M after a command line typed by the operator.


Default TFCB structure:
1. (x1) Drive code: 00h = current, 01h = A:, 02h = B:, etc.
2. (x8) Filename: 8 characters, padded with spaces if shorter.
3. (x3) Filetype: 3 characters, padded with spaces if shorter.
4. (x1) Ex byte: Used if the file is larger than 16k.
5. (x2) System use bytes
6. (x1) Record count
7. (x16) Record group list: Addresses of 1k byte groups of disk records allocated to the file

All fields other than the drive select byte and the name + extension bytes are the operating system's workspace.

More about disk addresses: The lower 1k blocks are reserved for CP/M's use for disk directory entries. User files usually start at block 2 (the third 1k block on the disk).

More about wildcards: The FCB may contain the ? character if the user specified a wildcard in the filename or filetype. You can use wildcards to find files, but not read/write files.

## How CP/M uses the FCB

- 