#include <stdio.h>      // Standard I/O functions
#include <stdlib.h>     // Standard library functions
#include <fcntl.h>      // File control options (open flags)
#include <unistd.h>     // POSIX API (read, write, close, sleep)
#include <string.h>     // String handling

#define DEVICE_PATH "/dev/led_device"  // Path to the LED device file

// Prints the user menu for LED control
void print_menu() {
    printf("\n=== LED Control Menu ===\n");
    printf("1. Turn ON LED\n");
    printf("2. Turn OFF LED\n");
    printf("3. Read LED state\n");
    printf("4. Exit\n");
    printf("Select an option: ");
}

// Clears the terminal screen using ANSI escape codes
void clear_screen() {
    printf("\033[2J\033[H"); 
}

int main() {
    int fd;                 // File descriptor for the device
    char option;            // Stores user's menu selection
    char buffer[2];         // Buffer to read LED state

    // Open the LED device file with read/write permissions
    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device"); 
        return 1;
    }

    while (1) {
        print_menu();          // Show menu to user
        option = getchar();    // Read user input
        getchar();             // Consume the newline character after input

        sleep(0.5);            // Delay for readability
        clear_screen();        // Clear terminal output

        switch (option) {
            case '1':
                // Write '1' to turn LED ON
                if (write(fd, "1", 1) < 0)
                    perror("Write failed");
                else
                    printf("LED turned ON\n");
                break;

            case '2':
                // Write '0' to turn LED OFF
                if (write(fd, "0", 1) < 0)
                    perror("Write failed");
                else
                    printf("LED turned OFF\n");
                break;

            case '3':
                // Move file pointer to beginning before reading
                lseek(fd, 0, SEEK_SET);
                // Read 1 byte representing LED state
                if (read(fd, buffer, 1) < 0)
                    perror("Read failed");
                else
                    printf("LED state: %s\n", buffer[0] == '1' ? "ON" : "OFF");
                break;

            case '4':
                // Exit the program
                close(fd);
                printf("Exiting.\n");
                return 0;

            default:
                // Handle invalid menu selections
                printf("Invalid option.\n");
        }
    }

    return 0;
}

