# Realiable Transport Protocol (Project From J.F. Kurose)
This is an implementation for the Go-Back-N protocol and the Alternating-Bit protocol. Original project requirements are in the [Project CSE 335.pdf](./Project%20CSE%20335.pdf) file. Colors are disabled in the code. To enable them, uncomment the line `#define COLORED_TERM` in the target file.

## Example Runs
### Go Back N Protocol
```
$ ./go_back_n.sh
-----  Stop and Wait Network Simulator Version 1.1 -------- 

Enter the number of messages to simulate: 10
Enter  packet loss probability [enter 0.0 for no loss]:0.0
Enter packet corruption probability [0.0 for no corruption]:0.0
Enter average time between messages from sender's layer5 [ > 0.0]:5.0
Enter TRACE:0

[A] SEND: Packet 0
[A] TIME: Start
[B] RECV: Packet 0 [aaaaaaaaaaaaaaaaaaaa]
[B] ASND: Packet 0
[A] SEND: Packet 1
[B] RECV: Packet 1 [bbbbbbbbbbbbbbbbbbbb]
[B] ASND: Packet 1
[A]  ACK: Packet 0
[A] TIME: Restart
[A]  ACK: Packet 1
[A] TIME: Stop
[A] SEND: Packet 2
[A] TIME: Start
[A] SEND: Packet 3
[B] RECV: Packet 2 [cccccccccccccccccccc]
[B] ASND: Packet 2
[A] SEND: Packet 4
[B] RECV: Packet 3 [dddddddddddddddddddd]
[B] ASND: Packet 3
[A]  ACK: Packet 2
[A] TIME: Restart
[B] RECV: Packet 4 [eeeeeeeeeeeeeeeeeeee]
[B] ASND: Packet 4
[A]  ACK: Packet 3
[A] TIME: Restart
[A] SEND: Packet 5
[B] RECV: Packet 5 [ffffffffffffffffffff]
[B] ASND: Packet 5
[A]  ACK: Packet 4
[A] TIME: Restart
[A] SEND: Packet 6
[A] SEND: Packet 7
[B] RECV: Packet 6 [gggggggggggggggggggg]
[B] ASND: Packet 6
[A] SEND: Packet 8
[A]  ACK: Packet 5
[A] TIME: Restart
[B] RECV: Packet 7 [hhhhhhhhhhhhhhhhhhhh]
[B] ASND: Packet 7
[A] SEND: Packet 9
[A]  ACK: Packet 6
[A] TIME: Restart
[B] RECV: Packet 8 [iiiiiiiiiiiiiiiiiiii]
[B] ASND: Packet 8
[A]  ACK: Packet 7
[A] TIME: Restart
[A]  ACK: Packet 8
[A] TIME: Restart
[B] RECV: Packet 9 [jjjjjjjjjjjjjjjjjjjj]
[B] ASND: Packet 9
[A]  ACK: Packet 9
[A] TIME: Stop
 Simulator terminated at time 70.071053
 after sending 10 msgs from layer5
```

