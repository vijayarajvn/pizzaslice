set(Database_SRCS
Connection.cpp
MySQLConnection.cpp
)

add_library(Database STATIC ${Database_SRCS})
target_link_libraries(Database)
