#include "include/env.h"

typedef struct ListNode_Class {
	int val;
	struct ListNode_Class *next;
}ListNode;

/*
 * ����˼·�������ʵ�ʾ��Ǽӷ����ӷ��Ļ������漰����λ�����⣬�������Ǿ���һ�������������½�λ
 * 
 * �ڱ��������н�ÿһλ�����ֶ�Ӧ��ӣ������λ�Ӹ�λ��ʮλ��ʮλ��Ȼ���ټӽ�λ
 * 
 * ���жԲ���λ��ʱ�򣬱���һ����λ��+��λ�����֣���λ����ǧλ�򲻼�
 */
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	int carry = 0;
	ListNode* result = (ListNode*)malloc(sizeof(ListNode));
	ListNode* origin = result;
	while (l1 != NULL || l2 != NULL || carry != NULL) {
		if (l1 != NULL) {
			carry = carry + l1->val;
			l1 = l1->next;
		}
		if (l2 != NULL) {
			carry = carry + l2->val;
			l2 = l2->next;
		}
		ListNode* node = (ListNode*)malloc(sizeof(ListNode));
		node->val = carry % 10;
		node->next = NULL;
		result->next = node;
		result = node;
		carry /= 10;
	}
	ListNode* temp = origin->next;
	free(origin);
	return temp;
}

void ListNode_free(ListNode* node) {
	ListNode* entry = node;
	while (entry != NULL) {
		ListNode* temp = entry;
		entry = entry->next;
		free(temp);
	}
}

ListNode* getNode(int a, int b, int c) {
	ListNode* node_a = malloc(sizeof(ListNode));
	node_a->val = a;
	ListNode* node_b = malloc(sizeof(ListNode));
	node_b->val = b;
	ListNode* node_c = malloc(sizeof(ListNode));
	node_c->val = c;
	node_a->next = node_b;
	node_b->next = node_c;
	node_c->next = NULL;
	return node_a;
}

void solution2() {
	ListNode* node_1 = getNode(2, 4, 3);
	ListNode* node_2 = getNode(5, 6, 4);
	ListNode* re = addTwoNumbers(node_1, node_2);
	ListNode_free(node_1);
	ListNode_free(node_2);
	ListNode* temp = re;
	while (re != NULL) {
		ALog("%x", re->val);
		re = re->next;
	}
	ListNode_free(temp);
}