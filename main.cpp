#include <bits/stdc++.h>
#define forn(i, n) for (int i = 0; i < (int)(n); i++)

using std::cin;
using std::cout;

template<typename T>
struct Node {
    Node *r;
    T val;
    Node() : val(T(0)), r(nullptr) {}
    Node(T _val) : val(_val), r(nullptr) {}
};

template<typename T>
void merge(Node<T> **res, Node<T> *left, Node<T> *right) {
    *res = nullptr;
    Node<T> head;
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

template<typename T>
void divide(Node<T> *start, Node<T> **left, Node<T> **right) {
    Node<T> *two_steps = nullptr, *one_step = nullptr;
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

template<typename T>
void merge_sort(Node<T> **head) {
    Node<T> *left = nullptr, *right = nullptr;
    if (((*head) == nullptr) || ((*head)->r == nullptr))
        return;
    divide(*head, &left, &right);
    merge_sort(&left);
    merge_sort(&right);
    merge(head, left, right);
}

int main() {
    Node<int> *head = nullptr;
    Node<int> start = 0;
    size_t n = 0;
    cin >> n;
    forn(i, n) {
        int v;
        cin >> v;
        if (i == 0) {
            head = new Node<int>(v);
            start.r = head;
        } else {
            head->r = new Node<int>(v);
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
