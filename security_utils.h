/**
 * @file security_utils.h
 * @brief 安全工具函数头文件
 * @note 提供密码哈希、验证等安全相关功能
 */

#ifndef SECURITY_UTILS_H
#define SECURITY_UTILS_H

#include <stdint.h>
#include "config.h"

// SHA-256哈希长度定义
#define SHA256_DIGEST_LENGTH 32
#define SHA256_HEX_LENGTH 65  // 64字符 + 1个终止符

/**
 * @brief 计算字符串的SHA-256哈希值
 * @param input 输入字符串
 * @param output 输出缓冲区，至少需要SHA256_HEX_LENGTH字节
 * @note 输出为64位十六进制字符串
 */
void sha256_hash(const char *input, char *output);

/**
 * @brief 验证密码是否匹配哈希值
 * @param password 明文密码
 * @param hash 存储的哈希值
 * @return 匹配返回1，不匹配返回0
 */
int verify_password(const char *password, const char *hash);

/**
 * @brief 生成密码哈希值
 * @param password 明文密码
 * @param hash_output 输出缓冲区，至少需要SHA256_HEX_LENGTH字节
 */
void hash_password(const char *password, char *hash_output);

/**
 * @brief 安全地清除内存中的敏感数据
 * @param ptr 指向敏感数据的指针
 * @param size 数据大小
 */
void secure_memset(void *ptr, size_t size);

#endif // SECURITY_UTILS_H