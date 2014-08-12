cmake_minimum_required(VERSION 2.6)
project(book NONE)

find_program(SNIPPETEXTRACTOR snippetextractor)
if (NOT SNIPPETEXTRACTOR)
    message(FATAL_ERROR "Need snippetextractor")
endif()

find_program(PANDOC pandoc)
if (NOT PANDOC)
    message(FATAL_ERROR "Need pandoc")
endif()

function(extract_snippets dir input output)
    add_custom_command(OUTPUT ${output}
        COMMAND ${SNIPPETEXTRACTOR} ${input} ${CMAKE_CURRENT_BINARY_DIR}/${output}
        MAIN_DEPENDENCY ${dir}/${input}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${dir}
        COMMENT "Extracting snippets from ${input}"
    )
endfunction()

extract_snippets(threadweaver introduction_to_TW.in.md 01_introduction_to_TW.md)
extract_snippets(threadweaver adding_tw_to_a_project.in.md 02_adding_tw_to_a_project.md)
extract_snippets(karchive main.md 03_karchive_main.md)
#extract_snippets(sonnet sonnet.md.in 04_sonnet.md)

set(files 01_introduction_to_TW.md 02_adding_tw_to_a_project.md 03_karchive_main.md)

add_custom_command(OUTPUT book.html
    COMMAND ${PANDOC} --toc --self-contained ${files} -o book.html
    DEPENDS ${files}
)
add_custom_target(book ALL DEPENDS book.html)