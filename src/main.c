#include <stdio.h>
#include <string.h>

#define PATH_MAX_LENGTH 100 // 最大文件路径长度 100
#define MAX_WORD_LEN 50 // 最大英文单词长度 50
#define MAX_UNIQUE_WORD 1000 // 最多统计 1000 个不同单词

typedef struct WordStatNode{
    char word[MAX_WORD_LEN + 1];
    int count;
}Word;

Word word_stat_arr[MAX_UNIQUE_WORD];
static int word_stat_index = 0;
static int word_total = 0;

static int top_word_number = 0; // 统计的前N个单词. 由用户输入

int to_lower(char ch);
int is_alpha(int c);

int stat_word_func(const char * str);
void print_word_stats(void);
void sort_words(void);
int is_correct_top_word_number(void);
int is_empty_word_file(void);


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
                    ++word_total;
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
                ++word_total;
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
        sort_words();

        if(is_empty_word_file()){
            return 0;
        }
        printf("\n");
        printf("----------- \n");
        printf("*********** \n");
        printf("\n");
        printf("总共有%d个单词 \n", word_stat_index);
        printf("请输入你想看的前N名单词: ");
        scanf("%d", &top_word_number);
        if(is_correct_top_word_number()){
            print_word_stats();
        }else{
            return 0;
        }
        
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

int stat_word_func(const char * str){
    if(word_stat_index == 0){
        word_stat_arr[word_stat_index].count = 1;
        strcpy(word_stat_arr[word_stat_index].word, str);
        word_stat_index++;
    }else{
        for (int i = 0; i < word_stat_index; i++)
        {
            Word * temp = &word_stat_arr[i];
            if(strcmp(temp->word, str) == 0){
                temp->count++;
                return 0;
            }
        }
        if(word_stat_index == MAX_UNIQUE_WORD){
            return -1;
        }
        word_stat_arr[word_stat_index].count = 1;
        strcpy(word_stat_arr[word_stat_index].word, str);
        word_stat_index++;
    }
    
    return 0;
}

int need_swap(Word a, Word b) {
    if (a.count != b.count) {
        return a.count < b.count; // 次数小的排后面
    }
    return strcmp(a.word, b.word) > 0; // 次数相同时，字典序大的排后面
}

void sort_words(void){
    if(word_stat_index == 0){
        return ;
    }
    int p = 0;
    int end = word_stat_index;

    // 冒泡排序
    while (p != end)    
    {
        while (p != end -1)
        {
            if(need_swap(word_stat_arr[p], word_stat_arr[p+1])){
                Word temp = word_stat_arr[p];
                word_stat_arr[p] = word_stat_arr[p+1];
                word_stat_arr[p+1] = temp;
            }
            ++p;
        }
        end = p;
        p = 0;
    }
    return ;
}

// 判断用户输入的数字是否合规
int is_correct_top_word_number(void){
    if(top_word_number <= 0){
        printf("错误数字, 统计失败 \n");
        return 0;
    }
    // 超过当前统计数,返回false
    if(top_word_number > word_stat_index){
        printf("超过不同单词数, 统计失败 \n");
        return 0;
    }
    return 1;
}

int is_empty_word_file(){
    if(word_total == 0){
        printf("文件中没有可识别的单词");
        return 1;
    }
    return 0;
}

// 打印单词统计
void print_word_stats(void){
    printf("🧮 当前文件的单词个数: %d \n", word_total);
    printf("📉 不同单词数：%d \n", word_stat_index);
    printf("\n");
    printf("排名前%d个单词的统计: \n", top_word_number);
    for (int i = 0; i < top_word_number; i++)
    {
        Word word = word_stat_arr[i];
        float frequency = (float)word.count / word_total;
        printf("🗒️ \n单词: %s, 出现次数: %d, 频率: %.4f \n", word.word, word.count, frequency);
    }
    
    
    return ;
}