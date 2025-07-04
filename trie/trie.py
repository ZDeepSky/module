class TrieNode:
    __slots__ = ('children', 'prefix_len')  # 优化内存
    def __init__(self):
        self.children = {}  # 子节点字典，键为整数(0-255)
        self.prefix_len = None  # 当前节点表示的前缀长度

class CIDRTrie:
    def __init__(self):
        self.root = TrieNode()

    def _ip_to_int(self, ip):
        """将IP地址转换为32位整数"""
        b1, b2, b3, b4 = map(int, ip.split('.'))
        return (b1 << 24) | (b2 << 16) | (b3 << 8) | b4

    def _int_to_ip(self, n):
        """将32位整数转换为IP地址"""
        return f"{(n >> 24) & 0xFF}.{(n >> 16) & 0xFF}.{(n >> 8) & 0xFF}.{n & 0xFF}"

    def _range_to_cidr(self, start, end):
        cidrs = []
        end_net = end
        start_net = start
        max_net = start_net
        while start_net <= end_net:
            # 计算当前起始地址的尾部0的个数
            mask = 32
            while mask > 0:
                # 计算当前掩码对应的网络地址

                min_net = start_net & (0xFFFFFFFF << (32 - mask))
                max_temp_net = min_net | ((1 << (32 - mask)) - 1)#-1之后就生成了 fffff
                print(f"{max_temp_net}, {end_net}")
                if max_temp_net <= end_net:
                    # 如果当前掩码的网络地址小于结束地址，则继续减小掩码
                    max_net = max_temp_net
                    mask -= 1
                    continue
                else:
                    cidr = self._int_to_ip(min_net) + '/' + str(mask+1)
                    cidrs.append(cidr)
                    start_net = max_net + 1  # 更新起始地址到下一个网络地址
                    break
        return cidrs


    def insert(self, cidr):
        # 解析CIDR
        ip_str, prefix_ori_len = cidr.split("/")
        prefix_len =  int(prefix_ori_len)
        ip_bytes = list(map(int, ip_str.split(".")))
        print(f"{prefix_len}")
        # 转换为二进制位序列（32位）
        node = self.root
        for byte in ip_bytes:
            if prefix_len <= 0:
                break
            if byte < 0 or byte > 255:
                raise ValueError("IP地址的每个字节必须在0到255之间")
            if byte not in node.children:
                new_node = TrieNode()
                node.children[byte] = new_node
            # 更新前缀长度
            prefix_len -= 8  # 每个字节减少8位
            node = node.children[byte]

        # 标记当前节点掩码长度
        node.prefix_len = int(prefix_len+8)

    def insert_range(self, startIp, endIp):
    #     # 解析起始和结束IP地址
        start_int = self._ip_to_int(startIp)
        end_int = self._ip_to_int(endIp)
        # 检查IP地址范围的合法性
        if start_int > end_int:
            raise ValueError("起始IP地址必须小于或等于结束IP地址")

        # 将范围转换为CIDR块列表
        cidrs = self._range_to_cidr(start_int, end_int)

        # 插入每个CIDR块到Trie树中
        for cidr in cidrs:
            self.insert(cidr)

    def contains_bite(self, byte, node):
        for mask in range(7, -1, -1):
            byte_temp = byte & (1 << mask)
            if byte_temp in node.children:
                node = node.children[byte_temp]
                if node.prefix_len is not None and node.prefix_len == mask:
                    return True
        return False

    def contains(self, ip):
        """判断IP是否属于Trie树中存储的任何CIDR范围"""
        # 解析IP为32位整数
        try:
            parts = list(map(int, ip.split('.')))
            if len(parts) != 4:
                raise ValueError("无效的IPv4地址")
            ip_int = (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8) | parts[3]
        except ValueError as e:
            raise ValueError("无效的IP地址格式") from e

        node = self.root
        for byte in parts:
            if byte < 0 or byte > 255:
                raise ValueError("IP地址的每个字节必须在0到255之间")
            if byte in node.children:
                node = node.children[byte]
                continue

            if self.contains_bite(byte, node):
                return True

        return False

    def print_trie(self):
        print(f"begin$$$$$$$$$$")
        def _print_node(node, prefix, layer):
            new_layer = layer
            if node.prefix_len is not None:
                print(f"{prefix}/{node.prefix_len+new_layer*8}")
            for byte, child in node.children.items():
                print(f"{byte}")
                _print_node(child, prefix + f".{byte}" if prefix else str(byte), new_layer+1)


        _print_node(self.root, "", -1)


trie = CIDRTrie()
trie.insert("192.168.1.0/24")
trie.insert("192.168.1.128/25")
trie.insert("10.0.0.0/15")
trie.insert_range("192.168.2.0", "192.168.2.100")
trie.print_trie()

# 测试查询
# print(trie.contains("192.168.1.100"))  # 输出：True
# print(trie.contains("192.168.2.100"))  # 输出：False
print(trie.contains("10.1.0.0"))    # 输出：True
# print(trie.contains("10.1.1.100"))    # 输出：False