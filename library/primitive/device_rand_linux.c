#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include "device_rand.h"

int device_rand(void *buf, size_t len)
{
    struct stat st;
    size_t i, wanted;
    int fd, ret;

start:
    fd = open("/dev/urandom", O_RDONLY, 0);

    if (fd == -1) {
        if (errno == EINTR) {
            goto start;
        }

        return -1;
    }

    fcntl(fd, F_SETFD, fcntl(fd, F_GETFD) | FD_CLOEXEC);

    if (fstat(fd, &st) == -1 || !S_ISCHR(st.st_mode)) {
        close(fd);
        return -1;
    }

    for (i = 0; i < len; ) {
        wanted = len - i;

        ret = read(fd, (char *)buf + i, wanted);

        if (ret == -1) {
            if (errno == EAGAIN || errno == EINTR) {
                continue;
            }

            close(fd);
            return -1;
        }

        i += ret;
    }

    close(fd);
    return 0;
}
