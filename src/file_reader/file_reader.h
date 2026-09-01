#ifndef FILE_READER_H
#define FILE_READER_H

#define PATH_MAX_LENGTH 100 // 最大文件路径长度 100

// 文件读取功能头文件
int to_lower(char ch);
int is_alpha(int c);
int get_user_file_path(char *path);

int get_file_word(FILE * pFile, char * word, int max_size);

#endif /* FILE_READER_H */
