make re -C all_tests > /dev/null

if [ $? -eq 0 ] ; then
    mkdir -p results
    ./tests/test_og > results/og 2>&1
    ./tests/test_ft > results/ft 2>&1
    diff results/ft results/og -c --color > results/diff 2>&1
    if [ $? -eq 0 ] ; then
        echo "$(tput setaf 2)No difference found between std and ft_containers"
    else
        echo "$(tput setaf 1)c pt (diff in ./results/diff)"
    fi
fi
