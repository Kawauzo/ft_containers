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
    typedef Compare                 key_compare;
    typedef Alloc                   allocator_type;
    typedef value_type&             reference;
    typedef const value_type&       const_reference;

    typedef typename Alloc::pointer       pointer;
    typedef typename Alloc::const_pointer const_pointer;


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
    typedef map_iterator<value_type, node_type>  iterator;

    /*
     * **************************************
     * ************ Variables ***************
     * **************************************
    */

    private:
    node_type *          _root;
    const key_compare    _cmp;
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
        _cmp(comp),
        _al(alloc)
    {}

    ~map() { destroy_rec(_root); }

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

    iterator end(){
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
    // ***** Size *****
    // the '- 1' is because of end iterator node
    unsigned int size(){ return size_rec(_root) - 1; }

private:
    unsigned int size_rec(node_type * n){
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
        if (x.first > n->val->first){
            n->r = insert_rec(n->r, x);
            n->r->parent = n;
        }
        else{
            n->l = insert_rec(n->l, x);
            n->l->parent = n;
        }
        return n;
    }

    /*
     * **************************************
     * ************** Lookup ****************
     * **************************************
    */

public:
    // ***** find *****
    node_type * find(const key_type & k) const { return find_rec(_root, k); }

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
        if (k > n->val->first){
            //std::cout << "\\" << std::endl;
            return (find_rec(n->r, k));
        }
        else{
            //std::cout << "/" << std::endl;
            return (find_rec(n->l, k));
        }
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
