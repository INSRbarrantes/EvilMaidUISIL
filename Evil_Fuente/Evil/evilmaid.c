#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define TARGET_FILE "/etc/systemd/system/em-shell.service"

int main() {
    // Crear un servicio systemd para EM Shell
    int fd = open(TARGET_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    const char* service_content =
        "[Unit]\n"
        "Description=EM Shell\n"
        "After=network.target\n\n"
        "[Service]\n"
        "ExecStart=/usr/bin/em-shell\n"
        "Restart=always\n\n"
        "[Install]\n"
        "WantedBy=multi-user.target\n";

    write(fd, service_content, strlen(service_content));
    close(fd);

    // Copiar el binario EM Shell al sistema
    system("cp /boot/em-shell /usr/bin/em-shell");
    system("chmod +x /usr/bin/em-shell");

    // Habilitar el servicio
    system("systemctl enable em-shell.service");

    return 0;
}