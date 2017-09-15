#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;

int main()
{
	WSADATA wsa_data;
	SOCKADDR_IN addr;

	WSAStartup(MAKEWORD(2, 0), &wsa_data);
	const auto server = socket(AF_INET, SOCK_STREAM, 0);

	InetPton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(5555);

	connect(server, reinterpret_cast<SOCKADDR *>(&addr), sizeof(addr));
	cout << "Connected to server!" << endl;

	const string buffer = "hello.";

	send(server, buffer.c_str(), sizeof(buffer), 0);
	cout << "Message sent!" << endl;

	closesocket(server);
	WSACleanup();
	cout << "Socket closed." << endl << endl;
}