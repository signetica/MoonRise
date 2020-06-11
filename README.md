# MoonRise
C++ class for calculating moon rise/set events for Unix, Linux, Arduino

## Overview
Compute times of moonrise and moonset at a specified latitude and longitude.

## Synopsis
Determine the nearest moon rise or set event previous, and the nearest
moon rise or set event subsequent, to the specified time in seconds since the
Unix epoch (January 1, 1970) and at the specified latitude and longitude in
degrees.

## Discussion and Applicability
This software minimizes computational work by performing the full calculation
of the lunar position three times, at the beginning, middle, and end of the
period of interest.  Three point interpolation is used to predict the position
for each hour, and the arithmetic mean is used to predict the half-hour positions.

The full computational burden is negligible on modern computers, but the
algorithm is effective and still useful for small embedded systems.

## Historical background
This software was originally adapted to javascript by Stephen R. Schmitt
from a BASIC program from the 'Astronomical Computing' column of Sky & Telescope,
April 1989, page 78.

## Usage

### Detailed synopsis
MoonRise mr(double latitude, double longitude, time_t time);

#### Arguments
*  latitude, longitude:	The location of interest, in decimal degrees.
			Latitude ranges from -90 (south pole) to 90 (north pole).
			Longitude ranges from -180 (west of Greenwich) to
			 180 (east of Greenwich).  

*  time:		The time to search for events, in GMT seconds from the
			Unix epoch (January 1, 1970).  
			The closest moon rise/set event will be found before
			and after this time.  In polar regions there may not
			be an event within the configurable search window,
			in which case zero, one, or two events may all be found
			either before or after *time*.  

#### Returned values
*  bool moonVisible = mr.isVisible;	// Moon is visible or not at *time*.
*  bool moonHasRise = mr.hasRise;	// There was a moonrise event in the search.
					// interval (default 24 hours) before *time*.  
*  bool moonHasSet = mr.hasSet;		// There was a moonset event in the search
					// interval after *time*.  
*  float moonRiseAz = mr.riseAz;	// Where the moon will rise/set in degrees from
*  float moonSetAz = mr.setAz;		// North.

*  time_t moonQueryTime = mr.queryTime;	// The *time* passed as the third argument.
*  time_t moonRiseTime = mr.riseTime;	// The moon rise event, in GMT seconds from
					// the Unix epoch.  
*  time_t moonSetTime = mr.setTime;	// The moon set event.
