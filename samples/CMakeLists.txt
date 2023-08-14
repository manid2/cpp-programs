#####################################################################
# Target level CMakeLists.txt file
#####################################################################

#-- targets
add_executable(array-2d src/array-2d.cpp)
add_executable(array-using-smart-ptr src/array-using-smart-ptr.cpp)
add_executable(extend-std-containers src/extend-std-containers.cpp)
add_executable(find-n-replace-string src/find-n-replace-string.cpp)
add_executable(threads-odd-even-seq-using-lamda
  src/threads-odd-even-seq-using-lamda.cpp)
add_executable(threads-odd-even-seq-using-predicate
  src/threads-odd-even-seq-using-predicate.cpp)

#-- link targets to libs
target_link_libraries(threads-odd-even-seq-using-lamda pthread)
target_link_libraries(threads-odd-even-seq-using-predicate pthread)
