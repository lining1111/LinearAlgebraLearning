include_directories(${CMAKE_SOURCE_DIR})

add_executable(ch1_section1 ch1_section1.cpp)
target_link_libraries(ch1_section1 ${LIBS})

add_executable(ch1_section2 ch1_section2.cpp)
target_link_libraries(ch1_section2 ${LIBS})

add_executable(ch1_section3 ch1_section3.cpp)
target_link_libraries(ch1_section3 ${LIBS})

add_executable(ch1_section4 ch1_section4.cpp)
target_link_libraries(ch1_section4 ${LIBS})