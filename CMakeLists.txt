cmake_minimum_required(VERSION 2.6)
project(ROvolets)
aux_source_directory(. SRC_LIST)
add_executable(ROvolets SharedElements.cpp
                        SharedElements.h
                        evaluateSolution.cpp
                        recuit.h
                        recuit.cpp
                        ressource.h
                        ressource.cpp)


