/**
 * @file math_utils.c
 * @brief 数学计算工具函数实现文件
 * @note 实现数学计算相关函数
 */

#include "math_utils.h"

/**
 * @brief 计算平均值
 * @details 计算浮点数数组的算术平均值
 *          遍历数组求和，然后除以元素个数
 * @param scores 浮点数数组
 * @param count 数组元素个数
 * @return 返回数组的平均值，如果count为0返回0.0
 * @note 如果count为0，函数返回0.0避免除零错误
 * @warning 如果scores为NULL且count>0，可能导致程序崩溃
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