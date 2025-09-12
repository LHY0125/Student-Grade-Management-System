/**
 * @file io_utils.c
 * @brief 输入输出工具函数实现文件
 * @note 实现界面显示、用户输入等相关函数
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifdef _WIN32
#include <conio.h>
#endif

#include "io_utils.h"
#include "config.h"
#include "string_utils.h"

/**
 * @brief 清理输入缓冲区
 * @details 清除标准输入流中的所有剩余字符，直到遇到换行符或文件结束符
 *          主要用于防止输入缓冲区中的残留字符影响后续输入操作
 * @note 在使用scanf等函数后调用此函数可以避免输入问题
 */
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/**
 * @brief 暂停系统，等待用户按键
 * @details 显示提示信息并等待用户按下任意键后继续执行
 *          在Windows系统下使用_getch()函数，在其他系统下使用getchar()函数
 * @note 用于在菜单操作完成后暂停，让用户有时间查看结果
 * @warning 在非Windows系统下需要按回车键才能继续
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
 * @details 根据操作系统类型调用相应的清屏命令
 *          Windows系统使用"cls"命令，其他系统使用"clear"命令
 * @note 用于清除终端屏幕内容，提供更好的用户界面体验
 * @warning 依赖于系统命令，在某些受限环境下可能无法正常工作
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
 * @details 输出一行由等号组成的分隔线，用于美化界面显示
 * @note 分隔线长度为40个字符，用于分隔不同的界面区域
 */
void printSeparator()
{
    printf("========================================\n");
}

/**
 * @brief 打印标题头
 * @details 以美观的格式显示标题，标题上下各有一条分隔线
 * @param title 要显示的标题文本，不能为NULL
 * @note 标题会居中显示，前面有10个空格的缩进
 * @warning 如果title为NULL，可能导致程序崩溃
 */
void printHeader(const char *title)
{
    printSeparator();
    printf("          %s\n", title);
    printSeparator();
}

/**
 * @brief 安全输入整数
 * @details 提供安全的整数输入功能，包含范围验证和错误处理
 *          使用fgets和sscanf组合避免缓冲区溢出，循环直到获得有效输入
 * @param prompt 显示给用户的提示信息
 * @param min 允许输入的最小值（包含）
 * @param max 允许输入的最大值（包含）
 * @return 返回用户输入的有效整数
 * @note 函数会一直循环直到用户输入有效的整数
 * @note 自动显示输入范围提示
 * @warning 如果prompt为NULL，printf可能出现问题
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
 * @details 提供安全的浮点数输入功能，包含范围验证和错误处理
 *          使用fgets和sscanf组合避免缓冲区溢出，循环直到获得有效输入
 * @param prompt 显示给用户的提示信息
 * @param min 允许输入的最小值（包含）
 * @param max 允许输入的最大值（包含）
 * @return 返回用户输入的有效浮点数
 * @note 函数会一直循环直到用户输入有效的浮点数
 * @note 自动显示输入范围提示，精度为小数点后1位
 * @warning 如果prompt为NULL，printf可能出现问题
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
 * @details 提供安全的字符串输入功能，包含空值检查和自动去除首尾空格
 *          使用fgets避免缓冲区溢出，自动移除换行符并处理空白字符
 * @param prompt 显示给用户的提示信息
 * @param buffer 存储输入字符串的缓冲区
 * @param maxLen 缓冲区的最大长度（包含终止符）
 * @note 函数会一直循环直到用户输入非空字符串
 * @note 自动移除输入字符串的首尾空白字符
 * @warning 如果buffer为NULL或maxLen<=0，可能导致程序崩溃
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
 * @details 使用ANSI转义序列在终端中输出彩色文本
 *          输出格式为：颜色代码 + 文本 + 重置代码
 * @param text 要输出的文本内容
 * @param color ANSI颜色代码字符串（如COLOR_RED、COLOR_GREEN等）
 * @note 输出后会自动重置颜色为默认值
 * @warning 如果终端不支持ANSI转义序列，可能显示乱码
 */
void printColored(const char *text, const char *color)
{
    printf("%s%s%s", color, text, COLOR_RESET);
}

/**
 * @brief 成功消息
 * @details 以绿色显示成功消息，用于提示操作成功完成
 * @param message 要显示的成功消息文本
 * @note 消息会以绿色显示，并在末尾自动添加换行符
 */
void printSuccess(const char *message)
{
    printColored(message, COLOR_GREEN);
    printf("\n");
}

/**
 * @brief 错误消息
 * @details 以红色显示错误消息，用于提示操作失败或出现错误
 * @param message 要显示的错误消息文本
 * @note 消息会以红色显示，并在末尾自动添加换行符
 */
void printError(const char *message)
{
    printColored(message, COLOR_RED);
    printf("\n");
}

/**
 * @brief 警告消息
 * @details 以黄色显示警告消息，用于提示需要注意的情况
 * @param message 要显示的警告消息文本
 * @note 消息会以黄色显示，并在末尾自动添加换行符
 */
void printWarning(const char *message)
{
    printColored(message, COLOR_YELLOW);
    printf("\n");
}

/**
 * @brief 信息消息
 * @details 以青色显示信息消息，用于提示一般性信息
 * @param message 要显示的信息消息文本
 * @note 消息会以青色显示，并在末尾自动添加换行符
 */
void printInfo(const char *message)
{
    printColored(message, COLOR_CYAN);
    printf("\n");
}

/**
 * @brief 安全输入单个字符
 * @details 提供安全的字符输入功能，避免缓冲区溢出
 * @param prompt 显示给用户的提示信息
 * @return 返回用户输入的字符
 * @note 自动清理输入缓冲区
 */
char safeInputChar(const char *prompt)
{
    char buffer[10];
    char result;
    
    while (1)
    {
        printf("%s: ", prompt);
        
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            // 移除换行符
            buffer[strcspn(buffer, "\n")] = '\0';
            trimString(buffer);
            
            if (strlen(buffer) == 1)
            {
                result = buffer[0];
                return result;
            }
        }
        
        printError("请输入单个字符！");
    }
}