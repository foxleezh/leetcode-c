#include "include/env.h"
/**
 * 将两个有序链表合并为一个新的有序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
 * <p>
 * 示例：
 * <p>
 * 输入：1->2->4, 1->3->4
 * 输出：1->1->2->3->4->4
 *
 * @author foxleezh
 * @date 2019-02-24.
 */

struct ListNode {
	int val;
	struct ListNode *next;
};

 /**
  * 解题思路：我们可以用归并排序的思想解决，也就是说，将两个有序链表的头结点进行比较，较小的放前面，较大的放后面
  * @return
  */
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
	// 类似归并排序中的合并过程
	struct ListNode head;
	struct ListNode *cur = &head;
	while (l1 != NULL && l2 != NULL) {
		if (l1->val < l2->val) {
			cur->next = l1;
			cur = cur->next;
			l1 = l1->next;
		}
		else {
			cur->next = l2;
			cur = cur->next;
			l2 = l2->next;
		}
	}
	// 任一为空，直接连接另一条链表
	if (l1 == NULL) {
		cur->next = l2;
	}
	else {
		cur->next = l1;
	}
	return head.next;
}

/**
 * 根据数组创建ListNode
 */
struct ListNode* createNode(int* nums,size_t size) {
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
	char* re = malloc(sizeof(char)*1000);
	re[0] = 0;
	char temp[10];
	struct ListNode* temp_node;
	while (node->next != NULL) {
		sprintf(temp,"%d",node->val);
		strcat(re,temp);
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


void solution21() {
	int nums1[3]= {1,3,5};
	int nums2[3]= {2,4,6};
	char* toString=nodeToString(mergeTwoLists(createNode(nums1, 3), createNode(nums2, 3)));
	ALog("%s",toString);
	free(toString);
}