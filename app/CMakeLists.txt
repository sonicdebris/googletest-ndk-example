# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.4.1)
add_library( native-lib SHARED
                src/main/cpp/native-lib.cpp
                src/main/cpp/Foo.cpp)
find_library( log-lib log )
target_link_libraries( native-lib ${log-lib} )

# build tests:

set(GOOGLETEST_ROOT ${ANDROID_NDK}/sources/third_party/googletest/googletest)
add_library(gtest STATIC ${GOOGLETEST_ROOT}/src/gtest_main.cc ${GOOGLETEST_ROOT}/src/gtest-all.cc)
target_include_directories(gtest PRIVATE ${GOOGLETEST_ROOT})
target_include_directories(gtest PUBLIC ${GOOGLETEST_ROOT}/include)

add_executable(footest src/main/cpp/test.cpp)
target_link_libraries(footest gtest native-lib)

# run tests:

#find_program(ADB adb PATHS "/home/android/sdk/platform-tools")
set(ADB /home/android/sdk/platform-tools/adb)
add_custom_command(TARGET footest POST_BUILD
    COMMAND ${ADB} shell mkdir -p /data/local/tmp/${ANDROID_ABI}
    COMMAND ${ADB} push $<TARGET_FILE:native-lib> /data/local/tmp/${ANDROID_ABI}/
    COMMAND ${ADB} push $<TARGET_FILE:footest> /data/local/tmp/${ANDROID_ABI}/
    COMMAND ${ADB} shell chmod 775 /data/local/tmp/${ANDROID_ABI}/footest
    COMMAND ${ADB} shell \"export LD_LIBRARY_PATH=/data/local/tmp/${ANDROID_ABI}\; /data/local/tmp/${ANDROID_ABI}/footest\")

