#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s /dev/input/eventX\n", argv[0]);
        return 1;
    }

    // The device path inputted from the user when calling the program.
    const char *device_path = argv[1];
    printf("Input path: %s\n", device_path);

    // The file descriptor of the file at the user inputted path.
    int fd = open(device_path, O_RDONLY | O_NONBLOCK);
    if (fd < 0) { // indicates error executing file open
        perror("Error while opening file.");
        return 1;
    }

    struct libevdev *dev = libevdev_new(); // The evdev device
    if (libevdev_set_fd(dev, fd) < 0) { // attempt to hook up to input device
        perror("Error while connecting to device.");
        return 1;
    }

    printf("Input device %s\n", libevdev_get_name(dev));

    // grab the input device so no other processes can receive input from it
    // EVIOCGRAB is a constant meaning grab or release the device
    // 1 signifies grabbing the device, 0 signifies releasing it
    if (ioctl(fd, EVIOCGRAB, 1) != 0) {
        perror("Failed to grab the device.");
    }

    struct input_event ev;

    while (1) {
        int err = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);

        if (err == LIBEVDEV_READ_STATUS_SUCCESS) {
           if (ev.type == EV_KEY) { // get keypress
               fprintf(stderr, "code=%d value=%d\n", ev.code, ev.value);
               fflush(stderr);
           }
        } else if (err == -EAGAIN) {
           usleep(50);
        } else {
           perror("Error while reading from input device.");
           break;
        }
    }

    libevdev_free(dev);
    close(fd);
    return 0;
}
