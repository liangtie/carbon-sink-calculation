install(
    TARGETS carbon-sink-calculation
    RUNTIME COMPONENT carbon-sink-calculation_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
