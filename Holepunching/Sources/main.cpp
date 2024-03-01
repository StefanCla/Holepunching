#include <cstdio>
#include <iostream>
#include "UDP.hpp"

int main()
{
	UDPHolepunch* Holepunch = new UDPHolepunch();

	if (!Holepunch->ConnectToServer())
	{
		std::cout << "ERROR: Failed to connect to server" << std::endl;
	}
	else
	{
		std::cout << "Server connected successfully" << std::endl;
	}

	if (!Holepunch->Send())
	{
		std::cerr << "ERROR: Failed to send message" << std::endl;
	}
	else
	{
		std::cout << "Message sent successfully" << std::endl;
	}

	if (!Holepunch->Receive())
	{
		std::cerr << "ERROR: Failed to receive message" << std::endl;
	}
	else
	{
		std::cout << "Message received successfully" << std::endl;
	}

	delete Holepunch;
}