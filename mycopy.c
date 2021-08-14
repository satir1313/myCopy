#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <error.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char **argv){

	int fd1, fd2;
	ssize_t nread;
	ssize_t nwrite;
	char buf[100];

	if(argc < 3){
		printf("Spesify fileName to copy\n");
		exit(0);
	}

	if(argc == 3){
	
		if((fd1 = open(argv[1], O_RDONLY, 0664)) < 0){
			printf("File does not exist3\n");
			exit(0);
		}
		fd2 = open (argv[2], O_WRONLY | O_CREAT, 0664);
		
		while((nread = read(fd1, buf, 100)) > 0){
			if((nwrite = write(fd2, buf, nread)) < 0){
				perror("writing failed");
				exit(1);
			}
		}
		
		close(fd1);
		close(fd2);
	}
	
	if(argc == 4){
		if(strcmp(argv[1], "-d") != 0){
			printf("-d to delete the original file");
			exit(0);
		}
		
		if((fd1 = open(argv[2], O_RDONLY, 0664)) < 0){
			printf("File does not exist4\n");
			exit(0);
		}
		fd2 = open (argv[3], O_WRONLY | O_CREAT, 0664);
		
		while((nread = read(fd1, buf, 100)) > 0){
			if((nwrite = write(fd2, buf, nread)) < 0){
				perror("writing failed");
				exit(1);
			}
		}
		
		close(fd1);
		close(fd2);
		unlink(argv[2]);
	}
	
return 0;
}
