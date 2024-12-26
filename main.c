#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (!listsSize) return NULL;
    short i, j, min = 10000, max = -10000, values[20000] = {0};
    struct ListNode *ptr, *ptr1 = NULL;

    for (i = 0; i < listsSize; i++) {
        ptr = lists[i];
        if (!ptr) continue;
        if (ptr->val < min) min = ptr->val;
        for (; ptr->next; values[ptr->val + 10000]++, ptr = ptr->next);
        values[ptr->val + 10000]++;
        if (ptr->val > max) max = ptr->val;
    }

    min += 10000, max += 10000;
    for (j = 0; j < listsSize && !lists[j]; j++);
    if (listsSize == j) return lists[0];
    
    for (i = min, ptr = lists[j++]; i <= max; i++) {
        for (i; values[i]; values[i]--) {
            if (!ptr) {
                while (!lists[j]) j++;
                ptr1->next = lists[j], ptr = lists[j++];
            }
            ptr->val = i - 10000, ptr1 = ptr, ptr = ptr->next;
        }
    }

    for (j = 0; j < listsSize && !lists[j]; j++);
    return lists[j];
}

void printList(struct ListNode* head) {
    printf("[");
    while (head) {
        printf("%d", head->val);
        if (head->next) printf(",");
        head = head->next;
    }
    printf("]");
}

int main() {
    // Create linked lists to merge
    struct ListNode *list1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    list1->val = 1;
    list1->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    list1->next->val = 4;
    list1->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    list1->next->next->val = 5;
    list1->next->next->next = NULL;

    struct ListNode *list2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    list2->val = 1;
    list2->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    list2->next->val = 3;
    list2->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    list2->next->next->val = 4;
    list2->next->next->next = NULL;

    struct ListNode *list3 = (struct ListNode*)malloc(sizeof(struct ListNode));
    list3->val = 2;
    list3->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    list3->next->val = 6;
    list3->next->next = NULL;

    struct ListNode *lists[3] = {list1, list2, list3};

    struct ListNode* mergedList = mergeKLists(lists, 3);
    printList(mergedList);

    return 0;
}