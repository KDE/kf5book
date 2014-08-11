#!/bin/sh
rm -Rf build && mkdir build
(cd threadweaver && snippetextractor introduction_to_TW.in.md ../build/01_introduction_to_TW.md)
(cd threadweaver && snippetextractor adding_tw_to_a_project.in.md ../build/02_adding_tw_to_a_project.md)
(cd karchive && snippetextractor main.md ../build/03_karchive_main.md)
(cd sonnet && snippetextractor sonnet.md.in ../build/04_sonnet.md)
(cd new-app && make && cp -Rfp screenshots ../build && cp new-app.rendered.md ../build/04_new-app.rendered.md)

(cd build && pandoc --toc --self-contained *.md -o book.html)
(cd build && pandoc --toc --self-contained *.md -o book.pdf)
(cd build && pandoc --toc --self-contained *.md -o book.epub)

