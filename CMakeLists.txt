cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(
    SURFsara-backup
    VERSION "0.0.1"
)

set(QT_MIN_VERSION "5.10.0")
set(KF5_MIN_VERSION "5.45.0")

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings NO_POLICY_SCOPE)

include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED
    Core
    Widgets
    DBus
)
set_package_properties(Qt5 PROPERTIES
	DESCRIPTION "Core library of the Qt5 framework"
	URL "http://www.qt.io"
	TYPE REQUIRED
)

find_package(KF5 REQUIRED COMPONENTS
    CoreAddons
    I18n
    Wallet
    WidgetsAddons   # KMessageBox
)

feature_summary(
	WHAT ALL
	FATAL_ON_MISSING_REQUIRED_PACKAGES
)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find includes in corresponding build directories
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

configure_file(app_meta_data.hpp.in ${CMAKE_BINARY_DIR}/generated/app_meta_data.hpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# List the source files for the project
set(SURFsara-backup_SRSC
	"main.cpp"
    "KWalletClient.cpp"
)

add_executable(${PROJECT_NAME} ${SURFsara-backup_SRSC})

target_link_libraries(
    ${PROJECT_NAME}
    ${Qt5Core_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5DBus_LIBRARIES}
    Qt5::Widgets
    KF5::CoreAddons
    KF5::I18n
    KF5::WidgetsAddons
    KF5::Wallet
)
