cmake_minimum_required(VERSION 3.24)
project(Gobang)

set(CMAKE_CXX_STANDARD 17)
set(EasyX_DIR ./easyx4mingw) # 指定下载的easyx4mingw位置

include_directories(${EasyX_DIR}/include)
link_directories(${EasyX_DIR}/lib64) # 如果是32位系统，则使用lib32
link_libraries(libEasyX.a libgdi32.a libole32.a) # 链接EasyX库

add_executable(Gobang cpp/main.cpp h/AI.h cpp/AI.cpp cpp/Man.cpp h/Man.h h/Chess.h cpp/Chess.cpp h/ChessGame.h cpp/ChessGame.cpp )
