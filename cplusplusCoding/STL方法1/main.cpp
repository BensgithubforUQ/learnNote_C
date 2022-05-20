#include "for_each.h"
#include "vector_base.h"
#include "transform.h"
#include "find.h"
#include "adjacent_find.h"
#include "binary_search.h"
#include "count.h"
#include "fourKindSorting.h"
#include "fourKindCopying.h"
#include "arithmetic_generate.h"
#include "set_algorithm.h"

int main() {
	srand((unsigned int)time(NULL));//写在main里面才有效
	//test_for_each0();
	//transform_test0();

	/*find_test();
	find_test1();*/

	/*find_if_test();
	find_if_test1();
	adjacent_find_test();*/

	//binary_search_test();
	/*count_test0();
	count_test1();*/

	/*count_if_test0();
	count_if_test1();*/

	/*sort_test0();*/
	//randomshuffle_test0();
	//merge_test0();
	//reverse_test();
	
	//copy_test0();
	//replace_test0();
	//replace_if_test0();
	//swap_test0();

	/*accumulate_test();
	fill_test();*/

	//set_intersection_test(); 
	//set_union_test();
	set_difference_test();
	return 0;
}