```
$ ./go_back_n.sh
-----  Stop and Wait Network Simulator Version 1.1 -------- 

Enter the number of messages to simulate: 50
Enter  packet loss probability [enter 0.0 for no loss]:0.3
Enter packet corruption probability [0.0 for no corruption]:0.0
Enter average time between messages from sender's layer5 [ > 0.0]:10.0
Enter TRACE:0

[A] SEND: Packet 0
[A] TIME: Start
[B] RECV: Packet 0 [aaaaaaaaaaaaaaaaaaaa]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Stop
[A] SEND: Packet 1
[A] TIME: Start
[A] SEND: Packet 2
[A] SEND: Packet 3
[A] SEND: Packet 4
[A] TIME: Timeout
[A] RSND: Packet 1
[A] RSND: Packet 2
[A] RSND: Packet 3
[A] RSND: Packet 4
[B] DROP: Packet 2
[B] DROP: Packet 3
[B] DROP: Packet 4
[A] SEND: Packet 5
[B] RECV: Packet 1 [bbbbbbbbbbbbbbbbbbbb]
[B] ASND: Packet 1
[B] DROP: Packet 3
[A] SEND: Packet 6
[A] TIME: Timeout
[A] RSND: Packet 1
[A] RSND: Packet 2
[A] RSND: Packet 3
[A] RSND: Packet 4
[A] RSND: Packet 5
[A] RSND: Packet 6
[B] DROP: Packet 6
[B] RECV: Packet 2 [cccccccccccccccccccc]
[B] ASND: Packet 2
[A] STOR: Packet 7
[B] RECV: Packet 3 [dddddddddddddddddddd]
[B] ASND: Packet 3
[B] RECV: Packet 4 [eeeeeeeeeeeeeeeeeeee]
[B] ASND: Packet 4
[A] STOR: Packet 8
[A]  ACK: Packet 3
[A] TIME: Restart
[A] SEND: Packet 7
[A] SEND: Packet 8
[B] DROP: Packet 6
[B] DROP: Packet 7
[A] SEND: Packet 9
[B] DROP: Packet 8
[B] DROP: Packet 9
[A] STOR: Packet 10
[A] TIME: Timeout
[A] RSND: Packet 4
[A] RSND: Packet 5
[A] RSND: Packet 6
[A] RSND: Packet 7
[A] RSND: Packet 8
[A] RSND: Packet 9
[B]  DUP: Packet 4
[B] ASND: Packet 4
[A]  ACK: Packet 4
[A] TIME: Restart
[A] SEND: Packet 10
[A] STOR: Packet 11
[A] STOR: Packet 12
[A] TIME: Timeout
[A] RSND: Packet 5
[A] RSND: Packet 6
[A] RSND: Packet 7
[A] RSND: Packet 8
[A] RSND: Packet 9
[A] RSND: Packet 10
[B] RECV: Packet 5 [ffffffffffffffffffff]
[B] ASND: Packet 5
[A] STOR: Packet 13
[B] RECV: Packet 6 [gggggggggggggggggggg]
[B] ASND: Packet 6
[A]  ACK: Packet 5
[A] TIME: Restart
[A] SEND: Packet 11
[B] RECV: Packet 7 [hhhhhhhhhhhhhhhhhhhh]
[B] ASND: Packet 7
[B] RECV: Packet 8 [iiiiiiiiiiiiiiiiiiii]
[B] ASND: Packet 8
[A]  ACK: Packet 7
[A] TIME: Restart
[A] SEND: Packet 12
[A] SEND: Packet 13
[A] STOR: Packet 14
[A] STOR: Packet 15
[B] RECV: Packet 9 [jjjjjjjjjjjjjjjjjjjj]
[B] ASND: Packet 9
[A] STOR: Packet 16
[A]  ACK: Packet 9
[A] TIME: Restart
[A] SEND: Packet 14
[A] SEND: Packet 15
[B] RECV: Packet 10 [kkkkkkkkkkkkkkkkkkkk]
[B] ASND: Packet 10
[A] STOR: Packet 17
[B] RECV: Packet 11 [llllllllllllllllllll]
[B] ASND: Packet 11
[A]  ACK: Packet 11
[A] TIME: Restart
[A] SEND: Packet 16
[A] SEND: Packet 17
[B] RECV: Packet 12 [mmmmmmmmmmmmmmmmmmmm]
[B] ASND: Packet 12
[B] DROP: Packet 14
[B] DROP: Packet 15
[B] DROP: Packet 16
[A] STOR: Packet 18
[A] STOR: Packet 19
[B] DROP: Packet 17
[A] STOR: Packet 20
[A] STOR: Packet 21
[A] TIME: Timeout
[A] RSND: Packet 12
[A] RSND: Packet 13
[A] RSND: Packet 14
[A] RSND: Packet 15
[A] RSND: Packet 16
[A] RSND: Packet 17
[B]  DUP: Packet 12
[B] ASND: Packet 12
[A] STOR: Packet 22
[A] STOR: Packet 23
[B] RECV: Packet 13 [nnnnnnnnnnnnnnnnnnnn]
[B] ASND: Packet 13
[A]  ACK: Packet 12
[A] TIME: Restart
[A] SEND: Packet 18
[A]  ACK: Packet 13
[A] TIME: Restart
[A] SEND: Packet 19
[B] RECV: Packet 14 [oooooooooooooooooooo]
[B] ASND: Packet 14
[B] RECV: Packet 15 [pppppppppppppppppppp]
[B] ASND: Packet 15
[A] STOR: Packet 24
[A]  ACK: Packet 14
[A] TIME: Restart
[A] SEND: Packet 20
[B] RECV: Packet 16 [qqqqqqqqqqqqqqqqqqqq]
[B] ASND: Packet 16
[A] STOR: Packet 25
[A] STOR: Packet 26
[B] RECV: Packet 17 [rrrrrrrrrrrrrrrrrrrr]
[B] ASND: Packet 17
[B] RECV: Packet 18 [ssssssssssssssssssss]
[B] ASND: Packet 18
[A] STOR: Packet 27
[A]  ACK: Packet 17
[A] TIME: Restart
[A] SEND: Packet 21
[A] SEND: Packet 22
[A] SEND: Packet 23
[B] RECV: Packet 19 [tttttttttttttttttttt]
[B] ASND: Packet 19
[A] STOR: Packet 28
[B] RECV: Packet 20 [uuuuuuuuuuuuuuuuuuuu]
[B] ASND: Packet 20
[B] RECV: Packet 21 [vvvvvvvvvvvvvvvvvvvv]
[B] ASND: Packet 21
[A]  ACK: Packet 20
[A] TIME: Restart
[A] SEND: Packet 24
[A] SEND: Packet 25
[A] SEND: Packet 26
[B] RECV: Packet 22 [wwwwwwwwwwwwwwwwwwww]
[B] ASND: Packet 22
[A]  ACK: Packet 21
[A] TIME: Restart
[A] SEND: Packet 27
[B] RECV: Packet 23 [xxxxxxxxxxxxxxxxxxxx]
[B] ASND: Packet 23
[A] STOR: Packet 29
[B] RECV: Packet 24 [yyyyyyyyyyyyyyyyyyyy]
[B] ASND: Packet 24
[A]  ACK: Packet 24
[A] TIME: Restart
[A] SEND: Packet 28
[A] SEND: Packet 29
[B] DROP: Packet 26
[A] SEND: Packet 30
[A] TIME: Timeout
[A] RSND: Packet 25
[A] RSND: Packet 26
[A] RSND: Packet 27
[A] RSND: Packet 28
[A] RSND: Packet 29
[A] RSND: Packet 30
[B] DROP: Packet 27
[A] STOR: Packet 31
[A] STOR: Packet 32
[B] DROP: Packet 28
[A] STOR: Packet 33
[A] STOR: Packet 34
[A] TIME: Timeout
[A] RSND: Packet 25
[A] RSND: Packet 26
[A] RSND: Packet 27
[A] RSND: Packet 28
[A] RSND: Packet 29
[A] RSND: Packet 30
[B] RECV: Packet 25 [zzzzzzzzzzzzzzzzzzzz]
[B] ASND: Packet 25
[B] RECV: Packet 26 [aaaaaaaaaaaaaaaaaaaa]
[B] ASND: Packet 26
[A]  ACK: Packet 25
[A] TIME: Restart
[A] SEND: Packet 31
[B] RECV: Packet 27 [bbbbbbbbbbbbbbbbbbbb]
[B] ASND: Packet 27
[A]  ACK: Packet 26
[A] TIME: Restart
[A] SEND: Packet 32
[A] STOR: Packet 35
[B] RECV: Packet 28 [cccccccccccccccccccc]
[B] ASND: Packet 28
[A]  ACK: Packet 27
[A] TIME: Restart
[A] SEND: Packet 33
[B] RECV: Packet 29 [dddddddddddddddddddd]
[B] ASND: Packet 29
[A] STOR: Packet 36
[A]  ACK: Packet 28
[A] TIME: Restart
[A] SEND: Packet 34
[B] RECV: Packet 30 [eeeeeeeeeeeeeeeeeeee]
[B] ASND: Packet 30
[B] RECV: Packet 31 [ffffffffffffffffffff]
[B] ASND: Packet 31
[B] RECV: Packet 32 [gggggggggggggggggggg]
[B] ASND: Packet 32
[A]  ACK: Packet 29
[A] TIME: Restart
[A] SEND: Packet 35
[A] STOR: Packet 37
[B] RECV: Packet 33 [hhhhhhhhhhhhhhhhhhhh]
[B] ASND: Packet 33
[A]  ACK: Packet 30
[A] TIME: Restart
[A] SEND: Packet 36
[A]  ACK: Packet 31
[A] TIME: Restart
[A] SEND: Packet 37
[B] DROP: Packet 36
[A] STOR: Packet 38
[B] DROP: Packet 37
[A]  ACK: Packet 32
[A] TIME: Restart
[A] SEND: Packet 38
[A] STOR: Packet 39
[A] STOR: Packet 40
[A]  ACK: Packet 33
[A] TIME: Restart
[A] SEND: Packet 39
[B] DROP: Packet 39
[A] STOR: Packet 41
[A] STOR: Packet 42
[A] STOR: Packet 43
[A] STOR: Packet 44
[A] TIME: Timeout
[A] RSND: Packet 34
[A] RSND: Packet 35
[A] RSND: Packet 36
[A] RSND: Packet 37
[A] RSND: Packet 38
[A] RSND: Packet 39
[A] STOR: Packet 45
[B] RECV: Packet 34 [iiiiiiiiiiiiiiiiiiii]
[B] ASND: Packet 34
[A] STOR: Packet 46
[B] RECV: Packet 35 [jjjjjjjjjjjjjjjjjjjj]
[B] ASND: Packet 35
[B] DROP: Packet 37
[A]  ACK: Packet 35
[A] TIME: Restart
[A] SEND: Packet 40
[A] SEND: Packet 41
[A] STOR: Packet 47
[B] DROP: Packet 41
[A] STOR: Packet 48
[A] STOR: Packet 49
[A] TIME: Timeout
[A] RSND: Packet 36
[A] RSND: Packet 37
[A] RSND: Packet 38
[A] RSND: Packet 39
[A] RSND: Packet 40
[A] RSND: Packet 41
[B] DROP: Packet 37
[B] DROP: Packet 38
[B] DROP: Packet 41
[A] TIME: Timeout
[A] RSND: Packet 36
[A] RSND: Packet 37
[A] RSND: Packet 38
[A] RSND: Packet 39
[A] RSND: Packet 40
[A] RSND: Packet 41
[B] RECV: Packet 36 [kkkkkkkkkkkkkkkkkkkk]
[B] ASND: Packet 36
[B] DROP: Packet 38
[B] DROP: Packet 39
[B] DROP: Packet 41
[A] TIME: Timeout
[A] RSND: Packet 36
[A] RSND: Packet 37
[A] RSND: Packet 38
[A] RSND: Packet 39
[A] RSND: Packet 40
[A] RSND: Packet 41
[B]  DUP: Packet 36
[B] ASND: Packet 36
[A]  ACK: Packet 36
[A] TIME: Restart
[A] SEND: Packet 42
[B] DROP: Packet 38
[B] DROP: Packet 39
[B] DROP: Packet 41
[A] TIME: Timeout
[A] RSND: Packet 37
[A] RSND: Packet 38
[A] RSND: Packet 39
[A] RSND: Packet 40
[A] RSND: Packet 41
[A] RSND: Packet 42
[B] DROP: Packet 39
[B] DROP: Packet 40
[B] DROP: Packet 41
[B] DROP: Packet 42
[A] TIME: Timeout
[A] RSND: Packet 37
[A] RSND: Packet 38
[A] RSND: Packet 39
[A] RSND: Packet 40
[A] RSND: Packet 41
[A] RSND: Packet 42
[B] RECV: Packet 37 [llllllllllllllllllll]
[B] ASND: Packet 37
[B] DROP: Packet 40
[A]  ACK: Packet 37
[A] TIME: Restart
[A] SEND: Packet 43
[A] TIME: Timeout
[A] RSND: Packet 38
[A] RSND: Packet 39
[A] RSND: Packet 40
[A] RSND: Packet 41
[A] RSND: Packet 42
[A] RSND: Packet 43
[B] RECV: Packet 38 [mmmmmmmmmmmmmmmmmmmm]
[B] ASND: Packet 38
[A]  ACK: Packet 38
[A] TIME: Restart
[A] SEND: Packet 44
[B] RECV: Packet 39 [nnnnnnnnnnnnnnnnnnnn]
[B] ASND: Packet 39
[B] RECV: Packet 40 [oooooooooooooooooooo]
[B] ASND: Packet 40
[A]  ACK: Packet 39
[A] TIME: Restart
[A] SEND: Packet 45
[B] RECV: Packet 41 [pppppppppppppppppppp]
[B] ASND: Packet 41
[B] RECV: Packet 42 [qqqqqqqqqqqqqqqqqqqq]
[B] ASND: Packet 42
[B] RECV: Packet 43 [rrrrrrrrrrrrrrrrrrrr]
[B] ASND: Packet 43
[B] RECV: Packet 44 [ssssssssssssssssssss]
[B] ASND: Packet 44
[A]  ACK: Packet 43
[A] TIME: Restart
[A] SEND: Packet 46
[A] SEND: Packet 47
[A] SEND: Packet 48
[A] SEND: Packet 49
[B] RECV: Packet 45 [tttttttttttttttttttt]
[B] ASND: Packet 45
[A]  ACK: Packet 44
[A] TIME: Restart
[B] RECV: Packet 46 [uuuuuuuuuuuuuuuuuuuu]
[B] ASND: Packet 46
[B] RECV: Packet 47 [vvvvvvvvvvvvvvvvvvvv]
[B] ASND: Packet 47
[A]  ACK: Packet 45
[A] TIME: Restart
[B] DROP: Packet 49
[A]  ACK: Packet 46
[A] TIME: Restart
[A]  ACK: Packet 47
[A] TIME: Restart
[A] TIME: Timeout
[A] RSND: Packet 48
[A] RSND: Packet 49
[B] RECV: Packet 48 [wwwwwwwwwwwwwwwwwwww]
[B] ASND: Packet 48
[B] RECV: Packet 49 [xxxxxxxxxxxxxxxxxxxx]
[B] ASND: Packet 49
[A] TIME: Timeout
[A] RSND: Packet 48
[A] RSND: Packet 49
[A] TIME: Timeout
[A] RSND: Packet 48
[A] RSND: Packet 49
[B]  DUP: Packet 48
[B] ASND: Packet 49
[A]  ACK: Packet 49
[A] TIME: Stop
 Simulator terminated at time 761.470215
 after sending 50 msgs from layer5
```

