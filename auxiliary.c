/**
 * @file auxiliary.c
 * @brief 辅助函数实现文件
 * @note 实现系统中使用的各种辅助函数
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#include <conio.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#include <termios.h>
#endif

#include "auxiliary.h"
#include "config.h"
#include "globals.h"
#include "stu.data.h"
#include "user_manage.h"

/**
 * @brief 清理输入缓冲区
 */
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/**
 * @brief 暂停系统，等待用户按键
 */
void pauseSystem()
{
    printf("\n按任意键继续...");
#ifdef _WIN32
    _getch();
#else
    getchar();
#endif
    printf("\n");
}

/**
 * @brief 清屏
 */
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * @brief 打印分隔线
 */
void printSeparator()
{
    printf("========================================\n");
}

/**
 * @brief 打印标题头
 * @param title 标题文本
 */
void printHeader(const char *title)
{
    printSeparator();
    printf("          %s\n", title);
    printSeparator();
}

/**
 * @brief 验证分数是否合法
 * @param score 分数
 * @return 合法返回true，否则返回false
 */
bool isValidScore(float score)
{
    return score >= MIN_SCORE && score <= MAX_SCORE;
}

/**
 * @brief 验证学号格式
 * @param id 学号
 * @return 合法返回true，否则返回false
 */
bool isValidStudentID(const char *id)
{
    if (id == NULL || strlen(id) == 0 || strlen(id) >= MAX_ID_LENGTH)
    {
        return false;
    }

    // 检查是否只包含数字和字母
    for (int i = 0; id[i] != '\0'; i++)
    {
        if (!isalnum(id[i]))
        {
            return false;
        }
    }

    return true;
}

/**
 * @brief 验证姓名格式
 * @param name 姓名
 * @return 合法返回true，否则返回false
 */
bool isValidName(const char *name)
{
    if (name == NULL || strlen(name) == 0 || strlen(name) >= MAX_NAME_LENGTH)
    {
        return false;
    }

    // 检查是否包含非法字符
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ' && name[i] != '-' &&
            (unsigned char)name[i] < 128)
        { // 允许中文字符
            return false;
        }
    }

    return true;
}

/**
 * @brief 验证性别
 * @param gender 性别字符
 * @return 合法返回true，否则返回false
 */
bool isValidGender(char gender)
{
    return gender == GENDER_MALE || gender == GENDER_FEMALE;
}

/**
 * @brief 验证年龄
 * @param age 年龄
 * @return 合法返回true，否则返回false
 */
bool isValidAge(int age)
{
    return age >= 10 && age <= 100;
}

/**
 * @brief 去除字符串首尾空格
 * @param str 字符串
 */
void trimString(char *str)
{
    if (str == NULL)
        return;

    // 去除开头空格
    char *start = str;
    while (isspace(*start))
        start++;

    // 去除结尾空格
    char *end = str + strlen(str) - 1;
    while (end > start && isspace(*end))
        end--;

    // 移动字符串
    int len = end - start + 1;
    memmove(str, start, len);
    str[len] = '\0';
}

/**
 * @brief 判断字符串是否为空
 * @param str 字符串
 * @return 为空返回true，否则返回false
 */
bool isEmptyString(const char *str)
{
    if (str == NULL)
        return true;

    while (*str)
    {
        if (!isspace(*str))
            return false;
        str++;
    }
    return true;
}

/**
 * @brief 检查文件是否存在
 * @param filename 文件名
 * @return 存在返回true，否则返回false
 */
bool fileExists(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file)
    {
        fclose(file);
        return true;
    }
    return false;
}

/**
 * @brief 创建目录
 * @param path 目录路径
 * @return 成功返回true，否则返回false
 */
bool createDirectory(const char *path)
{
#ifdef _WIN32
    return _mkdir(path) == 0 || errno == EEXIST;
#else
    return mkdir(path, 0755) == 0 || errno == EEXIST;
#endif
}

