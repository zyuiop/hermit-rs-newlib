#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/stat.h>

int sys_fcntl(int fildes, int cmd, int arg);

int fcntl(int fildes, int cmd, ...) {
    int arg = 0;

    // missing:
    // F_SETOWN => int,
    // F_GETLK | F_SETLK => struct flock *,
    int has_int = cmd == F_DUPFD || cmd == F_SETFD || cmd == F_SETFL;
    if (has_int) {
        va_list args;
        va_start(args, cmd);
        arg = va_arg(args, int);
        va_end(args);
    }

    int ret = sys_fcntl(fildes, cmd, arg);

    if (ret < 0) {
        ret = -1;
    }

    return ret;
}

int sys_open(const char *path, int oflag, mode_t mode);

int open(const char *path, int oflag, ...) {
    mode_t mode = 0;

    int has_mode = (oflag & O_CREAT) == O_CREAT;
    if (has_mode) {
        va_list args;
        va_start(args, oflag);
        mode = va_arg(args, mode_t);
        va_end(args);
    }

    int ret = sys_open(path, oflag, mode);

    if (ret < 0) {
        ret = -1;
    }

    return ret;
}

int fsync(int __fd) {
    // STUB
    return 0;
}

char* sys_getcwd(char *buf, size_t size);

char* getcwd(char *buf, size_t size) {
    return sys_getcwd(buf, size);
}
