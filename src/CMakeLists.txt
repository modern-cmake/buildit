add_library(buildit_buildit
            blocks/annotation_finder.cpp
            blocks/block.cpp
            blocks/block_visitor.cpp
            blocks/c_code_generator.cpp
            blocks/expr.cpp
            blocks/for_loop_finder.cpp
            blocks/label_inserter.cpp
            blocks/loop_finder.cpp
            blocks/stmt.cpp
            blocks/var.cpp
            blocks/var_namer.cpp
            builder/annotate.cpp
            builder/builder.cpp
            builder/builder_context.cpp
            builder/builder_context_support.cpp
            util/tracer.cpp)
set_target_properties(buildit_buildit PROPERTIES EXPORT_NAME buildit)
add_library(buildit::buildit ALIAS buildit_buildit)

target_include_directories(buildit_buildit PUBLIC $<BUILD_INTERFACE:${buildit_SOURCE_DIR}/include>)
target_compile_features(buildit_buildit PUBLIC cxx_std_11)
