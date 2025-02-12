#include "drivlib.h"

/// Keys are entered as keycode 0 (arr[x]) = ascii char
static const char ascii_french_legacy_azerty[] = {
    27,                                             // ESCAPE
    '1',                                            // 1
    '2',                                            // 2
    '3',                                            // 3
    '4',                                            // 4
    '5',                                            // 5
    '6',                                            // 6
    '7',                                            // 7
    '8',                                            // 8
    '9',                                            // 9
    '0',                                            // 0
    ')',                                            // OEM 4 (= in AZERTY)
    '=',                                            // OEM + (+ in AZERTY)
    '\b',                                           // BACKSPACE
    '\t',                                           // TAB
    'a',
    'z',
    'e',
    'r',
    't',
    'y',
    'u',
    'i',
    'o',
    'p',
    '^',                                            // OEM 6 (ˆ in AZERTY)
    '$',                                            // OEM 1 ($ in AZERTY)
    '\n',                                           // ENTER
    '?',                                            // L-CTRL (unchanged)
    'q',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    'm',
    '?',                                            // OEM 3 (ù in AZERTY)
    '*',                                            // OEM 7 (* in AZERTY)
    KB_VK_SHIFT,                                    // L-SHIFT (unchanged)
    '<',                                            // OEM 5 (< in AZERTY)
    'w',
    'x',
    'c',
    'v',
    'b',
    'n',
    ',',                                            // OEM COMMA
    ';',                                            // OEM PERIOD (; in AZERTY)
    ':',                                            // OEM 2 (: in AZERTY)
    '!',                                            // OEM 8 (! in AZERTY)
    KB_VK_SHIFT,                                    // R-SHIFT (unchanged)
    '?',                                            // MULTIPLY (unchanged)
    '?',                                            // L-MENU (unchanged)
    ' ',                                            // SPACE
    KB_VK_CAPSL,                                    // CAPS LOCK (unchanged)
    '?',                                            // F1
    '?',                                            // F2
    '?',                                            // F3
    '?',                                            // F4
    '?',                                            // F5
    '?',                                            // F6
    '?',                                            // F7
    '?',                                            // F8
    '?',                                            // F9
    '?',                                            // F10
    '?',                                            // NUM LOCK
    '?',                                            // SCROLL
    '?',                                            // HOME
    '?',                                            // UP
    '?',                                            // PRIOR
    '-',
    '?',                                            // LEFT
    '?',                                            // CLEAR
    '?',                                            // RIGHT
    '+',                                            // ADD
    '?',                                            // END
    '?',                                            // DOWN
    '?',                                            // NEXT
    '?',                                            // INSERT
    127,                                            // DEL
    '?',                                            // SNAPSHOT
    '?',                                            // OEM 102
    '?',                                            // F11
    '?'                                             // F12
};


/// Keys are entered as keycode 0 (arr[x]) = ascii char
static const char ascii_qwerty[] = {
    27,                                             // ESCAPE
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '-',                                            // OEM 4
    '=',                                            // OEM +
    '\b',
    '\t',
    'q',
    'w',
    'e',
    'r',
    't',
    'y',
    'u',
    'i',
    'o',
    'p',
    '[',                                            // OEM 6
    ']',                                            // OEM 1
    '\n',
    '?',                                            // L-CTRL
    'a',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    ';',                                            // OEM 3
    '\'',                                           // OEM 7
    '?',                                            // L-SHIFT
    '\\',                                           // OEM 5
    'z',
    'x',
    'c',
    'v',
    'b',
    'n',
    ',',                                            // OEM COMMA
    '.',                                            // OEM PERIOD
    '/',                                            // OEM 2
    '?',                                            // OEM 8
    '?',                                            // R-SHIFT
    '?',                                            // MULTIPLY
    '?',                                            // L-MENU
    ' ',
    '?',                                            // CAPS LOCK
    '?',                                            // F1
    '?',                                            // F2
    '?',                                            // F3
    '?',                                            // F4
    '?',                                            // F5
    '?',                                            // F6
    '?',                                            // F7
    '?',                                            // F8
    '?',                                            // F9
    '?',                                            // F10
    '?',                                            // NUM LOCK
    '?',                                            // SCROLL
    '?',                                            // HOME
    '?',                                            // UP
    '?',                                            // PRIOR
    '-',
    '?',                                            // LEFT
    '?',                                            // CLEAR
    '?',                                            // RIGHT
    '+',                                            // ADD
    '?',                                            // END
    '?',                                            // DOWN
    '?',                                            // NEXT
    '?',                                            // INSERT
    127,                                            // DEL
    '?',                                            // SNAPSHOT
    '?',                                            // OEM 102
    '?',                                            // F11
    '?'                                             // F12
};

const char *get_keyboard_layout(int code)
{
    if (code == KB_LAYOUT_AZERTY)
        return ascii_french_legacy_azerty;
    if (code == KB_LAYOUT_QWERTY)
        return ascii_qwerty;
    print("drivers/keyboard: unknown layout, fallback to ascii_qwerty");
    return ascii_qwerty;
}
