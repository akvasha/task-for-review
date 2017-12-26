#include <bits/stdc++.h>
#define forn(i, n) for (int i = 0; i < (int)(n); i++)

using std::cin;
using std::cout;

struct Node {
    Node *r;
    int val;
    Node() : val(0), r(nullptr) {}
    Node(int _val) : val(_val), r(nullptr) {}
};

void merge(Node **res, Node *left, Node *right) {
    *res = nullptr;
    Node head;
    if (left == nullptr) {
        *res = right;
        return;
    }
    if (right == nullptr) {
        *res = left;
        return;
    }
    if (left->val < right->val) {
        *res = left;
        left = left->r;
    } else {
        *res = right;
        right = right->r;
    }
    head.r = *res;
    while (left && right) {
        if (left->val < right->val) {
            (*res)->r = left;
            left = left->r;
        } else {
            (*res)->r = right;
            right = right->r;
        }
        (*res) = (*res)->r;
    }
    while (left) {
        (*res)->r = left;
        left = left->r;
        (*res) = (*res)->r;
    }
    while (right) {
        (*res)->r = right;
        right = right->r;
        (*res) = (*res)->r;
    }
    *res = head.r;
}

void divide(Node *start, Node **left, Node **right) {
    Node *two_steps = nullptr, *one_step = nullptr;
    if (start == nullptr || start->r == nullptr) {
        (*left) = start;
        (*right) = nullptr;
        return;
    }
    one_step = start;
    two_steps = start->r;
    while (two_steps != nullptr) {
        two_steps = two_steps->r;
        if (two_steps != nullptr) {
            two_steps = two_steps->r;
            one_step = one_step->r;
        }
    }

    (*left) = start;
    (*right) = one_step->r;
    one_step->r = nullptr;
}

void merge_sort(Node **head) {
    Node *left = nullptr, *right = nullptr;
    if (((*head) == nullptr) || ((*head)->r == nullptr))
        return;
    divide(*head, &left, &right);
    merge_sort(&left);
    merge_sort(&right);
    merge(head, left, right);
}

int main() {
    Node *head = nullptr;
    Node start = 0;
    size_t n = 0;
    cin >> n;
    forn(i, n) {
        int v;
        cin >> v;
        if (i == 0) {
            head = new Node(v);
            start.r = head;
        } else {
            head->r = new Node(v);
            head = head->r;
        }
    }
    merge_sort(&(start.r));
    while (start.r != nullptr) {
        cout << start.r->val << " ";
        start.r = (start.r)->r;
    }
    return 0;
}