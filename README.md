# 简单文件系统实现

用100M的文件模拟了一个文件系统。

支持以下功能：

多用户、多级目录、用户登录、权限控制和读写保护等。

文件/目录创建/删除，目录显示，文件打开/读/写/关闭等基本功能。

# 整体设计

​    对于文件系统的整体设计思路如下：

**模拟文件系统分为四层**：

1、块管理层：负责块的分配/回收、块的读/写等，由超级快(superblock)的数据结构实现。

2、文件控制块层：文件系统目录功能，目录文件由目录(dentry)配合inode的数据结构实现。

3、文件管理层：文件操作由file数据结构实现。

4、命令解释层，实现多种命令对上述底层文件与接口的映射。

**申请一个100MB的文件，模拟文件系统的存储空间就是该文件的存储空间。**将文件分块，用位示图的方法管理文件块。块的大小为$1KB$，并且用$0$号块做管理块，前面$1$~$13$号块做位示图。

由于每一个二进制位管理了一个$1KB$的块是否被使用，总共有

$$100MB/1KB=1024000$$

个块。$1024000/8/1024 ≈ 13$，得出需要的管理块的数量为$13$。也就是说，从第一块开始的前$13$个二进制位永远是1(因为它们要一直被占用)。

使用$Unix$经典思想中的索引结构的思想来简历块与目录之间的索引。对于文件中的数据块，和inode的存放，都是对$100MB$的文件进行操作的。本文建立了一个经济的策略：在申请inode存储空间时，从第$14$块开始遍历找到一个未被利用完的块(利用的空间不足1KB)进行申请。当申请文件的数据块时，从第$1023999$块(最后一块)开始从后往前遍历，对于文件的数据块，每一次分配都分配一个整块，记录文件对此块占用的实际大小。示意图如下图$5.1$：

| SB_0 | BM_0    | BM_1    | BM_2    | BM_3 | BM_4 | BM_5 | BM_6 | BM_7 | BM_8 |
| ------ | --------- | --------- | --------- | ------ | ------ | ------ | ------ | ------ | ------ |
| BM_9 | BM_{10} | BM_{11} | BM_{12} | IN_0 | IN_1 | IN_2 | …      |        |        |
|        |           |           |           |        |        |        |        |        |        |
|        |           |           |           |        |        |        |        |        |        |
|        |           |           |           |        |        |        |        |        |        |
|        |           |           |           |        |        |        |        |        |        |
|        |           |           |           |        |        |        |        |        |        |
|        |           |           |           |        |        |        |        |        |        |
|        |           |           |           |        |        |        |        |        |        |
|        |           |           |           |        |        | …      | DB_2 | DB_1 | DB_0 |

<center>块管理图</center>

(其中，$SB0​$位$super block_0​$，存储了超级块的信息，$BM_0​$~$BM_{12}​$为$13​$个位示图管理块，$IN_x​$存放的是$i​$节点的信息，注意：一个块可以存放多个i节点，$DB​$为$Data block​$，一个块只存一个信息)

## Super Block Data Structure

```C
struct super_block {

    unsigned long s_blocknumbers;   // 块的总数量

    unsigned long s_blocksize;      // 块的大小

    void *s_bdev;       // 存储块

    int s_bitmap_blks;  // 位示图的块数量

};
```

​    超级块是主要进行块管理的数据，超级块的数据结构包含了块的总数量，在实例化过程中，块的总数量为$1024000$块，块的大小为$1024B$，即$1024KB$，存储块成员变量指向$100MB$的空间，用`void*`指针的原因是方便进行类型转换。最后一个成员函数是位示图的块的数量，就像前文分析的那样，在这里这个值等于$13$。

## Super Block Operations

```C
struct super_block *init_block(struct dentry *root);    //初始化超级块

struct super_block *free_block(struct super_block *sb); //释放超级块

bool save_block(struct super_block *sb);                //保存块到文件

struct super_block *load_block(struct dentry *root);    //从文件读取块

struct inode *alloc_inode(struct super_block *sb);      //分配i节点

bool occupy_block(blkcnt_t blk_no, struct super_block *sb); //位示图修改 占用

bool release_block(blkcnt_t blk_no, struct super_block *sb);//位示图修改 释放

void *free_block_for_inode(struct super_block *sb, struct inode *inode); //释放i节点

unsigned long alloc_data_block(struct super_block *sb); //为数据文件分配块

void free_data_block(unsigned long blk_no, struct super_block *sb); //释放为数据文件分配的块

size_t write_block(struct super_block *sb, unsigned long block_no, char *stream, size_t size);  // 对块进行写操作

size_t read_block(struct super_block *sb, unsigned long block_no, char *stream, size_t size);   // 对块进行读操作
```

