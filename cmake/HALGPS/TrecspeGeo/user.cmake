# User customization for TrecspeGeo build.
# Keep this file in version control; the generated .generated files are recreated by CMake.

# The generated project creates the target before this file is included, so add the source
# directly to the already-created target instead of trying to modify the generated list.
target_sources(HALGPS_TrecspeGeo_image_DJF9GR8v PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../Src/hw_desc/src/hw_desc_io.c"
)

target_include_directories(HALGPS_TrecspeGeo_image_DJF9GR8v PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../../.."
)

target_compile_definitions(HALGPS_TrecspeGeo_image_DJF9GR8v PRIVATE
    __AVR_ATmega4809__=1
    __ATmega4809__=1
)

target_compile_options(HALGPS_TrecspeGeo_image_DJF9GR8v PRIVATE
    -mmcu=atmega4809
    -g
    -fpack-struct
    -fshort-enums
    -O0
    -fno-inline
)


# target_compile_options(HALGPS_TrecspeGeo_image_DJF9GR8v PRIVATE
#     -mmcu=atmega4809
#     -g
#     -gdwarf-2
#     -O0
#     -fno-inline
# )