```
$ ./go_back_n.sh
-----  Stop and Wait Network Simulator Version 1.1 -------- 

Enter the number of messages to simulate: 10
Enter  packet loss probability [enter 0.0 for no loss]:0.0
Enter packet corruption probability [0.0 for no corruption]:0.3
Enter average time between messages from sender's layer5 [ > 0.0]:10.0
Enter TRACE:0

[A] SEND: Packet 0
[A] TIME: Start
[B] DROP: Packet Invalid
[A] SEND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 0
[A] RSND: Packet 1
[B] DROP: Packet Invalid
[A] SEND: Packet 2
[B] RECV: Packet 0 [aaaaaaaaaaaaaaaaaaaa]
[B] ASND: Packet 0
[B] DROP: Packet Invalid
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 3
[B] DROP: Packet 2
[A] SEND: Packet 4
[B] DROP: Packet Invalid
[B] DROP: Packet 4
[A] SEND: Packet 5
[A] TIME: Timeout
[A] RSND: Packet 1
[A] RSND: Packet 2
[A] RSND: Packet 3
[A] RSND: Packet 4
[A] RSND: Packet 5
[B] DROP: Packet Invalid
[B] RECV: Packet 1 [bbbbbbbbbbbbbbbbbbbb]
[B] ASND: Packet 1
[A] SEND: Packet 6
[B] RECV: Packet 2 [cccccccccccccccccccc]
[B] ASND: Packet 2
[A] DROP: Packet Invalid
[A]  ACK: Packet 2
[A] TIME: Restart
[B] DROP: Packet Invalid
[B] DROP: Packet Invalid
[B] DROP: Packet Invalid
[A] SEND: Packet 7
[B] DROP: Packet 6
[B] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 3
[A] RSND: Packet 4
[A] RSND: Packet 5
[A] RSND: Packet 6
[A] RSND: Packet 7
[B] DROP: Packet Invalid
[B] DROP: Packet 4
[A] SEND: Packet 8
[B] DROP: Packet 5
[B] DROP: Packet Invalid
[B] DROP: Packet 7
[A] STOR: Packet 9
[A] TIME: Timeout
[A] RSND: Packet 3
[A] RSND: Packet 4
[A] RSND: Packet 5
[A] RSND: Packet 6
[A] RSND: Packet 7
[A] RSND: Packet 8
[B] DROP: Packet Invalid
[B] RECV: Packet 3 [dddddddddddddddddddd]
[B] ASND: Packet 3
[B] RECV: Packet 4 [eeeeeeeeeeeeeeeeeeee]
[B] ASND: Packet 4
[A] DROP: Packet Invalid
[B] RECV: Packet 5 [ffffffffffffffffffff]
[B] ASND: Packet 5
[A] TIME: Timeout
[A] RSND: Packet 3
[A] RSND: Packet 4
[A] RSND: Packet 5
[A] RSND: Packet 6
[A] RSND: Packet 7
[A] RSND: Packet 8
[A] DROP: Packet Invalid
[B] RECV: Packet 6 [gggggggggggggggggggg]
[B] ASND: Packet 6
[B] RECV: Packet 7 [hhhhhhhhhhhhhhhhhhhh]
[B] ASND: Packet 7
[A] DROP: Packet Invalid
[B] RECV: Packet 8 [iiiiiiiiiiiiiiiiiiii]
[B] ASND: Packet 8
[B] DROP: Packet Invalid
[A]  ACK: Packet 6
[A] TIME: Restart
[A] SEND: Packet 9
[B]  DUP: Packet 4
[B] ASND: Packet 8
[A]  ACK: Packet 7
[A] TIME: Restart
[B] DROP: Packet Invalid
[A]  ACK: Packet 8
[A] TIME: Restart
[A]  ACK: Packet 8
[B] DROP: Packet Invalid
[B] DROP: Packet Invalid
[B] DROP: Packet Invalid
[B] RECV: Packet 9 [jjjjjjjjjjjjjjjjjjjj]
[B] ASND: Packet 9
[A] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 9
[B]  DUP: Packet 9
[B] ASND: Packet 9
[A]  ACK: Packet 9
[A] TIME: Stop
 Simulator terminated at time 229.752228
 after sending 10 msgs from layer5
```

