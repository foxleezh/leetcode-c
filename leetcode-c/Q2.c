#include "include/env.h"

/**
 * 给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。
 * <p/>
 * 如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
 * <p/>
 * 您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 * <p/>
 * 示例：
 * <p/>
 * 输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
 * <p/>
 * 输出：7 -> 0 -> 8
 * <p/>
 * 原因：342 + 465 = 807
 * <p/>
 */


typedef struct ListNode_Class {
	int val;
	struct ListNode_Class *next;
}ListNode;

/*
 * 解题思路：这题的实质就是加法，加法的话就是涉及到进位的问题，所以我们就用一个变量来保存下进位
 * 
 * 在遍历过程中将每一位的数字对应相加，比如个位加个位，十位加十位，然后再加进位
 * 
 * 当有对不上位的时候，比如一个三位数+四位数这种，三位数的千位则不加
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