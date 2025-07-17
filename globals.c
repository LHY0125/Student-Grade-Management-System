/**
 * @file globals.c
 * @brief 全局变量定义文件
 * @note 定义所有全局变量的实际存储空间
 */

#include "globals.h"

// 全局变量定义
Student students[MAX_STUDENTS];             // 学生数组
User users[MAX_USERS];                      // 用户数组
int studentCount = 0;                       // 当前学生数量
int userCount = 0;                          // 当前用户数量
char currentUser[MAX_USERNAME_LENGTH] = ""; // 当前登录用户
bool isCurrentUserAdmin = false;            // 当前用户是否为管理员

// 系统状态变量
bool systemInitialized = false;            // 系统是否已初始化
bool dataModified = false;                 // 数据是否已修改

// 统计信息缓存
float overallAverageScore = 0.0;           // 全体学生平均分
float highestScore = 0.0;                  // 最高分
float lowestScore = 100.0;                 // 最低分
bool statsNeedUpdate = true;               // 统计信息是否需要更新

// 排序参数
int currentSortCriteria = 0;               // 当前排序依据
int currentSortOrder = 0;                  // 当前排序顺序

// 统计缓存
StatisticsCache statsCache = {false, {0}, {0}, {{0}}, 0, 0}; // 统计分析缓存