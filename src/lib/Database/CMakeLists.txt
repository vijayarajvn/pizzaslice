set(Database_SRCS
Connection.cpp
MySQLConnection.cpp
)

if (WIN32)
    set (Database_SRCS ${Database_SRCS} 
    Connection.h
    MySQLConnection.h
    Structs.h)
endif (WIN32)


add_library(Database STATIC ${Database_SRCS})
target_link_libraries(Database Utils)
