#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void sys_exit(int status);

void _exit(int status) {
	sys_exit(status);
}

int access(const char *path, int amode) {
	struct stat s;
	if (stat(path, &s)) {
		return -1;
	}

	if (s.st_mode & S_IFDIR) {
		return 0;
	}
	
	if (amode & W_OK) {
		if (s.st_mode & S_IWRITE) {
			return 0;
		}

		return -1;
	}

	return 0;
}

int chown(const char *path, uid_t owner, gid_t group) {
	return 0;
}

pid_t sys_getpid(void);

pid_t getpid(void) {
	return sys_getpid();
}

uid_t getuid(void) {
	return 0;
}

int setuid(uid_t uid) {
	if (uid != 0) {
		errno = EINVAL;
		return -1;
	}

	return 0;
}

uid_t geteuid(void) {
	return 0;
}

int seteuid(uid_t euid) {
	if (euid != 0) {
		errno = EINVAL;
		return -1;
	}

	return 0;
}

gid_t getgid(void) {
	return 0;
}

int setgid(gid_t gid) {
	if (gid != 0) {
		errno = EINVAL;
		return -1;
	}

	return 0;
}

gid_t getegid(void) {
	return 0;
}

int setegid(gid_t egid) {
	if (egid != 0) {
		errno = EINVAL;
		return -1;
	}

	return 0;
}

pid_t getpgid(pid_t pid) {
	if (pid != getpid()) {
		errno = ESRCH;
		return -1;
	}

	return getgid();
}

int setpgid(pid_t pid, pid_t pgid) {
	if (pid != getpid()) {
		errno = ESRCH;
		return -1;
	}

	if (pgid != getgid()) {
		errno = EINVAL;
		return -1;
	}

	return 0;
}

char *getlogin(void) {
	return "root";
}

int issetugid(void) {
	return 0;
}

int getlogin_r(char *name, size_t namesize) {
	if (name == NULL) {
		return ERANGE;
	}

	char *login = getlogin();
	size_t len = strlen(login) + 1;

	if (len > namesize) {
		return ERANGE;
	}

	memcpy(name, login, len);

	return 0;
}

int sys_isatty(int fildes);

int _isatty(int fildes) {
	int ret = sys_isatty(fildes);

	if (ret < 0) {
		ret = 0;
	}

	return ret;
}

int fsync(int fildes) {
	// Stubbed
	return 0;
}

int sys_getpagesize(void);

int getpagesize(void) {
	return sys_getpagesize();
}

size_t sys_get_processor_count(void);

long sysconf(int name) {
	switch (name) {
		case _SC_ARG_MAX: return ARG_MAX;
		case _SC_CLK_TCK: return CLK_TCK;
		case _SC_NPROCESSORS_CONF: return sys_get_processor_count();
		case _SC_NPROCESSORS_ONLN: return sys_get_processor_count();
		case _SC_PAGESIZE: return sys_getpagesize();
		case _SC_PRIORITY_SCHEDULING: return 1;
		case _SC_THREAD_DESTRUCTOR_ITERATIONS: return PTHREAD_DESTRUCTOR_ITERATIONS;
		case _SC_THREAD_KEYS_MAX: return PTHREAD_KEYS_MAX;
		case _SC_THREAD_STACK_MIN: return PTHREAD_STACK_MIN;
		case _SC_THREAD_THREADS_MAX: return PTHREAD_THREADS_MAX;
		case _SC_THREADS: return 1;
		case _SC_TIMERS: return 1;
		case _SC_THREAD_ATTR_STACKADDR: return -1;
		case _SC_THREAD_ATTR_STACKSIZE: return 1;
		case _SC_THREAD_PRIORITY_SCHEDULING: return -1;
		case _SC_THREAD_PRIO_INHERIT: return -1;
		case _SC_THREAD_PRIO_PROTECT: return -1;
		case _SC_THREAD_PROCESS_SHARED: return -1;
		case _SC_THREAD_SAFE_FUNCTIONS: return 1;
		case _SC_VERSION: return _POSIX_VERSION;
		default:
			errno = EINVAL;
			return -1;
	}
}

ssize_t sys_read_entropy(void *buffer, size_t length, uint32_t flags);

int getentropy(void *buffer, size_t length) {
	ssize_t ret = sys_read_entropy(buffer, length, 0);

	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	if (ret != length) {
		errno = EINVAL;
		return -1;
	}

	return 0;
}

int sys_chdir(const char *path);

int chdir(const char *path) {
	int ret = sys_chdir(path);

	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return 0;
}