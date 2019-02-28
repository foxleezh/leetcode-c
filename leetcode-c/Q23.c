#include "include/env.h"
/**
 * �ϲ� k �������������غϲ������������������������㷨�ĸ��Ӷȡ�
 * <p>
 * ʾ��:
 * <p>
 * ����:
 * [
 * 1->4->5,
 * 1->3->4,
 * 2->6
 * ]
 * ���: 1->1->2->3->4->4->5->6
 *
 * @author foxleezh
 * @date 2019-02-28.
 */

 
struct ListNode {
	int val;
	struct ListNode *next;
};
/**
 * �鲢���������ϲ�
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
  * ����˼·�� ���԰��չ鲢�����ԭ�������鲢
  * ʱ�临�Ӷ�Ϊmlogk,mΪ���������ֵ��ܸ�����kΪ�������
  * @return
  */
static struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
	if (listsSize == 0) {
		return NULL;
	}
	int k = listsSize;
	while (k > 1) {
		for (int i = 0; i < k / 2; i++) {
			//�����ϲ�
			lists[i] = mergeTwoLists(lists[i], lists[i + (k + 1) / 2]);
		}
		k = (k + 1) / 2;
	}
	return lists[0];
}



struct ListNode* createList(int* nums,size_t numsSize) {
	struct ListNode node;
	struct ListNode* cur = &node;
	for (int i = 0; i < numsSize; i++) {
		struct ListNode* next = malloc(sizeof(struct ListNode));
		next->val = nums[i];
		next->next = NULL;
		cur->next = next;
		cur = cur->next;
	}
	return node.next;
}

void solution23() {
	int nums1[] = {1,3};
	int nums2[] = { 2, 4, 7 };
	int nums3[] = { 3, 5, 9 };
	struct ListNode* node1 = createList(nums1,2);
	struct ListNode* node2 = createList(nums2,3);
	struct ListNode* node3 = createList(nums3,3);
	struct ListNode** nodes = malloc(sizeof(struct ListNode*)*3);
	nodes[0] = node1;
	nodes[1] = node2;
	nodes[2] = node3;
	struct ListNode* node = mergeKLists(nodes,3);
	while (node->next != NULL) {
		ALog("%d",node->val);
		struct ListNode* temp = node->next;
		free(node);
		node = temp;
	}
	ALog("%d", node->val);
	free(node);
	free(nodes);
}