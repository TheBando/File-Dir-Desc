#include "main.h"


int i,j;
DIR * d_ptr;
char dirspc[1024];
struct dirent * entptr;

struct stat stat_buf;


void print_details(struct stat stat_bufer){
    struct passwd *o;
    struct group *g;

    if(S_ISDIR(stat_bufer.st_mode))printf("FILE TYPE:\t\t\tdirectory\n");
    if(S_ISREG(stat_bufer.st_mode))printf("FILE TYPE:\t\t\tordinary\n");
    if(S_ISCHR(stat_bufer.st_mode))printf("FILE TYPE:\t\t\tchar dev\n");
    if(S_ISBLK(stat_bufer.st_mode))printf("FILE TYPE:\t\t\tblock dev\n");
    if(S_ISFIFO(stat_bufer.st_mode))printf("FILE TYPE:\t\t\tpipe\n");
    if(S_ISSOCK(stat_bufer.st_mode))printf("FILE TYPE:\t\t\tUD socket\n");
    if(S_ISLNK(stat_bufer.st_mode))printf("FILE TYPE:\t\t\tsymbolic link\n");


    char prot_buf[10];

    for ( j = 0; j < 9; j++) prot_buf[j] = '-';

    if ( stat_bufer.st_mode & S_IRUSR) prot_buf[0] = 'r';
    if ( stat_bufer.st_mode & S_IWUSR) prot_buf[1] = 'w';
    if ( stat_bufer.st_mode & S_IXUSR) prot_buf[2] = 'x';
    if ( stat_bufer.st_mode & S_IRGRP) prot_buf[3] = 'r';
    if ( stat_bufer.st_mode & S_IWGRP) prot_buf[4] = 'w';
    if ( stat_bufer.st_mode & S_IXGRP) prot_buf[5] = 'x';
    if ( stat_bufer.st_mode & S_IROTH) prot_buf[6] = 'r';
    if ( stat_bufer.st_mode & S_IWOTH) prot_buf[7] = 'w';
    if ( stat_bufer.st_mode & S_IXOTH) prot_buf[8] = 'x';
    printf("PERMISSIONS:\t\t\t%s\n", prot_buf);


    if ( (o = getpwuid(stat_bufer.st_uid)) == NULL){
        printf("OWNER_NAME:\t\t\t%d\n", stat_bufer.st_uid);
    } else {
        printf("OWNER_NAME:\t\t\t%s\n", o->pw_name );
    }

    if ( (g = getgrgid(stat_bufer.st_gid)) == NULL){
        printf("GROUP_NAME\t\t\t%d\n", stat_bufer.st_gid);
    } else {
        printf("GROUP_NAME\t\t\t%s\n", g->gr_name);
    }

    printf("DATE_OF_LAST_MODIFICATION:\t%s", ctime(&(stat_bufer.st_mtime)));

    printf("LINK_COUNT:\t\t\t%lu", stat_bufer.st_nlink);

    if ( (S_ISCHR(stat_bufer.st_mode)) || (S_ISBLK(stat_bufer.st_mode)) ){
        printf("MAJOR - MINOR CODES:\t\t%d, %d\n", major(stat_bufer.st_rdev), minor(stat_bufer.st_rdev));
    } else {
        printf("SIZE_IN_BYTES\t\t\t%d\n", stat_bufer.st_size);
    }


    printf("INODE_NUMBER:\t\t\t%lu\n\n", stat_bufer.st_ino);


}






int main(int argc, char* argv[]){
    if (argc > 1){ /* get file name from command line */
        for( i = 1; i < argc; i++){
            if (lstat(argv[i], &stat_buf) == -1){
                perror("bad file name for stat:");
                /*printf(" %s",argv[i]);*/
                exit(1);
            }


        printf("FILENAME:\t\t\t%s\n", argv[i]);
        print_details(stat_buf);
    }

    } else { /* from working directory */
        if((d_ptr = opendir(".")) == NULL){
            perror("failed to open current directory");
            exit(1);
        }
        while((entptr = readdir(d_ptr)) != NULL){
            if (lstat(entptr->d_name, &stat_buf) == -1){
                perror("bad file name for stat");
                exit(1);
            }
            printf("FILENAME:\t\t\t%s\n", entptr->d_name);
            print_details(stat_buf);
        }
    }
    return 0;
}
