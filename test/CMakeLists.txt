include_directories(${partymaker_SOURCE_DIR}/include)
add_executable(daemon_application_test ../src/DaemonApplication.cpp ../src/DownloadMeasureTask.cpp DaemonApplicationTest.cpp)
target_link_libraries(daemon_application_test ${CONAN_LIBS})