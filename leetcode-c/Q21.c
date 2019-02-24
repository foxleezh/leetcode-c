#include "include/env.h"
/**
 * ��������������ϲ�Ϊһ���µ������������ء���������ͨ��ƴ�Ӹ�����������������нڵ���ɵġ�
 * <p>
 * ʾ����
 * <p>
 * ���룺1->2->4, 1->3->4
 * �����1->1->2->3->4->4
 *
 * @author foxleezh
 * @date 2019-02-24.
 */

struct ListNode {
	int val;
	struct ListNode *next;
};

 /**
  * ����˼·�����ǿ����ù鲢�����˼������Ҳ����˵�����������������ͷ�����бȽϣ���С�ķ�ǰ�棬�ϴ�ķź���
  * @return
  */
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
	// ���ƹ鲢�����еĺϲ�����
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
	// ��һΪ�գ�ֱ��������һ������
	if (l1 == NULL) {
		cur->next = l2;
	}
	else {
		cur->next = l1;
	}
	return head.next;
}

/**
 * �������鴴��ListNode
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
 * ���struct ListNode�е�ֵ
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