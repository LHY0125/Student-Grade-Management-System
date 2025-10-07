/**
 * @file security_utils.c
 * @brief 安全工具函数实现文件
 * @note 实现密码哈希、验证等安全相关功能
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "security_utils.h"

// SHA-256常量
static const uint32_t k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// 右旋转函数
#define ROTR(n,x) (((x) >> (n)) | ((x) << (32 - (n))))

// SHA-256辅助函数
#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTR(2,x) ^ ROTR(13,x) ^ ROTR(22,x))
#define EP1(x) (ROTR(6,x) ^ ROTR(11,x) ^ ROTR(25,x))
#define SIG0(x) (ROTR(7,x) ^ ROTR(18,x) ^ ((x) >> 3))
#define SIG1(x) (ROTR(17,x) ^ ROTR(19,x) ^ ((x) >> 10))

/**
 * @brief SHA-256哈希计算核心函数
 * @param data 输入数据
 * @param len 数据长度
 * @param hash 输出哈希值（32字节）
 */
static void sha256_compute(const uint8_t *data, size_t len, uint8_t *hash)
{
    uint32_t h[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
    
    size_t new_len = len + 1;
    while (new_len % 64 != 56) {
        new_len++;
    }
    new_len += 8;
    
    uint8_t *msg = calloc(new_len, 1);
    if (!msg) return;
    
    memcpy(msg, data, len);
    msg[len] = 0x80;
    
    uint64_t bits_len = len * 8;
    for (int i = 0; i < 8; i++) {
        msg[new_len - 1 - i] = (bits_len >> (i * 8)) & 0xff;
    }
    
    for (size_t chunk = 0; chunk < new_len; chunk += 64) {
        uint32_t w[64];
        
        for (int i = 0; i < 16; i++) {
            w[i] = (msg[chunk + i * 4] << 24) |
                   (msg[chunk + i * 4 + 1] << 16) |
                   (msg[chunk + i * 4 + 2] << 8) |
                   (msg[chunk + i * 4 + 3]);
        }
        
        for (int i = 16; i < 64; i++) {
            w[i] = SIG1(w[i - 2]) + w[i - 7] + SIG0(w[i - 15]) + w[i - 16];
        }
        
        uint32_t a = h[0], b = h[1], c = h[2], d = h[3];
        uint32_t e = h[4], f = h[5], g = h[6], h_val = h[7];
        
        for (int i = 0; i < 64; i++) {
            uint32_t t1 = h_val + EP1(e) + CH(e, f, g) + k[i] + w[i];
            uint32_t t2 = EP0(a) + MAJ(a, b, c);
            h_val = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
        }
        
        h[0] += a; h[1] += b; h[2] += c; h[3] += d;
        h[4] += e; h[5] += f; h[6] += g; h[7] += h_val;
    }
    
    for (int i = 0; i < 8; i++) {
        hash[i * 4] = (h[i] >> 24) & 0xff;
        hash[i * 4 + 1] = (h[i] >> 16) & 0xff;
        hash[i * 4 + 2] = (h[i] >> 8) & 0xff;
        hash[i * 4 + 3] = h[i] & 0xff;
    }
    
    free(msg);
}

/**
 * @brief 计算字符串的SHA-256哈希值
 * @param input 输入字符串
 * @param output 输出缓冲区，至少需要SHA256_HEX_LENGTH字节
 */
void sha256_hash(const char *input, char *output)
{
    if (!input || !output) return;
    
    uint8_t hash[SHA256_DIGEST_LENGTH];
    sha256_compute((const uint8_t *)input, strlen(input), hash);
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        snprintf(output + i * 2, 3, "%02x", hash[i]);
    }
    output[SHA256_HEX_LENGTH - 1] = '\0';
}

/**
 * @brief 验证密码是否匹配哈希值
 * @param password 明文密码
 * @param hash 存储的哈希值
 * @return 匹配返回1，不匹配返回0
 */
int verify_password(const char *password, const char *hash)
{
    if (!password || !hash) return 0;
    
    char computed_hash[SHA256_HEX_LENGTH];
    sha256_hash(password, computed_hash);
    
    return strcmp(computed_hash, hash) == 0;
}

/**
 * @brief 生成密码哈希值
 * @param password 明文密码
 * @param hash_output 输出缓冲区，至少需要SHA256_HEX_LENGTH字节
 */
void hash_password(const char *password, char *hash_output)
{
    sha256_hash(password, hash_output);
}

/**
 * @brief 安全地清除内存中的敏感数据
 * @param ptr 指向敏感数据的指针
 * @param size 数据大小
 */
void secure_memset(void *ptr, size_t size)
{
    if (ptr) {
        volatile char *p = (volatile char *)ptr;
        while (size--) {
            *p++ = 0;
        }
    }
}