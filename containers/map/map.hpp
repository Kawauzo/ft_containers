#ifndef MAP_HPP
# define MAP_HPP

# include <iostream> // TESTING, DELETE AFTERWARDS
# include <cstdio> // TESTING, DELETE AFTERWARDS


# include "../utils/comparisons.hpp" // needed relational operators
# include "../utils/pair.hpp"       // needed for ft::pair and ft::make_pair
# include "../utils/iterators.hpp" // needed for reverse iterator
# include "map_iterator.hpp"      // iterator

# include <memory>    // needed for std::allocator
# include <limits>   // needed for max_size()

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
    typedef enum {red, black} color_type;
    struct node_type{
        color_type   color;
        value_type * val;
        node_type  * l;
        node_type  * r;
        node_type  * parent;

        // default constructor used for end() nodes, color set to black
        node_type(): color(black),
                     val(NULL),
                     l(NULL),
                     r(NULL),
                     parent(NULL) {}

        // value constructor, color set to red
        node_type(const value_type & x, Alloc & al): color(red),
                                                     val(al.allocate(1)),
                                                     l(NULL),
                                                     r(NULL),
                                                     parent(NULL)
        { al.construct(val, x); }

        ~node_type(){}
    };

public:
    typedef map_iterator<value_type, node_type>              iterator;
    typedef map_iterator<const value_type, const node_type>  const_iterator;
    typedef reverse_iterator<const_iterator>                 const_reverse_iterator;
    typedef reverse_iterator<iterator>                       reverse_iterator;

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
    size_type            _sz;

    /*
     * **************************************
     * ********* Member Functions ***********
     * **************************************
    */

    void _insert_ends(){
        _root = new node_type();
        _root->r = new node_type();
        _root->r->parent = _root;
    }

public:

    // ***** Constructors *****
    //
    // Default
    explicit map (const key_compare& comp = key_compare(),
                  const allocator_type& alloc = allocator_type()) :
        _root(NULL),
        _cmp_k(comp),
        _cmp(comp),
        _al(alloc),
        _sz(0)
    { _insert_ends(); }

    // Range
    template< class InputIt >
    map (InputIt first, InputIt last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) :
        _root(NULL),
        _cmp_k(comp),
        _cmp(comp),
        _al(alloc),
        _sz(0)
    { _insert_ends(); insert(first, last); }

    // Copy
    map (const map & cpy):
        _root(NULL),
        _cmp_k(cpy._cmp_k),
        _cmp(cpy._cmp),
        _al(cpy._al),
        _sz(0)
    { _insert_ends(); insert(cpy.begin(), cpy.end()); }


    // ***** Destructor *****
    ~map() { destroy_rec(_root); }


    // ***** Assignment operator *****
    map& operator=(const map& other){
        clear();
        insert(other.begin(), other.end());
        return *this;
    }

    // ***** Max_size *****
private:
    size_type _elem_size() const { return sizeof(node_type) - sizeof(value_type*) + sizeof(value_type); }
public:
    size_type max_size() const {
        return std::numeric_limits<difference_type>::max() / (_elem_size() / 2 < 1 ? 1 : _elem_size() / 2 );
    }

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

public:
    // ***** operator[] *****

    mapped_type& operator[] (const key_type& k){
        return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
    }
    /*
     * **************************************
     * ************* Iterator ***************
     * **************************************
    */

