#include "include/env.h"
/**
 * 给定一个字符串 s 和一些长度相同的单词 words。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。
 *
 * 注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。
 *
 *
 *
 * 示例 1：
 *
 * 输入：
 *   s = "barfoothefoobarman",
 *   words = ["foo","bar"]
 * 输出：[0,9]
 * 解释：
 * 从索引 0 和 9 开始的子串分别是 "barfoor" 和 "foobar" 。
 * 输出的顺序不重要, [9,0] 也是有效答案。
 * 示例 2：
 *
 * 输入：
 *   s = "wordgoodgoodgoodbestword",
 *   words = ["word","good","best","word"]
 * 输出：[]
 *
 * @author foxleezh
 * @date 2019-03-18.
 */


typedef struct Node_Class Node;

typedef struct HashMap_Class HashMap;

struct Node_Class {
	char* key;
	int value;
	struct Node_Class *next;
};


struct HashMap_Class
{
	int threshold; //桶个数
	struct Node_Class** table; //桶列表
};

/*
 * 初始化HashMap
 * @initialCapacity 初始容量，也就是HashMap中桶的个数，一般为 (预估最大个数)/0.75f+1
 */
static void HashMap_Init(HashMap* map, int initialCapacity) {
	int threshold = 1;
	//自动填充为大于initialCapacity的2的倍数值
	while (threshold < initialCapacity)
		threshold <<= 1;
	map->threshold = threshold;
	Node** table = malloc(sizeof(Node)*threshold);
	memset(table, 0, sizeof(Node) * threshold);
	map->table = table;
}

/*
 * HashMap的Hash值计算，采用ELFhash 
 *
 */
static unsigned int HashMap_HashCode(HashMap* map, char* key) {
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;

	while (*key)
	{
		hash = hash * a + (*key++);
		a *= b;
	}

	return (hash & 0x7FFFFFFF);
}

/*
 * HashMap的put方法，首先将产生的Hash值做高低位异或，然后再取余，产生的值小于threshold
 * 产生的值作为桶的下标，找到对应的桶
 * 遍历桶中的链表，一个个比较key值，key相同则替换value值，如果没有key就在桶最后面加上一个Node
 *
 */
static void HashMap_Put(HashMap* map, char* key_origin, int value) {
	Node *p;
	Node *tail;
	unsigned int hash = HashMap_HashCode(map, key_origin);
	//得到Hash值后将高低位交互运算下
	hash = hash ^ (hash >> 16);
	//最后取余数
	hash = hash & (map->threshold - 1);
	p = map->table[hash];
	//如果桶是空的就新建Node放入桶中
	if (p == NULL) {
		Node* node = malloc(sizeof(Node));
		size_t key_len = strlen(key_origin);
		char* key = malloc(sizeof(char)*(key_len + 1));
		key[key_len] = 0;
		memcpy(key, key_origin, key_len);
		node->key = key;
		node->value = value;
		node->next = NULL;
		map->table[hash] = node;
	}
	else {
		while (p != NULL) {
			//如果找到key就替换
			if (!strcmp(p->key , key_origin)) {
				p->value = value;
				break;
			}
			tail = p;
			p = p->next;
			//找到末尾也找不到key，就新建Node添加到最后
			if (p == NULL) {
				Node* node = malloc(sizeof(Node));
				size_t key_len = strlen(key_origin);
				char* key = malloc(sizeof(char)*(key_len + 1));
				key[key_len] = 0;
				memcpy(key, key_origin, key_len);
				node->key = key;
				node->value = value;
				node->next = NULL;
				tail->next = node;
			}
		}
	}
}


static void HashMap_Remove(HashMap* map, char* key) {
	Node *p;
	unsigned int hash = HashMap_HashCode(map, key);
	//得到Hash值后将高低位交互运算下
	hash = hash ^ (hash >> 16);
	//最后取余数
	hash = hash & (map->threshold - 1);
	p = map->table[hash];
	Node* pre = p;
	while (p != NULL) {
		//如果找到key就替换
		if (!strcmp(p->key,key)) {
			if (!strcmp(pre->key, p->key)) {
				map->table[hash] = p->next;
			}
			else {
				pre->next = p->next;
			}
			free(p->key);
			free(p);
			break;
		}
		pre = p;
		p = p->next;
	}
}

/*
 * HashMap的get方法，与put方法差不多，只是找到对应的key之后直接返回Node,其他时候返回NULL
 */
static Node* HashMap_Get(HashMap* map, char* key) {
	Node *p;
	unsigned int hash = HashMap_HashCode(map, key);
	hash = hash ^ (hash >> 16);
	hash = hash & (map->threshold - 1);
	p = map->table[hash];
	if (p == NULL) {
		return NULL;
	}
	else {
		while (p != NULL) {
			if (!strcmp(p->key,key)) {
				return p;
				break;
			}
			p = p->next;
			if (p == NULL) {
				return NULL;
			}
		}
	}
	return NULL;
}

static bool HashMap_Contains(HashMap* map, char* key) {
	if (HashMap_Get(map, key) != NULL) {
		return true;
	}
	else {
		return false;
	}
}

