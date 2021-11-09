make re -C ./tests/output_cmp/ > /dev/null

if [ $? -eq 0 ] ; then
    mkdir -p results
    ./tests/output_cmp/test_og > results/og_cmp 2>&1
    ./tests/output_cmp/test_ft > results/ft_cmp 2>&1
    diff results/ft_cmp results/og_cmp -c --color > results/diff_cmp 2>&1
    if [ $? -eq 0 ] ; then
        echo "$(tput setaf 2)No difference found between std and ft_containers"
    else
        echo "$(tput setaf 1)Diff in outputs (diff in ./results/diff)"
    fi
fi
