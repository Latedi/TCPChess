TCPChess
========

Play chess using the command line.
This program is made for Windows and utilizes TCP sockets for networking.

How to play

Connect:
To host start the executable and input 'host'. You will the be prompted for a port number to use.
To connect to a host type 'connect'. You will the be prompted for a port to use and then an IP address to connect to.
NOTE: If you are hosting don't forget to forward the port you are intending to use.

Play:
To move use the command 'Move <c1> <c2>' where <c1> is a valid tile with a piece you own and <c2> is a valid tile to which <c1> can move.
Coordinates go from a to h and from 1 to 8. So the minimum coordinate is a1 and the maximum coordinate is h8.
Castling is done with either '0-0' (kingside) or '0-0-0' (queenside). You can exchange the zeros for Os if you like.
To quit type 'quit'
To print a message with this information type 'help' while playing the game.


For the less technical, the game can be downloaded in .rar format here:
https://www.dropbox.com/s/fck74meueano0yt/TCPChess-1.0.rar