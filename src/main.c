#include <stdio.h>
#include <string.h>
#include "word_stats.h"
#include "file_reader.h"


int main(){
    char filePath[PATH_MAX_LENGTH] = {'\0'};
    int get_path_ret = get_user_file_path(filePath);
    if(get_path_ret != 0) {
        return -1;
    }
    FILE * pFile = fopen(filePath, "r");
    if (pFile!=NULL)
    {
        printf("=====打开文件成功, 开始读取单词===== \n");
        
        while (feof(pFile) == 0)
        {
            char word[MAX_WORD_LEN + 1] = {0};
            int ret = get_file_word(pFile, word, MAX_WORD_LEN);
            if(ret != 0){
                fclose(pFile);
                return 0;
            }
            int result = stat_word_func(word);
            if(result == -1){
                printf("文件读取完成 \n");
                fclose(pFile);
                return -1;
            }
        }
        printf("文件读取完成 \n");
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

