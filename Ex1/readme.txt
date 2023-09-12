208588392 208407379

Part A:
Q1:
https://dev.to/0xbf/implement-tee-cli-in-c-c-lang-2p5c

Q2:
https://www.geeksforgeeks.org/explicitly-assigning-port-number-client-socket/

https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/

Part B:

https://stackoverflow.com/questions/174531/how-to-read-the-content-of-a-file-to-a-string-in-c
https://idiotdeveloper.com/file-transfer-using-tcp-socket-in-c/



script(0):

Script started on 2022-12-02 01:29:48+02:00 [TERM="xterm-256color" TTY="/dev/pts/0" COLUMNS="139" LINES="14"]
]0;idankam98@DESKTOP-KF1QKC0: ~/Operating_Systems_Course/OS_EX2[01;32midankam98@DESKTOP-KF1QKC0[00m:[01;34m~/Operating_Systems_Course/OS_EX2[00m$ make clean
rm -f *.o *.a *.so mync myshell mytee
]0;idankam98@DESKTOP-KF1QKC0: ~/Operating_Systems_Course/OS_EX2[01;32midankam98@DESKTOP-KF1QKC0[00m:[01;34m~/Operating_Systems_Course/OS_EX2[00m$ make akk[K[Kll
gcc  mync.c -o mync
gcc  myshell.c -o myshell
gcc  mytee.c -o mytee
]0;idankam98@DESKTOP-KF1QKC0: ~/Operating_Systems_Course/OS_EX2[01;32midankam98@DESKTOP-KF1QKC0[00m:[01;34m~/Operating_Systems_Course/OS_EX2[00m$ ./mytee t1.txt
1234
1234
1010
1010
abc
abc
^C
]0;idankam98@DESKTOP-KF1QKC0: ~/Operating_Systems_Course/OS_EX2[01;32midankam98@DESKTOP-KF1QKC0[00m:[01;34m~/Operating_Systems_Course/OS_EX2[00m$ ./shell
bash: ./shell: No such file or directory
]0;idankam98@DESKTOP-KF1QKC0: ~/Operating_Systems_Course/OS_EX2[01;32midankam98@DESKTOP-KF1QKC0[00m:[01;34m~/Operating_Systems_Course/OS_EX2[00m$ ./shellmshellyshell
~~~~~~ SHELL ~~~~~~

/home/idankam98/Operating_Systems_Course/OS_EX2>DIR
.
..
.vscode
Makefile
mync
mync.c
myshell
myshell.c
mytee
mytee.c
README.md
t1.txt
typescript
/home/idankam98/Operating_Systems_Course/OS_EX2>COPY t1.txt t2.txt
file is copied
/home/idankam98/Operating_Systems_Course/OS_EX2>ls -  l | sort -r
total 116
here
-rwxr-xr-x 1 idankam98 idankam98 22520 Dec  2 01:30 myshell
-rwxr-xr-x 1 idankam98 idankam98 17472 Dec  2 01:30 mync
-rwxr-xr-x 1 idankam98 idankam98 16968 Dec  2 01:30 mytee
-rw-r--r-- 1 idankam98 idankam98 10038 Dec  2 01:19 myshell.c
-rw-r--r-- 1 idankam98 idankam98  3183 Dec  2 01:21 mync.c
-rw-r--r-- 1 idankam98 idankam98  1024 Dec  2 01:31 typescript
-rw-r--r-- 1 idankam98 idankam98   864 Dec  2 01:21 mytee.c
-rw-r--r-- 1 idankam98 idankam98   258 Dec  2 01:27 Makefile
-rw-r--r-- 1 idankam98 idankam98   211 Dec  2 01:22 README.md
-rw-r--r-- 1 idankam98 idankam98    14 Dec  2 01:30 t1.txt
-rw------- 1 idankam98 idankam98    14 Dec  2 01:31 t2.txt
]0;idankam98@DESKTOP-KF1QKC0: ~/Operating_Systems_Course/OS_EX2[01;32midankam98@DESKTOP-KF1QKC0[00m:[01;34m~/Operating_Systems_Course/OS_EX2[00m$ 
[K]0;idankam98@DESKTOP-KF1QKC0: ~/Operating_Systems_Course/OS_EX2[01;32midankam98@DESKTOP-KF1QKC0[00m:[01;34m~/Operating_Systems_Course/OS_EX2[00m$ ./mync -L 5060
Socket successfully created..
Socket successfully binded..