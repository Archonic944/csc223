#!/usr/bin/expect -f

set cpm_root "/Users/gabriel/Downloads/School/DECS/CPM_Altair8800_WinMacLin"
set timeout 10

spawn "$cpm_root/altair8800"
expect "sim>"
send "set cpu 8080\r"
send "attach dsk0 $cpm_root/A.dsk\r"
send "attach dsk1 $cpm_root/B.dsk\r"
send "attach dsk2 $cpm_root/C.dsk\r"
send "attach dsk3 $cpm_root/D.dsk\r"
send "load $cpm_root/dbl.bin ff00\r"
send "go ff00\r"
expect "A>"
send "c:\r"
expect "C>"

# Run the BST program
send "bstmain\r"
expect "Enter your choice:"

# Insert some values: 45, 25, 65, 15, 35
send "1\r"
expect "Enter value to insert:"
send "45\r"
expect "Enter your choice:"

send "1\r"
expect "Enter value to insert:"
send "25\r"
expect "Enter your choice:"

send "1\r"
expect "Enter value to insert:"
send "65\r"
expect "Enter your choice:"

send "1\r"
expect "Enter value to insert:"
send "15\r"
expect "Enter your choice:"

send "1\r"
expect "Enter value to insert:"
send "35\r"
expect "Enter your choice:"

# In-order traversal (should be sorted: 15 25 35 45 65)
send "4\r"
expect "Enter your choice:"

# Pre-order traversal
send "5\r"
expect "Enter your choice:"

# Post-order traversal
send "6\r"
expect "Enter your choice:"

# Search for 35
send "3\r"
expect "Enter value to search:"
send "35\r"
expect "Enter your choice:"

# Search for 99 (not in tree)
send "3\r"
expect "Enter value to search:"
send "99\r"
expect "Enter your choice:"

# Find smallest
send "7\r"
expect "Enter your choice:"

# Find largest
send "8\r"
expect "Enter your choice:"

# Count nodes
send "9\r"
expect "Enter your choice:"

# Delete 25
send "2\r"
expect "Enter value to delete:"
send "25\r"
expect "Enter your choice:"

# In-order after deletion
send "4\r"
expect "Enter your choice:"

# Exit
send "10\r"
expect "C>"

send "\x05"
expect "sim>"
send "q\r"
expect eof
