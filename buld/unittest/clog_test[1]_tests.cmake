add_test( test_clog.test_clog /home/hyq/MiniOB/buld/bin/clog_test [==[--gtest_filter=test_clog.test_clog]==] --gtest_also_run_disabled_tests)
set_tests_properties( test_clog.test_clog PROPERTIES WORKING_DIRECTORY /home/hyq/MiniOB/buld/unittest)
set( clog_test_TESTS test_clog.test_clog)
