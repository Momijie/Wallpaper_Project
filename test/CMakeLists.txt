# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(Wallpaper_ProjectTests LANGUAGES C)

# ---- Tests ----

add_executable(Wallpaper_Project_test source/Wallpaper_Project_test.c)
target_link_libraries(Wallpaper_Project_test PRIVATE Wallpaper_Project_lib)
target_compile_features(Wallpaper_Project_test PRIVATE c_std_99)

add_test(NAME Wallpaper_Project_test COMMAND Wallpaper_Project_test)

# ---- End-of-file commands ----

add_folders(Test)