### Alternating Bit Protocol
```
$ ./alternating_bit_protocol.sh 
-----  Stop and Wait Network Simulator Version 1.1 -------- 

Enter the number of messages to simulate: 10
Enter  packet loss probability [enter 0.0 for no loss]:0.0
Enter packet corruption probability [0.0 for no corruption]:0.0
Enter average time between messages from sender's layer5 [ > 0.0]:5.0
Enter TRACE:0

[A] SEND: Packet 0
[A] TIME: Start
[B] RECV: Packet 0 [aaaaaaaaaaaaaaaaaaaa]
[B] ASND: Packet 0
[A] STOR: Packet 1
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [bbbbbbbbbbbbbbbbbbbb]
[B] ASND: Packet 1
[A] STOR: Packet 0
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[A] STOR: Packet 1
[B] RECV: Packet 0 [cccccccccccccccccccc]
[B] ASND: Packet 0
[A] STOR: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[A] STOR: Packet 1
[B] RECV: Packet 1 [dddddddddddddddddddd]
[B] ASND: Packet 1
[A] STOR: Packet 0
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[A] STOR: Packet 1
[A] STOR: Packet 0
[B] RECV: Packet 0 [eeeeeeeeeeeeeeeeeeee]
[B] ASND: Packet 0
[A] STOR: Packet 1
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [ffffffffffffffffffff]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [gggggggggggggggggggg]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [hhhhhhhhhhhhhhhhhhhh]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [iiiiiiiiiiiiiiiiiiii]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [jjjjjjjjjjjjjjjjjjjj]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Stop
 Simulator terminated at time 107.629364
 after sending 10 msgs from layer5
```

