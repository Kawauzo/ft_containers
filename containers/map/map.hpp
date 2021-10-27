#ifndef MAP_HPP
# define MAP_HPP

# include <iostream> // TESTING, DELETE AFTERWARDS
# include <cstdio> // TESTING, DELETE AFTERWARDS


# include "../utils/pair.hpp" // needed for ft::pair and ft::make_pair

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
        value_type *val;
        node_type  *l;
        node_type  *r;

        node_type(): val(NULL), l(NULL), r(NULL) {}
        node_type(const value_type & x, Alloc & al): val(al.allocate(1)), l(NULL), r(NULL) {
            al.construct(val, x);
        }
        ~node_type(){}
    };

    /*
     * **************************************
     * ************ Variables ***************
     * **************************************
    */

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
        _root(NULL),
        _cmp(comp),
        _al(alloc)
    {}

    ~map() { destroy_rec(_root); }

private:
    // recursive function to destroy a node
    // and all it's children
    void destroy_rec(node_type *n){
        if (n){
            destroy_rec(n->l);
            destroy_rec(n->r);
            delete n;
        }
    }

    /*
     * **************************************
     * ************* Capacity ***************
     * **************************************
    */

public:
    // ***** Size *****
    unsigned int size(){ return size_rec(_root); }

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
        _root = NULL;
    }

    // Insert
    void insert(const value_type & x){
        if (!_root){
            _root = new node_type(x, _al);
        }
        else
            insert_rec(_root, x);
    }

private:
    // recursive function for inserting
    node_type * insert_rec(node_type * n, const value_type & x){
        if (!n){
            return new node_type(x, _al);
        }
        if (x.first > n->val->first)
            n->r = insert_rec(n->r, x);
        else
            n->l = insert_rec(n->l, x);
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
        if (!n){
            //std::cout << "not found" << std::endl;
            return (NULL);
        }
        //std::cout << *n->key << std::endl;
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
            std::cout << n->val->first << '\n';
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
