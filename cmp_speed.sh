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
        echo "$(tput setaf 2)  Same output"
    else
        echo "$(tput setaf 1)  Diff in output, find diff in ./results/"
    fi
fi

echo

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
        echo "$(tput setaf 2)  Same output"
    else
        echo "$(tput setaf 1)  Diff in output, find diff in ./results/"
    fi
fi

echo
# Speed Comparison for map
make re -C ./tests/time_map/ > /dev/null
if [ $? -eq 0 ] ; then
    mkdir -p results
    echo "$(tput setaf 2)Test map speed: "
    echo -n "$(tput sgr0)   ft : "
    $TIMECMD ./tests/time_map/maptime_ft > results/ft_map_spd
    echo -n "$(tput sgr0 2)  std : "
    $TIMECMD ./tests/time_map/maptime_og > results/og_map_spd
    diff results/ft_map_spd results/og_map_spd -c --color > results/diff_map_spd 2>&1
    if [ $? -eq 0 ] ; then
        echo "$(tput setaf 2)  Same output"
    else
        echo "$(tput setaf 1)  Diff in output, find diff in ./results/"
    fi
fi

echo
# Speed Comparison for set
make re -C ./tests/time_set/ > /dev/null
if [ $? -eq 0 ] ; then
    mkdir -p results
    echo "$(tput setaf 2)Test set speed: "
    echo -n "$(tput sgr0)   ft : "
    $TIMECMD ./tests/time_set/settime_ft > results/ft_set_spd
    echo -n "$(tput sgr0 2)  std : "
    $TIMECMD ./tests/time_set/settime_og > results/og_set_spd
    diff results/ft_set_spd results/og_set_spd -c --color > results/diff_set_spd 2>&1
    if [ $? -eq 0 ] ; then
        echo "$(tput setaf 2)  Same output"
    else
        echo "$(tput setaf 1)  Diff in output, find diff in ./results/"
    fi
fi
