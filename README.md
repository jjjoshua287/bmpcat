# bmpcat
A bitmap parser and terminal viewer using ANSI escape codes for color, written in C++

## Usage

### Linux
```bash
chmod +x bmpcat-linux-x64
./bmpcat-linux-x64 image.bmp
```

#### Windows
```cmd
bmpcat-windows-x64.exe image.bmp
```

Or run without arguments and enter it:
```bash
./bmpcat
Enter bitmap file: image.bmp
```

### Example

Try it with the included example image:
```bash
./bmpcat TailsHUD.bmp
```

## Technical Details
- Supports 24-bit uncompressed BMP files
- Renders using ANSI 24-bit color escape codes
- Handles row padding correctly
- No external dependencies

## Limitations
- Large images may not fit in your terminal window
- Terminal characters are taller than wide, causing some vertical stretching
