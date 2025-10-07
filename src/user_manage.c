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
#include "io_utils.h"
#include "string_utils.h"
#include "security_utils.h"
#include "validation.h"

/**
 * @brief 处理用户登录
 * @details 提供用户登录验证功能，验证用户名和密码的正确性
 *          登录成功后设置当前用户信息和管理员权限
 * @return int 登录成功返回1，失败返回0
 * @note 登录过程：
 *       1. 获取用户输入的用户名和密码
 *       2. 遍历用户数组进行验证
 *       3. 验证成功则设置currentUser和isCurrentUserAdmin
 * @note 设置的全局变量：
 *       - currentUser: 当前登录用户名
 *       - isCurrentUserAdmin: 当前用户是否为管理员
 */
int loginSystem()
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("\n");
    safeInputString("请输入用户名", username, MAX_USERNAME_LENGTH);
    safeInputString("请输入密码", password, MAX_PASSWORD_LENGTH);

    // 验证用户名和密码
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0 &&
            verify_password(password, users[i].passwordHash))
        {
            // 登录成功
            strncpy(currentUser, username, MAX_USERNAME_LENGTH - 1);
            currentUser[MAX_USERNAME_LENGTH - 1] = '\0';
            isCurrentUserAdmin = users[i].isAdmin;
            // 安全清除密码
            secure_memset(password, strlen(password));
            return 1;
        }
    }

    // 安全清除密码
    secure_memset(password, strlen(password));
    return 0; // 登录失败
}

/**
 * @brief 从文件加载用户数据
 * @details 从USERS_FILE文件中读取用户数据到内存
 *          如果文件不存在，则创建默认的管理员和普通用户账户
 * @note 文件格式：每行格式为 "username:password:isAdmin"
 *       其中isAdmin为1表示管理员，0表示普通用户
 * @note 默认账户：
 *       - 管理员：用户名admin，密码123456
 *       - 普通用户：用户名teacher，密码password
 * @warning 如果文件格式错误，可能导致数据加载不完整
 */
