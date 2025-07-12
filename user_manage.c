/**
 * @file user_manage.c
 * @brief 用户管理实现文件
 * @note 实现用户认证和管理功能
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_manage.h"
#include "config.h"
#include "globals.h"
#include "auxiliary.h"

/**
 * @brief 处理用户登录
 * @return 登录成功返回1，失败返回0
 */
int loginSystem() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    
    printf("\n");
    safeInputString("请输入用户名", username, MAX_USERNAME_LENGTH);
    safeInputString("请输入密码", password, MAX_PASSWORD_LENGTH);
    
    // 验证用户名和密码
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && 
            strcmp(users[i].password, password) == 0) {
            // 登录成功
            strcpy(currentUser, username);
            isCurrentUserAdmin = users[i].isAdmin;
            return 1;
        }
    }
    
    return 0; // 登录失败
}

/**
 * @brief 从文件加载用户数据
 */
void loadUsersFromFile() {
    FILE* file = fopen(USERS_FILE, "r");
    if (file == NULL) {
        // 文件不存在，创建默认管理员账户
        strcpy(users[0].username, "admin");
        strcpy(users[0].password, "123456");
        users[0].isAdmin = true;
        
        strcpy(users[1].username, "teacher");
        strcpy(users[1].password, "password");
        users[1].isAdmin = false;
        
        userCount = 2;
        
        // 保存默认用户到文件
        saveUsersToFile();
        printInfo("已创建默认用户账户：");
        printInfo("管理员 - 用户名: admin, 密码: 123456");
        printInfo("普通用户 - 用户名: teacher, 密码: password");
        return;
    }
    
    userCount = 0;
    char line[200];
    
    while (fgets(line, sizeof(line), file) && userCount < MAX_USERS) {
        // 移除换行符
        line[strcspn(line, "\n")] = '\0';
        
        // 解析格式：username:password:isAdmin
        char* username = strtok(line, ":");
        char* password = strtok(NULL, ":");
        char* adminFlag = strtok(NULL, ":");
        
        if (username && password && adminFlag) {
            strcpy(users[userCount].username, username);
            strcpy(users[userCount].password, password);
            users[userCount].isAdmin = (strcmp(adminFlag, "1") == 0);
            userCount++;
        }
    }
    
    fclose(file);
}

/**
 * @brief 将用户数据保存到文件
 */
void saveUsersToFile() {
    FILE* file = fopen(USERS_FILE, "w");
    if (file == NULL) {
        printError("无法保存用户数据！");
        return;
    }
    
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s:%s:%d\n", 
                users[i].username, 
                users[i].password, 
                users[i].isAdmin ? 1 : 0);
    }
    
    fclose(file);
}

/**
 * @brief 增加用户账户
 */
void addUserAccount() {
    clearScreen();
    printHeader("添加用户账户");
    
    if (userCount >= MAX_USERS) {
        printError("用户数量已达上限！");
        pauseSystem();
        return;
    }
    
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    
    printf("\n");
    safeInputString("请输入新用户名", username, MAX_USERNAME_LENGTH);
    
    // 检查用户名是否已存在
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printError("用户名已存在！");
            pauseSystem();
            return;
        }
    }
    
    safeInputString("请输入密码", password, MAX_PASSWORD_LENGTH);
    
    printf("\n用户类型：\n");
    printf("1. 普通用户\n");
    printf("2. 管理员\n");
    int userType = safeInputInt("请选择用户类型", 1, 2);
    
    // 添加新用户
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    users[userCount].isAdmin = (userType == 2);
    userCount++;
    
    // 保存到文件
    saveUsersToFile();
    dataModified = true;
    
    printSuccess("用户添加成功！");
    pauseSystem();
}

/**
 * @brief 删除用户账户
 */
void deleteUserAccount() {
    clearScreen();
    printHeader("删除用户账户");
    
    if (userCount <= 1) {
        printError("至少需要保留一个用户账户！");
        pauseSystem();
        return;
    }
    
    char username[MAX_USERNAME_LENGTH];
    printf("\n");
    safeInputString("请输入要删除的用户名", username, MAX_USERNAME_LENGTH);
    
    // 不能删除当前登录用户
    if (strcmp(username, currentUser) == 0) {
        printError("不能删除当前登录的用户！");
        pauseSystem();
        return;
    }
    
    // 查找并删除用户
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            // 移动后面的用户向前
            for (int j = i; j < userCount - 1; j++) {
                users[j] = users[j + 1];
            }
            userCount--;
            
            // 保存到文件
            saveUsersToFile();
            dataModified = true;
            
            printSuccess("用户删除成功！");
            pauseSystem();
            return;
        }
    }
    
    printError("用户不存在！");
    pauseSystem();
}

/**
 * @brief 修改用户密码
 */
void modifyUserPassword() {
    clearScreen();
    printHeader("修改用户密码");
    
    char username[MAX_USERNAME_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];
    
    printf("\n");
    safeInputString("请输入用户名", username, MAX_USERNAME_LENGTH);
    
    // 查找用户
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            safeInputString("请输入新密码", newPassword, MAX_PASSWORD_LENGTH);
            
            strcpy(users[i].password, newPassword);
            
            // 保存到文件
            saveUsersToFile();
            dataModified = true;
            
            printSuccess("密码修改成功！");
            pauseSystem();
            return;
        }
    }
    
    printError("用户不存在！");
    pauseSystem();
}

/**
 * @brief 查看所有用户
 */
void viewAllUsers() {
    clearScreen();
    printHeader("所有用户列表");
    
    if (userCount == 0) {
        printWarning("暂无用户数据！");
        pauseSystem();
        return;
    }
    
    printf("\n");
    printf("%-20s %-15s %-10s\n", "用户名", "用户类型", "状态");
    printSeparator();
    
    for (int i = 0; i < userCount; i++) {
        printf("%-20s %-15s %-10s\n", 
               users[i].username,
               users[i].isAdmin ? "管理员" : "普通用户",
               strcmp(users[i].username, currentUser) == 0 ? "当前用户" : "");
    }
    
    printf("\n总用户数: %d\n", userCount);
    pauseSystem();
}