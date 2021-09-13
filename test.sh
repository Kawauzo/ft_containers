make re -C all_tests > /dev/null

if [ $? -eq 0 ] ; then
    mkdir -p results
    ./all_tests/test_og > results/og 2>&1
    ./all_tests/test_ft > results/ft 2>&1
    diff results/ft results/og -c
fi
