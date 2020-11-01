//the main progarm file
//it will looks for the make file, and pass the File obj to the parser

int main(){
    FILE *file;
    FILE *file_m = fopen("./makefile","r");
    FILE *file_M = fopen("./Makefile","r");
    //check if there is a makefile 
    if(NULL != file_m){
        file = file_m;
    }
    //check if there is a Makefile
    else if (NULL != file_M){
        file = file_M;
    }
    //no makefile exists, return error
    else{
        fprintf(stderr,"ERROR: no makefile exists\n");
        exit(1);
    }
    //pass the file obj to the parser
    parseFile(file);    
}
