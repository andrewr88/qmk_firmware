# Corne Keyboard Keymap

## Base Layer
```
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │  Q  │  W  │  E  │  R  │  T  │PSCR │     │HOME │  Y  │  U  │  I  │  O  │  P  │  '  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │  A  │  S  │  D  │  F  │  G  │ END │     │ INS │  H  │  J  │  K  │  L  │  ;  │LT_MD│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┘     └─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ DEL │  Z  │  X  │  C  │  V  │  B  │                 │  N  │  M  │  ,  │  .  │  /  │  /  │
└─────┴─────┴─────┴─────┴─────┴─────┘                 └─────┴─────┴─────┴─────┴─────┴─────┘
               ┌─────┬─────┬─────┐           ┌─────┬─────┬─────┐
               │MO_FN│LT_NA│MO_NU│           │OS_SH│MO_NA│MO_SY│
               └─────┴─────┴─────┘           └─────┴─────┴─────┘
```

## Symbol Layer (_SYMB)
```
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │  -  │  _  │  =  │  +  │  \  │PSCR │     │HOME │UNDO │  &  │  *  │  .  │PSTE │ INS │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │  '  │  "  │  (  │  )  │  `  │ END │     │ INS │  :  │OS_SH│OS_CT│OS_AL│OS_GU│ PGUP│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┘     └─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ DEL │  ;  │  :  │  [  │  ]  │  `  │                 │  -  │  !  │  <  │  >  │  ?  │ PGDN│
└─────┴─────┴─────┴─────┴─────┴─────┘                 └─────┴─────┴─────┴─────┴─────┴─────┘
               ┌─────┬─────┬─────┐           ┌─────┬─────┬─────┐
               │     │     │ ENT │           │     │     │     │
               └─────┴─────┴─────┘           └─────┴─────┴─────┘
```

## Number Layer (_NUM)
```
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │ TAB │  ←  │  .  │  →  │  _  │PSCR │     │HOME │EVAL │  7  │  8  │  9  │  +  │ INS │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │OS_GU│OS_AL│OS_CT│OS_SH│MO_NA│ END │     │ INS │  :  │  4  │  5  │  6  │  -  │ PGUP│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┘     └─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ DEL │UNDO │     │  ,  │  :  │REDO │                 │  -  │  1  │  2  │  3  │     │ PGDN│
└─────┴─────┴─────┴─────┴─────┴─────┘                 └─────┴─────┴─────┴─────┴─────┴─────┘
               ┌─────┬─────┬─────┐           ┌─────┬─────┬─────┐
               │     │     │     │           │ ENT │BSPC │  0  │
               └─────┴─────┴─────┘           └─────┴─────┴─────┘
```

## Function Layer (_FUN)
```
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │  1  │  2  │  3  │  4  │  5  │PSCR │     │HOME │TO_LH│ F7  │ F8  │ F9  │ F12 │ INS │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │OS_GU│OS_AL│OS_CT│OS_SH│     │ END │     │ INS │     │ F4  │ F5  │ F6  │ F11 │ PGUP│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┘     └─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ DEL │  6  │  7  │  8  │  9  │  0  │                 │     │ F1  │ F2  │ F3  │ F10 │ KC_PGDN │
└─────┴─────┴─────┴─────┴─────┴─────┘                 └─────┴─────┴─────┴─────┴─────┴─────┘
               ┌─────┬─────┬─────┐           ┌─────┬─────┬─────┐
               │     │     │     │           │     │CAPS │     │
               └─────┴─────┴─────┘           └─────┴─────┴─────┘
```

## Navigation Layer (_NAV)
```
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │SW_WI│PRV_T│CLS_W│NXT_T│SW_AP│PSCR │     │HOME │ PGU │HOME │  ↑  │ END │DWRD │ KC_BSPC │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │OS_GU│OS_AL│OS_CT│OS_SH│OS_NW│ END │     │ INS │ PGD │  ←  │  ↓  │  →  │ SPC │ KC_ENT │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┘     └─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ DEL │UNDO │ CUT │COPY │PSTE │REDO │                 │ ESC │BSPC │ ENT │ TAB │ DEL │ OS_SHFT │
└─────┴─────┴─────┴─────┴─────┴─────┘                 └─────┴─────┴─────┴─────┴─────┴─────┘
               ┌─────┬─────┬─────┐           ┌─────┬─────┬─────┐
               │MKLNK│     │NWTB │           │ ENT │BSPC │     │
               └─────┴─────┴─────┘           └─────┴─────┴─────┘
```

