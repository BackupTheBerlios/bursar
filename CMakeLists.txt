# set project title
PROJECT( bursar )

# set version
SET( APP_VERSION "0.0.1" )

# set data directory
SET( DATA_DIR "../share/bursar" )

# set db templates directory
SET( DB_TEMPLATES_DIR "${DATA_DIR}/dbtemplates/" )

# generate config file
configure_file( src/cmake/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h )

# create apple bundle
IF( APPLE )
    SET( PROGNAME Bursar )
    #SET( MACOSX_BUNDLE_ICON_FILE Bursar.icns )
    SET( MACOSX_BUNDLE_SHORT_VERSION_STRING ${APP_VERSION} )
    SET( MACOSX_BUNDLE_VERSION ${APP_VERSION} )
    SET( MACOSX_BUNDLE_LONG_VERSION_STRING Version ${APP_VERSION} )
    SET( CMAKE_OSX_ARCHITECTURES i386 )
ELSE( APPLE )
    SET( PROGNAME bursar )
ENDIF( APPLE )

# set cmake settings
CMAKE_MINIMUM_REQUIRED( VERSION 2.6.2 )
SET( CMAKE_COLOR_MAKEFILE ON )
SET( CMAKE_VERBOSE_MAKEFILE ON )
SET( CMAKE_INCLUDE_CURRENT_DIR TRUE )

# include source directories
INCLUDE_DIRECTORIES( src )
INCLUDE_DIRECTORIES( src/base )
INCLUDE_DIRECTORIES( src/common )
INCLUDE_DIRECTORIES( src/data )
INCLUDE_DIRECTORIES( src/widgets )
INCLUDE_DIRECTORIES( src/wizards )
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} )

# add headers
INCLUDE( cmake/headers.cmake )

# add sources
INCLUDE( cmake/sources.cmake )

# add ui
INCLUDE( cmake/ui.cmake )

# add resources
SET( bursar_RESOURCES src/resources/bursar.qrc )

# add db templates
INCLUDE( cmake/dbtemplates.cmake )


# enable warnings
IF( CMAKE_COMPILER_IS_GNUCXX )
    ADD_DEFINITIONS( -g -Wall )
ENDIF( CMAKE_COMPILER_IS_GNUCXX )

# enable QtGui
SET( QT_USE_QTGUI TRUE )

# enable QtXml
SET( QT_USE_QTSQL TRUE )

# enable QtSql
SET( QT_USE_QTXML TRUE )

# find Qt4 libraries
FIND_PACKAGE( Qt4 REQUIRED )

# add Qt4 macros and variables
INCLUDE( ${QT_USE_FILE} )

# prepare Qt4 specifics
QT4_ADD_RESOURCES( bursar_RESOURCES_SRCS ${bursar_RESOURCES} )

# generate ui_xxx.h files
QT4_WRAP_UI( bursar_UI_HDRS ${bursar_UI} )

# generate moc_xxx.h files
QT4_WRAP_CPP( bursar_MOC_HDRS ${bursar_HDRS} )

# build application
IF( APPLE )
    # TODO
ELSE( APPLE )
    ADD_EXECUTABLE( ${PROGNAME} ${bursar_SRCS} ${bursar_MOC_HDRS} ${bursar_RESOURCES_SRCS} ${bursar_UI_HDRS} )
    TARGET_LINK_LIBRARIES( ${PROGNAME} ${QT_LIBRARIES} )
ENDIF( APPLE )

# install application and files required
# note: will install to CMAKE_INSTALL_PREFIX, which can be set e.g.
#       cmake -DCMAKE_INSTALL_PREFIX=/usr
INSTALL( TARGETS ${PROGNAME} DESTINATION bin )
INSTALL( FILES ${bursar_DBTEMPLATES} DESTINATION share/bursar/dbtemplates )

