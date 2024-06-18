cmake_minimum_required(VERSION 3.5)

project(lab4 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets PrintSupport REQUIRED)

include_directories("D:/libraries/boost_1_84_0")

include_directories()

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        psfparam.h
	psfparam.cpp
        psfcalc.h
        psfcalc.cpp
        sample.h
        SampleComplex.h
        SampleComplex.cpp
        qcustomplot.h
        qcustomplot.cpp
		PSFcalc.rc
)

add_executable(lab4 WIN32
    ${PROJECT_SOURCES})

set(FFTW_PATH "D:/libraries/fftw-3.3.5-dll64")
include_directories(${FFTW_PATH})
set(FFTW_LIB "${FFTW_PATH}/libfftw3-3.lib")

target_link_libraries(lab4 PRIVATE Qt6::Widgets Qt6::PrintSupport ${QT_QTMAIN_LIBRARY} ${FFTW_LIB})