​    对于超级块的操作，主要分以下几对，首先是超级块的初始化和超级块的释放，超级块的初始化表示了超级块的格式化过程，具体来说就是动态申请$100MB$的空间，并将位示图初始化，用第$0$块存放超级块数据结构的信息，$1$~$13$块存放位示图，超级块的释放即将内存释放置空。

​       接着是超级块与文件的连接，由于块是用动态申请的$100MB$内存模拟的，所以将其信息存放在一个$100MB$大小的文件中。

​       接着是分配$i$节点与释放$i$节点,由于对$i$节点的分配与释放也是通过对内存进行修改完成的,所以$i$节点的释放与分配也是超级块应尽的责任。

​       配套$i$节点分配与释放的，需要对位示图进行修改和释放的函数，这个函数主要是修改位示图中管理某一块的位操作，本文另外在辅助函数中定义了判断当前块是否被占用，占用了多少空间等函数，详见附录。

​       接下来，还要考虑块对于文件数据块的支持，由于文件数据块与$i​$节点的分配方式是不同的(前者是从后往前遍历一个空闲块，后者是从前往后遍历一个没有被用完的块)，所以对数据块的申请与释放单独设计了两个函数。

​       最后，为了支持文件对数据块进行读写，增加了write_block和read_block两个函数，参数是参照Linux系统的write和read进行设计的。

## Inode Data Structure

```C
struct inode {

    struct super_block *i_sb;   // 节点对应的超级块

    struct blk_lists *i_list;   // i节点所对应的块链表

    unsigned long i_nlink;      // i节点被硬链接的数量

    unsigned long i_no;         // i节点的编号

    unsigned long i_uid;        // i节点所属的用户的id

    blkcnt_t i_blocks;          // i节点占用的块数量

    unsigned long i_btyes;      // i节点的大小，以Byte为单位

    u_mode_t mode;              // 模式

};
```

​    $i$节点的数据结构由以上部分组成。由于一个系统中可能有多个超级块，所以此处添加了$i$节点的超级块成员函数，实际使用时只用到了一个超级块。​$i$节点所对应的块链表表示i节点所占的块。后续的一些成员如注释所示。最后的成员$mode$表现了$inode$所处的模式，用于权限控制，详情可见后文对用户和权限控制的说明。

## Inode Operations

```C
void get_inode_memory_by_num(struct inode *inode, struct super_block *sb);  // 根据i节点的序号得到i节点

void put_inode_memory_by_num(struct inode *inode, struct super_block *sb);  // 根据i节点的序号写入i节点的信息

bool test_block_free_by_inode_num(unsigned long inode_num, struct super_block *sb); // 查询i节点号所对应的块是否空闲

void fill_block_by_inode_num(unsigned long inode_num, struct super_block *sb);  // 写位示图
```

​    由于i节点不能离开目录项和块操作而单独存在，所以专门对i节点的操作是不多的，此处对i节点的操作主要是从块中读出i节点的信息，以及将i节点的信息修改入块，后两个函数是用来检测是否存储出现了问题，通过测试i节点对应的块是否为空闲得到读取内容是否与之前存储的不一致，或者读错文件等问题。

## Dentry Structure

``` C
struct dentry {
     char type;                  // 目录项的类型
     struct inode *d_inode;      // 对应的i节点
     struct dir_hash_table *subdirs[**HASH_TABLE_ROW**]; // 子目录hash表
     struct tm *d_time;          // 创建的时间
     struct super_block *d_sb;   // 对应的超级块
     struct dentry *parent;      // 父目录
     char d_iname[**DNAME_LEN**];    // 目录项的名称
 };
```

目录项包含的第一个成员type表示了目录项的类型，本文支持的类型有l：硬链接，d：目录，f：普通文件。每个目录项都包含了自己的子目录，子目录是一个hash表，详情可见后文的存储数据结构设计。为了方便整个文件树的互相访问，设计了父目录成员函数。

## Dentry Operations

```C
bool save_entry(struct dentry *root, struct super_block *sb);   // 保存目录项到文件

bool load_entry(struct dentry *root, struct super_block *sb);   // 从文件读取目录项

struct dir_hash_table *d_hash(struct dentry *dentry);           // 计算目录项的hash值

void hash_table_insert(struct dentry *dentry, struct dentry *sub_dentry);   // 插入目录项到哈希表

void hash_table_delete(struct dentry *dentry, struct dentry *sub_dentry);   // 从哈希表删除目录项

struct dentry *search_by_str(struct dentry *current_dentry, const char *dname); // 查询hash表

void packet_user_dlist(dlist *dl, struct user_linked_list *head, struct dentry *root);  // 将目录项与用户名对应

struct dentry *change_home_dir(dlist *dl, struct usr_ptr *current_user);    // 改变当前路径

void get_current_path_str(struct dentry *dentry, char *str);    // 得到当前的路径

void travel_dentry(queue *q, slist *str_list, struct dentry *begin_dentry, size_t num); // 遍历目录项
```

