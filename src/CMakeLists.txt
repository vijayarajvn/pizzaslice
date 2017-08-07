add_subdirectory(lib)

set(PizzaSlice_SRCS CommandLinePizzaSlice.cpp)

add_executable(pizzaslice ${PizzaSlice_SRCS} )

target_link_libraries(pizzaslice
Database
)
