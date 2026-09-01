#include <stdio.h>
#include <string.h>
#include "file_reader.h"

// 获取用户文件路径
int get_user_file_path(char *path){
    // 提示用户输入文本文件路径
    printf("请输入文本路径:");
    if(fgets(path, PATH_MAX_LENGTH, stdin) == NULL){
        printf("路径获取失败 \n");
        return -1;
    }
    int path_len = strlen(path);
    if(path_len == PATH_MAX_LENGTH - 1 && path[path_len - 1] != '\n'){
        printf("文件路径输入过长 \n");
        return -1;
    }
    // 输入的路径末尾\n转成\0
    path[strcspn(path, "\n")] = '\0';
    return 0;
}

int get_file_word(FILE * pFile, char * word, int max_size){
    int index = 0;
    int ch = fgetc(pFile);
    while (ch != EOF)
    {
        if(is_alpha(ch)){
            if(index == max_size){
                printf("单词超过规定长度 \n");
                return -1;
            }
            word[index] = to_lower(ch);
            ++index;
        }else{
            word[index] = '\0';
            if(index > 0){
                return 0;
            }
        }
        ch = fgetc(pFile);
    }
    if(feof(pFile)){
        if(index > 0){
            word[index] = '\0';
            return 0;
        }
    }
    return 0;
}

int is_alpha(int c){
    if(c >= 'a' && c <= 'z'){
        return 1;
    }
    if(c >= 'A' && c <= 'Z'){
        return 1;
    }
    return 0;
}

int to_lower(char ch){
    if(ch >= 'A' && ch <= 'Z'){
        return 'a' + (ch - 'A');
    }else if(ch >= 'a' && ch <= 'z'){
        return ch;
    }
    return -1;
}