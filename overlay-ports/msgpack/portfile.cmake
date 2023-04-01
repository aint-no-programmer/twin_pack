if (EXISTS ${CURRENT_INSTALLED_DIR}/include/msgpack/pack.h)
    message(FATAL_ERROR "Cannot install ${PORT} when rest-rpc is already installed, please remove rest-rpc using \"./vcpkg remove rest-rpc:${TARGET_TRIPLET}\"")
endif()

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO msgpack/msgpack-c
    REF cpp-4.1.3
    SHA512 1252a2d61b119e9a8db6cc3667d2ae3234784d6607e2d08b836ab2f561455aa8c14ac134de0e8bb47f85a9fa86a9b325babd0a5a437daa0f270143d07738adcf
    HEAD_REF master
)

if(VCPKG_LIBRARY_LINKAGE STREQUAL static)
    set(MSGPACK_ENABLE_SHARED OFF)
    set(MSGPACK_ENABLE_STATIC ON)
else()
    set(MSGPACK_ENABLE_SHARED ON)
    set(MSGPACK_ENABLE_STATIC OFF)
endif()

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
    OPTIONS
        # -DMSGPACK_ENABLE_SHARED=${MSGPACK_ENABLE_SHARED}
        # -DMSGPACK_ENABLE_STATIC=${MSGPACK_ENABLE_STATIC}
		-DMSGPACK_USE_BOOST=OFF
		-DMSGPACK_NO_BOOST=ON
        -DMSGPACK_BUILD_EXAMPLES=OFF
        -DMSGPACK_BUILD_TESTS=OFF)

vcpkg_install_cmake()
vcpkg_copy_pdbs()
vcpkg_fixup_cmake_targets(CONFIG_PATH lib/cmake/msgpackc-cxx)

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)

file(COPY ${SOURCE_PATH}/COPYING DESTINATION ${CURRENT_PACKAGES_DIR}/share/msgpack)
file(RENAME ${CURRENT_PACKAGES_DIR}/share/msgpack/COPYING ${CURRENT_PACKAGES_DIR}/share/msgpack/copyright)

vcpkg_fixup_pkgconfig()
