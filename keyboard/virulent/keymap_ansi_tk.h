// Virulent TenKey
/*
     * TK:
     *
     *                       ,-----------------------------------------------------------. 
     *                       |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| 
     *                       `-----------------------------------------------------------' 
     * ,-------------------. ,-----------------------------------------------------------. 
     * |Del|Pls|Div|Ply|Mns| |~  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  Backs| 
     * |-------------------| |-----------------------------------------------------------| 
     * |   |  7|  8|  9|   | |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  
     * |---------------|  +| |-----------------------------------------------------------| 
     * |   |  4|  5|  6|   | |Cap   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|     Ret| 
     * |-------------------| |-----------------------------------------------------------| 
     * |   |  1|  2|  3|   | |    Shif|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|     Shift| 
     * |---------------|Ent| |-----------------------------------------------------------| 
     * |   |      0|  .|   | |Ctrl |Gui|Alt  |         Spc      |Del |Gui |Fn0|Men|Rig|
     * `-------------------' `-----------------------------------------------------------' 
     */
static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty + a few media keys */
    KEYMAP_ANSI_TK(\
                                   ESC, PSCR,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,  \
        DEL, PPLS,PSLS,PAST,PMNS,  GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, \
        PGUP,HOME,   7,   8,   9,  TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
        PGDN,END,    4,   5,   6,  CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,  \
        INS, UP,     1,   2,   3,  FN0, LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,UP,  RSFT, \
        LEFT,DOWN,RGHT,   0, DOT,  LCTL,LGUI,     LALT,LSFT,LCTL,BSPC,SPC, DEL,      RGUI,LEFT,DOWN,RGHT),
    /* 1: media keys */
    KEYMAP_ANSI_TK(\
                                   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        1,   2,   3,   4,   5,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        Q,   W,   E,   R,   T,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        A,   S,   D,   F,   G,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS, \
        Z,   X,   C,   V,   B,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        LCTL,F11, F10, N,   LSFT,  TRNS,TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,TRNS)
};
static const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_TOGGLE(1)
};
