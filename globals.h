/**
 * @file globals.h
 * @brief 全局变量声明头文件
 * @note 集中管理所有全局变量的声明，提高代码可维护性
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdbool.h>
#include "config.h"
#include "main_menu.h"

// 用户结构体定义
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    bool isAdmin;  // 是否为管理员
} User;

// 全局变量声明
extern Student students[MAX_STUDENTS];      // 学生数组
extern User users[MAX_USERS];               // 用户数组
extern int studentCount;                    // 当前学生数量
extern int userCount;                       // 当前用户数量
extern char currentUser[MAX_USERNAME_LENGTH]; // 当前登录用户
extern bool isCurrentUserAdmin;             // 当前用户是否为管理员

// 系统状态变量
extern bool systemInitialized;             // 系统是否已初始化
extern bool dataModified;                  // 数据是否已修改（用于判断是否需要保存）

// 统计信息缓存（可选，用于提高性能）
extern float overallAverageScore;          // 全体学生平均分
extern float highestScore;                 // 最高分
extern float lowestScore;                  // 最低分
extern bool statsNeedUpdate;               // 统计信息是否需要更新

#endif // GLOBALS_H