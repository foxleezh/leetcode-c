#include "include/env.h"
/**
 *
 * ����һ������ÿ k ���ڵ�һ����з�ת�������ط�ת�������
 *
 * k ��һ��������������ֵС�ڻ��������ĳ��ȡ�����ڵ��������� k ������������ô�����ʣ��ڵ㱣��ԭ��˳��
 *
 * ʾ�� :
 *
 * �����������1->2->3->4->5
 *
 * �� k = 2 ʱ��Ӧ������: 2->1->4->3->5
 *
 * �� k = 3 ʱ��Ӧ������: 3->2->1->4->5
 *
 * ˵�� :
 *
 * ����㷨ֻ��ʹ�ó����Ķ���ռ䡣
 * �㲻��ֻ�ǵ����ĸı�ڵ��ڲ���ֵ��������Ҫʵ�ʵĽ��нڵ㽻����
 *
 * @author foxleezh
 * @date 2019-03-12.
 */


 /**
  * ����˼·�����⿼������ָ�뷨������������(-1)->1->2->3->4->5, -1�����������ģ� ��һ��ָ���pre(-1)���ڶ���ָ���cur(1),������ָ���post��cur����һ����
  *
  * ���ص��ע�·�ת�����������Ű�����������ת
  *
  * ��ô�������ҵ�2��������pre(-1)���棬˳���Ϊ-1->2->1->3->4->5
  *
  * ���ҵ�3��������pre(-1)���棬˳���Ϊ-1->3->2->1->4->5
  *
  * ���ҵ�4��������pre(-1)���棬˳���Ϊ-1->4->3->2->1->5
  *
  * ����ҵ�5��������pre(-1)���棬˳���Ϊ-1->5->4->3->2->1
  *
  * �������������ʹ�����Զ��cur(1)��������ֳ�������ŵ�pre(-1)���棬����˳�򱣳ֲ��䣬���Ϲ������������pre��cur��ֵ�ǲ���ģ�postһֱ�ڱ�
  *
  * Ȼ�������ٹ�ע�ֶε����⣬һ���Ƿֳ�num/k��
  *
  * ÿ�η�ת�����󣬱��һ��pre��cur��ֵ
  */
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
	struct ListNode dummy;
	struct ListNode *pre = &dummy;
	struct ListNode *cur = pre;
	struct ListNode *post;
	dummy.next = head;
	int num = 0;
	while (cur = cur->next) ++num;
	while (num >= k) {
		cur = pre->next;//���cur��ֵ
		for (int i = 1; i < k; ++i) {
			post = cur->next; //���postΪcur����һ��
			cur->next = post->next;//��cur����һ�����ӵ�post����һ�����൱�ڳ��post
			post->next = pre->next;//�������post���ӵ�cur
			pre->next = post;//��pre���ӵ������post
		}
		pre = cur;//���pre��ֵ
		num -= k;
	}
	return dummy.next;
}


void solution25() {
	int nums1[] = { 1,2,3,4,5 };
	char* toString = nodeToString((reverseKGroup(nodeCreate(nums1, 5), 4)));
	ALog("%s", toString);
	free(toString);
}