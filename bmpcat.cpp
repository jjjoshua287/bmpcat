#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <string>

#pragma pack(push, 1)

struct BMPHeader {
    uint16_t signature;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t pixelDataOffset;
};

struct BitmapInfoHeader {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t ColorPlanes;
    uint16_t bitsPerPixel;
    uint32_t compressionMethod;
    uint32_t imageSize; 
    uint32_t imageResolutionX;
    uint32_t imageResolutionY;
    uint32_t ColorsInPalette;
    uint32_t ImportantColors;

};

void printColoredPixel(uint8_t red, uint8_t green, uint8_t blue, int width = 2){
    std::cout << "\033[48;2;"
              << static_cast<int>(red) << ";"
              << static_cast<int>(green) << ";"
              << static_cast<int>(blue) << "m";

    for (int i = 0; i < width; ++i) {
        std::cout << " ";
    }

    std::cout << "\033[0m";
}

int main(int argc, char* argv[]){
    std::istream* input = &std::cin;
    std::string file;
    
    if (argc == 1) {
        std::cout << "Enter bitmap file: ";
        std::cin >> file;
    } else {
        file = argv[1];
    }

    std::ifstream bmp;
    bmp.open(file, std::ios::binary);
    
    if (!bmp.is_open()){
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }
    std::cout << "Successfully opened file!" << std::endl;
    
    BMPHeader header;
    bmp.read(reinterpret_cast<char*>(&header), 14);
    
    if (header.signature != 0x4D42) {
        std::cerr << "Not a valid BMP File!" << std::endl;
        return 1;
    }

    BitmapInfoHeader infoHeader;
    bmp.read(reinterpret_cast<char*>(&infoHeader), 40);
    bmp.seekg(header.pixelDataOffset);

    int bytesPerPixel = infoHeader.bitsPerPixel / 8;
    //int pixelBytes = infoHeader.width * infoHeader.height * bytesPerPixel; // No Padding
    int bytesPerRow = ((infoHeader.width * bytesPerPixel + 3) / 4) * 4; // Bytes per row with Padding
    int totalBytes = bytesPerRow * infoHeader.height; // total bytes per row with padding

    std::vector<uint8_t> pixelData;

    pixelData.resize(totalBytes);
    bmp.read(reinterpret_cast<char*>(pixelData.data()), totalBytes);
    
    for (int i = infoHeader.height - 1; i >= 0; i--){ // Represents the row
        for (int j = 0; j < infoHeader.width; j++) { // Represents the column
            //int index = (i * infoHeader.width * bytesPerPixel) + (j * bytesPerPixel);
            int index = (i * bytesPerRow) + (j * bytesPerPixel); 
            uint8_t blue = pixelData[index];
            uint8_t green = pixelData[index + 1];
            uint8_t red = pixelData[index + 2];
            printColoredPixel(red, green, blue);
        }
        std::cout << "\n";
    }
    
    bmp.close();
    return 0;
}