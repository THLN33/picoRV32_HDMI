

#define QR_CODE_DY 10
#define QR_CODE_DX 15

#define LOGO_PICO_DY 5
#define LOGO_PICO_DX 9

#define LOGO_RV32_DY 3
#define LOGO_RV32_DX (1+12)

void display_qrcode(uint32_t x, uint32_t y);
void display_pico_logo(uint32_t x, uint32_t y);
void display_RV32_logo(uint32_t x, uint32_t y);

void test_video_text(void);

void scroll_line(unsigned char line);
