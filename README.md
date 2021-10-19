# SocketTest
This a test for TCP echo service

## Content
* Description

* Architecture
  *  Server
  *  Client

* Usage
  * Installation
  * Execute

## Description 
#### *Core implementation*
The core part of this lab project is that the TCP server is equipped with the multithread techniques in respond to the high concurrence of request from client side. Considering the experimental purpose as well as the computing costs limitation of this lab, the acceptance is simply range from 0 to maximum 16. 

#### *Main functions*


## Architecture
Focusing on the server, there is a standard process for it to initiate and handle the TCP connection.
1. Create a socket
2. Bind the socket to the specific port
3. Listen and then accept the incoming requests (if any), the current thread is now contemporarily blocked until the emerge of requests from the clients.
4. Create and start a new sub-thread to handle the most recent incoming request dedicately, this connection is then binded to and maintained by a new specialized socket.
5. Read the messages from clients and echo back to the corresponding origins by using write.
6. Close down the specilized socket after the client end up the connection by using function close to send out the EOF.

## Usage
*compile and installation*
1. Enter into the subdirectory "cmake_build_debug"
2. command: (in sequence)
* cmake ..
* make
* make install

*Running the server and cients*
* cd install/bin && ./tcp_server <server IP>  (for server)
* cd install/bin && ./tcp_server <server IP> 1035  (for client)
 
***N.B. since the permanent port of server for this service is preset to 1035***
