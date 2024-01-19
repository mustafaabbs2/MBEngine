cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(FlowSolver)


add_subdirectory(Driver)
add_subdirectory(LinearSolver)
#add_subdirectory(Mesher)
add_subdirectory(ParticleSolver)
