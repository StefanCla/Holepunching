#pragma once
#include <winsock2.h>
#include <string>

class UDPHolepunch
{
public:
	UDPHolepunch();
	~UDPHolepunch();

	bool ConnectToServer();
	bool Receive();
	bool Send();

private:
	bool Initialize();
	bool ConnectToSocket();

private:
	WSADATA* m_WsaData;
	SOCKET* m_ClientSocket;
	addrinfo* m_AddrInfo;
	addrinfo* m_AddrResult;

	int m_InitResult;

	const std::string m_IP = "127.0.0.1";
	const std::string m_Port = "62000";
};