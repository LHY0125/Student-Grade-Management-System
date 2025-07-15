/**
 * @file io_utils.h
 * @brief 输入输出工具函数头文件
 * @note 包含界面显示、用户输入等相关函数声明
 */

#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <stdbool.h>

// 界面显示函数
void clearInputBuffer();                    // 清理输入缓冲区
void pauseSystem();                         // 暂停系统，等待用户按键
void clearScreen();                         // 清屏
void printSeparator();                      // 打印分隔线
void printHeader(const char* title);       // 打印标题头

// 安全输入函数
int safeInputInt(const char* prompt, int min, int max);  // 安全输入整数
float safeInputFloat(const char* prompt, float min, float max); // 安全输入浮点数
void safeInputString(const char* prompt, char* buffer, int maxLen); // 安全输入字符串

// 颜色输出函数
void printColored(const char* text, const char* color);  // 彩色输出
void printSuccess(const char* message);    // 成功消息
void printError(const char* message);      // 错误消息
void printWarning(const char* message);    // 警告消息
void printInfo(const char* message);       // 信息消息

#endif // IO_UTILS_H