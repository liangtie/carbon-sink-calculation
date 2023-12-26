install(
    TARGETS carbon-sink-calculation_exe
    RUNTIME COMPONENT carbon-sink-calculation_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
