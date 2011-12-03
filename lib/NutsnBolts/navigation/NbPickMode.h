#ifndef NB_PICKMODE_H
#define NB_PICKMODE_H

/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

#include <Inventor/SbVec3d.h>
#include <NutsnBolts/navigation/NbNavigationMode.h>

class NbPickModeP;

typedef void NbPickModePickCB(void * closure, const SbVec3d & pos, const SoPath * path);

class NB_DLL_API NbPickMode : public NbNavigationMode {
  typedef NbNavigationMode inherited;
  NB_NAVIGATION_MODE_HEADER(NbPickMode);

public:
  static void initClass(void);

  NbPickMode(SbName name);
  virtual ~NbPickMode(void);

  virtual NbNavigationMode * clone(void) const;

  void addPickCallback(NbPickModePickCB * cb, void * closure);
  void removePickCallback(NbPickModePickCB * cb, void * closure);

protected:
  virtual SbBool handleEvent(const SoEvent * event, 
                             const NbNavigationControl * ctrl);

  void invokePickCallbacks(const SbVec3d & pos, const SoPath * path);

private:
  NbPickModeP * pimpl;

}; // NbPitchMode

#endif // !NB_PICKMODE_H
