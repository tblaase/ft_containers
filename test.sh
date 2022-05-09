#!/bin/bash

make re
# run the following lines until #end -1 to show the times differently
# echo "time of ft::"
# time ./ft_containers > ft_out.log
# echo
# echo "time of std::"
# time ./std_containers > std_out.log
# end
./ft_containers > ft_out.log
./std_containers > std_out.log

# be carefull with enabling valgrind, it might take some time, depending on the size of the used memory-area
# valgrind --leak-check=full --track-origins=yes ./ft_containers > ft_out.log
# valgrind --leak-check=full --track-origins=yes ./std_containers > std_out.log

diff \
	--old-group-format=$'\e[0;31m%<\e[0m' \
	--new-group-format=$'\e[0;31m%>\e[0m' \
	--unchanged-group-format=$'\e[0;32m%=\e[0m' \
	ft_out.log std_out.log

# other diff format

diff -y ft_out.log std_out.log
