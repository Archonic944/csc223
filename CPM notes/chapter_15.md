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

The minimum size of any file is 1024 bytes (1k).

CP/M allocates disk space in "groups" of 8 records each.

The convenience of this system is that instead of every record being in the address space, it's less granular. One byte can store the address to a single group. CP/M handles translating group number to the group's starting record address.

## Creating a disk file

CP/M allocates by finding the lowest numbered disk group not allocated to another file. The first time we write, that address is placed into byte d0 in the FCB.

As we write, CP/M updates the record count and cr. Each group of 8 records written fills the next disk allocation byte with the next lowest unallocated group number.

When we close the file, CP/M writes the first 32 bytes of the FCB to the disk directory. This is a **directory entry**. The drive select byte is zeroed because the directory entry has to be on the same disk as the data.

Erasing the file doesn't zero out the data on disk, it just marks the entry as deleted by changing the first byte of the filename to E5h. The space is then available for new files.

"Dynamic disk space allocaton" refers to how entire directory entries can be overwritten in a nonlinear fashion as files are created and deleted.

TABLE 15-1. The library of user subroutines constructed by
completing all of the exercises in this book.

## Table 15-1
| Source Listing | File Name    | Contents                          |
|----------------|--------------|-----------------------------------|
| 15-2           | DISKEQU.LIB  | Data and address value assignments
|                |              | for disk programs.                |
| 15-1           | SHOFN.LIB    | Show file name subroutine.        |
| 16-1           | GET.LIB      | GET: a file from disk subroutine. |
| 17-1           | PUT.LIB      | PUT: a file onto disk subroutine. |
| 16-2           | DISKSU.LIB   | Disk subroutines, miscellaneous.  |
| (Part of      | CPMIO.LIB    | Input/output subroutines.         |
| CPMIO.ASM)     |              |                                   |
| 16-3           | RAM.LIB      | Memory area assignments.          |
