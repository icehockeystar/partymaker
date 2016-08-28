include_directories(${partymaker_SOURCE_DIR}/include)
add_executable(daemon_application_test ../src/DaemonApplication.cpp ../src/DownloadMeasureTask.cpp ../src/MetricsExporter.cpp DaemonApplicationTest.cpp)
target_link_libraries(daemon_application_test ${CONAN_LIBS})
add_executable(metrics_exporter_test ../src/MetricsExporter.cpp ../src/DownloadMeasureTask.cpp
  MetricsExporterTest.cpp)
target_link_libraries(metrics_exporter_test ${CONAN_LIBS})
