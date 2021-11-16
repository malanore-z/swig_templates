cmake_minimum_required(VERSION 3.10)

project(malanore)

set(CMAKE_CXX_STANDARD 11)

option(USE_SWIG "" ON)

if (USE_SWIG)
    # set variables
    set(SWIG_CPLUSCLPUS ON)
    set(SWIG_SOURCE ${PROJECT_SOURCE_DIR}/swig/malanore.i)
    set(JAVA_GROUP_ID "cn.malanore")
    set(JAVA_ARTIFACT_ID ${PROJECT_NAME})
    set(JAVA_LIB ${JAVA_ARTIFACT_ID}4j)
endif(USE_SWIG)

file(GLOB_RECURSE PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

message(${PROJECT_SOURCES})

if (BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
else(BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})
endif(BUILD_SHARED_LIBS)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

if (USE_SWIG)
    # scan include and link libraries
    find_package(Java REQUIRED)
    find_package(JNI REQUIRED)
    find_package(SWIG REQUIRED)
    include(UseJava)
    include(UseSWIG)

    string(REPLACE "." "/" JAVA_PACKAGE_SUBDIR ${JAVA_GROUP_ID})

    set(JAVA_GEN_DIR ${JAVA_ROOT_DIR}/${JAVA_GROUP_ID}/src/main/java/${JAVA_PACKAGE_SUBDIR})
    set(SOURCE_GEN_DIR ${JAVA_ROOT_DIR}/${JAVA_GROUP_ID}/src/main/cpp)
    set(CMAKE_SWIG_OUTDIR ${JAVA_GEN_DIR})
    set(SWIG_OUTFILE_DIR ${SOURCE_GEN_DIR})
    set(CMAKE_SWIG_FLAGS -c++ -package ${JAVA_GEN_PACKAGE})
    if (SWIG_CPLUSPLUS)
        set_property(SOURCE ${SWIG_SOURCE} PROPERTY CPLUSPLUS ON)
    endif (SWIG_CPLUSPLUS)
    if (BUILD_SHARED_LIBS)
        swig_add_library(${JAVA_LIB} TYPE SHARED LANGUAGE java SOURCES ${SWIG_SOURCE})
    else (BUILD_SHARED_LIBS)
        swig_add_library(${JAVA_LIB} TYPE STATIC LANGUAGE java SOURCES ${SWIG_SOURCE})
    endif (BUILD_SHARED_LIBS)

    swig_link_libraries(${JAVA_LIB} PRIVATE ${PROJECT_NAME})

endif(USE_SWIG)
