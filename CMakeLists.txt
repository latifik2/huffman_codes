cmake_minimum_required(VERSION 3.22)

project(HuffmanCLI)

include_directories(headers)
add_executable(HuffmanCLI
	 source/App.cpp
	 source/Compare.cpp
	 source/Debug.cpp
	 source/Huffman.cpp
	 source/TreeNode.cpp
)

add_library(BitArray 
	lib/BitArray.cpp
	lib/BitArray.h
)


target_link_libraries(HuffmanCLI BitArray)

