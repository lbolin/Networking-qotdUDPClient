//Lauren Bolin

#include <winsock2.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
#pragma comment(lib,"ws2_32.lib")

const int MAXBUF = 128;
int UDP_recv(SOCKET, char*, int, char*, char*);
int UDP_send(SOCKET, char*, int, const char*, const char*);
SOCKET passivesock(const char*, const char*);

int main()
{
	char textLine[MAXBUF] = "";

	WORD VersionRequired = 0x0202;
	WSADATA wsaData;
	int err = WSAStartup(VersionRequired, &wsaData);
	if (err)
	{
		cout << "Unable to initialize Windows Socket library." << endl;
		return 0;
	}

	SOCKET socket = passivesock("qotd", "udp");

	if (socket != INVALID_SOCKET)
	{
		while (true)
		{
			char receiveBuffer[MAXBUF] = "";
			char remoteIP[MAXBUF] = "";
			char remotePort[MAXBUF] = "";
			int numberBytesRecvd = UDP_recv(socket, receiveBuffer, MAXBUF-1, remoteIP, remotePort);

			if (numberBytesRecvd > 0)
			{
				receiveBuffer[numberBytesRecvd] = '\0';
				if (_stricmp("sendQOTD",receiveBuffer)== 0)
				{
					std::ifstream fs;
					fs.open("utd.txt");

						if (fs.is_open())
						{
							fs.clear();
								fs.getline(textLine, MAXBUF - 1);
								while (!fs.eof())
								{
									strcat_s(textLine, "\n");
									int lengthOfTextLine = strlen(textLine);
									int len = UDP_send(socket, textLine, lengthOfTextLine + 1, remoteIP, remotePort);
									fs.getline(textLine, MAXBUF - 1);
								}
							fs.close();
						}
				}
			}
		}
	}
	WSACleanup();
	return 0;
}