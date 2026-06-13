# Wallpapers App 
## Description
Simple app for changing wallpapers
## Config file
Example:
```TXT
[settings]
strategy = 3
type = 2
interval = 1
source = C:\path\to\images (Windows style) | /users/user/path/to/images (Unix style)
```

Fields description:
| name | description |
|---|---|
| strategy | Changing strategy |
| type |Schedule type |
| interval | Interval between changing |
| path | Path to background images |

Strategy values:
| value | description |
|---|---|
| 1 | static (no change) |
| 2 | round robin (next one |
| 3 | random) |

Schedule type values:
| value | description |
|---|---|
| 1 | minute |
| 2 | hourly |
| 3 | daily |
| 4 | weekly |
| 5 | monthly |
