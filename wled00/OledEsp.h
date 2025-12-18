#ifndef OLEDESP_H
#define OLEDESP_H

#include <U8g2lib.h>
#include <vector>

#define OLED_RESET U8X8_PIN_NONE
#define OLED_SDA 5
#define OLED_SCL 6


class OledEsp {
  public:
    OledEsp();
    void begin();
    void showMessage(const String& msg);
    void addMessage(const String& msg);  // Add without updating display
    void update();                        // Update display once
    void clear();

  private:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
    std::vector<String> lines;
    void updateDisplay();
};

#endif
