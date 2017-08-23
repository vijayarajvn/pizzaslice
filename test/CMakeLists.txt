set(MySQLConnectionQueryTestApp_SRCS MySQLConnectionQueryTestApp.cpp)

add_executable(MySQLConnectionQueryTestApp ${MySQLConnectionQueryTestApp_SRCS} )

target_link_libraries(
MySQLConnectionQueryTestApp
Database 
Utils ${Boost_LIBRARIES} ${MARIADB_LIBRARIES})
