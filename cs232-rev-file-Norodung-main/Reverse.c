/*
Student Name: Noro Dung
Student ID: ned24
Date: February 9, 2024
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void check_num_args(int argc, char *argv[])
/*This checks to make sure the right number of arguments have been given
it expects to recieve 3 arguments */
{  
    while(argc != 3){
    	fprintf(stderr, "%s You need to provide 3 arguments!\n", argv[0]);
        exit(-1);
    }

}

void check_src_file_is_regular(char *myfile)
/*This will check that it is not a special file but files like txt and soft links*/
{
	struct stat file_stat;
	if (stat(myfile, &file_stat)== -1){
		perror("Error: ");
		exit(-1);
	}

	
	if(S_ISREG(file_stat.st_mode) == 0){
		perror("It is not a regular file");
		exit(-1);
	}

 }

void copy_src_to_dest(char *src_myfile, char *dest_myfile)
/*This opens the source file, read from it. Then writes into the destination file*/
{
	FILE *src_filename, *dest_filename;
	src_filename = fopen(src_myfile, "rb");
	if(src_filename == NULL){
		perror("Error: You file cannot open!");
		fclose(src_filename);
		exit(-1);
	}

	dest_filename = fopen(dest_myfile, "wb");
	if (dest_filename == NULL){
		perror("Error: Dest file cannot open ");
		fclose(src_filename);
		exit(-1);
	}
/*start looking into the file and start from the index -1*/
	fseek(src_filename, -1, SEEK_END);
	long file_size = ftell(src_filename);
	long i = file_size - 1;
	while (i >= -1){
		fseek(src_filename, i+1, SEEK_SET);
		char ch = fgetc(src_filename);
		i-=1;
		fputc(ch, dest_filename);
	}
	fclose(src_filename);
	fclose(dest_filename);

}


int main(int argc, char *argv[])
{
	/* These functions each call exit(-1) if there is a problem. */
	check_num_args(argc, argv);
	check_src_file_is_regular(argv[1]);
	copy_src_to_dest(argv[1], argv[2]);
	return 0;   /* no error */
}
