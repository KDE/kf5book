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
extract_snippets(new-app new-app.md 04_new-app.md)

file(COPY new-app/screenshots DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(files book.md 01_introduction_to_TW.md 02_adding_tw_to_a_project.md 03_karchive_main.md 04_new-app.md)

add_custom_command(OUTPUT KDE-Frameworks-Cookbook.html
    COMMAND ${PANDOC} --toc --self-contained ${files} -o book.html
    DEPENDS ${files}
)
add_custom_target(htmlbook ALL DEPENDS KDE-Frameworks-Cookbook.html)

add_custom_command(OUTPUT KDE-Frameworks-Cookbook.epub
    COMMAND ${PANDOC} -t epub3 --no-highlight -S --toc --epub-metadata=book-metadata.xml --number-sections --epub-cover-image=covers/cover-front.png --self-contained ${files} -o KDE-Frameworks-Cookbook.epub
    DEPENDS ${files}
)
add_custom_target(epubbook ALL DEPENDS KDE-Frameworks-Cookbook.epub)


