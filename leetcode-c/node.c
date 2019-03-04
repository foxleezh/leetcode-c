#include "node.h"
#include "include/env.h"



/**
 * 根据数组创建ListNode
 */
struct ListNode* nodeCreate(int* nums, size_t size) {
	if (size == 0) {
		return NULL;
	}
	struct ListNode* head = malloc(sizeof(struct ListNode));
	struct ListNode* origin = head;
	head->val = nums[0];
	for (int i = 1; i < size; i++) {
		struct ListNode* next = malloc(sizeof(struct ListNode));
		next->val = nums[i];
		head->next = next;
		head = next;
	}
	head->next = NULL;
	return origin;
}

/**
 * 输出struct ListNode中的值
 */
char* nodeToString(struct ListNode* node) {
	char* re = malloc(sizeof(char) * 1000);
	re[0] = 0;
	char temp[10];
	struct ListNode* temp_node;
	while (node->next != NULL) {
		sprintf(temp, "%d", node->val);
		strcat(re, temp);
		strcat(re, "->");
		temp_node = node->next;
		free(node);
		node = temp_node;
	}
	sprintf(temp, "%d", node->val);
	strcat(re, temp);
	free(node);
	return re;
}

void nodeFree(struct ListNode* node) {
	struct ListNode* entry = node;
	while (entry != NULL) {
		struct ListNode* temp = entry;
		entry = entry->next;
		free(temp);
	}
}
