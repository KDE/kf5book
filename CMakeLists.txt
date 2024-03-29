cmake_minimum_required(VERSION 2.6)
project(book NONE)

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(KDEInstallDirs)

set(BOOKDIR ${CMAKE_INSTALL_DATAROOTDIR}/doc/frameworks5)

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
extract_snippets(threadweaver/threadweaver/examples HelloWorldRaw.in.md 03_HelloWorldRaw.md)
extract_snippets(threadweaver/threadweaver/examples HelloInternet.in.md 04_HelloInternet.md)
extract_snippets(threadweaver/threadweaver/examples ThumbNailer.in.md 05_ThumbNailer.md)
extract_snippets(karchive main.md 06_karchive_main.md)
extract_snippets(kitemmodels kitemmodels.md 06_kitemmodels_main.md)
extract_snippets(sonnet sonnet.in.md 07_sonnet.md)
extract_snippets(ki18n ki18n.in.md 08_ki18n.md)
extract_snippets(new-app new-app.md 09_new-app.md)
extract_snippets(kidletime intro_kidletime.in.md 10_kidletime.md)

file(COPY introduction/screenshots DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY new-app/screenshots DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY threadweaver/threadweaver/examples/screenshots DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY covers DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(files 
    ${CMAKE_SOURCE_DIR}/book.md
    ${CMAKE_SOURCE_DIR}/introduction/frameworks5.md
    01_introduction_to_TW.md
    02_adding_tw_to_a_project.md
    03_HelloWorldRaw.md
    04_HelloInternet.md
    05_ThumbNailer.md
    06_karchive_main.md
    06_kitemmodels_main.md
    07_sonnet.md
    08_ki18n.md
    09_new-app.md
    10_kidletime.md
)

add_custom_command(OUTPUT KDE-Frameworks-Cookbook.html
    COMMAND ${PANDOC} --toc --self-contained ${files} -o KDE-Frameworks-Cookbook.html
    DEPENDS ${files}
)
add_custom_target(htmlbook ALL DEPENDS KDE-Frameworks-Cookbook.html)

add_custom_command(OUTPUT KDE-Frameworks-Cookbook.pdf
    COMMAND ${PANDOC} --toc --number-sections ${files} -o KDE-Frameworks-Cookbook.pdf
    --template=${CMAKE_SOURCE_DIR}/pdf-template.tex
    --top-level-division=chapter
    DEPENDS ${files} pdf-template.tex
)
add_custom_target(pdfbook ALL DEPENDS KDE-Frameworks-Cookbook.pdf)

add_custom_command(OUTPUT KDE-Frameworks-Cookbook.epub
    COMMAND ${PANDOC} -t epub3 --no-highlight --toc
    --epub-metadata=${CMAKE_SOURCE_DIR}/book-metadata.xml --number-sections
    --epub-cover-image=${CMAKE_SOURCE_DIR}/covers/cover-front.png --self-contained ${files} -o KDE-Frameworks-Cookbook.epub
    DEPENDS ${files}
)
add_custom_target(epubbook ALL DEPENDS KDE-Frameworks-Cookbook.epub)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/KDE-Frameworks-Cookbook.html
        ${CMAKE_CURRENT_BINARY_DIR}/KDE-Frameworks-Cookbook.epub
        ${CMAKE_CURRENT_BINARY_DIR}/KDE-Frameworks-Cookbook.pdf
    DESTINATION ${BOOKDIR}
)

