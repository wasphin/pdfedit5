//========================================================================
//
// NameToCharCode.h
//
// Copyright 2001-2003 Glyph & Cog, LLC
//
//========================================================================

#ifndef NAMETOCHARCODE_H
#define NAMETOCHARCODE_H

#include <xpdf-aconf.h>

#ifdef USE_GCC_PRAGMAS
#pragma interface
#endif

#include "xpdf/CharTypes.h"

struct NameToCharCodeEntry;

//------------------------------------------------------------------------

class NameToCharCode {
public:

  NameToCharCode();
  ~NameToCharCode();

  void add(char *name, CharCode c);
  CharCode lookup(char *name);

private:

  int hash(char *name);

  NameToCharCodeEntry *tab;
  int size;
  int len;
};

#endif
