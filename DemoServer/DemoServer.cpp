#include <iostream>
#include <winsock2.h>

using namespace std;

int main()
{
	WSADATA wsa_data;
	SOCKET client;
	SOCKADDR_IN server_addr, client_addr;

	WSAStartup(MAKEWORD(2, 0), &wsa_data);
	const auto server = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5555);

	bind(server, reinterpret_cast<SOCKADDR *>(&server_addr), sizeof(server_addr));
	listen(server, 0);

	cout << "Listening for incoming connections..." << endl;

	char buffer[1024];
	int client_addr_size = sizeof(client_addr);

	if ((client = accept(server, reinterpret_cast<SOCKADDR *>(&client_addr), &client_addr_size)) != INVALID_SOCKET)
	{
		cout << "Client connected!" << endl;
		recv(client, buffer, sizeof(buffer), 0);
		
		cout << "Client says: " << buffer << endl;
		memset(buffer, 0, sizeof(buffer));

		closesocket(client);
		cout << "Client disconnected." << endl;
	}
}