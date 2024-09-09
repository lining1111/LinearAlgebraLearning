include_directories(${CMAKE_SOURCE_DIR})

##ch1

add_executable(ch1_section1 ch1_section1.cpp)
target_link_libraries(ch1_section1 ${LIBS})

add_executable(ch1_section2 ch1_section2.cpp)
target_link_libraries(ch1_section2 ${LIBS})

add_executable(ch1_section3 ch1_section3.cpp)
target_link_libraries(ch1_section3 ${LIBS})

add_executable(ch1_section4 ch1_section4.cpp)
target_link_libraries(ch1_section4 ${LIBS})

add_executable(ch1_section5 ch1_section5.cpp)
target_link_libraries(ch1_section5 ${LIBS})

add_executable(ch1_section6 ch1_section6.cpp)
target_link_libraries(ch1_section6 ${LIBS})

add_executable(ch1_section7 ch1_section7.cpp)
target_link_libraries(ch1_section7 ${LIBS})

##ch2 如何求解线性系统，计算各种分解，例如LU，QR，SVD，本征分解

add_executable(ch2_section1 ch2_section1.cpp)
target_link_libraries(ch2_section1 ${LIBS})

add_executable(ch2_section2 ch2_section2.cpp)
target_link_libraries(ch2_section2 ${LIBS})

##ch3 几何运算
add_executable(ch3_section1 ch3_section1.cpp)
target_link_libraries(ch3_section1 ${LIBS})