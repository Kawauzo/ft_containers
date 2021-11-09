make -C tests/print_tree/ > /dev/null

if [ $? -eq 0 ] ; then
    mkdir -p results
    ./tests/print_tree/print_rb_tree
fi
