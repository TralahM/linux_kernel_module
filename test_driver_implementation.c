/*
 * =====================================================================================
 *
 *       Filename:  test_driver_implementation.c
 *
 *    Description:  Test The Implementation of the pa2_char_driver.ko module
 *
 *        Version:  1.0
 *
 *        Created:  02/25/2022 07:37:23 PM
 *
 *       Revision:  none
 *
 *       Compiler:  gcc
 *
 *         Author:  Tralah M Brian (https://github.com/TralahM),
 * briantralah@gmail.com
 *
 *         Email:   briantralah@gmail.com
 *
 *   Organization:  Research and Development
 *
 *   Company:       TralahTek LLC
 *
 * =====================================================================================
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void usage() {
    printf(
        "Usage: test_driver_implementation <path to character "
        "device>\n\nExample: \t test_driver_implementation "
        "/dev/simple_character_device.\n\n\t<TralahM "
        "(briantralah@gmail.com)>.\n");
}

int main(int argc, char* argv[]) {
    char* user_buffer =
        "Hello World Testing the driver for simple_character_device.";
    char buffer[BUFFER_SIZE];
    int buffer_size;
    ssize_t ret_in, ret_out;
    buffer_size = strlen(user_buffer);
    int input_fd, output_fd;
    if (argc < 2) {
        usage();
        exit(0);
    };
    // Open file and set input file descriptor
    input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1) {
        perror("open");
        return 2;
    }
    // int test read file;
    while ((ret_in = read(input_fd, &buffer, BUFFER_SIZE)) > 0) {
        printf("Read %s  %ld bytes:%s\n", argv[1], ret_in, buffer);
    }
    printf("Closing input file descriptor\n");
    close(input_fd);

    output_fd = open(argv[1], O_WRONLY, 0777);
    if (output_fd == -1) {
        perror("open");
        return 3;
    }

    ret_out = write(output_fd, user_buffer, (ssize_t)buffer_size);
    if (ret_out != buffer_size) {
        printf("ret_out: %d buffer_size: %d\n", (int)ret_out, buffer_size);
        perror("write");
        return 4;
    }
    printf("Closing output file descriptor\n");
    close(output_fd);
    return 0;
}
