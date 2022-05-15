#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'

make re
# run the following lines until #end to show the times differently
# echo "time of ft::"
# time ./ft_containers > ft_out.log
# echo
# echo "time of std::"
# time ./std_containers > std_out.log
# end
if [ -x "ft_containers" ] && [ -x "std_containers" ]
then
	./ft_containers > ft_out.log;
	./std_containers > std_out.log;

# be carefull with enabling valgrind, it might take some time, depending on the size of the used memory-area
	# valgrind --leak-check=full --track-origins=yes ./ft_containers > ft_out.log; \
	# valgrind --leak-check=full --track-origins=yes ./std_containers > std_out.log; \

# showing diff
	if [ -r ft_out.log ] && [ -r std_out.log ]
	then
		diff \
		--old-group-format=$'\e[0;31m%<\e[0m' \
		--new-group-format=$'\e[0;31m%>\e[0m' \
		--unchanged-group-format=$'\e[0;32m%=\e[0m' \
		ft_out.log std_out.log
		# other diff format
		diff -y ft_out.log std_out.log
	else
		echo -e "${RED}.log missing, can't diff, make sure no errors occured${RESET}"
	fi
else
	echo -e "${RED}no binaries to execute, check file-permissions and/or if make failed.${RESET}"
fi

echo -e "${GREEN}Finished - check the printed diffs.${RESET}"
