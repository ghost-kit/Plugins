#DateTime Libraries specific to our GHOST needs

add_external_project(
    DateTime

    CMAKE_ARGS
        -DMACOSX_VERSION_MIN=10.6

    BUILD_COMMAND
        make

    INSTALL_COMMAND
        make install

)