/**
 * @brief 计算平均分
 * @param scores 分数数组
 * @param count 分数个数
 * @return 平均分
 */
float calculateAverage(float scores[], int count)
{
    if (count <= 0)
        return 0.0;

    float sum = 0.0;
    for (int i = 0; i < count; i++)
    {
        sum += scores[i];
    }
    return sum / count;
}

/**
 * @brief 安全输入整数
 * @param prompt 提示信息
 * @param min 最小值
 * @param max 最大值
 * @return 输入的整数
 */
int safeInputInt(const char *prompt, int min, int max)
{
    int value;
    char buffer[100];

    while (1)
    {
        printf("%s (%d-%d): ", prompt, min, max);

        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            if (sscanf(buffer, "%d", &value) == 1)
            {
                if (value >= min && value <= max)
                {
                    return value;
                }
            }
        }

        printError("输入无效，请重新输入！");
    }
}

/**
 * @brief 安全输入浮点数
 * @param prompt 提示信息
 * @param min 最小值
 * @param max 最大值
 * @return 输入的浮点数
 */
float safeInputFloat(const char *prompt, float min, float max)
{
    float value;
    char buffer[100];

    while (1)
    {
        printf("%s (%.1f-%.1f): ", prompt, min, max);

        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            if (sscanf(buffer, "%f", &value) == 1)
            {
                if (value >= min && value <= max)
                {
                    return value;
                }
            }
        }

        printError("输入无效，请重新输入！");
    }
}

/**
 * @brief 安全输入字符串
 * @param prompt 提示信息
 * @param buffer 缓冲区
 * @param maxLen 最大长度
 */
void safeInputString(const char *prompt, char *buffer, int maxLen)
{
    while (1)
    {
        printf("%s: ", prompt);

        if (fgets(buffer, maxLen, stdin) != NULL)
        {
            // 移除换行符
            buffer[strcspn(buffer, "\n")] = '\0';
            trimString(buffer);

            if (!isEmptyString(buffer))
            {
                return;
            }
        }

        printError("输入不能为空，请重新输入！");
    }
}

/**
 * @brief 彩色输出
 * @param text 文本
 * @param color 颜色代码
 */
void printColored(const char *text, const char *color)
{
    printf("%s%s%s", color, text, COLOR_RESET);
}

/**
 * @brief 成功消息
 * @param message 消息
 */
void printSuccess(const char *message)
{
    printColored(message, COLOR_GREEN);
    printf("\n");
}

/**
 * @brief 错误消息
 * @param message 消息
 */
void printError(const char *message)
{
    printColored(message, COLOR_RED);
    printf("\n");
}

/**
 * @brief 警告消息
 * @param message 消息
 */
void printWarning(const char *message)
{
    printColored(message, COLOR_YELLOW);
    printf("\n");
}

/**
 * @brief 信息消息
 * @param message 消息
 */
void printInfo(const char *message)
{
    printColored(message, COLOR_CYAN);
    printf("\n");
}

/**
 * @brief 初始化系统
 * @return 成功返回true，否则返回false
 */
bool initializeSystem()
{
    // 创建数据目录
    if (!createDataDirectories())
    {
        return false;
    }

    // 加载用户数据
    loadUsersFromFile();

    // 加载学生数据
    loadStudentsFromFile();

    systemInitialized = true;
    return true;
}

/**
 * @brief 创建数据目录
 * @return 成功返回true，否则返回false
 */
bool createDataDirectories()
{
    if (!createDirectory("data"))
    {
        return false;
    }

    if (!createDirectory(BACKUP_DIR))
    {
        return false;
    }

    return true;
}

/**
 * @brief 清理系统资源
 */
void cleanupSystem()
{
    // 保存数据
    if (dataModified)
    {
        saveStudentsToFile();
        saveUsersToFile();
    }

    systemInitialized = false;
}