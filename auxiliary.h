/**
 * @file auxiliary.h
 * @brief 辅助函数头文件
 * @note 包含系统中使用的各种辅助函数声明
 */

#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <stdbool.h>
#include "main_menu.h"

// 输入输出辅助函数
void clearInputBuffer();                    // 清理输入缓冲区
void pauseSystem();                         // 暂停系统，等待用户按键
void clearScreen();                         // 清屏
void printSeparator();                      // 打印分隔线
void printHeader(const char* title);       // 打印标题头

// 数据验证函数
bool isValidScore(float score);             // 验证分数是否合法 (0-100)
bool isValidStudentID(const char* id);      // 验证学号格式
bool isValidName(const char* name);         // 验证姓名格式
bool isValidGender(char gender);            // 验证性别
bool isValidAge(int age);                   // 验证年龄

// 字符串处理函数
void trimString(char* str);                 // 去除字符串首尾空格
bool isEmptyString(const char* str);        // 判断字符串是否为空
void toLowerCase(char* str);                // 转换为小写
void toUpperCase(char* str);                // 转换为大写

// 文件操作辅助函数
bool fileExists(const char* filename);      // 检查文件是否存在
bool createDirectory(const char* path);     // 创建目录
bool backupFile(const char* source, const char* backup); // 备份文件

// 数学计算辅助函数
float calculateAverage(float scores[], int count);       // 计算平均分
float findMaxScore(float scores[], int count);           // 找最高分
float findMinScore(float scores[], int count);           // 找最低分


// 安全输入函数
int safeInputInt(const char* prompt, int min, int max);  // 安全输入整数
float safeInputFloat(const char* prompt, float min, float max); // 安全输入浮点数
void safeInputString(const char* prompt, char* buffer, int maxLen); // 安全输入字符串
char safeInputChar(const char* prompt, const char* validChars);     // 安全输入字符

// 系统初始化和清理函数
bool initializeSystem();                   // 初始化系统
void cleanupSystem();                      // 清理系统资源
bool createDataDirectories();              // 创建数据目录

// 颜色输出函数
void printColored(const char* text, const char* color);  // 彩色输出
void printSuccess(const char* message);    // 成功消息
void printError(const char* message);      // 错误消息
void printWarning(const char* message);    // 警告消息
void printInfo(const char* message);       // 信息消息

#endif // AUXILIARY_H