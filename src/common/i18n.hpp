#ifndef _I18N_HPP_
#define _I18N_HPP_

/**
 * Header file for the macro required when using i18n.
 */
// FIXME(pht) : replace this with a generated config.h
//#include <config.h>


/* Name of package */
#define PACKAGE "ube"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "phtrivier@yahoo.fr"

/* Define to the full name of this package. */
#define PACKAGE_NAME "ube"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "ube 0.3.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "ube"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.3.1"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "0.3.1"

// OK 

#include <locale.h>
#include "gettext.h"
#define _(String) gettext(String)

#endif // _I18N_HPP_
