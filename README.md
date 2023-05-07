Program to Retrieve Webpage using SSL/TLS.

This is a C program that retrieves a webpage from a specified URL using SSL/TLS protocol. 

The program prompts the user to enter the URL of the webpage to be retrieved and extracts the hostname and path from it. It then creates a TCP/IP socket, resolves the hostname to an IP address, connects to the server using the socket, and wraps the socket with SSL/TLS. 

Finally, it sends an HTTP GET request to the server and receives the response.

Dependencies
This program requires the following dependencies:

OpenSSL library (libssl-dev package on Ubuntu) 
libxml2 library (libxml2-dev package on Ubuntu)

Running the Program
To compile the program, run the following command in the terminal: 
gcc -o program program.c -lssl -lcrypto -lxml2

To run the program, execute the following command: 
./program

The program will prompt you to enter the URL of the webpage to be retrieved. 

Enter the URL and press Enter eg code.org/helloworld. The program will retrieve the webpage using SSL/TLS and display the response on the terminal.

Note: This program only works with HTTPS URLs (i.e., URLs that start with "https://").


