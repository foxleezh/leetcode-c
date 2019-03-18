#include "include/env.h"
/**
 * ����һ���ַ��� s ��һЩ������ͬ�ĵ��� words���ҳ� s ��ǡ�ÿ����� words �����е��ʴ����γɵ��Ӵ�����ʼλ�á�
 *
 * ע���Ӵ�Ҫ�� words �еĵ�����ȫƥ�䣬�м䲻���������ַ���������Ҫ���� words �е��ʴ�����˳��
 *
 *
 *
 * ʾ�� 1��
 *
 * ���룺
 *   s = "barfoothefoobarman",
 *   words = ["foo","bar"]
 * �����[0,9]
 * ���ͣ�
 * ������ 0 �� 9 ��ʼ���Ӵ��ֱ��� "barfoor" �� "foobar" ��
 * �����˳����Ҫ, [9,0] Ҳ����Ч�𰸡�
 * ʾ�� 2��
 *
 * ���룺
 *   s = "wordgoodgoodgoodbestword",
 *   words = ["word","good","best","word"]
 * �����[]
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
	int threshold; //Ͱ����
	struct Node_Class** table; //Ͱ�б�
};

/*
 * ��ʼ��HashMap
 * @initialCapacity ��ʼ������Ҳ����HashMap��Ͱ�ĸ�����һ��Ϊ (Ԥ��������)/0.75f+1
 */
static void HashMap_Init(HashMap* map, int initialCapacity) {
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
 * HashMap��Hashֵ���㣬����ELFhash 
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
 * HashMap��put���������Ƚ�������Hashֵ���ߵ�λ���Ȼ����ȡ�࣬������ֵС��threshold
 * ������ֵ��ΪͰ���±꣬�ҵ���Ӧ��Ͱ
 * ����Ͱ�е�����һ�����Ƚ�keyֵ��key��ͬ���滻valueֵ�����û��key����Ͱ��������һ��Node
 *
 */
static void HashMap_Put(HashMap* map, char* key_origin, int value) {
	Node *p;
	Node *tail;
	unsigned int hash = HashMap_HashCode(map, key_origin);
	//�õ�Hashֵ�󽫸ߵ�λ����������
	hash = hash ^ (hash >> 16);
	//���ȡ����
	hash = hash & (map->threshold - 1);
	p = map->table[hash];
	//���Ͱ�ǿյľ��½�Node����Ͱ��
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
			//����ҵ�key���滻
			if (!strcmp(p->key , key_origin)) {
				p->value = value;
				break;
			}
			tail = p;
			p = p->next;
			//�ҵ�ĩβҲ�Ҳ���key�����½�Node��ӵ����
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
	//�õ�Hashֵ�󽫸ߵ�λ����������
	hash = hash ^ (hash >> 16);
	//���ȡ����
	hash = hash & (map->threshold - 1);
	p = map->table[hash];
	Node* pre = p;
	while (p != NULL) {
		//����ҵ�key���滻
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
 * HashMap��get��������put������ֻ࣬���ҵ���Ӧ��key֮��ֱ�ӷ���Node,����ʱ�򷵻�NULL
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
	  * ����˼·������զһ�����ѣ����ֱ������ǰ�words������Ͽ����г�����Ȼ��һһ�Աȣ����Ŷ���ʱ���϶��и����ķ���
	  *
	  * ���Ƿ������⣬words�е��ַ�������һ�µģ�����ȽϹؼ�������words�ĳ�����1,�ǲ��Ǹо�������
	  *
	  * ��ͱ���ִ����Ƿ���������������ַ��������ǾͿ������ƶ���������ѯ�������Ƿ���������ַ�
	  *
	  * �뵽��ѯ������Hash��������ݵģ����ǿ��Զ�������Hash��һ���������洰���г��ֵ��ַ�����һ���������������е��ַ���
	  *
	  * Hash��keyΪ�ַ�����valueΪ���ֵĴ���
	  *
	  * ����������ָ��left��right���ֱ��ʾ���ڵĿ�ʼ�ͽ�������ÿ�����ʵĳ���Ϊl��ÿ��ȡright+l��Ϊһ�����ʣ���������ʴ��봰��Hash����
	  *
	  * �����������������Hash���в����ڣ�˵��������䲻�ϸ�������Ҫ��left��Ϊright,right��Ϊright+l������
	  *
	  * �����������������Hash���д��ڲ��ҳ��ִ���С������Hash����ִ�������ô��right����l����ȡ������left����l
	  *
	  * ��right-left�����䳤������Ϊ�����������ַ��������ĳ���ʱ����ʾƥ������ȷ���ַ���
	  *
	  */
int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
	size_t s_len = strlen(s);
	int* result = malloc(sizeof(int)*s_len);
	if (s==NULL|| s_len == 0 || words == NULL || wordsSize == 0) {
		return result;
	}
	HashMap* wordsCount = generateCount(words,wordsSize);//�������ַ���������Hash��
	int length = strlen(words[0]);
	if (length > s_len) {
		return result;
	}
	int initialCapacity = (int)((float)s_len / (wordsSize*0.75F) + 1.0F);
	HashMap* window = malloc(sizeof(HashMap));
	HashMap_Init(window, initialCapacity);
	char* temp_w= malloc(sizeof(char)*(length + 1));
	temp_w[length] = 0;
	for (int i = 0; i < length; ++i) {//��λѭ������֤ÿ�������������
		int left = i;
		int right = i;
		while (right <= s_len - length && left <= s_len - length * wordsSize) {
			memcpy(temp_w,s+right,length);
			incr(window, temp_w);//ȡһ���ַ����봰��Hash��
			if (!HashMap_Contains(wordsCount, temp_w)) {//�������ַ�������Hash���в����ڣ��������ڲ�����left��right
				HashMap_Clear(window);
				right += length;
				left = right;
				continue;
			}
			while (HashMap_Get(window, temp_w)->value > HashMap_Get(wordsCount, temp_w)->value) {//������Hash���ַ�������������Hash�ַ�����ʱ��left+l,���Ӵ������Ƴ�����ߵ��ַ�
				char* sub1 = malloc(sizeof(char)*(length + 1));
				memcpy(sub1, s + left, length);
				sub1[length] = 0;
				decr(window, sub1);
				free(sub1);
				left += length;
			}
			right += length;
			if (right - left == length * wordsSize) {//�����ڳ������õ��������ַ��ܳ���ʱ����ʾƥ��ɹ�����������
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