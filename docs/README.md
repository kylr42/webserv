# Socket

<details>
    <summary>What is socket?</summary>
    <p>Sockets allow communication between two different processes on the same or different machines. It's a way to talk to other computers using standard Unix file descriptors. Socket looks and behaves much like a low-level file descriptor. This is because commands such as read() and write() work with sockets in the same way they do with files and pipes.</p>
</details>

<details>
    <summary>Basic notion TCP/IP sockets.</summary>

- Create a socket.
  ``` c++
    int server_fd = socket(domain, type, protocol); 
  ```
  - domain or address family :
    - communication domain in which the socket should be created.
    - For TCP/IP sockets, we want to specify the IP address family "AF_INET".
  - type :
    - type of service.
    - For TCP/IP sockets, we want to specify the virtual circuit service "SOCK_STREAM".
  - protocol :
    - indicate a specific protocol to use in supporting the sockets operation.
    - Since there’s only one form of virtual circuit service, there are no variations of the protocol, so the last argument, protocol, is zero.
    
  ``` c++
    #include <sys/socket.h>
    ...
    ...
    if ((server_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    std::cerr << "error: socket creation" << std::endl;
    exit(1);
    }
  ```
- Identify a socket.
  - When we talk about naming a socket, we are talking about assigning a transport address to the socket (a port number in IP networking). In sockets, this operation is called binding an address and the bind system call is used for this.
    ```c++
    int server_fd = socket(domain, type, protocol);
    ``` 
  - socket :
    - The first parameter, socket, is the socket that was created with the socket system call.
  - sockaddr :
      - For the second parameter, the structure sockaddr is a generic container that just allows the OS to be able to read the first couple of bytes that identify the address family.
      - For IP networking, we use struct sockaddr_in, which is defined in the header <netinet/in.h>
        ``` c++
        struct sockaddr_in 
        {
            __uint8_t         sin_len;
            sa_family_t       sin_family;
            in_port_t         sin_port;
            struct in_addr    sin_addr;
            char              sin_zero[8];
        };
        ```
        - Before calling bind, we need to fill out this structure.
            - sin_family
              - The address family we used when we set up the socket.
              - In our case, it’s "AF_INET".
            - sin_port
              - The port number (the transport address). You can explicitly assign a transport address (port) or allow the operating system to assign one.
              - If you’re a client and won’t be receiving incoming connections, you’ll usually just let the operating system pick any available port number by specifying port 0.
              - If you’re a server, you’ll generally pick a specific number since clients will need to know a port number to connect to.
            - sin_addr
              - The address for this socket. This is just your machine’s IP address.
              - Most of the time, we don’t care to specify a specific interface and can let the operating system use whatever it wants.
              - The special address for this is 0.0.0.0, defined by the symbolic constant "INADDR_ANY".
  - address_len
    - the third parameter specifies the length of that structure.
    - This is simply sizeof(struct sockaddr_in).
    ```c++
    #include <sys/socket.h>
    …
    struct sockaddr_in address;
    const int PORT = 8080; //Where the clients can reach at
    /* htonl converts a long integer (e.g. address) to a network representation */
    /* htons converts a short integer (e.g. port) to a network representation */
    
    memset((char *)&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);
    
    if ((bind(listen_fd, (struct sockaddr *) &address, sizeof(address))) < 0) {
        std::cerr << "error: socket creation" << std::endl;
        exit(1);
    }
    ```
- Server wait incoming connection.
  - Before a client can connect to a server, the server should have a socket that is prepared to accept the connections. The listen system call tells a socket that it should be capable of accepting incoming connections.
    ```c++
    #include <sys/socket.h> 
    int listen(int socket, int backlog);
    ```
  - backlog 
    - The second parameter, backlog, defines the maximum number of pending connections that can be queued up before connections are refused.
  - The original socket that was set up for listening is used only for accepting connections, not for exchanging data.
  - The accept system call grabs the first connection request on the queue of pending connections (set up in listen) and creates a new socket for that connection.
  ```c++
  #include <sys/socket.h>
  int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
  ```
  - socket
    - The first parameter, socket, is the socket that was set for accepting connections with listen.
  - address
    - The second parameter, address, is the address structure that gets filed in with the address of the client that is doing the connect.
  - address_len 
    - The third parameter is filled in with the length of the address structure.
  ```c++
  if (listen(server_fd, 3) < 0) { 
    std::cerr << "error: listern call" << std::endl;
    exit(EXIT_FAILURE); 
  }
  if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)addrlen))<0){
    std::cerr << "error: accept call" << std::endl;            
    exit(EXIT_FAILURE);        
  }
  ```
  - By default, socket operations are synchronous, or blocking, and accept will block until a connection is present on the queue.
  - The answer to this is non-blocking I/O. We set a flag on a socket which marks that socket as non-blocking.
  - this means that, when performing calls on that socket (such as read and write), if the call cannot complete, then instead it will fail with an error like EWOULDBLOCK or EAGAIN.
  - To mark a socket as non-blocking, we use the fcntl system call.
  ```c++
  //WARNING!!! DO NOT USE THIS IN WEBSERV 42 PROJECT
  #include <fcntl.h>
  int flags;
  if ((flags = fcntl(server_fd, F_GETFL)) < 0){
    std::cerr << "could not get file flags" << std::endl;
    exit(1);
  }
  ```
    - F_GETFL
      - Return (as the function result) the file access mode and the file status flags; arg is ignored.
  ```c++
  if (fcntl(server_fd, F_SETFL, flags | O_NONBLOCK) < 0){
    std::cerr << "could not set file flags" << std::endl;
    exit(1);
  }
  ```
  - F_SETFL
    - F_SETFL overwrites the flags with exactly what you pass in the third parameter, "flags" the old parameter, "|" then the new flag in, here O_NONBLOCK.
</details>

