#include <stdio.h>
#include <string.h>
#include "word_stats.h"

#define PATH_MAX_LENGTH 100 // 最大文件路径长度 100

int to_lower(char ch);
int is_alpha(int c);


int main(){
    // 提示用户输入文本文件路径
    printf("请输入文本路径:");
    char filePath[PATH_MAX_LENGTH];
    if(fgets(filePath, PATH_MAX_LENGTH, stdin) == NULL){
        printf("读取文件失败");
        return -1;
    } 
    size_t path_len = strlen(filePath);
    if(path_len == PATH_MAX_LENGTH - 1 && filePath[path_len - 1] != '\n'){
        printf("输入路径过长");
        return -1;
    }
    filePath[strcspn(filePath, "\n")] = '\0';
    FILE * pFile = fopen(filePath, "r");
    if (pFile!=NULL)
    {
        
        printf("fopen success, begin read file \n");
        char word[MAX_WORD_LEN + 1]; // +1 是用于最后保留'\0', 做结尾符.
        int index = 0;
        int ch = fgetc(pFile);
        while (ch != EOF)
        {
            if(is_alpha(ch)){
                if(index == MAX_WORD_LEN){
                    printf("单词长度超过规定");
                    fclose(pFile);
                    return -1;
                }
                word[index] = to_lower(ch);
                ++index;
            }else{
                word[index] = '\0';
                if(index > 0){
                    int ret = stat_word_func(word);
                    if(ret == -1){
                        printf("不同单词数量超过上限");
                        fclose(pFile);
                        return -1;
                    }
                }
                
                index = 0;
            }
            ch = fgetc(pFile);
        }
        if(feof(pFile)){
            if(index > 0){
                word[index] = '\0';
                printf("单词: %s \n", word);
                int ret = stat_word_func(word);
                if(ret == -1){
                    printf("不同单词数量超过上限");
                    fclose(pFile);
                    return -1;
                }
                index = 0;
            }
            printf("文件读取完成 \n");
        }
        if(ferror(pFile)){
            printf("\n");
            printf("读取文件失败 \n");
            fclose(pFile);
            return -1;
        }
        fclose (pFile);
        printf("\n");
        printf("读取文件操作完成 \n");
        printf("\n");
        if(get_top_number() != 0){
            printf("统计出错");
        };
    }else{
        printf("\n");
        printf("fopen fail");
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
