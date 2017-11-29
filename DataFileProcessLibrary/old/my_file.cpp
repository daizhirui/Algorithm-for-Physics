#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE* createFile(char * filename, char * formate, char * mode, int index){
    char * file = strcat
    FILE * fp = fopen();
}

/** Target:
 * createFile
 * deleteFile
 * readFile
 * writeFile
 * renameFile
 * copyFile
 * moveFile
 * createDirectory
 * deleteDirectory
 * renameDirectory
 * copyDirectory
 * moveDirectory
 * cross Platform
 * create data table header
 * add table column
 * delete table column
 * insert table column
 * /

/** File Struct:
 * Filename:char[]
 * Formate:char[]
 * Path:char[]
 * IOMode:char[]
 * InitialNote:char[]
 * Number of Columns:int
 * Header:char[][]
 * 
 * /

 /**
  * 获取当前工作目录是使用函数：getcwd。cwd指的是“current working directory”，这样就好记忆了。

函数说明：
    函数原型：char* getcwd(char* buffer, int len);
    参数：buffer是指将当前工作目录的绝对路径copy到buffer所指的内存空间， len是buffer的长度。
    返回值：获取成功则返回当前工作目录（绝对路径），失败则返回false（即NULL）。 
    该函数所属头文件为<direct.h>

具体使用如下例：（特别注意的是，当你使用的是Linux系统时，请注意你是否具有相关的权限，如果权限不够会导致获取失败）
  * /

/**
 * #include <stdio.h>
#include <stdlib.h>
void main()
{
system("DIR /D C:\\ /s /B > a.log");
}
C:\下的所有文件夹，子文件夹里所有文件，转向到 文本文件 a.log 里。
格式:
C:\aaa\bbb\ccc\...
只要文件夹命令：
dir /d c: /B /ad
只要文件夹命令，含子文件夹：
dir /d c: /B /ad /s
*/
