#ifndef WORD_STATS_H
#define WORD_STATS_H

#define MAX_WORD_LEN 50 // 最大英文单词长度 50
#define MAX_UNIQUE_WORD 1000 // 最多统计 1000 个不同单词
// 单个单词结构体: 1. 字符串word 2. 统计次数count
typedef struct WordStatNode{
    char word[MAX_WORD_LEN + 1]; // +1 是以/0结尾
    int count;
}Word;

typedef struct WordStats{
    Word word_arr[MAX_UNIQUE_WORD]; // 统计单词结构体数组.
    int total;// 单词总数
    int index; // 不同单词有效计数.
}WordStats;


// 纳入单词进入统计单词结构体
int stat_word_func(const char * str);
// 按统计次数排序
void sort_words(void);
// 打印单词统计
void print_word_stats(void);
// 获取top_n
int get_top_number(void);
// 输入的top_n是否正确
int is_correct_top_word_number(void);
// 是否为空文件
int is_empty_word_file(void);

#endif /* WORD_STATS_H */