```
$ ./alternating_bit_protocol.sh 
-----  Stop and Wait Network Simulator Version 1.1 -------- 

Enter the number of messages to simulate: 50
Enter  packet loss probability [enter 0.0 for no loss]:0.3
Enter packet corruption probability [0.0 for no corruption]:0.0
Enter average time between messages from sender's layer5 [ > 0.0]:10.0
Enter TRACE:0

[A] SEND: Packet 0
[A] TIME: Start
[B] RECV: Packet 0 [aaaaaaaaaaaaaaaaaaaa]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Stop
[A] SEND: Packet 1
[A] TIME: Start
[A] STOR: Packet 0
[A] STOR: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[A] STOR: Packet 0
[B] RECV: Packet 1 [bbbbbbbbbbbbbbbbbbbb]
[B] ASND: Packet 1
[A] STOR: Packet 1
[A] STOR: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[A] STOR: Packet 1
[A] STOR: Packet 0
[A] STOR: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 0
[A] STOR: Packet 0
[A] STOR: Packet 1
[A] STOR: Packet 0
[A] STOR: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 0
[B] RECV: Packet 0 [cccccccccccccccccccc]
[B] ASND: Packet 0
[A] STOR: Packet 0
[A] STOR: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 0
[A] STOR: Packet 0
[A] STOR: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 0
[A] STOR: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[A] STOR: Packet 1
[A] STOR: Packet 0
[A] STOR: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 0
[A] STOR: Packet 0
[A] STOR: Packet 1
[B]  DUP: Packet 0
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [dddddddddddddddddddd]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[A] STOR: Packet 0
[A] STOR: Packet 1
[B] RECV: Packet 0 [eeeeeeeeeeeeeeeeeeee]
[B] ASND: Packet 0
[A] STOR: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[A] STOR: Packet 1
[A] STOR: Packet 0
[A] STOR: Packet 1
[A] STOR: Packet 0
[A] STOR: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[A] STOR: Packet 0
[A] STOR: Packet 1
[A] STOR: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 1
[B] RECV: Packet 1 [ffffffffffffffffffff]
[B] ASND: Packet 1
[A] STOR: Packet 1
[A] STOR: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 1
[A] STOR: Packet 1
[A] STOR: Packet 0
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A] STOR: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A] STOR: Packet 0
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[A] STOR: Packet 1
[B] RECV: Packet 0 [gggggggggggggggggggg]
[B] ASND: Packet 0
[A] STOR: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [hhhhhhhhhhhhhhhhhhhh]
[B] ASND: Packet 1
[A] STOR: Packet 1
[A] STOR: Packet 0
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[A] STOR: Packet 1
[A] STOR: Packet 0
[B] RECV: Packet 0 [iiiiiiiiiiiiiiiiiiii]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [jjjjjjjjjjjjjjjjjjjj]
[B] ASND: Packet 1
[A] STOR: Packet 1
[A] STOR: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 1
[A] STOR: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [kkkkkkkkkkkkkkkkkkkk]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [llllllllllllllllllll]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [mmmmmmmmmmmmmmmmmmmm]
[B] ASND: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[B]  DUP: Packet 0
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [nnnnnnnnnnnnnnnnnnnn]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [oooooooooooooooooooo]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B] RECV: Packet 1 [pppppppppppppppppppp]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [qqqqqqqqqqqqqqqqqqqq]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [rrrrrrrrrrrrrrrrrrrr]
[B] ASND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [ssssssssssssssssssss]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [tttttttttttttttttttt]
[B] ASND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[B] RECV: Packet 0 [uuuuuuuuuuuuuuuuuuuu]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B] RECV: Packet 1 [vvvvvvvvvvvvvvvvvvvv]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [wwwwwwwwwwwwwwwwwwww]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B] RECV: Packet 1 [xxxxxxxxxxxxxxxxxxxx]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [yyyyyyyyyyyyyyyyyyyy]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [zzzzzzzzzzzzzzzzzzzz]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[B] RECV: Packet 0 [aaaaaaaaaaaaaaaaaaaa]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [bbbbbbbbbbbbbbbbbbbb]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[B] RECV: Packet 0 [cccccccccccccccccccc]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [dddddddddddddddddddd]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [eeeeeeeeeeeeeeeeeeee]
[B] ASND: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[B]  DUP: Packet 0
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B] RECV: Packet 1 [ffffffffffffffffffff]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[B] RECV: Packet 0 [gggggggggggggggggggg]
[B] ASND: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[B]  DUP: Packet 0
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B] RECV: Packet 1 [hhhhhhhhhhhhhhhhhhhh]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[B] RECV: Packet 0 [iiiiiiiiiiiiiiiiiiii]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B] RECV: Packet 1 [jjjjjjjjjjjjjjjjjjjj]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[B] RECV: Packet 0 [kkkkkkkkkkkkkkkkkkkk]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B] RECV: Packet 1 [llllllllllllllllllll]
[B] ASND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[B] RECV: Packet 0 [mmmmmmmmmmmmmmmmmmmm]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B] RECV: Packet 1 [nnnnnnnnnnnnnnnnnnnn]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [oooooooooooooooooooo]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [pppppppppppppppppppp]
[B] ASND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [qqqqqqqqqqqqqqqqqqqq]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [rrrrrrrrrrrrrrrrrrrr]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [ssssssssssssssssssss]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [tttttttttttttttttttt]
[B] ASND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [uuuuuuuuuuuuuuuuuuuu]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 1
[B] RECV: Packet 1 [vvvvvvvvvvvvvvvvvvvv]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [wwwwwwwwwwwwwwwwwwww]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [xxxxxxxxxxxxxxxxxxxx]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Stop
 Simulator terminated at time 2215.469727
 after sending 50 msgs from layer5
```

