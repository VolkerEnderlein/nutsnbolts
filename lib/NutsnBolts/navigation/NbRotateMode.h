#ifndef NB_ROTATEMODE_H
#define NB_ROTATEMODE_H

/**************************************************************************\
 *
 *  This file is part of the SIM Nuts'n'Bolts extension library for Coin.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License ("GPL") version 2
 *  as published by the Free Software Foundation.  See the file COPYING
 *  at the root directory of this source distribution for additional
 *  information about the GNU GPL.
 *
 *  For using SIM Nuts'n'Bolts with software that can not be combined with
 *  the GNU GPL, and for taking advantage of the additional benefits of
 *  our support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion AS, Bygd�y all� 5, N-0257 Oslo, NORWAY. (www.sim.no)
 *
\**************************************************************************/

#include <NutsnBolts/navigation/NbNavigationMode.h>

class NbRotateModeP;

class NB_DLL_API NbRotateMode : public NbNavigationMode {
  typedef NbNavigationMode inherited;

public:
  NbRotateMode(SbName modename);
  virtual ~NbRotateMode(void);

protected:
  virtual SbBool handleEvent(const SoEvent * event, const NbNavigationInfo * info);

  virtual void abort(const SoEvent * event, const NbNavigationInfo * info);

private:
  NbRotateModeP * pimpl;

}; // NbRotateMode

#endif // !NB_ROTATEMODE_H
