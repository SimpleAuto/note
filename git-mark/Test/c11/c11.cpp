#include <iostream>
#include <string>
#include <set>
#include <tuple>
 
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>
 
// 这个例子是 说明 std::cin和std::cout的迭代器用法以及std::copy的用法展示
int main()
{
	// template<class InputIt, class OutputIt>
	// OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
    std::vector<int> from_vector(10);
    std::istream_iterator<int> i2(std::cin);
	while(*i2 != 0)
		from_vector.push_back(*i2++);

    //std::copy(i2, i2, from_vector.begin());
	std::copy(from_vector.begin(), from_vector.end(), std::ostream_iterator<int>(std::cout, ""));
 
    std::vector<int> to_vector;
    std::copy(from_vector.begin(), from_vector.end(),std::back_inserter(to_vector));
// or, alternatively,
//  std::vector<int> to_vector(from_vector.size());
//  std::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
// either way is equivalent to
//  std::vector<int> to_vector = from_vector;
 
    std::cout << "to_vector contains: ";
    std::ostream_iterator<int> i1(std::cout, "\n ");
    std::copy(to_vector.begin(), to_vector.end(), i1);
    
    //std::copy(to_vector.begin(), to_vector.end(),
     //         std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
}
