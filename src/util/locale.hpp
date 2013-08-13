//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) 2001 - 2012 Twan van Laarhoven and Sean Hunt             |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#ifndef HEADER_UTIL_LOCALE
#define HEADER_UTIL_LOCALE

/** @file util/locale.hpp
 *
 *  @brief Utilities for localisation of text.
 *  Whenever text is used that can be translated to another language (and is not code related)
 *  one of the macros from this file should be used
 */

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <util/string.hpp>
#include <stdio.h>

class Package;
class Game;
class StyleSheet;
class SymbolFont;

// ----------------------------------------------------------------------------- : Localisation macros

enum LocaleCategory
{	LOCALE_CAT_MENU
,	LOCALE_CAT_HELP
,	LOCALE_CAT_TOOL
,	LOCALE_CAT_TOOLTIP
,	LOCALE_CAT_LABEL
,	LOCALE_CAT_BUTTON
,	LOCALE_CAT_TITLE
,	LOCALE_CAT_TYPE
,	LOCALE_CAT_ACTION
,	LOCALE_CAT_ERROR
,	LOCALE_CAT_MAX
};

typedef String (*DefaultLocaleFun)(const String&);
/// Return the input and issue a warning
String warn_and_identity(const String&);
/// Return the input and don't issue a warning
String string_identity(const String&);

/// Translate 'key' in the category 'cat' using the current locale
String tr(LocaleCategory cat, const String& key, DefaultLocaleFun def = warn_and_identity);

/// Translate 'key' in the for a Package using the current locale
String tr(const Package&, const String& key, DefaultLocaleFun def);

/// Translate 'key' in the for a Package using the current locale
String tr(const Package&, const String& subcat, const String& key, DefaultLocaleFun def);

/// A localized string for menus
#define _MENU_(s)    tr(LOCALE_CAT_MENU,      _(s))
/// A localized string for help/statusbar text
#define _HELP_(s)    tr(LOCALE_CAT_HELP,      _(s))
/// A localized string for the text of toolbar buttons
#define _TOOL_(s)    tr(LOCALE_CAT_TOOL,      _(s))
/// A localized string for tooltip text for toolbar buttons
#define _TOOLTIP_(s) tr(LOCALE_CAT_TOOLTIP,   _(s))
/// A localized string for labels
#define _LABEL_(s)   tr(LOCALE_CAT_LABEL,     _(s))
/// A localized string for buttons/checkboxes/etc.
#define _BUTTON_(s)  tr(LOCALE_CAT_BUTTON,    _(s))
/// A localized string for window titles
#define _TITLE_(s)   tr(LOCALE_CAT_TITLE,     _(s))
/// A localized string for type names in scripts
#define _TYPE_(s)    tr(LOCALE_CAT_TYPE,      _(s))
/// A localized string for action names
#define _ACTION_(s)  tr(LOCALE_CAT_ACTION,    _(s))
/// A localized string for error messages
#define _ERROR_(s)   tr(LOCALE_CAT_ERROR,     _(s))

/// A localized string for menus, with 1 argument (printf style)
#define _MENU_1_(s,a)		string_format(_MENU_(s),    a)
/// A localized string for context menus, contains no "\tshortcut"
#define _CONTEXT_MENU_(s)   remove_shortcut(_MENU_(s))

/// A localized string for tooltip text, with 1 argument (printf style)
#define _HELP_1_(s,a)		string_format(_HELP_(s),    a)

/// A localized string for tooltip text, with 1 argument (printf style)
#define _TOOLTIP_1_(s,a)	string_format(_TOOLTIP_(s), a)

/// A localized string for tooltip labels, with 1 argument (printf style)
#define _LABEL_1_(s,a)		string_format(_LABEL_(s),   a)

/// A localized string for button text, with 1 argument (printf style)
#define _BUTTON_1_(s,a)		string_format(_BUTTON_(s), a)

/// A localized string for window titles, with 1 argument (printf style)
#define _TITLE_1_(s,a)		string_format(_TITLE_(s), a)

/// A localized string for type names in scripts, with 1 argument (printf style)
#define _TYPE_1_(s,a)		string_format(_TYPE_(s), a)

/// A localized string for action names, with 1 argument (printf style)
#define _ACTION_1_(s,a)		string_format(_ACTION_(s), a)

/// A localized string for error messages, with 1 argument (printf style)
#define _ERROR_1_(s,a)		string_format(_ERROR_(s),   a)
/// A localized string for error messages, with 2 argument (printf style)
#define _ERROR_2_(s,a,b)	string_format(_ERROR_(s), a, b) // format_string(_ERROR_(s),   a, b)
/// A localized string for error messages, with 3 argument (printf style)
#define _ERROR_3_(s,a,b,c)	string_format(_ERROR_(s), a, b, c)
/// A localized string for error messages, with 4 argument (printf style)
#define _ERROR_4_(s,a,b,c,d) string_format(_ERROR_(s),   a, b, c, d)


std::basic_string<wchar_t> string_format(const std::basic_string<wchar_t> fmt, ...) {
    int size = 100;
    std::basic_string<wchar_t> str;
    va_list ap;
    while (1) {
        str.resize(size);
        va_start(ap, fmt);
        int n = vsnprintf((char *)str.c_str(), size, (char *)fmt.c_str(), ap);
        va_end(ap);
        if (n > -1 && n < size) {
            str.resize(n);
            return str;
        }
        if (n > -1)
            size = n + 1;
        else
            size *= 2;
    }
    return str;
}

std::basic_string<wchar_t> string_format(const std::basic_string<wchar_t> fmt, const std::basic_string<wchar_t> arg) {
    int size = 100;
    std::basic_string<wchar_t> str;
    while (1) {
        str.resize(size);
        int n = snprintf((char *)str.c_str(), size, (char *)fmt.c_str(), arg);
        if (n > -1 && n < size) {
            str.resize(n);
            return str;
        }
        if (n > -1)
            size = n + 1;
        else
            size *= 2;
    }
    return str;
}

std::basic_string<wchar_t> string_format(const std::basic_string<wchar_t> fmt, int i, const std::basic_string<wchar_t> arg) {
    int size = 100;
    std::basic_string<wchar_t> str;
    while (1) {
        str.resize(size);
        int n = snprintf((char *)str.c_str(), size, (char *)fmt.c_str(), i, arg);
        if (n > -1 && n < size) {
            str.resize(n);
            return str;
        }
        if (n > -1)
            size = n + 1;
        else
            size *= 2;
    }
    return str;
}

std::basic_string<wchar_t> string_format(
    const std::basic_string<wchar_t> fmt,
    const std::basic_string<wchar_t> arg,
    const std::basic_string<wchar_t> arg2
) {
    int size = 100;
    std::basic_string<wchar_t> str;
    while (1) {
        str.resize(size);
        int n = snprintf((char *)str.c_str(), size, (char *)fmt.c_str(), arg, arg2);
        if (n > -1 && n < size) {
            str.resize(n);
            return str;
        }
        if (n > -1)
            size = n + 1;
        else
            size *= 2;
    }
    return str;
}

std::basic_string<wchar_t> string_format(const char *fmt, ...) {
    int size = 100;
    std::basic_string<wchar_t> str;
    va_list ap;
    while (1) {
        str.resize(size);
        va_start(ap, fmt);
        int n = vsnprintf((char *)str.c_str(), size, fmt, ap);
        va_end(ap);
        if (n > -1 && n < size) {
            str.resize(n);
            return str;
        }
        if (n > -1)
            size = n + 1;
        else
            size *= 2;
    }
    return str;
}

#endif
