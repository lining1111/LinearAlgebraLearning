cmake_minimum_required(VERSION 3.27)
project(LinearAlgebraLearning)

set(CMAKE_CXX_STANDARD 14)
include_directories(${PROJECT_SOURCE_DIR})

set(USE_QT 1)

if (USE_QT)
    message("use qt")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)



list(APPEND CMAKE_PREFIX_PATH "/home/lining/Qt/5.15.0/gcc_64")
set(QT_PATH "/home/lining/Qt/5.15.0/gcc_64")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
    include_directories(${QT_PATH}/include)
    set(LIBS
            Qt::Core
            Qt::Gui
            Qt::Widgets)
endif ()

find_package(gflags REQUIRED)
find_package(glog REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(fmt REQUIRED)
find_package(Poco REQUIRED)
find_package(xpack REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

set(LIBS ${LIBS} gflags::gflags glog::glog SQLite::SQLite3 fmt::fmt Poco::Poco xpack::xpack Eigen3::Eigen)

if (OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    set(LIBS ${LIBS} ${OpenCV_LIBS})
endif ()

message("LIBS:${LIBS}")
#cmake依赖
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
include(utility)
include(CPM)

##源文件列表相关
set(filtration_dirlist cmake-build-debug .idea .git conan cmake test)
SUBDIRLISTINCLUDE(SRC_DIRS ${CMAKE_SOURCE_DIR} 2 ${filtration_dirlist})
message(STATUS "SRC_DIRS:${SRC_DIRS}")
foreach (src_dir ${SRC_DIRS})
    aux_source_directory(${src_dir} SRC_FILES)
endforeach (src_dir)
list(REMOVE_ITEM SRC_FILES ./main.cpp)


add_executable(LinearAlgebraLearning main.cpp ${SRC_FILES})
target_link_libraries(LinearAlgebraLearning ${LIBS})
redefine_file_macro(LinearAlgebraLearning)

add_subdirectory(test)