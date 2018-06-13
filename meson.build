project('libstack', 'cpp',
        default_options : ['cpp_std=c++17'])

incdir = include_directories('include')

testlib = shared_library('master_test', 'test/t_master.cpp',
                         include_directories : incdir)
test_obj_file = testlib.extract_objects('test/t_master.cpp')

executable('test_dynamic_array', 'test/t_dynamic_array.cpp', 
           objects : test_obj_file, 
           include_directories : incdir)
