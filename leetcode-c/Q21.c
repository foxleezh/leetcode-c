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


void solution21() {
	int nums1[3]= {1,3,5};
	int nums2[3]= {2,4,6};
	char* toString=nodeToString(mergeTwoLists(nodeCreate(nums1, 3), nodeCreate(nums2, 3)));
	ALog("%s",toString);
	free(toString);
}