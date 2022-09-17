# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/unistd.h>
# include <sys/stat.h>
# include <fcntl.h>

void checkIfFileExists(const char *fileName);

int main (void) {
    char *fileName = "/home/vscode/src/Cursus/mini-free/testing/file";

    checkIfFileExists(fileName);
    return 0;

}

void checkIfFileExists(const char *fileName){

    if(!access(fileName, F_OK )){
        printf("The File %s was Found\n",fileName);
    }else{
        printf("The File %s not Found\n",fileName);
    }
    
    if(!access(fileName, R_OK )){
        printf("The File %s can be read\n",fileName);
    }else{
        printf("The File %s cannot be read\n",fileName);
    }
    
    if(!access( fileName, W_OK )){
        printf("The File %s  can be Edited\n",fileName);
    }else{
        printf("The File %s  cannot be Edited\n",fileName);
    }
    
    if(!access( fileName, X_OK )){
        printf("The File %s is an Executable\n",fileName);
    }else{
        printf("The File %s is not an Executable\n",fileName);
    }

}