cmake_minimum_required(VERSION 3.10)

#if(BUILD_KINESIS_PLUGIN)
  # Locate the aws sdk for c++ package.
  find_package(AWSSDK REQUIRED COMPONENTS kinesis)

  file(GLOB HEADERS "include/eosio/kinesis_plugin/*.hpp")
  file(GLOB HEADERS "include/eosio/mongo_db_plugin/*.hpp")

  add_library( kinesis_plugin
               kinesis_plugin.cpp
               ${HEADERS} )
               
#  target_include_directories(kinesis_plugin
#          PUBLIC "include"
#          )
  target_include_directories( kinesis_plugin PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/appbase/include")

  target_link_libraries(kinesis_plugin
          PUBLIC chain_plugin eosio_chain appbase fc ${AWSSDK_LINK_LIBRARIES}
          )

  message("mongo_db_plugin not selected and will be omitted.")
#endif()
