#ifndef _I18N_HPP_
#define _I18N_HPP_

/**
 * Header file for the macro required when using i18n.
 */
#include <config.h>
#include <locale.h>
#include "gettext.h"
#define _(String) gettext(String)

#endif // _I18N_HPP_
