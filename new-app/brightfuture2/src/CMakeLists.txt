set( brightfuture_SRCS
    main.cpp
    brightfuture.cpp
)

ki18n_wrap_ui(brightfuture_SRCS brightfuture.ui)

add_executable( brightfuture ${brightfuture_SRCS} )

target_link_libraries( brightfuture
    Qt5::Widgets
    KF5::CoreAddons
    KF5::I18n
    KF5::Plotting
)

install( TARGETS brightfuture ${INSTALL_TARGETS_DEFAULT_ARGS} )
install( PROGRAMS brightfuture.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