public:
    iterator begin(){
        if (!_sz)
            return end();
        node_type* tmp = _root;
        while (tmp->l && tmp->l->val)
            tmp = tmp->l;
        return iterator(tmp);
    }

    const_iterator begin() const {
        if (!_sz)
            return end();
        node_type* tmp = _root;
        while (tmp->l && tmp->l->val)
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

    reverse_iterator rbegin(){ return reverse_iterator(end()); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

    reverse_iterator rend(){ return reverse_iterator(begin()); }

    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }



    /*
     * **************************************
     * ************* Capacity ***************
     * **************************************
    */

public:
    // ***** Empty *****
    bool empty() const { return !_sz ? true : false; }

    // ***** Size *****
    size_type size() const { return _sz; }

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

    // ***** Clear *****
    void clear(){
        destroy_rec(_root);
        _sz = 0;
        _insert_ends();
    }

    // ***** Insert *****
    //
    // Insert elem
    ft::pair<iterator, bool> insert(const value_type & x){
        ft::pair<iterator, bool> ret = insert_body(_root, x);
        if (ret.second){
            ++_sz;
            if (_sz <= 2)
                _root->color = black;
            else
                _insert_fix(ret.first.base());
        }
        return ret;
    }

    // Insert hint
    iterator insert(iterator pos, const value_type & x){
        (void)pos;
        return insert(x).first;
    }

    // Insert range
    template< class InputIt >
    void insert( InputIt first, InputIt last ){
        while (first != last){
            insert(*first);
            ++first;
        }
    }

private:
    // main function for inserting
    // qu'on soit clair c'est une ABOMINATION
    ft::pair<iterator, bool> insert_body(node_type * n, const value_type & x){
        while (n->val){
            // if element exists, return false
            if (x.first == n->val->first)
                return ft::make_pair(n, false);
            if (_cmp(x, *n->val)){               // left path
                if (n->l)                       // if it exists, go this way
                    n = n->l;
                else {                        // else insert and return
                    n->l = new node_type(x, _al);;
                    n->l->parent = n;
                    return ft::make_pair(n->l, true);
                }
            }
            else {                       // right path, same as above
                if (n->r)
                    n = n->r;
                else {
                    n->r = new node_type(x, _al);;
                    n->r->parent = n;
                    return ft::make_pair(n->r, true);
                }
            }
        }
        // if we get here, it means we've reached end() node
        node_type *tmp = new node_type(x, _al);
        tmp->parent = n->parent;
        if (n->parent && n == n->parent->r)
            tmp->r = n;
        else
            tmp->l = n;
        if (_root == n){            // first insertion in tree
            _root = tmp;
            tmp->r = n->r;        // separate the 2 end nodes
            tmp->r->parent = tmp;
            n->r = NULL;
        }
        else if (n == n->parent->r)
            n->parent->r = tmp;
        else
            n->parent->l = tmp;
        n->parent = tmp;
        return ft::make_pair(tmp, true);
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

    // takes a node's child and its new parent,
    // sets it if they're not adjacent
    void _swap_set_parent(node_type* child, node_type* new_parent){
        if (child && child != new_parent)
            child->parent = new_parent;
    }

    // takes a node's parent and its new child,
    // sets it if they're not adjacent
    void _swap_set_child(node_type* old_child, node_type* new_child){
        if (old_child->parent && old_child->parent != new_child){
            if (old_child->parent->l == old_child)
                old_child->parent->l = new_child;
            else
                old_child->parent->r = new_child;
        }
    }

    // function that swaps 2 nodes,
    // used, ie, if a node to delete has 2 children
    // c'est la pire chose que j'ai ecrit de TOUTE ma vie
    void _swap_nodes(node_type* ptr, node_type* tmp){
        _swap_set_parent(ptr->l, tmp);
        _swap_set_parent(ptr->r, tmp);
        _swap_set_child(ptr, tmp);
        if (ptr == _root)
            _root = tmp;
        else if (tmp == _root)
            _root = ptr;
        _swap_set_parent(tmp->l, ptr);
        _swap_set_parent(tmp->r, ptr);
        _swap_set_child(tmp, ptr);
        node_type *old_l = ptr->l;
        node_type *old_r = ptr->r;
        node_type *old_p = ptr->parent;
        if (tmp->l != ptr)
            ptr->l = tmp->l;
        else
            ptr->l = tmp;
        if (tmp->r != ptr)
            ptr->r = tmp->r;
        else
            ptr->r = tmp;
        if (tmp->parent != ptr)
            ptr->parent = tmp->parent;
        else
            ptr->parent = tmp;
        if (old_l != tmp)
            tmp->l = old_l;
        else
            tmp->l = ptr;
        if (old_r != tmp)
            tmp->r = old_r;
        else
            tmp->r = ptr;
        if (old_p != tmp)
            tmp->parent = old_p;
        else
            tmp->parent = ptr;
        ptr->color = tmp->color;
    }

public:
    // erase node at iterator, and reconnect children
    void erase(iterator pos){
        node_type *ptr = pos.base();
        if (_sz == 1)
            return clear();             //used to reset end() nodes
        if (ptr->l && ptr->r){
            node_type *tmp = ptr->r;
            while (tmp->l && tmp->l->val)
                tmp = tmp->l;
            _swap_nodes(ptr, tmp);
            erase(iterator(ptr));
        }
        else {
            color_type old_color = ptr->color;
            node_type* parent = ptr->parent;
            bool side = (ptr->parent && ptr == ptr->parent->l) ? 0 : 1;

            if (!ptr->l && !ptr->r)
                set_parent_target(ptr, NULL);
            else if (!ptr->l && ptr->r)
                set_parent_target(ptr, ptr->r);
            else if (ptr->l && !ptr->r)
                set_parent_target(ptr, ptr->l);
            _al.destroy(ptr->val);
            _al.deallocate(ptr->val, 1);
            delete ptr;
            --_sz;
            if (old_color == black && _sz > 1){
                if (!side)
                    _erase_fix(parent->l, parent);
                else
                    _erase_fix(parent->r, parent);
            }
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
        iterator it = find(k);
        if (it == end())
            return 0;
        erase(it);
        return 1;
    }

    // ***** swap *****
    void swap(map& other){
        node_type *tmp_root = _root;
        size_type tmp_sz = _sz;
        _root = other._root;
        _sz = other._sz;
        other._root = tmp_root;
        other._sz = tmp_sz;
    }

    /*
     * **************************************
     * ************** Lookup ****************
     * **************************************
    */

public:
    // ***** count *****
    size_t count(const key_type & k) const {
        const_iterator it = find(k);
        if (it == end())
            return 0;
        return 1;
    }

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
        if (!n || (n && !n->val))
            return (NULL);
        if (k == n->val->first)
            return (n);
        if (_cmp_k(k, n->val->first))
            return (find_rec(n->l, k));
        else
            return (find_rec(n->r, k));
    }

public:
    iterator       lower_bound (const key_type& k){
        iterator it = begin();
        while (it != end() && _cmp_k(it->first, k))
            ++it;
        return it;
    }

    const_iterator lower_bound (const key_type& k) const {
        const_iterator it = begin();
        while (it != end() && _cmp_k(it->first, k))
            ++it;
        return it;

    }

    iterator       upper_bound (const key_type& k){
        iterator it = begin();
        while (it != end() && !_cmp_k(k, it->first))
            ++it;
        return it;
    }

    const_iterator upper_bound (const key_type& k) const {
        const_iterator it = begin();
        while (it != end() && !_cmp_k(k, it->first))
            ++it;
        return it;
    }

    ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const{
        return ft::make_pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k));
    }

    ft::pair<iterator,iterator> equal_range (const key_type& k){
        return ft::make_pair<iterator,iterator>(lower_bound(k), upper_bound(k));
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
     * *********** Red - Black **************
     * **************************************
    */

  // Rotate left
  void _l_rotate(node_type* x) {
    node_type* y = x->r;
    x->r = y->l;
    if (y->l != NULL) {
      y->l->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
      _root = y;
    } else if (x == x->parent->l) {
      x->parent->l = y;
    } else {
      x->parent->r = y;
    }
    y->l = x;
    x->parent = y;
  }

  void _r_rotate(node_type* x) {
    node_type* y = x->l;
    x->l = y->r;
    if (y->r != NULL) {
      y->r->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
      _root = y;
    } else if (x == x->parent->r) {
      x->parent->r = y;
    } else {
      x->parent->l = y;
    }
    y->r = x;
    x->parent = y;
  }

  // For balancing the tree after insertion
  void _insert_fix(node_type* k) {
    node_type*  u;
    while (k->parent && k->parent->color == red) {
      if (k->parent == k->parent->parent->r) {
        u = k->parent->parent->l;
        if (u && u->color == red) {
          u->color = black;
          k->parent->color = black;
          k->parent->parent->color = red;
          k = k->parent->parent;
        } else {
          if (k == k->parent->l) {
            k = k->parent;
            _r_rotate(k);
          }
          k->parent->color = black;
          k->parent->parent->color = red;
          _l_rotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->r;

        if (u && u->color == red) {
          u->color = black;
          k->parent->color = black;
          k->parent->parent->color = red;
          k = k->parent->parent;
        } else {
          if (k == k->parent->r) {
            k = k->parent;
            _l_rotate(k);
          }
          k->parent->color = black;
          k->parent->parent->color = red;
          _r_rotate(k->parent->parent);
        }
      }
      if (k == _root)
        break;
    }
    _root->color = black;
  }

    bool is_black(node_type *s){
        if (!s || s->color == black)
            return true;
        return false;
    }


  // For balancing the tree after deletion
  void _erase_fix(node_type* x, node_type* parent) {
    node_type* s;
    while (x != _root && is_black(x)) {
      if (x)
        parent = x->parent;
      if (x == parent->l) {
        s = parent->r;
        if (s->color == red) {
          s->color = black;
          parent->color = red;
          _l_rotate(parent);
          s = parent->r;
        }

        if (is_black(s->l) && is_black(s->r)) {
          s->color = red;
          x = parent;
        } else {
          if (is_black(s->r)) {
            s->l->color = black;
            s->color = red;
            _r_rotate(s);
            s = parent->r;
          }

          s->color = parent->color;
          parent->color = black;
          s->r->color = black;
          _l_rotate(parent);
          x = _root;
        }
      } else {
        s = parent->l;
        if (s->color == red) {
          s->color = black;
          parent->color = red;
          _r_rotate(parent);
          s = parent->l;
        }

        if (is_black(s->r)) {
          s->color = red;
          x = parent;
        } else {
          if (is_black(s->l)) {
            s->r->color = black;
            s->color = red;
            _l_rotate(s);
            s = parent->l;
          }

          s->color = parent->color;
          parent->color = black;
          s->l->color = black;
          _r_rotate(parent);
          x = _root;
        }
      }
    }
    x->color = black;
  }





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
            if (n->color == black)
                std::cout << "\033[1;30;47m";
            else
                std::cout << "\033[1;31m";
            if (n->val)
                std::cout << n->val->first;
            else
                std::cout << "end";
            std::cout <<  "\033[0m" << '\n';
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
};  // --------- End of map


    /*
     * **************************************
     * ** Non member - Relational operator **
     * **************************************
    */

template< class Key, class T, class Compare, class Alloc >
bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs ){
    if (lhs.size() != rhs.size())
        return false;
    typename ft::map<Key, T, Compare, Alloc>::const_iterator lit = lhs.begin();
    typename ft::map<Key, T, Compare, Alloc>::const_iterator rit = rhs.begin();
    while (lit != lhs.end())
        if (*lit++ != *rit++)
            return false;
    return true;
}

template< class Key, class T, class Compare, class Alloc >
bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs ){
    return !(lhs == rhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
                const ft::map<Key,T,Compare,Alloc>& rhs ){
    return ft::lexicographical_compare(lhs.begin(), lhs.end(),
                                        rhs.begin(), rhs.end());
}

template< class Key, class T, class Compare, class Alloc >
bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs,
               const ft::map<Key,T,Compare,Alloc>& rhs) {
    return (!(lhs == rhs) && !(lhs < rhs));
}

template< class Key, class T, class Compare, class Alloc >
bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs,
                const ft::map<Key,T,Compare,Alloc>& rhs) {
    return ((lhs == rhs) || (lhs < rhs));
}

template< class Key, class T, class Compare, class Alloc >
bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs,
                const ft::map<Key,T,Compare,Alloc>& rhs) {
    return ((lhs == rhs) || !(lhs < rhs));
}



} // --------- End of ft namespace

#endif