void loadUsersFromFile()
{
    FILE *file = fopen(USERS_FILE, "r");
    if (file == NULL)
    {
        // 文件不存在，创建默认管理员账户
        strncpy(users[0].username, "admin", MAX_USERNAME_LENGTH - 1);
        users[0].username[MAX_USERNAME_LENGTH - 1] = '\0';
        hash_password("123456", users[0].passwordHash);
        users[0].isAdmin = true;

        strncpy(users[1].username, "teacher", MAX_USERNAME_LENGTH - 1);
        users[1].username[MAX_USERNAME_LENGTH - 1] = '\0';
        hash_password("password", users[1].passwordHash);
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

    while (fgets(line, sizeof(line), file) && userCount < MAX_USERS)
    {
        // 移除换行符
        line[strcspn(line, "\n")] = '\0';

        // 解析格式：username:passwordHash:isAdmin
        char *username = strtok(line, ":");
        char *passwordHash = strtok(NULL, ":");
        char *adminFlag = strtok(NULL, ":");

        if (username && passwordHash && adminFlag)
        {
            strncpy(users[userCount].username, username, MAX_USERNAME_LENGTH - 1);
            users[userCount].username[MAX_USERNAME_LENGTH - 1] = '\0';
            strncpy(users[userCount].passwordHash, passwordHash, SHA256_HEX_LENGTH - 1);
            users[userCount].passwordHash[SHA256_HEX_LENGTH - 1] = '\0';
            users[userCount].isAdmin = (strcmp(adminFlag, "1") == 0);
            userCount++;
        }
    }

    fclose(file);
}

/**
 * @brief 将用户数据保存到文件
 * @details 将内存中的用户数据写入到USERS_FILE文件中
 *          采用文本格式存储，每个用户占一行
 * @note 文件格式：每行格式为 "username:password:isAdmin"
 *       其中isAdmin为1表示管理员，0表示普通用户
 * @warning 如果文件无法打开，将显示错误信息
 */
void saveUsersToFile()
{
    FILE *file = fopen(USERS_FILE, "w");
    if (file == NULL)
    {
        printError("无法保存用户数据！");
        return;
    }

    for (int i = 0; i < userCount; i++)
    {
        fprintf(file, "%s:%s:%d\n",
                users[i].username,
                users[i].passwordHash,
                users[i].isAdmin ? 1 : 0);
    }

    fclose(file);
}

/**
 * @brief 增加用户账户
 * @details 提供交互式界面添加新的用户账户
 *          包括用户名唯一性检查、密码设置和用户类型选择
 * @note 添加流程：
 *       1. 检查用户数量是否达到上限
 *       2. 输入新用户名并检查唯一性
 *       3. 设置密码
 *       4. 选择用户类型（普通用户/管理员）
 *       5. 保存到文件并更新数据修改标志
 * @warning 如果用户数量已达MAX_USERS上限，将拒绝添加
 * @warning 如果用户名已存在，将拒绝添加
 */
void addUserAccount()
{
    clearScreen();
    printHeader("添加用户账户");

    if (userCount >= MAX_USERS)
    {
        printError("用户数量已达上限！");
        pauseSystem();
        return;
    }

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("\n");
    do {
        safeInputString("请输入新用户名", username, MAX_USERNAME_LENGTH);
        if (!isValidUsername(username)) {
            printError("用户名格式无效！用户名长度必须在3-20字符之间，只能包含字母和数字。");
            continue;
        }
        
        // 检查用户名是否已存在
        bool exists = false;
        for (int i = 0; i < userCount; i++)
        {
            if (strcmp(users[i].username, username) == 0)
            {
                printError("用户名已存在！");
                exists = true;
                break;
            }
        }
        if (!exists) break;
    } while (true);

    do {
        safeInputString("请输入密码", password, MAX_PASSWORD_LENGTH);
        if (!isValidPassword(password)) {
            printError("密码格式无效！密码长度必须在6-50字符之间。");
            continue;
        }
        break;
    } while (true);

    printf("\n用户类型：\n");
    printf("1. 普通用户\n");
    printf("2. 管理员\n");
    int userType = safeInputInt("请选择用户类型", 1, 2);

    // 添加新用户
    strncpy(users[userCount].username, username, MAX_USERNAME_LENGTH - 1);
    users[userCount].username[MAX_USERNAME_LENGTH - 1] = '\0';
    hash_password(password, users[userCount].passwordHash);
    users[userCount].isAdmin = (userType == 2);
    userCount++;
    
    // 安全清除明文密码
    secure_memset(password, strlen(password));

    // 保存到文件
    saveUsersToFile();
    dataModified = true;

    printSuccess("用户添加成功！");
    pauseSystem();
}

/**
 * @brief 删除用户账户
 * @details 提供交互式界面删除指定的用户账户
 *          包含安全检查，防止删除当前登录用户和最后一个用户
 * @note 删除限制：
 *       - 不能删除当前登录的用户
 *       - 系统至少需要保留一个用户账户
 * @note 删除过程：
 *       1. 输入要删除的用户名
 *       2. 进行安全检查
 *       3. 查找用户并删除
 *       4. 重新排列用户数组
 *       5. 保存到文件并更新数据修改标志
 * @warning 删除操作不可逆，请谨慎操作
 */
void deleteUserAccount()
{
    clearScreen();
    printHeader("删除用户账户");

    if (userCount <= 1)
    {
        printError("至少需要保留一个用户账户！");
        pauseSystem();
        return;
    }

    char username[MAX_USERNAME_LENGTH];
    printf("\n");
    safeInputString("请输入要删除的用户名", username, MAX_USERNAME_LENGTH);

    // 不能删除当前登录用户
    if (strcmp(username, currentUser) == 0)
    {
        printError("不能删除当前登录的用户！");
        pauseSystem();
        return;
    }

    // 查找并删除用户
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            // 移动后面的用户向前
            for (int j = i; j < userCount - 1; j++)
            {
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
 * @details 提供交互式界面修改指定用户的密码
 *          管理员可以修改任何用户的密码
 * @note 修改流程：
 *       1. 输入要修改密码的用户名
 *       2. 查找用户是否存在
 *       3. 输入新密码
 *       4. 更新用户密码
 *       5. 保存到文件并更新数据修改标志
 * @warning 密码修改后立即生效，用户需要使用新密码登录
 */
void modifyUserPassword()
{
    clearScreen();
    printHeader("修改用户密码");

    char username[MAX_USERNAME_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];

    printf("\n");
    safeInputString("请输入用户名", username, MAX_USERNAME_LENGTH);

    // 查找用户
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            safeInputString("请输入新密码", newPassword, MAX_PASSWORD_LENGTH);

            hash_password(newPassword, users[i].passwordHash);
            
            // 安全清除明文密码
            secure_memset(newPassword, strlen(newPassword));

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
 * @details 显示系统中所有用户的信息列表
 *          包括用户名、用户类型和当前登录状态
 * @note 显示内容：
 *       - 用户名
 *       - 用户类型（管理员/普通用户）
 *       - 状态（标识当前登录用户）
 *       - 总用户数统计
 * @note 表格格式显示，便于查看和管理
 * @warning 如果没有用户数据，将显示警告信息
 */
void viewAllUsers()
{
    clearScreen();
    printHeader("所有用户列表");

    if (userCount == 0)
    {
        printWarning("暂无用户数据！");
        pauseSystem();
        return;
    }

    printf("\n");
    printf("%-20s %-15s %-10s\n", "用户名", "用户类型", "状态");
    printSeparator();

    for (int i = 0; i < userCount; i++)
    {
        printf("%-20s %-15s %-10s\n",
               users[i].username,
               users[i].isAdmin ? "管理员" : "普通用户",
               strcmp(users[i].username, currentUser) == 0 ? "当前用户" : "");
    }

    printf("\n总用户数: %d\n", userCount);
    pauseSystem();
}