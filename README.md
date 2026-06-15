# Wallpapers App 
## Description
Simple terminal app for changing wallpapers

## Quick start
### Windows
1. Download the MinGW tools and cmake
2. Add this tools to your PATH variable
3. Go to build directory
4. Run this commands
```BASH
cmake .. -G "MinGW Makefiles"
cmake --build . -- -j4
```
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
