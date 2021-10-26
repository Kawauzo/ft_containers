#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

// testing
#include <iostream>

// decrire la classe ici

namespace ft {

template <class T>
class bst {
    typedef T data;

private:
    struct node {
        data *val;
        node *l;
        node *r;

        node(data &x) : val(new data(x)), l(NULL), r(NULL) {}
        ~node() {delete val;}
    };

    node *root; //pointer to the top of the tree

public:
    // ***** Cstructor *****
    bst():root(NULL) {}

private:
    // recursive function for inserting
    void destroy_rec(node *n){
        if (n){
            destroy_rec(n->l);
            destroy_rec(n->r);
            delete n;
        }
    }
public:
    // ***** Cstructor *****
    ~bst() { destroy_rec(root); }

private:
    // recursive function for inserting
    node * insert_rec(node * n, data & x){
        if (!n)
            return new node(x);
        if (x > *n->val)
            n->r = insert_rec(n->r, x);
        else
            n->l = insert_rec(n->l, x);
        return n;
    }

public:
    // ***** insert element *****
    void insert(data x){
        if (!root)
            root = new node(x);
        else
            insert_rec(root, x);
    }

private:
    // recursive function to find a value
    node * find_rec(node *n, const data & val) const {
        if (!n){
            std::cout << "not found" << std::endl;
            return (NULL);
        }
        std::cout << *n->val << std::endl;
        if (val == *n->val){
            std::cout << std::endl;
            return (n);
        }
        if (val > *n->val){
            std::cout << "\\" << std::endl;
            return (find_rec(n->r, val));
        }
        else{
            std::cout << "/" << std::endl;
            return (find_rec(n->l, val));
        }
    }

public:
    // ***** find element *****
    node * find(const data & x) const { return find_rec(root, x); }

};

}

#endif
