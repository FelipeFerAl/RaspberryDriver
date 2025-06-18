#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_PATH "/dev/led_device"

void print_menu() {
    printf("\n=== LED Control Menu ===\n");
    printf("1. Turn ON LED\n");
    printf("2. Turn OFF LED\n");
    printf("3. Read LED state\n");
    printf("4. Exit\n");
    printf("Select an option: ");
}

void clear_screen() {
    printf("\033[2J\033[H"); // ANSI escape codes to clear terminal
}

int main() {
    int fd;
    char option;
    char buffer[2];

    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device");
        return 1;
    }

    while (1) {
        print_menu();
        option = getchar();
        getchar(); // consume newline

        sleep(0.5);
        clear_screen();

        switch (option) {
            case '1':
                if (write(fd, "1", 1) < 0)
                    perror("Write failed");
                else
                    printf("LED turned ON\n");
                break;
            case '2':
                if (write(fd, "0", 1) < 0)
                    perror("Write failed");
                else
                    printf("LED turned OFF\n");
                break;
            case '3':
                lseek(fd, 0, SEEK_SET);  // Reset file offset
                if (read(fd, buffer, 1) < 0)
                    perror("Read failed");
                else
                    printf("LED state: %s\n", buffer[0] == '1' ? "ON" : "OFF");
                break;
            case '4':
                close(fd);
                printf("Exiting.\n");
                return 0;
            default:
                printf("Invalid option.\n");
        }
    }

    return 0;
}
