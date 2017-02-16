#include "Socket.h"



Socket::Socket()
{
	if (!InitializeSockets()) {
		std::cout << "FAILED TO INIT SOCKET";
	}
}


Socket::~Socket()
{
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
		close(socket);
#elif PLATFORM == PLATFORM_WINDOWS
	closesocket(handle);
#endif
	ShutdownSockets();
}
bool Socket::InitializeSockets()
{
#if PLATFORM == PLATFORM_WINDOWS
	WSADATA WsaData;
	return WSAStartup(MAKEWORD(2, 2),
		&WsaData)
		== NO_ERROR;
#else
	return true;
#endif
}

void Socket::ShutdownSockets()
{
#if PLATFORM == PLATFORM_WINDOWS
	WSACleanup();
#endif
}

bool Socket::IsOpen() const
{
	return this->handle > 0;
}

bool Socket::Open(unsigned short port)
{
	this->handle = socket(AF_INET,
		SOCK_DGRAM,
		IPPROTO_UDP);

	if (this->handle <= 0)
	{
		printf("failed to create socket\n");
		return false;
	}

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons((unsigned short)port);

	if (bind(this->handle,
		(const sockaddr*)&address,
		sizeof(sockaddr_in)) < 0)
	{
		printf("failed to bind socket\n");
		return false;
	}
	printf("Listening on port %d\n", port);


#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

	int nonBlocking = 1;
	if (fcntl(this->handle,
		F_SETFL,
		O_NONBLOCK,
		nonBlocking) == -1)
	{
		printf("failed to set non-blocking\n");
		return false;
	}

#elif PLATFORM == PLATFORM_WINDOWS

	DWORD nonBlocking = 1;
	if (ioctlsocket(handle,
		FIONBIO,
		&nonBlocking) != 0)
	{
		printf("failed to set non-blocking\n");
		return false;
	}

#endif

	return true;
}


bool Socket::Send(const Address & destination,const void * data,int size){


	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(destination.GetAddress());
	addr.sin_port = htons(destination.GetPort());


	int sent_bytes = sendto(handle, (const char*)data, size,0, (sockaddr*)&addr,	sizeof(sockaddr_in));

	if (sent_bytes != size)
	{
		int e = WSAGetLastError();
		fprintf(stderr, "Error %d\n", e);
		printf("failed to send packet\n");
		return false;
	}

	return true;
}

int Socket::Receive(Address & sender,
	void * packet_data,
	int max_packet_size)
{
#if PLATFORM == PLATFORM_WINDOWS
	typedef int socklen_t;
#endif

	sockaddr_in from;
	socklen_t fromLength = sizeof(from);

	int bytes = recvfrom(this->handle,
		(char*)packet_data,
		max_packet_size,
		0,
		(sockaddr*)&from,
		&fromLength);

	unsigned int from_address =
		ntohl(from.sin_addr.s_addr);

	unsigned int from_port =
		ntohs(from.sin_port);

	sender = Address(from_address, from_port);

	return bytes;
}
Address::Address()
{
	init(0, 0);
}

Address::Address(unsigned char a,
	unsigned char b,
	unsigned char c,
	unsigned char d,
	unsigned short port)
{
	unsigned int address = (a << 24) |
		(b << 16) |
		(c << 8) |
		d;
	init(address, port);
}

Address::Address(unsigned int address,
	unsigned short port)
{
	init(address, port);
}

void Address::init(unsigned int address, unsigned short port)
{
	this->address = address;
	this->port = port;
}

unsigned int Address::GetAddress() const
{
	return this->address;
}

unsigned short Address::GetPort() const
{
	return this->port;
}