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

//获取文件大小
unsigned long bweb_get_file_size(char *filename)
{
    unsigned long filesize=-1;
	
    FILE *fp=NULL;

    fp=fopen(filename,"rb");
    if(fp==NULL)
	{
    	return filesize;
    }
	
    fseek(fp,0L,SEEK_END);
	
    filesize=ftell(fp);
	
    fclose(fp);

    return filesize;

}

//把文件的内容读到Buf里面
int bweb_read_file_tobuf(char *filename,unsigned long file_size,char *buf)
{
    FILE *fp;
	
    int len=0,size=0;
	
    if((fp=fopen(filename,"rb"))==NULL)
	{
        printf("open error,%s\n",strerror(errno));
		
		return -1;
    }
	
    if(file_size>size_1G)
	{
        printf("file too large\n");
		
		return -1;
        
    }else
	{
            size=fread(buf+len,1,file_size-len,fp);
            if(size!=file_size)
            {
                printf("fread error\n");		
		return -1;
            }      
    }
    if(fclose(fp))
	{
        printf("fclose error\n");		
	return -1;
    }
	
	return 1;

}

//读取系统目录中的文件
int bweb_parse_file()
{
    DIR *dir;
	
    int ret;
	
    struct dirent *ptr;
	
    char name[1024];
	
    unsigned long filesize;

    char *buf;
	
    char curdir[1024];
	
	char filepath[1024];
	
	 if(NULL == getcwd(curdir,sizeof(curdir)))
	{
        strcpy(curdir, "/");
    }
	 
	 sprintf(filepath,"%s/jsonfile",curdir);
	 
	 printf("in the dir %s\n",filepath);
	 
    if((dir=opendir(filepath))==NULL)
	{
        printf("read_dirfile_tobuf error\n");
        return -1;
    }	
	 
    while((ptr=readdir(dir)) != NULL)
		{
        if(ptr->d_type == 8){
			
        	sprintf(name, "%s/%s", filepath, ptr->d_name);
			
            filesize=bweb_get_file_size(name);
		
            buf = (char *)malloc(filesize+1);
			if(buf == NULL)
			{
				printf("malloc error\n");
				return -1;
			}
			memset(buf, 0, filesize+1);
            printf("the ptr->name=%s\n", name);
             
            ret=bweb_read_file_tobuf(name, filesize, buf);
			if(ret<0)
			{
				printf("bweb_read_file_tobuf error\n");
				return -1;
			}
			
			//printf("the read buf=%s\n", buf);
			
            //bweb_HandReciveDataWeb(buf,filesize);
            /*解析函数
            */       
           free(buf);

        }
    }
	
	closedir(dir);
	
    return 1;
}

		
