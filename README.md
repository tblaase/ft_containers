# ft_containers
My solution for ft_containers of the common-core of 42 school.

## Basics
The goal of this project was to recode the STL-containers of c++98.<br>
The mandatory containers where `std::vector`, `std::stack` and `std::map`.<br>
They had to have the exact same structure as the original containers and support every function the standard-containers supported.<br>

## Testing
In the end of the project you had to make sure the containers worked as intended and had a good performance.<br>
For that I created a Makefile that compiles my [main.cpp](/src/main.cpp) with `make all` into two different binaries:
 - once with the `std::` namespace
 - once with the `ft::` namespace<br>
After that you can run them individually to see the output.<br>
Or run my [`test.sh`](/test.sh), which does not need the `make all` before, since it runs `make re` anyways to make sure everything is in perfect working order.<br>
My testing script will run the two binaries one after another, put their output into .log files and diff them in two different ways.<br>
![diff1](/readme_additions/diff1.png)<br>
This diff shows differences in red and similarities in green.<br>
<br>
![diff2](/readme_additions/diff2.png)<br>
This diff shows the `ft::containers` output on the left and the `std::containers` output on the right.<br>
<br>
## Conclusions
This project teached the very inner workings of the c++ STL-containers, which made working with them in later projects like [webserv](https://github.com/tblaase/webserv) a lot easier.<br>
It also shows that my red_black_tree is far from perfect, which made my ft::map be a lot slower than the std::map, which can be seen in the output of my [main.cpp](/src/main.cpp).<br>