主要需要说明的是，由于子目录是利用哈希表存储的，所以目录项操作中有许多与哈希表相关的，包括计算哈希值，插入，删除等，它们都是通过调用基本的hash函数来实现的。

​       由于文件操作的难度过大，需要动态监测键盘上下左右、backspace键等，所以本文的设计仅仅是一个非常原始的文件打开和读写操作。利用了目录项和i节点的索引操作和超级块中对块的读写操作对文件进行简单地读写。

## Auxiliary Data Structures and Operations

​    本次实验用于辅助存储与操作的数据结构有基本链表、双向队列以及哈希链表等，由于基本链表很常见，下面只对双向队列与哈希链表进行说明。

### 双向队列

```C
typedef struct _queue_node {
    qtype val;                  // value of the node
    int aux;                    // auxiliary info
    struct _queue_node *next;   // next the node
}qnode;
queue *init_queue(void); // 初始化队列，分配内存
queue *free_queue(queue **q); // 销毁队列，回收 
qtype get_front_queue(const queue *q); // 得到队列的第一个元素
qtype get_rear_queue(const queue *q); // 得到队列的最后一个元素
bool queue_empty(const queue *q); // 判断队列是否为空
bool enqueue(qtype item, queue *q); // 入队列
qtype dequeue(queue *q); // 出队列
qtype dequeue_rear(queue *q); // 获得队列的尾部
size_t get_size_of_queue(const queue *q); // 获得队列的大小 
void print_queue(const queue *q); // 输出队列元素，用于双向队列主要来解决遍历哈希表，解析路径名等操作。
```

​    双向队列主要来解决遍历哈希表，解析路径名等操作。

### 用链表解决冲突的哈希表设计

​    本文设计了一个哈希表的数据结构用于保存一个目录项的子目录，方便快速查找。对于一个目录项的文件名，首先将其ASCII码想加，得到一个哈希值，然后用它对10的余数作为哈希表的入口，解决冲突的方法是用链表将结果链起来。

```C
struct dir_hash_table {

    int hash_key;       // 哈希值

    char *dname;        // 目录名

    struct dentry *corres_dentry;   // 相对应的目录

    struct dir_hash_table *next;    // 链表元素

};
```

哈希表的操作都与目录项操作有关。

# 用户名与优先级

支持的用户类别与优先级别如下

| **优先级** | **用户类别**    | **备注**         |
| ---------- | --------------- | ---------------- |
| **0**      | 根用户root      | 每个系统只有一个 |
| **1**      | 管理员用户admin | 可以有多个       |
| **2**      | 访客用户guest   | 需要验证密码     |

用户名与密码存储在./data/user_info.txt中，默认内容如下

| **用户编号** | **用户名** | **密码**   | 优先级 |
| ------------ | ---------- | ---------- | ------ |
| **0**        | root       | root123456 | 0      |
| **1**        | cat        | cat123456  | 1      |
| **2**        | dog        | dog123456  | 1      |
| **3**        | lion       | lion123456 | 1      |
| **4**        | guest      | none       | 2      |

ls -l的第一列显示的权限信息，如下图。(不同于Linux的user、group和所有用户，本系统中rwxrwxrwx分别表示了第0级用户，第1级用户和第2级用户的权限)。

![image-20190326190354561](/Users/yongxinxu/Library/Application Support/typora-user-images/image-20190326190354561.png)

# 支持的指令

| **指令名称** | **功能**           | **扩展**        |
| ------------ | ------------------ | --------------- |
| **shutdown** | 保存并关闭文件系统 | 无              |
| **su**       | 切换当前用户       | 无              |
| **ls**       | 展示当前的目录     | -R递归   -l具体 |
| **rename**   | 修改文件名         | 无              |
| **rm**       | 删除文件/目录      | 无              |
| **mkdir**    | 创建目录           | 无              |
| **chmod**    | 修改权限           | 无              |
| **cd**       | 更改当前目录       | 无              |
| **edit**     | 编辑文件           | 无              |
| **clear**    | 清空显示屏         | 无              |
| **cat**      | 输出当前文件内容   | 无              |

# 注意

本系统主要在于对目录文件的架构。数据文件的输入比较简单，只能edit输入字符串后，按enter保存。 

本文件系统非常简易，设计有诸多不符合现代文件系统指出，还请见谅！

数据文件的保存有一点问题，还没有设计完成。目录文件无误。



