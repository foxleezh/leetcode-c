#include "include/env.h"

/**
 * 给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
 * <p/>
 * 示例:
 * <p/>
 * 给定 nums = [2, 7, 11, 15], target = 9
 * <p/>
 * 因为 nums[0] + nums[1] = 2 + 7 = 9
 * 所以返回 [0, 1]
 */

typedef struct Node_Class Node;

typedef struct HashMap_Class HashMap;

struct Node_Class {
	int key;
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
void HashMap_Init(HashMap* map,int initialCapacity) {
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
 * HashMap的Hash值计算，暂时是就是自己
 * 
 */
int HashMap_HashCode(HashMap* map, int key) {
	return key;
}

/*
 * HashMap的put方法，首先将产生的Hash值做高低位异或，然后再取余，产生的值小于threshold
 * 产生的值作为桶的下标，找到对应的桶
 * 遍历桶中的链表，一个个比较key值，key相同则替换value值，如果没有key就在桶最后面加上一个Node
 *
 */
void HashMap_Put(HashMap* map,int key,int value) {
	Node *p;
	Node *tail;
	unsigned int hash = (unsigned int)HashMap_HashCode(map, key);
	//得到Hash值后将高低位交互运算下
	hash= hash ^ (hash >> 16);
	//最后取余数
	hash=hash&(map->threshold - 1);
	p = map->table[hash];
	//如果桶是空的就新建Node放入桶中
	if (p == NULL) {
		Node* node = malloc(sizeof(Node));
		node->key = key;
		node->value = value;
		node->next = NULL;
		map->table[hash] = node;
	}else {
		while (p != NULL) {
			//如果找到key就替换
			if (p->key == key) {
				p->value = value;
				break;
			}
			tail = p;
			p = p->next;
			//找到末尾也找不到key，就新建Node添加到最后
			if (p == NULL) {
				Node* node = malloc(sizeof(Node));
				node->key = key;
				node->value = value;
				node->next = NULL;
				tail->next = node;
			}
		}
	}
}

/*
 * HashMap的get方法，与put方法差不多，只是找到对应的key之后直接返回Node,其他时候返回NULL
 */
Node* HashMap_Get(HashMap* map, int key) {
	Node *p;
	unsigned int hash = (unsigned int)HashMap_HashCode(map, key);
	hash = hash ^ (hash >> 16);
	hash = hash & (map->threshold - 1);
	p = map->table[hash];
	if (p == NULL) {
		return NULL;
	}
	else {
		while (p != NULL) {
			if (p->key == key) {
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

bool HashMap_Contains(HashMap* map, int key) {
	if (HashMap_Get(map, key) != NULL) {
		return true;
	}
	else {
		return false;
	}
}

void HashMap_Free(HashMap* map) {
	for (int i = 0; i < map->threshold; i++) {
		Node *entry = map->table[i];
		while (entry != NULL) {
			Node *temp = entry;
			entry = entry->next;
			free(temp);
		}
	}
	free(map->table);
	free(map);
}

int* twoSum(int* nums, int numsSize, int target)
{
	if (numsSize < 2) return NULL;
	int *res = (int *)malloc(sizeof(int) * 2);
	//最好算一下初始容量，提高效率
	int initialCapacity = (int)((float)numsSize/ 0.75F + 1.0F);
	HashMap* map = malloc(sizeof(HashMap));
	HashMap_Init(map,initialCapacity);
	for (int i = 0; i < numsSize; i++) {
		//在map中寻找余数
		if (!HashMap_Contains(map,target - nums[i])) {
			HashMap_Put(map,nums[i], i);
		}
		else {
			res[0] = HashMap_Get(map,target - nums[i])->value;
			res[1] = i;
			break;
		}
	}
	HashMap_Free(map);
	return res;
}

void solution1() {
	int nums[65] = { 591, 955, 829, 805, 312, 83, 764, 841, 12, 744, 104, 773, 627, 306, 731, 539, 349, 811, 662, 341, 465, 300, 491, 423, 569, 405, 508, 802, 500, 747, 689, 506, 129, 325, 918, 606, 918, 370, 623, 905, 321, 670, 879, 607, 140, 543, 997, 530, 356, 446, 444, 184, 787, 199, 614, 685, 778, 929, 819, 612, 737, 344, 471, 645, 726 };
	int* re=twoSum(nums,65, 789);
	ALog("%x,%x", re[0],re[1]);
	free(re);
}