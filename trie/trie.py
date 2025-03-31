class CIDRTrie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, cidr):
        # 解析CIDR
        ip_str, prefix_len = cidr.split("/")
        prefix_len = int(prefix_len)
        ip_bytes = list(map(int, ip_str.split(".")))

        # 转换为二进制位序列（32位）
        binary_str = "".join(f"{byte:08b}" for byte in ip_bytes)
        binary_str = binary_str[:prefix_len]

        # 逐层插入到Trie树
        node = self.root
        for i in range(0, len(binary_str), 8):
            byte_bits = binary_str[i:i+8].ljust(8, '0')
            byte = int(byte_bits, 2)
            if byte not in node.children:
                new_node = TrieNode()
                new_node.parent = node
                node.children[byte] = new_node
            node = node.children[byte]

        # 标记当前节点掩码长度
        node.prefix_len = prefix_len

    def contains(self, ip):
        # 解析IP地址
        ip_bytes = list(map(int, ip.split(".")))

        # 转换为二进制位序列（32位）
        binary_str = "".join(f"{byte:08b}" for byte in ip_bytes)

        # 从根节点开始遍历
        node = self.root
        for i in range(0, 32, 8):
            byte_bits = binary_str[i:i+8]
            byte = int(byte_bits, 2)
            if byte not in node.children:
                # 未找到匹配路径，返回False
                return False
            node = node.children[byte]

        # 遍历完成后，检查当前节点的掩码长度
        if node.prefix_len is not None:
            # 计算IP地址的网络地址
            network_address = self._get_network_address(ip, node.prefix_len)
            # 检查IP地址是否属于该CIDR块
            return network_address == self._get_network_address(ip, node.prefix_len)
        else:
            return False

    def _get_network_address(self, ip, prefix_len):
        # 计算IP地址的网络地址
        ip_bytes = list(map(int, ip.split(".")))
        binary_str = "".join(f"{byte:08b}" for byte in ip_bytes)
        network_bits = binary_str[:prefix_len] + "0" * (32 - prefix_len)
        network_octets = [network_bits[i:i+8] for i in range(0, 32, 8)]
        network_address = ".".join(str(int(octet, 2)) for octet in network_octets)
        return network_address



trie = CIDRTrie()
trie.insert("192.168.1.0/24")
trie.insert("192.168.1.128/25")
trie.insert("10.0.0.0/16")


# 测试查询
print(trie.contains("192.168.1.100"))  # 输出：True
print(trie.contains("192.168.2.100"))  # 输出：False
print(trie.contains("10.0.1.100"))    # 输出：True
print(trie.contains("10.1.1.100"))    # 输出：False