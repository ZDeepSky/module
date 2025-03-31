#include <iostream>
#include <vector>
#include <string>
#include <arpa/inet.h>

using namespace std;

// IPv4 字符串转 32 位整数（主机字节序）
uint32_t ip_to_uint(const string& ip) {
    struct in_addr addr;
    if (inet_pton(AF_INET, ip.c_str(), &addr) != 1) {
        throw invalid_argument("Invalid IPv4 address");
    }
    return ntohl(addr.s_addr);
}

// 32 位整数转 IPv4 字符串
string uint_to_ip(uint32_t ip) {
    struct in_addr addr;
    addr.s_addr = htonl(ip);
    char buf[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &addr, buf, INET_ADDRSTRLEN) == nullptr) {
        throw runtime_error("Error converting uint to IP");
    }
    return string(buf);
}

// 核心算法：从最大掩码开始递减，找到覆盖当前地址的最大块
vector<string> range_to_cidr(uint32_t start, uint32_t end) {
    vector<string> cidrs;
    while (start <= end) {
        // 当前起始地址的最长后缀零位数
        int suffix_zero = 0;
        uint32_t temp = start;
        // while ((temp & 1) == 0 && temp != 0) {
        //     temp >>= 1;
        //     suffix_zero++;
        // }

        // 从最大掩码（最小块）开始尝试
        //计算掩码范围内的最大最小
        int mask = 32;
        uint32_t max_block = 0;
        printf("suffix_zero = 0x%x\r\n", suffix_zero);
        for (; mask >= 0; mask--) {
            uint32_t maxtemp = (0xffffffff);
            uint32_t current_min = start & (maxtemp<<(32-mask));
            uint32_t current_max = start | (~(maxtemp<<(32-mask)));
            // uint32_t block_size = 1 << (32 - mask);
            // uint32_t current_max = start + block_size - 1;
            printf("mask = 0x%x\r\n", mask);
            printf("current_min = 0x%x\r\n", current_min);
            printf("current_max = 0x%x\r\n", current_max);
            if ((current_max <= end) && (current_min>= start) ) {
                max_block = current_max;
            }
            else{
                printf("end\r\n");
                break;
            }
        }

        // 记录 CIDR 块
        cidrs.push_back(uint_to_ip(start) + "/" + to_string(mask+1));
        start = max_block + 1; // 处理下一个地址
    }
    return cidrs;
}

// 输入起始和结束 IP，输出 CIDR 列表
vector<string> range_to_cidr(const string& start_ip, const string& end_ip) {
    uint32_t start = ip_to_uint(start_ip);
    uint32_t end = ip_to_uint(end_ip);
    if (start > end) return {};
    return range_to_cidr(start, end);
}

int main() {
    auto cidrs = range_to_cidr("192.168.1.2", "192.168.1.7");
    for (const auto& cidr : cidrs) {
        cout << cidr << endl;
    }



    char test1 = 0xff<<2;
    printf("test1 = %0x\r\n",test1);
    printf("test2 = %0x\r\n",~test1);
    return 0;
}