```
$ ./alternating_bit_protocol.sh 
-----  Stop and Wait Network Simulator Version 1.1 -------- 

Enter the number of messages to simulate: 10
Enter  packet loss probability [enter 0.0 for no loss]:0.0
Enter packet corruption probability [0.0 for no corruption]:0.3
Enter average time between messages from sender's layer5 [ > 0.0]:10.0
Enter TRACE:0

[A] SEND: Packet 0
[A] TIME: Start
[B] DROP: Packet Invalid
[A] STOR: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 0
[A] STOR: Packet 0
[B] DROP: Packet Invalid
[A] STOR: Packet 1
[A] TIME: Timeout
[A] RSND: Packet 0
[B] RECV: Packet 0 [aaaaaaaaaaaaaaaaaaaa]
[B] ASND: Packet 0
[A] STOR: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[A] STOR: Packet 1
[B] RECV: Packet 1 [bbbbbbbbbbbbbbbbbbbb]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] DROP: Packet Invalid
[A] STOR: Packet 0
[A] STOR: Packet 1
[A] STOR: Packet 0
[A] TIME: Timeout
[A] RSND: Packet 0
[B] RECV: Packet 0 [cccccccccccccccccccc]
[B] ASND: Packet 0
[A] STOR: Packet 1
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B] RECV: Packet 1 [dddddddddddddddddddd]
[B] ASND: Packet 1
[A] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [eeeeeeeeeeeeeeeeeeee]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [ffffffffffffffffffff]
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [gggggggggggggggggggg]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [hhhhhhhhhhhhhhhhhhhh]
[B] ASND: Packet 1
[A] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Restart
[A] SEND: Packet 0
[B] RECV: Packet 0 [iiiiiiiiiiiiiiiiiiii]
[B] ASND: Packet 0
[A]  ACK: Packet 0
[A] TIME: Restart
[A] SEND: Packet 1
[B] RECV: Packet 1 [jjjjjjjjjjjjjjjjjjjj]
[B] ASND: Packet 1
[A] DROP: Packet Invalid
[A] TIME: Timeout
[A] RSND: Packet 1
[B]  DUP: Packet 1
[B] ASND: Packet 1
[A]  ACK: Packet 1
[A] TIME: Stop
 Simulator terminated at time 671.898438
 after sending 10 msgs from layer5
```