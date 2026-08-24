#include <stdio.h>
#include <string.h>

#define PATH_MAX_LENGTH 100

int main(){
    // 提示用户输入文本文件路径
    printf("请输入文本路径:");
    char filePath[PATH_MAX_LENGTH];
    fgets(filePath, PATH_MAX_LENGTH, stdin);
    filePath[strcspn(filePath, "\n")] = '\0';
    // scanf("%s", filePath);
    FILE * pFile = fopen(filePath, "r");
    if (pFile!=NULL)
    {
        printf("fopen success, begin read file \n");
        
        int result = fgetc(pFile);
        while (result != EOF)
        {
            printf("%c", result);
            result = fgetc(pFile);
        }
        if(feof(pFile)){
            printf("\n");
            printf("文件读取完成 \n");
        }
        if(ferror(pFile)){
            printf("读取文件失败 \n");
            return -1;
        }
        fclose (pFile);
        printf("读取文件操作完成 \n");
    }else{
        printf("fopen fail");
    }

    return 0;
}