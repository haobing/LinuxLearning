#include<unistd.h>  
#include<stdio.h>  
#include<dirent.h>  
#include<string.h>  
#include<sys/stat.h>  
#include<stdlib.h>

void printfdir(char *dir,int depth)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	char pwd[256];
	char buf[256];
	if((dp=opendir(dir))==NULL){
		sprintf(buf,"cannot open directory:%s\n",dir);
		fprintf(stderr,"%s",buf);
		return;
	}
	chdir(dir);
	while((entry=readdir(dp))!=NULL){
		sprintf(pwd,"%s%s",dir,entry->d_name);
		lstat(pwd,&statbuf);
		if(S_ISDIR(statbuf.st_mode)){
			if(strcmp(".",entry->d_name)==0||strcmp("..",entry->d_name))
				continue;
			printf("%*s%s\n",depth," ",entry->d_name);
			printfdir(pwd,depth+4);
		}
		else
			printf("%*s%s\n",depth," ",entry->d_name);
		}
		closedir(dp);
	}
	int main()
	{
		printf("Directory scan of /home:\n");
		printfdir("/home",0);
		printf("done\n");
		exit(0);
	}
	
			
		