## Navigation Windows Layer (_NAVWIN)
```
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │A(Q) │A(W) │A(F) │A(P) │A(B) │PSCR │     │HOME │A(J) │A(7) │A(8) │A(9) │A(') │ INS │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │OS_GU│OS_AL│OS_CT│OS_SH│     │ END │     │ INS │A(M) │A(4) │A(5) │A(6) │A(O) │ PGUP│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┘     └─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ DEL │A(Z) │A(X) │A(C) │A(D) │A(V) │                 │A(K) │A(1) │A(2) │A(3) │A(/) │ PGDN│
└─────┴─────┴─────┴─────┴─────┴─────┘                 └─────┴─────┴─────┴─────┴─────┴─────┘
               ┌─────┬─────┬─────┐           ┌─────┬─────┬─────┐
               │     │     │     │           │     │     │     │
               └─────┴─────┴─────┘           └─────┴─────┴─────┘
```

## Navigation Left Hand Layer (_NAVLH)
```
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │TO_BA│HOME │  ↑  │ END │ PGU │PSCR │     │HOME │     │     │     │     │     │ INS │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │ SPC │  ←  │  ↓  │  →  │ PGD │ END │     │ INS │     │OS_SH│OS_CT│OS_AL│OS_GU│ PGUP│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┘     └─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ DEL │ DEL │ TAB │ ENT │BSPC │ ESC │                 │     │     │     │     │     │     │
└─────┴─────┴─────┴─────┴─────┴─────┘                 └─────┴─────┴─────┴─────┴─────┴─────┘
               ┌─────┬─────┬─────┐           ┌─────┬─────┬─────┐
               │TO_BA│TO_BA│     │           │ ENT │BSPC │     │
               └─────┴─────┴─────┘           └─────┴─────┴─────┘
```

## Media Layer (_MDIA)
```
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │BOOT │     │RGB_T│     │CG_TG│PSCR │     │HOME │WH_U │MPRV │MS_U │MNXT │PSCR │ INS │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │OS_GU│OS_AL│OS_CT│OS_SH│     │ END │     │ INS │WH_D │MS_L │MS_D │MS_R │     │ PGUP│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┘     └─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ DEL │     │     │     │     │     │                 │MUTE │VOLD │MPLY │VOLU │     │ PGDN│
└─────┴─────┴─────┴─────┴─────┴─────┘                 └─────┴─────┴─────┴─────┴─────┴─────┘
               ┌─────┬─────┬─────┐           ┌─────┬─────┬─────┐
               │     │     │     │           │BTN3 │BTN1 │BTN2 │
               └─────┴─────┴─────┘           └─────┴─────┴─────┘
```

## Key Legend

### Layer Keys
- `MO_FUN`: Momentary layer switch to Function layer
- `MO_NAV`: Momentary layer switch to Navigation layer
- `MO_NUM`: Momentary layer switch to Number layer
- `MO_SYMB`: Momentary layer switch to Symbol layer
- `LT_NAV_SPACE`: Space when tapped, Navigation layer when held
- `LT_MDIA_O`: O when tapped, Media layer when held
- `OSL_NAVWIN`: One-shot layer to Navigation Windows layer
- `TO(_BASE)`: Switch to Base layer
- `TO(_NAVLH)`: Switch to Navigation Left Hand layer

### One-shot Modifiers
- `OS_SHFT`: One-shot Shift
- `OS_CTRL`: One-shot Control
- `OS_ALT`: One-shot Alt
- `OS_GUI`: One-shot GUI (Windows/Command)

### Custom Keys
- `SW_WIN`: Switch windows
- `PRV_TAB`: Previous tab
- `CLS_WIN`: Close window
- `NXT_TAB`: Next tab
- `SW_APP`: Switch applications
- `MW_UNDO`: Undo (Command+Z/Ctrl+Z)
- `MW_CUT`: Cut (Command+X/Ctrl+X)
- `MW_COPY`: Copy (Command+C/Ctrl+C)
- `MW_PSTE`: Paste (Command+V/Ctrl+V)
- `MW_REDO`: Redo (Command+Shift+Z/Ctrl+Y)
- `MW_MKLNK`: Make link (Command+K/Ctrl+K)
- `MW_NWTB`: New tab (Command+T/Ctrl+T)
- `MW_SELECT_ALL`: Select all (Command+A/Ctrl+A)
- `DWRD`: Delete word
- `REV_COLON`: Reversed colon (; when shifted, : when not)
- `VSC_EVAL`: VSCode evaluate
- `CG_TOGG`: Caps Word toggle
- `RGB_TOG`: RGB toggle
- `QK_BOOT`: Reset keyboard

### Mouse Keys
- `WH_U`: Mouse wheel up
- `WH_D`: Mouse wheel down
- `MS_U`: Mouse up
- `MS_D`: Mouse down
- `MS_L`: Mouse left
- `MS_R`: Mouse right
- `BTN1`: Mouse button 1 (left click)
- `BTN2`: Mouse button 2 (right click)
- `BTN3`: Mouse button 3 (middle click)

### Media Keys
- `MPRV`: Media previous
- `MNXT`: Media next
- `MPLY`: Media play/pause
- `MUTE`: Mute
- `VOLD`: Volume down
- `VOLU`: Volume up 
