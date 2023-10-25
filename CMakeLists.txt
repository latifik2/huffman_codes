cmake_minimum_required(VERSION 3.22)

project(HuffmanCLI)

#include_directories(headers)
add_executable(HuffmanCLI
	 source/App.cpp
	 headers/App.h
	 source/Compare.cpp
	 headers/Compare.h
	 source/Debug.cpp
	 headers/Debug.h
	 source/Huffman.cpp
	 headers/Huffman.h
	 source/TreeNode.cpp
	 headers/TreeNode.h
)

add_library(BitArray 
	lib/BitArray.cpp
	lib/BitArray.h
)


target_link_libraries(HuffmanCLI BitArray)

