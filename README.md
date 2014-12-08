Interprocess-Communication-using-PIPES-in-c
===========================================

Using pipes sender Process have to communicate(send) some “string” and receiver process have to reply back with reverse of the string.

A simple program to understand the usage of "PIPE" in c. The sender process communicates some string on one end of the pipe and the receiver process reads that string from another end of the same pipe. It reverses the string using the helper function and writes on the same end of the pipe. The sender process reads and displays the reversed string from its end of the pipe.


Helper Functions: 
(1) char *strrev(char *str)
      Returns the reverse of the string "str" to the parent function.
