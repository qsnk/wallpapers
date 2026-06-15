# Wallpapers App 
## Description
Simple terminal app for changing wallpapers

## Quick start
### Windows
1. Download the MinGW tools and cmake
2. Add this tools to your PATH variable
3. Go to build directory
4. Run this commands:
```BASH
cmake .. -G "MinGW Makefiles"
cmake --build . -- -j4
```

Run app in terminal:
```BASH
.\build\wallpapers.exe
```

Create windows scheduled task:
```BASH
.\build\wallpapers.exe -t
```

For better user experience you should do this steps:
1. Navigate to task scheduler
2. Find task named "Wallpaper changing"
3. Double click on it
4. In the "General" tab – Set "run with highest privileges" to checked
5. In the "Actions" tab – Double click on executable, then in the section "Working directory" paste full path to folder with your "config.ini" file.


### Unix like
Soon...

## About configuration file
Example:
```TXT
[settings]
strategy = 3
type = 2
interval = 1
source = C:\path\to\images (Windows style)
exe_path = C:\path\to\executable
```

Fields description:
| name | description |
|---|---|
| strategy | Changing strategy |
| type |Schedule type |
| interval | Interval between changing |
| source | Background images source |
| exe_path | Location of executable to create task with |

Strategy values:
| value | description |
|---|---|
| 1 | static (no change) |
| 2 | round robin (next one) |
| 3 | random |

Schedule type values:
| value | description |
|---|---|
| 1 | minute |
| 2 | hourly |
| 3 | daily |
| 4 | weekly |
| 5 | monthly |
