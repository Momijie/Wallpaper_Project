install(
    TARGETS Wallpaper_Project_exe
    RUNTIME COMPONENT Wallpaper_Project_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
