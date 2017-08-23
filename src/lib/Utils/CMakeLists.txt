set (Utils_SRCS 
  UtilityFunctions.cpp
  )

if (WIN32)
  set (Utils_SRCS ${Utils_SRCS} 
    UtilityFunctions.h
    )
endif (WIN32)

add_library (Utils STATIC ${Utils_SRCS}) 

target_link_libraries (Utils 
  ${Boost_LIBRARIES})

