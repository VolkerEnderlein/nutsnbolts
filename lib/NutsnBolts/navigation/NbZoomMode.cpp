
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>

#include <NutsnBolts/navigation/NbNavigationInfo.h>

#include <NutsnBolts/navigation/NbZoomMode.h>

// *************************************************************************

/*!
  \class NbZoomMode NutsnBolts/navigation/NbZoomMode.h
  \brief Class that implements the zooming action.

  \ingroup navigation
*/

// *************************************************************************


/*!
  Constructor.  Needs to know its container navigation system and mode name.
*/

NbZoomMode::NbZoomMode(NbNavigationSystem * system, SbName name)
  : inherited(system, name)
{
  // no need for a private implementation now, but we've set off room for
  // it if we ever need one in the future.
  this->pimpl = NULL;
}

/*!
  Destructor.  Doesn't do anything currently.
*/

NbZoomMode::~NbZoomMode(void)
{
}

/*!
  This method handles the zooming operation.
*/

SbBool
NbZoomMode::handleEvent(const SoEvent * event, const NbNavigationInfo * info)
{
  if ( ! event->isOfType(SoLocation2Event::getClassTypeId()) ) {
    return FALSE;
  }
  SoCamera * camera = info->getCamera();
  if ( !camera ) {
    return FALSE;
  }

  // fprintf(stderr, "NbZoomMode::handleEvent() %s\n",
  //	  this->getModeName().getString());

  SbVec2f initposn = this->getInitialNormalizedPosition(info);
  SbVec2f currentposn = this->getCurrentNormalizedPosition(info);
  const float factor = (currentposn[1] - initposn[1]) * 20.0f;
  float multiplicator = float(exp(factor));

  info->restoreCamera();

  if ( camera->isOfType(SoOrthographicCamera::getClassTypeId()) ) {
    SoOrthographicCamera * oc = (SoOrthographicCamera *) camera;
    oc->height = oc->height.getValue() * multiplicator;
  } else if ( camera->isOfType(SoPerspectiveCamera::getClassTypeId()) ) {

    const float oldfocaldist = camera->focalDistance.getValue();
    const float newfocaldist = oldfocaldist * multiplicator;

    SbVec3f direction;
    camera->orientation.getValue().multVec(SbVec3f(0, 0, -1), direction);

    const SbVec3f oldpos = camera->position.getValue();
    const SbVec3f newpos = oldpos + (newfocaldist - oldfocaldist) * -direction;

    // This catches a rather common user interface "buglet": if the
    // user zooms the camera out to a distance from origo larger than
    // what we still can safely do floating point calculations on
    // (i.e. without getting NaN or Inf values), the faulty floating
    // point values will propagate until we start to get debug error
    // messages and eventually an assert failure from core Coin code.
    //
    // With the below bounds check, this problem is avoided.
    //
    // (But note that we depend on the input argument ''diffvalue'' to
    // be small enough that zooming happens gradually. Ideally, we
    // should also check distorigo with isinf() and isnan() (or
    // inversely; isinfite()), but those only became standardized with
    // C99.)

    const float distorigo = newpos.length();
    // sqrt(FLT_MAX) == ~ 1e+19, which should be both safe for further
    // calculations and ok for the end-user and app-programmer.
    if ( distorigo > float(sqrt(FLT_MAX)) ) {
#if 0 // debug
      fprintf(stderr, "zoomed too far (distance to origo==%f (%e))",
	      distorigo, distorigo);
#endif // debug
    }
    else {
      camera->position = newpos;
      camera->focalDistance = newfocaldist;
    }
  } else {
    // unsupported camera type - no zoom implemented
    return FALSE;
  }

  return TRUE;
}
