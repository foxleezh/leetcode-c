#include "include/env.h"

/**
 * ����һ���������� nums ��һ��Ŀ��ֵ target�������ڸ��������ҳ���ΪĿ��ֵ���� ���� ���������������ǵ������±ꡣ
 * <p/>
 * ʾ��:
 * <p/>
 * ���� nums = [2, 7, 11, 15], target = 9
 * <p/>
 * ��Ϊ nums[0] + nums[1] = 2 + 7 = 9
 * ���Է��� [0, 1]
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
	int threshold; //Ͱ����
	struct Node_Class** table; //Ͱ�б�
};

/*
 * ��ʼ��HashMap
 * @initialCapacity ��ʼ������Ҳ����HashMap��Ͱ�ĸ�����һ��Ϊ (Ԥ��������)/0.75f+1
 */
void HashMap_Init(HashMap* map,int initialCapacity) {
	int threshold = 1;
	//�Զ����Ϊ����initialCapacity��2�ı���ֵ
	while (threshold < initialCapacity)
		threshold <<= 1;
	map->threshold = threshold;
	Node** table = malloc(sizeof(Node)*threshold);
	memset(table, 0, sizeof(Node) * threshold);
	map->table = table;
}

/*
 * HashMap��Hashֵ���㣬��ʱ�Ǿ����Լ�
 * 
 */
int HashMap_HashCode(HashMap* map, int key) {
	return key;
}

/*
 * HashMap��put���������Ƚ�������Hashֵ���ߵ�λ���Ȼ����ȡ�࣬������ֵС��threshold
 * ������ֵ��ΪͰ���±꣬�ҵ���Ӧ��Ͱ
 * ����Ͱ�е�����һ�����Ƚ�keyֵ��key��ͬ���滻valueֵ�����û��key����Ͱ��������һ��Node
 *
 */
void HashMap_Put(HashMap* map,int key,int value) {
	Node *p;
	Node *tail;
	unsigned int hash = (unsigned int)HashMap_HashCode(map, key);
	//�õ�Hashֵ�󽫸ߵ�λ����������
	hash= hash ^ (hash >> 16);
	//���ȡ����
	hash=hash&(map->threshold - 1);
	p = map->table[hash];
	//���Ͱ�ǿյľ��½�Node����Ͱ��
	if (p == NULL) {
		Node* node = malloc(sizeof(Node));
		node->key = key;
		node->value = value;
		node->next = NULL;
		map->table[hash] = node;
	}else {
		while (p != NULL) {
			//����ҵ�key���滻
			if (p->key == key) {
				p->value = value;
				break;
			}
			tail = p;
			p = p->next;
			//�ҵ�ĩβҲ�Ҳ���key�����½�Node��ӵ����
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
 * HashMap��get��������put������ֻ࣬���ҵ���Ӧ��key֮��ֱ�ӷ���Node,����ʱ�򷵻�NULL
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
	//�����һ�³�ʼ���������Ч��
	int initialCapacity = (int)((float)numsSize/ 0.75F + 1.0F);
	HashMap* map = malloc(sizeof(HashMap));
	HashMap_Init(map,initialCapacity);
	for (int i = 0; i < numsSize; i++) {
		//��map��Ѱ������
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