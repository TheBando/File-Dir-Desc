#define _FILE_OFFSET_BITS   64

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

/* *********************************** */
/*
struct stat {

    dev_t st_dev; /* device inode resides on

    ino_t st_ino; /* this inode's number

    mode_t st_mode; /* protection


    nlink_t st_nlink; /* number or hard links to the file

    uid_t st_uid; /* user-id of owner

    gid_t st_gid; /* group-id of owner

    dev_t st_rdev; /* dev type, for inode that is dev

    off_t st_size; /* total size of file

    time_t st_atime; /* file last access time

    time_t st_mtime; /* file last modify time

    time_t st_ctime; /* file last status change time

    uint_t st_blksize; /* opt blocksize for file sys i/o ops

    int st_blocks; /* actual number of blocks allocated 
};
*/
void print_details(struct stat  );
