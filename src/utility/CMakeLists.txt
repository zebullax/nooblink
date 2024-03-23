TARGET_SOURCES(nooblink
    PUBLIC conversion.cpp
    PUBLIC byte_util.cpp
)

TARGET_SOURCES(nooblink_test
        PRIVATE byte_util.t.cpp)