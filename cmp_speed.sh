TIMECMD="/usr/bin/time -f'%E'"

# Speed Comparison for vector
make re -C ./tests/time_vector/ > /dev/null
if [ $? -eq 0 ] ; then
    mkdir -p results
    echo "$(tput setaf 2)Test vector speed: "
    echo -n "$(tput sgr0)   ft : "
    $TIMECMD ./tests/time_vector/vectime_ft > results/ft_vector_spd
    echo -n "$(tput sgr0 2)  std : "
    $TIMECMD ./tests/time_vector/vectime_og > results/og_vector_spd
    diff results/ft_vector_spd results/og_vector_spd -c --color > results/diff_vector_spd 2>&1
    if [ $? -eq 0 ] ; then
        echo "$(tput setaf 2)  Same ouputs"
    else
        echo "$(tput setaf 1)  Diff in outputs, find diff in ./results/"
    fi
fi

# Speed Comparison for stack
make re -C ./tests/time_stack/ > /dev/null
if [ $? -eq 0 ] ; then
    mkdir -p results
    echo "$(tput setaf 2)Test stack speed: "
    echo -n "$(tput sgr0)   ft : "
    $TIMECMD ./tests/time_stack/stacktime_ft > results/ft_stack_spd
    echo -n "$(tput sgr0 2)  std : "
    $TIMECMD ./tests/time_stack/stacktime_og > results/og_stack_spd
    diff results/ft_stack_spd results/og_stack_spd -c --color > results/diff_stack_spd 2>&1
    if [ $? -eq 0 ] ; then
        echo "$(tput setaf 2)  Same ouputs"
    else
        echo "$(tput setaf 1)  Diff in outputs, find diff in ./results/"
    fi
fi
