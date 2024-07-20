#pragma once

// Character Map symbols
// https://www.unicode.org/charts/PDF/ ,  https://www.unicode.org/charts/PDF/U2600.pdf
// Couldn't define as const variable because was getting the error...
    // error LNK2005: "wchar_t const * const Variables::[X]" (?[X]@Variables@@3PEB_WEB) already defined in TexasHoldEm.obj
// @suitHexChars
#define SPADE L"\u2660"
#define CLUB L"\u2663"
#define HEART L"\u2665"
#define DIAMOND L"\u2666"