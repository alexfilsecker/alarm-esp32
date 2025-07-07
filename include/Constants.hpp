// For the scale
const int DOUT_PIN = 19;
const int CLK_PIN = 18;
const long THRESHOLD = 1000000;

// For the buzzer
const int BUZZER_PIN = 13;

// For the RealTimeClock
const int SDA_PIN = 21;
const int SCL_PIN = 22;

// For sending read
const unsigned long long SEND_READ_PERIOD = 500; // ms

// For the Internet
constexpr const char *SSID = "WiFi FB 2.4";
constexpr const char *PASSWORD = "alexander";
constexpr const char *NTP_SERVER = "pool.ntp.org";
const long GMT_OFFSET = -4 * 3600;

constexpr const char *WEB_SOCKET_IP = "192.168.50.146";
const int WEB_SOCKET_PORT = 8000;
