#ifndef TREE_PRINTER_HPP
# define TREE_PRINTER_HPP

# include <iostream>
# include "../../containers/map/map.hpp"

// TESTING --- A class that prints a map's underlying red/black
template <
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Alloc = std::allocator<ft::pair<const Key, T> >
> class map_printer : public ft::map<Key, T, Compare, Alloc>{

    typedef typename ft::map<Key, T, Compare, Alloc> map;
    typedef typename map::color_type color_type;

private:
    unsigned int max_depth_rec(typename map::node_type * n){
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
    unsigned int max_depth(){ return max_depth_rec(this->_root); }


public:
    map_printer(){};
    ~map_printer(){};




    void  print()
    {
        std::cout << "Black Depth :" << std::endl;
        black_depth(this->_root, 0);
        std::cout << std::endl << "Display tree :" << std::endl;
        node_print(this->_root, 0, max_depth());
        std::cout << std::endl << std::endl;

    }
    void black_depth(typename map::node_type * n, int d) {
        if (n->val &&  n->color == map::color_type::black)
            ++d;
        if ((!n->r && !n->l) || !n->val) {
            /*
            if (n->val)
                std::cout << n->val->first << '/';
            else
                std::cout << n->parent->val->first << '/';
                */
            std::cout << d << ' ';
            return;
        }
        if (n->l)
            black_depth(n->l, d);
        if (n->r)
            black_depth(n->r, d);
    }

    void  node_print(typename map::node_type * n, int current_level, int max_level) {
        int i;

        if (n) {
            node_print(n->r, current_level + 1, max_level);
            for (i = 0; i < current_level; i++) {
                printf("    ");
            }
            if (n->color == map::color_type::black)
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
};


#endif
