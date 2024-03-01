#include "UDP.hpp"
#include <iostream>
#include <WS2tcpip.h>

UDPHolepunch::UDPHolepunch()
	: m_WsaData(nullptr)
	, m_ClientSocket(nullptr)
	, m_AddrInfo(nullptr)
	, m_AddrResult(nullptr)
	, m_InitResult(0)
{
	if (!Initialize())
	{
		std::cerr << "Error: WSA initialized failed" << std::endl;
	}
	else
	{
		std::cout << "Client successfully initialized" << std::endl;
	}

	if (!ConnectToSocket())
	{
		std::cerr << "Error: Failed to connect to socket" << std::endl;
	}
	else
	{
		std::cout << "Socket successfully connected" << std::endl;
	}
}

UDPHolepunch::~UDPHolepunch()
{
	WSACleanup();

	delete m_AddrInfo;
	delete m_ClientSocket;
	delete m_WsaData;
}

bool UDPHolepunch::Initialize()
{
	m_WsaData = new WSADATA();
	m_AddrInfo = new addrinfo();

	m_InitResult = WSAStartup(MAKEWORD(2, 2), m_WsaData);

	if (m_InitResult != 0)
		return false;

	m_AddrInfo->ai_family = AF_INET;
	m_AddrInfo->ai_socktype = SOCK_DGRAM;
	m_AddrInfo->ai_protocol = IPPROTO_UDP;
	
	m_InitResult = getaddrinfo(m_IP.c_str(), m_Port.c_str(), m_AddrInfo, &m_AddrResult);
	if (m_InitResult != 0)
	{
		WSACleanup();
		return false;
	}

	return true;
}

bool UDPHolepunch::ConnectToSocket()
{
	m_ClientSocket = new SOCKET();
	*m_ClientSocket = INVALID_SOCKET;

	*m_ClientSocket = socket(m_AddrResult->ai_family, m_AddrResult->ai_socktype, m_AddrResult->ai_protocol);

	if (*m_ClientSocket == INVALID_SOCKET)
	{
		WSACleanup();
		return false;
	}

	return true;
}

bool UDPHolepunch::ConnectToServer()
{
	m_InitResult = connect(*m_ClientSocket, m_AddrResult->ai_addr, m_AddrResult->ai_addrlen);
	if (m_InitResult == SOCKET_ERROR)
	{
		closesocket(*m_ClientSocket);
		WSACleanup();
		return false;
	}

	return true;
}

bool UDPHolepunch::Send()
{
	const char* sendbuf = "This is a test";

	m_InitResult = send(*m_ClientSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (m_InitResult = SOCKET_ERROR)
	{
		closesocket(*m_ClientSocket);
		WSACleanup();
		return false;
	}

	return true;
}

bool UDPHolepunch::Receive()
{
	char recvbuf[512];
	m_InitResult = recv(*m_ClientSocket, recvbuf, 512, 0);

	if (m_InitResult > 0)
	{
		std::cout << "Bytes received: " << m_InitResult << std::endl;
		return true;
	}
	else if(m_InitResult == 0)
	{
		std::cout << "Connection closed" << std::endl;
		return true;
	}
	else
	{
		std::cout << "ERROR: No bytes received" << std::endl;
		return false;
	}
}