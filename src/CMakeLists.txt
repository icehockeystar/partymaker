include_directories(${partymaker_SOURCE_DIR}/include)

set(SOURCE_FILES DaemonStarter.cpp DaemonApplication.cpp DownloadMeasureTask.cpp MetricsExporter.cpp)

add_executable(partymaker_daemon ${SOURCE_FILES})
target_link_libraries(partymaker_daemon ${CONAN_LIBS})