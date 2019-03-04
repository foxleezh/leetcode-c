#include "include/env.h"
/**
 * 合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。
 * <p>
 * 示例:
 * <p>
 * 输入:
 * [
 * 1->4->5,
 * 1->3->4,
 * 2->6
 * ]
 * 输出: 1->1->2->3->4->4->5->6
 *
 * @author foxleezh
 * @date 2019-02-28.
 */

/**
 * 归并排序，两两合并
 */
static struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
	struct ListNode root;
	struct ListNode* node = &root;
	while (list1 != NULL && list2 != NULL) {
		if (list1->val <= list2->val) {
			node->next = list1;
			list1 = list1->next;
		}
		else {
			node->next = list2;
			list2 = list2->next;
		}
		node = node->next;
	}
	if (list1 == NULL) {
		node->next = list2;
	}
	if (list2 == NULL) {
		node->next = list1;
	}
	return root.next;
}

 /**
  * 解题思路： 可以按照归并排序的原理，两两归并
  * 时间复杂度为mlogk,m为链表中数字的总个数，k为链表个数
  * @return
  */
static struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
	if (listsSize == 0) {
		return NULL;
	}
	int k = listsSize;
	while (k > 1) {
		for (int i = 0; i < k / 2; i++) {
			//两两合并
			lists[i] = mergeTwoLists(lists[i], lists[i + (k + 1) / 2]);
		}
		k = (k + 1) / 2;
	}
	return lists[0];
}

void solution23() {
	int nums1[] = {1,3};
	int nums2[] = { 2, 4, 7 };
	int nums3[] = { 3, 5, 9 };
	struct ListNode* node1 = nodeCreate(nums1,2);
	struct ListNode* node2 = nodeCreate(nums2,3);
	struct ListNode* node3 = nodeCreate(nums3,3);
	struct ListNode** nodes = malloc(sizeof(struct ListNode*)*3);
	nodes[0] = node1;
	nodes[1] = node2;
	nodes[2] = node3;
	char* toString = nodeToString(mergeKLists(nodes, 3));
	ALog("%s", toString);
	free(toString);
	free(nodes);
}