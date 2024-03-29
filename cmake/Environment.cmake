# Try obtain by -DCMAKE_TOOLCHAIN_FILE cmake's option
#
if (DEFINED CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Using user's environment vcpkg toolchain: " ${CMAKE_TOOLCHAIN_FILE})
    include(${CMAKE_TOOLCHAIN_FILE})

else ()

    # As alternative, just paste it here:
    #
    if (NOT DEFINED RUN_ON_CI OR NOT RUN_ON_CI)
        set(CMAKE_TOOLCHAIN_FILE C:/Users/ALEKSEY/vcpkg/scripts/buildsystems/vcpkg.cmake)
    endif ()

endif ()