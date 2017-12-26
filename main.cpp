#include <bits/stdc++.h>
using namespace std;
template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }
#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define forab(i, a, b) for (int i = (int)(a); i < (int)(b); i++)
const int maxn = int(1e6) + 10;

struct Node {
    Node *r;
    int val;
    Node() : val(0), r(nullptr) {}
    Node(int _val) : val(_val), r(nullptr) {}
};

struct List {
    Node *first; Node *last; Node *useless;
    size_t sz;

    List() : first(nullptr), last(nullptr), useless(new Node(-1)), sz(0) {}

    void push_back(int v) {
        Node *curr = new Node(v);
        if (sz == 0) {
            first = last = curr;
        } else {
            last->r = curr;
            last = curr;
        }
        last->r = useless;
        ++sz;
    }

    void push_front(int v) {
        Node *curr = new Node(v);
        if (sz == 0) {
            first = last = curr;
        } else {
            curr->r = first;
            first = curr;
        }
        useless->r = first;
        ++sz;
    }

    size_t size() const {
        return sz;
    }

    struct list_iterator {
        Node *it;

        list_iterator(Node *_it) : it(_it) {}

        bool operator == (list_iterator other) {
            return it == other.it;
        }

        bool operator != (list_iterator other) {
            return !(it == other.it);
        }

        int& operator*() {
            return it->val;
        }

        list_iterator& operator++() {
            it = it->r;
            return *this;
        }

        list_iterator operator++(int) {
            auto curr = *this;
            it = it->r;
            return curr;
        }
    };

    list_iterator begin() {
        return first;
    }

    list_iterator end() {
        return useless;
    }

    ~List() {
        if (sz == 0)
            return;
        while (first != last) {
            Node *curr = first->r;
            delete first;
            first = curr;
        }
        delete first;
        first = last = nullptr;
        delete useless;
    }
};

List* merge(List *l, List *r) {
    List *res = new List;
    auto first_it = l->begin(), second_it = r->begin();
    while (first_it != l->end() && second_it != r->end()) {
        if (*(first_it) < *(second_it))
            res->push_back(*(first_it++));
        else
            res->push_back(*(second_it++));
    }
    while (first_it != l->end())
        res->push_back(*(first_it++));
    while (second_it != r->end())
        res->push_back(*(second_it++));
    return res;
}

void merge_sort(List *l) {
    if (l->size() == 1)
        return;
    int mid = (l->size()) >> 1;
    List *left_list = new List, *right_list = new List;
    auto x = l->begin();
    while (left_list->size() != mid)
        left_list->push_back(*(x++));
    while (x != l->end())
        right_list->push_back(*(x++));
    merge_sort(left_list);
    merge_sort(right_list);
    *l = *merge(left_list, right_list);
    delete left_list;
    delete right_list;
}

int main() {
    List *l = new List;
    size_t n = 0;
    cin >> n;
    forn(i, n) {
        int val;
        cin >> val;
        l->push_back(val);
    }
    merge_sort(l);
    auto x = l->begin();
    while (x != l->end())
        cout << *(x++) << " ";
    return 0;
}
