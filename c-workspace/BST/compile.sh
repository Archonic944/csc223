#!/usr/bin/expect -f

set cpm_root "/Users/gabriel/Downloads/School/DECS/CPM_Altair8800_WinMacLin"
set src_root "/Users/gabriel/Development/Github/csc215/c-workspace/BST"

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

# Copy files to C: drive
send "a:r $src_root/BST.H\r"
expect "C>"
send "a:r $src_root/BST.C\r"
expect "C>"
send "a:r $src_root/BSTMAIN.C\r"
expect "C>"

# Compile each .C file
send "cc BST\r"
expect {
    "C>" {}
    timeout { puts "TIMEOUT on cc BST"; exit 1 }
}
send "cc BSTMAIN\r"
expect {
    "C>" {}
    timeout { puts "TIMEOUT on cc BSTMAIN"; exit 1 }
}

# Link: BSTMAIN first (has main), then BST
send "clink BSTMAIN BST\r"
expect {
    "C>" {}
    timeout { puts "TIMEOUT on clink"; exit 1 }
}

send "\x05"
expect "sim>"
send "q\r"
expect eof
