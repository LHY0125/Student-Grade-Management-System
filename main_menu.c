/**
 * @file main_menu.c
 * @brief 主菜单实现文件
 * @note 实现各种菜单显示功能
 */

 #include <stdio.h>
 #include "main_menu.h"
 #include "config.h"
 #include "auxiliary.h"
 #include "globals.h"
 
 /**
  * @brief 显示主菜单
  */
 void displayMainMenu()
 {
     printHeader("学生成绩管理系统 - 主菜单");
     printf("\n");
     printf("当前用户: %s %s\n", currentUser, 
            isCurrentUserAdmin ? "(管理员)" : "(普通用户)");
     printf("\n");
     printf("1. 基本功能管理\n");
     printf("2. 统计分析功能\n");
     if (isCurrentUserAdmin)
     {
         printf("3. 系统管理功能\n");
     }
     printf("0. 退出系统\n");
     printf("\n");
     printSeparator();
 }
 
 /**
  * @brief 显示基本功能菜单
  */
 void displayBasicFunctionsMenu()
 {
     printHeader("基本功能管理");
     printf("\n");
     printf("1. 添加学生信息\n");
     printf("2. 删除学生信息\n");
     printf("3. 修改学生信息\n");
     printf("4. 按学号查找学生\n");
     printf("5. 按姓名查找学生\n");
     printf("6. 显示所有学生\n");
     printf("7. 学生信息排序\n");
     printf("0. 返回主菜单\n");
     printf("\n");
     printf("当前学生总数: %d\n", studentCount);
     printf("\n");
     printSeparator();
 }
 
 /**
  * @brief 显示统计功能菜单
  */
 void displayStatisticsMenu()
 {
     printHeader("统计分析功能");
     printf("\n");
     printf("1. 课程统计分析\n");
     printf("2. 成绩分布统计\n");
     printf("3. 分数段统计\n");
     printf("4. 综合统计分析\n");
     printf("0. 返回主菜单\n");
     printf("\n");
     printf("当前学生总数: %d\n", studentCount);
     if (studentCount > 0) {
         printf("系统平均分: %.2f\n", overallAverageScore);
     }
     printf("\n");
     printSeparator();
 }
 
 /**
  * @brief 显示管理功能菜单
  */
 void displayAdminMenu()
 {
     printHeader("系统管理功能");
     printf("\n");
     printf("1. 添加用户账户\n");
     printf("2. 删除用户账户\n");
     printf("3. 修改用户密码\n");
     printf("4. 查看所有用户\n");
     printf("0. 返回主菜单\n");
     printf("\n");
     printf("当前用户总数: %d\n", userCount);
     printf("\n");
     printSeparator();
 }