static void HashMap_Free(HashMap* map) {
	for (int i = 0; i < map->threshold; i++) {
		Node *entry = map->table[i];
		while (entry != NULL) {
			Node *temp = entry;
			free(entry->key);
			entry = entry->next;
			free(temp);
		}
	}
	free(map->table);
	free(map);
}

static void HashMap_Clear(HashMap* map) {
	for (int i = 0; i < map->threshold; i++) {
		Node *entry = map->table[i];
		while (entry != NULL) {
			Node *temp = entry;
			free(entry->key);
			entry = entry->next;
			free(temp);
		}
		map->table[i] = NULL;
	}
}

static void incr(HashMap* map, char* key) {
	if (HashMap_Contains(map,key)) {
		HashMap_Put(map,key, HashMap_Get(map,key)->value + 1);
	}
	else {
		HashMap_Put(map,key,1);
	}
}

static HashMap* generateCount(char** words,int wordsSize) {
	int initialCapacity = (int)((float)wordsSize / 0.75F + 1.0F);
	HashMap* wordsCount = malloc(sizeof(HashMap));
	HashMap_Init(wordsCount, initialCapacity);
	for (size_t i = 0; i < wordsSize; i++)
	{
		incr(wordsCount,words[i]);
	}
	return wordsCount;
}



void decr(HashMap* map, char* key) {
	if (HashMap_Contains(map, key)) {
		int value = HashMap_Get(map, key)->value;
		if (value <= 1) {
			HashMap_Remove(map,key);
		}
		else {
			HashMap_Put(map,key, value - 1);
		}
	}
}


 /**
	  * 解题思路：这题咋一看好难，有种暴力法是把words所有组合可能列出来，然后一一对比，想着都耗时，肯定有更简便的方法
	  *
	  * 我们分析题意，words中的字符长度是一致的，这个比较关键，假设words的长度是1,是不是感觉会简单许多
	  *
	  * 这就变成字串中是否包含数组中所有字符，那我们就可以用移动窗口来查询窗口中是否包含所有字符
	  *
	  * 想到查询，那用Hash表是最方便快捷的，我们可以定义两个Hash表，一个用来保存窗口中出现的字符串，一个用来保存数组中的字符串
	  *
	  * Hash表key为字符串，value为出现的次数
	  *
	  * 窗口有两个指针left和right，分别表示窗口的开始和结束，设每个单词的长度为l，每次取right+l作为一个单词，将这个单词存入窗口Hash表中
	  *
	  * 假设这个单词在数组Hash表中不存在，说明这个区间不合格，所以需要将left置为right,right置为right+l继续找
	  *
	  * 假设这个单词在数组Hash表中存在并且出现次数小于数组Hash表出现次数，那么将right加上l继续取，否则将left加上l
	  *
	  * 当right-left的区间长度正好为数组中所有字符加起来的长度时，表示匹配上正确的字符了
	  *
	  */
int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
	size_t s_len = strlen(s);
	int* result = malloc(sizeof(int)*s_len);
	if (s==NULL|| s_len == 0 || words == NULL || wordsSize == 0) {
		return result;
	}
	HashMap* wordsCount = generateCount(words,wordsSize);//将所有字符加入数组Hash表
	int length = strlen(words[0]);
	if (length > s_len) {
		return result;
	}
	int initialCapacity = (int)((float)s_len / (wordsSize*0.75F) + 1.0F);
	HashMap* window = malloc(sizeof(HashMap));
	HashMap_Init(window, initialCapacity);
	char* temp_w= malloc(sizeof(char)*(length + 1));
	temp_w[length] = 0;
	for (int i = 0; i < length; ++i) {//错位循环，保证每种情况都遍历到
		int left = i;
		int right = i;
		while (right <= s_len - length && left <= s_len - length * wordsSize) {
			memcpy(temp_w,s+right,length);
			incr(window, temp_w);//取一个字符加入窗口Hash表
			if (!HashMap_Contains(wordsCount, temp_w)) {//如果这个字符在数组Hash表中不存在，就清理窗口并重置left和right
				HashMap_Clear(window);
				right += length;
				left = right;
				continue;
			}
			while (HashMap_Get(window, temp_w)->value > HashMap_Get(wordsCount, temp_w)->value) {//当窗口Hash中字符次数多于数组Hash字符次数时，left+l,交从窗口中移除最左边的字符
				char* sub1 = malloc(sizeof(char)*(length + 1));
				memcpy(sub1, s + left, length);
				sub1[length] = 0;
				decr(window, sub1);
				free(sub1);
				left += length;
			}
			right += length;
			if (right - left == length * wordsSize) {//当窗口长度正好等于数组字符总长度时，表示匹配成功，加入结果中
				result[(*returnSize)++]=left;
			}
		}
		HashMap_Clear(window);
	}
	free(temp_w);
	HashMap_Free(window);
	HashMap_Free(wordsCount);
	return result;
}




void solution30() {
	char* strs[4] = { "word","good","best","word" };
	int* returnSize = malloc(sizeof(int));
	*returnSize = 0;
	int** re=findSubstring("wordgoodgoodgoodbestword", strs, 4, returnSize);
	for (size_t i = 0; i < *returnSize; i++)
	{
		ALog("%d",re[i]);
	}
	free(re);
	free(returnSize);
}