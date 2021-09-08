make re -C all_tests > /dev/null

mkdir -p results
./all_tests/test_og > results/og
./all_tests/test_ft > results/ft

diff results/ft results/og -c
