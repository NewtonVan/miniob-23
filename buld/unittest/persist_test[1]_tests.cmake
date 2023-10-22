add_test( test_persist.test_persist_file_io /home/hyq/MiniOB/buld/bin/persist_test [==[--gtest_filter=test_persist.test_persist_file_io]==] --gtest_also_run_disabled_tests)
set_tests_properties( test_persist.test_persist_file_io PROPERTIES WORKING_DIRECTORY /home/hyq/MiniOB/buld/unittest)
set( persist_test_TESTS test_persist.test_persist_file_io)
