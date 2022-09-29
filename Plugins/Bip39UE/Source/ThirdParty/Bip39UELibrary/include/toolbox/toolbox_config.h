/*!
 * toolbox.
 * toolbox_config.h
 *
 * \date 11/30/2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef TOOLBOX_CONFIG_H
#define TOOLBOX_CONFIG_H

// #cmakedefine HAVE_IOSFWD_H 1
// #cmakedefine HAVE_REGEX_H 1
// #cmakedefine HAVE_STD_REGEX 1
// #cmakedefine HAVE_BOOST_REGEX 1
// #cmakedefine HAVE_EXCEPTION_H 1
// #cmakedefine HAVE_TERMIOS_H 1
// #cmakedefine HAVE_UNISTD_H 1
//
// #cmakedefine TOOLBOX_SHARED
// #cmakedefine TOOLBOX_EXPORTING

#ifdef TOOLBOX_SHARED
#ifdef TOOLBOX_EXPORTING
#if _MSC_VER
#define TOOLBOX_API __declspec(dllexport)
#define TOOLBOX_EXT
#else
#define TOOLBOX_API __attribute__((visibility("default")))
#define TOOLBOX_EXT
#endif
#else
#if _MSC_VER
#define TOOLBOX_API __declspec(dllimport)
#define TOOLBOX_EXT extern
#else
#define TOOLBOX_API
#define TOOLBOX_EXT
#endif
#endif
#else
#define TOOLBOX_API
#define TOOLBOX_EXT
#endif // TOOLBOX_SHARED

#endif // TOOLBOX_CONFIG_H
