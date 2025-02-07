#include "../../include/extlib/color.h"

using namespace std;

// Fungsi untuk mereset format
string reset() {
    return "\033[0m";
}

// Fungsi untuk format teks
string bold() { return "\033[1m"; }
string faint() { return "\033[2m"; }
string italic() { return "\033[3m"; }
string underline() { return "\033[4m"; }
string inverse() { return "\033[7m"; }
string strikethrough() { return "\033[9m"; }

// Fungsi untuk warna teks (foreground)
string fgBlack() { return "\033[30m"; }
string fgRed() { return "\033[31m"; }
string fgGreen() { return "\033[32m"; }
string fgYellow() { return "\033[33m"; }
string fgBlue() { return "\033[34m"; }
string fgMagenta() { return "\033[35m"; }
string fgCyan() { return "\033[36m"; }
string fgWhite() { return "\033[37m"; }

// Fungsi untuk warna latar belakang (background)
string bgBlack() { return "\033[40m"; }
string bgRed() { return "\033[41m"; }
string bgGreen() { return "\033[42m"; }
string bgYellow() { return "\033[43m"; }
string bgBlue() { return "\033[44m"; }
string bgMagenta() { return "\033[45m"; }
string bgCyan() { return "\033[46m"; }
string bgWhite() { return "\033[47m"; }

// Fungsi untuk warna teks intensitas tinggi
string fgBrightBlack() { return "\033[90m"; }
string fgBrightRed() { return "\033[91m"; }
string fgBrightGreen() { return "\033[92m"; }
string fgBrightYellow() { return "\033[93m"; }
string fgBrightBlue() { return "\033[94m"; }
string fgBrightMagenta() { return "\033[95m"; }
string fgBrightCyan() { return "\033[96m"; }
string fgBrightWhite() { return "\033[97m"; }

// Fungsi untuk warna latar belakang intensitas tinggi
string bgBrightBlack() { return "\033[100m"; }
string bgBrightRed() { return "\033[101m"; }
string bgBrightGreen() { return "\033[102m"; }
string bgBrightYellow() { return "\033[103m"; }
string bgBrightBlue() { return "\033[104m"; }
string bgBrightMagenta() { return "\033[105m"; }
string bgBrightCyan() { return "\033[106m"; }
string bgBrightWhite() { return "\033[107m"; }
