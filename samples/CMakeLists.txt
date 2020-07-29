file(GLOB sample_sources CONFIGURE_DEPENDS "*.cpp")

set(DIFF ${CMAKE_COMMAND} -E compare_files --ignore-eol)

foreach (sample IN LISTS sample_sources)
    get_filename_component(target "${sample}" NAME_WE)
    add_executable(${target} ${sample})
    target_link_libraries(${target} PRIVATE buildit::buildit)
    set_target_properties(${target} PROPERTIES ENABLE_EXPORTS TRUE)

    add_test(NAME ${target}
             COMMAND ${target} >${target}.0 && ${DIFF} ${target}.0 ${CMAKE_CURRENT_SOURCE_DIR}/outputs/${target})
endforeach ()
