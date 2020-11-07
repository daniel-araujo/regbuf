cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE Debug)

project(reg_tests)

enable_testing()

add_library(reg ../reg.c ../reg.h)
target_compile_options(reg PRIVATE -Wall -Wextra -pedantic -Werror)

# For tests defined in a single C file.
function(test_single_c_file target)
    add_executable(${target} ${target}.c)
    target_link_libraries(${target} reg)
    add_test(NAME ${target} COMMAND ${target})
endfunction(test_single_c_file)

# For tests defined in posix shell.
function(test_sh target)
    add_test(NAME ${target} COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/${target})
endfunction(test_sh)

test_sh(readme__example)

test_single_c_file(bugfix__popping_length_of_partially_filled_region_moves_head_to_next_region)

test_single_c_file(reg_add__does_not_insert_elements_out_of_bounds_of_region)
test_single_c_file(reg_add__fills_first_region_and_half_of_second)
test_single_c_file(reg_add__fills_three_regions_and_ignores_overfill)
test_single_c_file(reg_add__fills_two_regions_and_remaining_one)
test_single_c_file(reg_add__first_time_places_elements_in_first_region)
test_single_c_file(reg_add__remembers_where_it_left_off_in_new_region)
test_single_c_file(reg_add__remembers_where_it_left_off_in_same_region)
test_single_c_file(reg_add__when_current_region_fills_up_moves_to_next)
test_single_c_file(reg_add__wraps_around_from_second_region_to_first)
test_single_c_file(reg_add__wraps_around_if_space_is_free)

test_single_c_file(reg_destroy__use_after_free_detection)

test_single_c_file(reg_get__copies_elements_to_pointer)
test_single_c_file(reg_get__does_nothing_if_length_is_0)
test_single_c_file(reg_get__removes_elements)
test_single_c_file(reg_get__retrives_array_of_elements_in_two_regions)
test_single_c_file(reg_get__wraps_around)

test_single_c_file(reg_pop__does_not_clear_data_in_region)
test_single_c_file(reg_pop__from_first_region_up_to_tail_in_second_region)
test_single_c_file(reg_pop__next_add_continues_where_it_left_off)
test_single_c_file(reg_pop__up_to_tail_in_first_region)
test_single_c_file(reg_pop__wraps_around)
