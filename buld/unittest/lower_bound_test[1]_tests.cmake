add_test( lower_bound.test_lower_bound /home/hyq/MiniOB/buld/bin/lower_bound_test [==[--gtest_filter=lower_bound.test_lower_bound]==] --gtest_also_run_disabled_tests)
set_tests_properties( lower_bound.test_lower_bound PROPERTIES WORKING_DIRECTORY /home/hyq/MiniOB/buld/unittest)
set( lower_bound_test_TESTS lower_bound.test_lower_bound)
