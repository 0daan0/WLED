#include "OledEsp.h"
#include <vector>

// Constructor
OledEsp::OledEsp()
    : u8g2(U8G2_R0, OLED_RESET, OLED_SCL, OLED_SDA)
{
}

// Split a string into multiple lines based on max chars per line
std::vector<String> wrapText(const String& text, int maxCharsPerLine) {
    std::vector<String> lines;
    int start = 0;
    int len = text.length();

    while (start < len) {
        int chunkLen = maxCharsPerLine;
        if (start + chunkLen > len) {
            chunkLen = len - start;
        }
        lines.push_back(text.substring(start, start + chunkLen));
        start += chunkLen;
    }
    return lines;
}

// Initialize the display
void OledEsp::begin() {
    u8g2.begin();
    u8g2.setContrast(255);
    u8g2.setBusClock(400000);
    u8g2.clearBuffer();
    u8g2.sendBuffer();
}

void OledEsp::showMessage(const String& msg) {
    const int maxCharsPerLine = 11;  // Based on 72px / ~4px per char
    auto wrappedLines = wrapText(msg, maxCharsPerLine);

    for (auto& line : wrappedLines) {
        lines.push_back(line);
    }

    // Limit total lines
    const int maxLines = 10;  // enough buffer
    while (lines.size() > maxLines) {
        lines.erase(lines.begin());
    }

    updateDisplay();
}

// Add message without updating display (for batching)
void OledEsp::addMessage(const String& msg) {
    const int maxCharsPerLine = 11;
    auto wrappedLines = wrapText(msg, maxCharsPerLine);

    for (auto& line : wrappedLines) {
        lines.push_back(line);
    }

    // Limit total lines
    const int maxLines = 10;
    while (lines.size() > maxLines) {
        lines.erase(lines.begin());
    }
}

// Manually trigger display update
void OledEsp::update() {
    updateDisplay();
}

// Clear all lines
void OledEsp::clear() {
    lines.clear();
    updateDisplay();
}

// Draw lines on display
void OledEsp::updateDisplay() {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tr);  // Bigger, more readable font

    const int charHeight = 10;       // Font height in pixels
    const int lineSpacing = 1;       // Extra space between lines
    const int lineHeight = charHeight + lineSpacing;

    const int xOffset = 30;
    const int yOffset = 21;           // Start from top of the display

    const int maxDisplayLines = 46 / lineHeight;  // 40px height screen

    int startIdx = (lines.size() > maxDisplayLines)
                   ? (lines.size() - maxDisplayLines)
                   : 0;

    for (int i = startIdx; i < lines.size(); ++i) {
        int y = yOffset + ((i - startIdx) * lineHeight) + charHeight;
        u8g2.drawStr(xOffset, y, lines[i].c_str());
    }

    u8g2.sendBuffer();
}
