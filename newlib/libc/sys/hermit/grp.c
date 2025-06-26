#include <grp.h>
#include <stdio.h>

struct group	*getgrgid (gid_t) {
    printf("warn: getgrgid called! \n");
    return NULL;
}

struct group	*getgrnam (const char *) {
    printf("warn: getgrnam called! \n");
    return NULL;
}