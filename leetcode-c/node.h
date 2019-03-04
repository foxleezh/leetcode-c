#pragma once
#include "include/env.h"

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* nodeCreate(int* nums, size_t size);

char* nodeToString(struct ListNode* node);

