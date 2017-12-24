#include <bits/stdc++.h>
using namespace std;
template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }
#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define forab(i, a, b) for (int i = (int)(a); i < (int)(b); i++)
const int maxn = int(1e6) + 10;

struct node {
    node *r;
    int val;
    node() : val(0), r(nullptr) {}
    node(int _val) : val(_val), r(nullptr) {}
};

struct List {
    node *first; node *last; node *useless;
    size_t sz;

    List() : first(nullptr), last(nullptr), useless(new node(-1)), sz(0) {}

    void push_back(int v) {
        node *curr = new node(v);
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
        node *curr = new node(v);
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
        node *it;

        list_iterator(node *_it) : it(_it) {}

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
            node *curr = first->r;
            delete first;
            first = curr;
        }
        delete first;
        first = last = nullptr;
        delete useless;
    }
};

void merge(List *(&res), List *l, List *r) {
    auto s1 = l->begin(), s2 = r->begin();
    while (s1 != l->end() && s2 != r->end()) {
        if (*(s1) < *(s2))
            res->push_back(*(s1++));
        else
            res->push_back(*(s2++));
    }
    while (s1 != l->end())
        res->push_back(*(s1++));
    while (s2 != r->end())
        res->push_back(*(s2++));
}

void merge_sort(List *(&l)) {
    if (l->size() == 1)
        return;
    int mid = (l->size()) >> 1;
    List *l1 = new List, *l2 = new List;
    auto x = l->begin();
    while (l1->size() != mid)
        l1->push_back(*(x++));
    while (x != l->end())
        l2->push_back(*(x++));
    merge_sort(l1);
    merge_sort(l2);
    delete l;
    l = new List;
    merge(l, l1, l2);
    delete l1;
    delete l2;
}

int main() {
    List *l = new List;
    int n;
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
