cmake_minimum_required(VERSION 3.15)
project(Wallpapers LANGUAGES C)

# Собираем все .c в src
file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")

# Создаём исполняемый
add_executable(wallpapers ${PROJECT_SOURCES})

# Убираем консоль при запуске
set_target_properties(wallpapers PROPERTIES WIN32_EXECUTABLE TRUE)

# Стандарт C
set_target_properties(wallpapers PROPERTIES
  C_STANDARD 11
  C_STANDARD_REQUIRED YES
)

# Включаем заголовки из src
target_include_directories(wallpapers PRIVATE "${CMAKE_SOURCE_DIR}/src")

# Чтение флагов компиляции из compile_flags.txt (пробелы или переносы)
set(COMPILE_FLAGS_FILE "${CMAKE_SOURCE_DIR}/compile_flags.txt")
if(EXISTS "${COMPILE_FLAGS_FILE}")
  file(READ "${COMPILE_FLAGS_FILE}" _flags_raw)
  string(STRIP "${_flags_raw}" _flags_raw)
  string(REPLACE "\r\n" "\n" _flags_raw "${_flags_raw}")
  string(REPLACE "\r" "\n" _flags_raw "${_flags_raw}")
  string(REPLACE "\n" " " _flags_raw "${_flags_raw}")
  string(REGEX REPLACE " +" ";" _flags_list "${_flags_raw}")
  if(_flags_list)
    target_compile_options(wallpapers PRIVATE ${_flags_list})
  endif()
endif()
