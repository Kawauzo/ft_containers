#ifndef MAP_HPP
# define MAP_HPP

# include <iostream> // TESTING, DELETE AFTERWARDS
# include <cstdio> // TESTING, DELETE AFTERWARDS


# include "../utils/pair.hpp" // needed for ft::pair and ft::make_pair
# include "map_iterator.hpp" // iterator

# include <memory> // needed for std::allocator

namespace ft {

template <
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Alloc = std::allocator<ft::pair<const Key, T> >
> class map {
    public:

    /*
     * **************************************
     * ********** Member Types **************
     * **************************************
    */

    typedef Key                     key_type;
    typedef T                       mapped_type;
    typedef ft::pair<const Key, T>  value_type;

    typedef std::ptrdiff_t          difference_type;
    typedef std::size_t             size_type;
    typedef Alloc                   allocator_type;
    typedef value_type&             reference;
    typedef const value_type&       const_reference;

    typedef typename Alloc::pointer       pointer;
    typedef typename Alloc::const_pointer const_pointer;

    typedef Compare                 key_compare;

    //Class that compares 2 objects of value_type
    class value_compare :
    public std::binary_function<value_type, value_type, bool> {
        friend class map;
        protected:
        Compare comp;
        // constructed with map's comparison object
        value_compare (Compare c) : comp(c) {}
        public:
        typedef bool result_type;
        typedef value_type first_argument_type;
        typedef value_type second_argument_type;
        bool operator() (const value_type& x, const value_type& y) const {
            return comp(x.first, y.first);
        }
    };

    private:
    // ***** private BST node_type *****
    struct node_type{
        value_type * val;
        node_type  * l;
        node_type  * r;
        node_type  * parent;

        node_type(): val(NULL), l(NULL), r(NULL), parent(NULL){}
        node_type(const value_type & x, Alloc & al): val(al.allocate(1)), l(NULL), r(NULL), parent(NULL) {
            al.construct(val, x);
        }
        ~node_type(){}
    };

    public:
    typedef map_iterator<value_type, node_type>        iterator;
    typedef map_iterator<const value_type, const node_type>  const_iterator;

    /*
     * **************************************
     * ************ Variables ***************
     * **************************************
    */

    private:
    node_type *          _root;
    const key_compare    _cmp_k;
    const value_compare  _cmp;
    allocator_type       _al;

    /*
     * **************************************
     * ********* Member Functions ***********
     * **************************************
    */

public:

    // ***** Constructors *****
    //
    explicit map (const key_compare& comp = key_compare(),
                  const allocator_type& alloc = allocator_type()) :
        _root(new node_type),
        _cmp_k(comp),
        _cmp(comp),
        _al(alloc)
    {}

    ~map() { destroy_rec(_root); }


    // ***** Get_allocator *****
    allocator_type get_allocator() const {return _al;}

private:
    // recursive function to destroy a node
    // and all it's children
    void destroy_rec(node_type *n){
        if (n){
            if (n->val){
                _al.destroy(n->val);
                _al.deallocate(n->val, 1);
            }
            destroy_rec(n->l);
            destroy_rec(n->r);
            delete n;
        }
    }


    /*
     * **************************************
     * ********** Element access ************
     * **************************************
    */

    // ***** At *****
    T& at(const key_type & k){
        node_type *res = find(k);
        if (!res)
            throw std::out_of_range("");
        return res->val->second;
    }

    const T& at(const key_type & k) const { return at(k); }

    // ***** operator[] *****

    /*
     * **************************************
     * ************* Iterator ***************
     * **************************************
    */

public:
    iterator begin(){
        node_type* tmp = _root;
        while (tmp->l)
            tmp = tmp->l;
        return iterator(tmp);
    }

    const_iterator begin() const {
        node_type* tmp = _root;
        while (tmp->l)
            tmp = tmp->l;
        return iterator(tmp);
    }

    iterator end(){
        node_type* tmp = _root;
        while (tmp->r)
            tmp = tmp->r;
        return iterator(tmp);
    }

    const_iterator end() const {
        node_type* tmp = _root;
        while (tmp->r)
            tmp = tmp->r;
        return iterator(tmp);
    }

    /*
     * **************************************
     * ************* Capacity ***************
     * **************************************
    */

public:
    // ***** Empty *****
    bool empty() const { return size() ? 1 : 0; }

    // ***** Size *****
    // the '- 1' is because of end iterator node
    size_type size() const { return size_rec(_root) - 1; }

private:
    unsigned int size_rec(node_type * n) const {
        if (n == NULL)
            return 0;
        else
            return (size_rec(n->l) + size_rec(n->r) + 1);
    }

public:
    /*
     * **************************************
     * ************ Modifiers ***************
     * **************************************
    */

    // Clear
    void clear(){
        destroy_rec(_root);
        _root = new node_type;
    }

    // Insert
    void insert(const value_type & x){
        insert_rec(_root, x);
    }

private:
    // recursive function for inserting
    node_type * insert_rec(node_type * n, const value_type & x){
        if (n){
            if (!n->val){
                node_type *tmp = new node_type(x, _al);
                tmp->parent = n->parent;
                tmp->r = n;
                n->parent = tmp;
                if (_root == n)
                    _root = tmp;
                return tmp;
            }
        }
        else {
            return new node_type(x, _al);
        }
        if (x.first == n->val->first)
            return n;
        if (_cmp(x, *n->val)){
            n->l = insert_rec(n->l, x);
            n->l->parent = n;
        }
        else{
            n->r = insert_rec(n->r, x);
            n->r->parent = n;
        }
        return n;
    }

    // ***** erase *****
private:
    // set parent's child to target,
    // and target's parent to deleted node parent
    void set_parent_target(node_type *ptr, node_type *target){
        if (ptr->parent){
            if (ptr->parent->l == ptr)
                ptr->parent->l = target;
            else
                ptr->parent->r = target;
        }
        else
            _root = target;
        if (target)
            target->parent = ptr->parent;
    }

public:
    // erase node at iterator, and reconnect children
    void erase(iterator pos){
        node_type *ptr = pos.base();
        if (ptr->l && ptr->r){
            node_type *tmp = ptr->r;
            while (tmp->l && tmp->l->val)
                tmp = tmp->l;
            value_type *swp = ptr->val;
            ptr->val = tmp->val;
            tmp->val = swp;
            ptr = tmp;
            erase(iterator(tmp));
        }
        else {
            if (!ptr->l && !ptr->r)
                set_parent_target(ptr, NULL);
            else if (!ptr->l && ptr->r)
                set_parent_target(ptr, ptr->r);
            else if (ptr->l && !ptr->r)
                set_parent_target(ptr, ptr->l);
            _al.destroy(ptr->val);
            _al.deallocate(ptr->val, 1);
            delete ptr;
        }
    }

    // erase range
    void erase(iterator first, iterator last){
        iterator tmp = first;
        while (first != last){
            ++tmp;
            erase(first);
            first = tmp;
        }
    }

    // erase item matching key
    size_t erase(key_type k){
        node_type *res = find_rec(_root, k);
        if (!res)
            return 0;
        erase(iterator(k));
        return 1;
    }

    /*
     * **************************************
     * ************** Lookup ****************
     * **************************************
    */

public:
    // ***** find *****
    iterator       find(const key_type & k) {
        node_type *res = find_rec(_root, k);
        if (res)
            return iterator(res);
        return end();
    }

    const_iterator find(const key_type & k) const {
        node_type *res = find_rec(_root, k);
        if (res)
            return iterator(res);
        return end();
    }

private:
    // recursive function to find a value
    node_type * find_rec(node_type *n, const key_type & k) const {
        if (!n || (n && !n->val)){
            //std::cout << "not found" << std::endl;
            return (NULL);
        }
        //std::cout << n->val->first << std::endl;
        if (k == n->val->first){
            //std::cout << std::endl;
            return (n);
        }
        if (_cmp_k(k, n->val->first)){
            //std::cout << "/" << std::endl;
            return (find_rec(n->l, k));
        }
        else{
            //std::cout << "\\" << std::endl;
            return (find_rec(n->r, k));
        }
    }

    /*
     * **************************************
     * ************ Observers ***************
     * **************************************
    */

public:
    key_compare   key_comp()   const { return _cmp_k; }
    value_compare value_comp() const { return _cmp; }

    /*
     * **************************************
     * ************** TESTIN ****************
     * **************************************
    */

private:
    unsigned int max_depth_rec(node_type * n){
        if (n == NULL)
            return 0;
        else {
            unsigned int lDepth = max_depth_rec(n->l);
            unsigned int rDepth = max_depth_rec(n->r);

            if (lDepth > rDepth)
                return lDepth + 1;
            else
                return rDepth + 1;
        }

    }
    // ***** max_depth *****
    unsigned int max_depth(){ return max_depth_rec(_root); }
public:
    // TESTING --- print tree
    void  print()
    {
        printf("Display tree : \n");
        node_print(_root, 0, max_depth());
        printf("\n\n");

    }

    void  node_print(node_type *n, int current_level, int max_level)
    {
        int i;

        if (n) {
            node_print(n->r, current_level + 1, max_level);
            for (i = 0; i < current_level; i++) {
                printf("    ");
            }
            if (n->val)
                std::cout << n->val->first << '\n';
            else
                std::cout << "end" << '\n';
            node_print(n->l, current_level + 1, max_level);
        }
        else {
            if (current_level < max_level) {
                node_print(NULL, current_level + 1, max_level);
                for (i = 0; i < current_level; i++) {
                    printf("    ");
                }
                printf("..\n");
                node_print(NULL, current_level + 1, max_level);
            }
        }
    }




};






}

#endif
