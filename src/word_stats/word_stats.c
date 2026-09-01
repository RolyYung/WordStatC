#include <stdio.h>
#include <string.h>
#include "word_stats.h"

WordStats word_stats = {0};
static int top_word_number = 0; // 统计的前N个单词. 由用户输入

int stat_word_func(const char * str){
    word_stats.total++;
    if(word_stats.index == 0){
        word_stats.word_arr[word_stats.index].count = 1;
        strcpy(word_stats.word_arr[word_stats.index].word, str);
        word_stats.index++;
        
    }else{
        for (int i = 0; i < word_stats.index; i++)
        {
            Word * temp = &word_stats.word_arr[i];
            if(strcmp(temp->word, str) == 0){
                temp->count++;
                return 0;
            }
        }
        if(word_stats.index == MAX_UNIQUE_WORD){
            return -1;
        }
        word_stats.word_arr[word_stats.index].count = 1;
        strcpy(word_stats.word_arr[word_stats.index].word, str);
        word_stats.index++;
    }
   
    
    return 0;
}

// 内部函数不需要暴露
static int need_swap(Word a, Word b) {
    if (a.count != b.count) {
        return a.count < b.count; // 次数小的排后面
    }
    return strcmp(a.word, b.word) > 0; // 次数相同时，字典序大的排后面
}

void sort_words(void){
    if(word_stats.index == 0){
        return ;
    }
    int p = 0;
    int end = word_stats.index;

    // 冒泡排序
    while (p != end)    
    {
        while (p != end -1)
        {
            if(need_swap(word_stats.word_arr[p], word_stats.word_arr[p+1])){
                Word temp = word_stats.word_arr[p];
                word_stats.word_arr[p] = word_stats.word_arr[p+1];
                word_stats.word_arr[p+1] = temp;
            }
            ++p;
        }
        end = p;
        p = 0;
    }
    return ;
}

// 打印单词统计
void print_word_stats(void){
    printf("🧮 当前文件的单词个数: %d \n", word_stats.total);
    printf("📉 不同单词数：%d \n", word_stats.index);
    printf("\n");
    printf("排名前%d个单词的统计: \n", top_word_number);
    for (int i = 0; i < top_word_number; i++)
    {
        Word word = word_stats.word_arr[i];
        float frequency = (float)word.count / word_stats.total;
        printf("🗒️ \n单词: %s, 出现次数: %d, 频率: %.4f \n", word.word, word.count, frequency);
    }
    
    
    return ;
}

int get_top_number(void){
    if(is_empty_word_file()){
        return 0;
    }
    sort_words();
    printf("----------- \n");
    printf("*********** \n");
    printf("\n");
    printf("总共出现了%d个不同单词 \n", word_stats.index);
    printf("请输入你想看的前N名单词: ");
    scanf("%d", &top_word_number);
    if(is_correct_top_word_number()){
        print_word_stats();
        return 1;
    }else{
        return 0;
    }
}

// 判断用户输入的数字是否合规
int is_correct_top_word_number(void){
    if(top_word_number <= 0){
        printf("错误数字, 统计失败 \n");
        return 0;
    }
    // 超过当前统计数,返回false
    if(top_word_number > word_stats.index){
        printf("超过不同单词数, 统计失败 \n");
        return 0;
    }
    return 1;
}

int is_empty_word_file(){
    if(word_stats.total == 0){
        printf("文件中没有可识别的单词 by: empty_word_file\n ");
        return 1;
    }
    return 0;
}