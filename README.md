# MoonRise
C++ class for calculating moon rise/set events for Unix, Linux, Arduino

# Overview
Compute times of moonrise and moonset at a specified latitude and longitude.

## Detailed synopsis
Determine the nearest moon rise or set event previous, and the nearest
moon rise or set event subsequent, to the specified time in seconds since the
Unix epoch (January 1, 1970) and at the specified latitude and longitude in
degrees.

## Discussion and Applicability
This software minimizes computational work by performing the full calculation
of the lunar position three times, at the bigging, middle, and end of the
period of interest.  Three point interpolation is used to predict the position
for each hour, and the arithmetic mean is used to predict the half-hour positions.

The full computational burden is negligable on modern computers, but the
algorithm is effective and still useful for small embedded systems.

## Historical background
This software was originally adapted to javascript by Stephen R. Schmitt
from a BASIC program from the 'Astronomical Computing' column of Sky & Telescope,
April 1989, page 78.
