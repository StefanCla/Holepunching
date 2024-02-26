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
	m_ClientSocket = new SOCKET();
	m_AddrInfo = new addrinfo();

	*m_ClientSocket = INVALID_SOCKET;
	m_InitResult = WSAStartup(MAKEWORD(2, 2), m_WsaData);

	if (m_InitResult != 0)
		return false;

	m_AddrInfo->ai_family = AF_INET;
	m_AddrInfo->ai_socktype = SOCK_DGRAM;
	m_AddrInfo->ai_protocol = IPPROTO_UDP;
	
	m_InitResult = getaddrinfo(m_IP.c_str(), m_Port.c_str(), m_AddrInfo, &m_AddrResult);
	if (m_AddrResult != 0)
	{
		WSACleanup();
		return false;
	}

	return true;
}