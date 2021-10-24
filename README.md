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
The core part of this lab project is that the TCP server is equipped with the multithread techniques in respond to the high concurrence of request from client side. This is mainly implemented by using an open-source packet released in Github called "tinycthread". It is indeed that pthread library can be put into use, however tinycthread module integreted furtherly pthread which means the enhancement of the cross-platform compatibility (could be used on both WIN32 and MAC) and offer the API even just the same as pthread simultaneously.

Considering the experimental purpose as well as the computing costs limitation of this lab, the acceptance is simply range from 0 to maximum 16. The max_queue argument is designed to handle this overflow -- if the connected client is euqal to the maximum queueing length, the next ingress request will be refused.

#### *Main functions*


## Architecture
Focusing on the server, there is a standard process for it to initiate and handle the TCP connection.
1. Create a socket
2. Bind the socket to the specific port
3. Listen and then accept the incoming requests (if any), the current thread is now contemporarily blocked until the emerge of requests from the clients.
4. Create and start a new sub-thread to handle the most recent incoming request dedicately, this connection is then binded to and maintained by a new specialized socket.
5. Read the messages from clients and echo back to the corresponding origins by using write.
6. Close down the specilized socket after the client end up the connection by using function close to send out the EOF.

It is somewhat simpler than the case for server. Create skt --> request by function connect (initiate the handshake process) --> write and read --> close for goodbye.
One client process corresponds to one connection, which precipitate to the simplicity of the client-side situation, since no mutithread techniques needed to be used and no several connections needed to be operated and maintance at the same time.
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
