set( brightfuture_SRCS
    main.cpp
    brightfuture.cpp
)

add_executable( brightfuture ${brightfuture_SRCS} )

target_link_libraries( brightfuture
    Qt5::Widgets
    KF5::CoreAddons
    KF5::I18n
    KF5::Plotting
    KF5::ConfigGui
)

install( TARGETS brightfuture ${INSTALL_TARGETS_DEFAULT_ARGS} )
install( PROGRAMS brightfuture.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
