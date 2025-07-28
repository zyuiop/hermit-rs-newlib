#ifndef _SYS_FCNTL_H
#define _SYS_FCNTL_H

#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

#define F_DUPFD  0
#define F_GETFD  1
#define F_SETFD  2
#define F_GETFL  3
#define F_SETFL  4
#define F_GETLK  5
#define F_SETLK  6
#define F_SETLKW 7

#define FD_CLOEXEC 1

int fcntl(int fildes, int cmd, ...);

#define O_RDONLY    00000000
#define O_WRONLY    00000001
#define O_RDWR      00000002
#define O_CREAT     00000100
#define O_EXCL      00000200
#define O_TRUNC     00001000
#define O_APPEND    00002000
#define O_NONBLOCK  00004000
#define O_DIRECT    00040000
#define O_DIRECTORY 00200000
#define O_CLOEXEC   02000000

#define O_ACCMODE (O_RDONLY|O_WRONLY|O_RDWR)

int open(const char *path, int oflag, ...);

/* Operations for the `flock' call.  */
#define LOCK_SH 1	/* Shared lock.  */
#define LOCK_EX 2 	/* Exclusive lock.  */
#define LOCK_UN 8	/* Unlock.  */

/* Can be OR'd in to one of the above.  */
#define LOCK_NB 4	/* Don't block when locking.  */


/* Apply or remove an advisory lock, according to OPERATION,
   on the file FD refers to.  */
static inline int flock (int __fd, int __operation) {
   return 0;
}



__END_DECLS

#endif /* _SYS_FCNTL_H */
