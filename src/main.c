#include <stdio.h>
#include <string.h>

#define PATH_MAX_LENGTH 10

int is_alpha(int c){
    if(c >= 'a' && c <= 'z'){
        return 1;
    }
    if(c >= 'A' && c <= 'Z'){
        return 1;
    }
    return 0;
}

int main(){
    // 提示用户输入文本文件路径
    printf("请输入文本路径:");
    char filePath[PATH_MAX_LENGTH];
    fgets(filePath, PATH_MAX_LENGTH, stdin);
    int path_len = strlen(filePath);
    if(path_len == PATH_MAX_LENGTH - 1 && filePath[path_len - 1] != '\n'){
        printf("输入路径过长");
        return -1;
    }
    filePath[strcspn(filePath, "\n")] = '\0';
    FILE * pFile = fopen(filePath, "r");
    if (pFile!=NULL)
    {
        printf("fopen success, begin read file \n");
        
        int result = fgetc(pFile);
        while (result != EOF)
        {
            if(is_alpha(result)){
                printf("字符: %c \n", result);
            }else{
                printf("分隔符: %c \n", result);
            }
            result = fgetc(pFile);
        }
        if(feof(pFile)){
            printf("\n");
            printf("文件读取完成 \n");
        }
        if(ferror(pFile)){
            printf("读取文件失败 \n");
            fclose(pFile);
            return -1;
        }
        fclose (pFile);
        printf("读取文件操作完成 \n");
    }else{
        printf("fopen fail");
    }

    return 0;
}