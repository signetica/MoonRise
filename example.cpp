/*
 * Print out the moon rise and set times, demonstrating the use of the MoonRise
 * class.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "MoonRise.h"

int
main(int argc, char *argv[]) {
  double latitude = 42;
  double longitude = -90;

  // In Unix/Linux, the Unix time is the seconds since the start of January 1, 1970,
  // in GMT.
  time_t t = time(NULL);

  // On the Arduino, if one uses the popular TimeLib.h library, getting the time
  // in GMT can be more complex.  MoonRise needs the GMT Unix time, and returns
  // values in that format.  But TimeLib's now() returns someting similar to Unix
  // time, but in a different timezone.

  // Something like this may work:
  //
  // To produce the Unix time in seconds (in GMT) on the Arduino, we have to
  // figure out the difference between whatever is residing in now()
  // and GMT, then add and subtract it to convert to and from GMT.
  // The value of time() seems even more inscrutable and less useful.

#ifdef Arduino
  // Arduino TimeLib only!!!
  time_t t = now();
  struct tm gmt_tm = *gmtime(&t);
  gmt_tm.tm_isdst = -1;
  time_t gmtOffset = mktime(&gmt_tm) - t;
  // End Arduino TimeLib workaround
#else
#define gmtOffset 0
#endif

  // Find the last and next lunar set and rise.  The gmtOffset is only for Arduino.
  MoonRise mr(latitude, longitude, t + gmtOffset);

  // Returned values:
  bool moonVisible = mr.isVisible;
  bool moonHasRise = mr.hasRise;
  bool moonHasSet = mr.hasSet;
  float moonRiseAz = mr.riseAz;	      // Where the moon will rise/set in degrees from
  float moonSetAz = mr.setAz;	      // North.

  // Convert returned value from GMT to local time zone on the Arduino.
  time_t moonQueryTime = mr.queryTime - gmtOffset;
  time_t moonRiseTime = mr.riseTime - gmtOffset;
  time_t moonSetTime = mr.setTime - gmtOffset;

  // Use the results as desired (use the gmtOffset variables on the Arduino):
  printf("Moon rise/set nearest %.24s for latitude %.2f longitude %.2f:\n",
	 ctime(&mr.queryTime), latitude, longitude);

  printf("Preceeding event:\n");
  if ((!mr.hasRise || (mr.hasRise && mr.riseTime > mr.queryTime)) &&
      (!mr.hasSet || (mr.hasSet && mr.setTime > mr.queryTime)))
    printf("\tNo moon rise or set during preceeding %d hours\n", MR_WINDOW/2);
  if (mr.hasRise && mr.riseTime < mr.queryTime)
    printf("\tMoon rise at %.24s, Azimuth %.2f\n", ctime(&mr.riseTime), mr.riseAz);
  if (mr.hasSet && mr.setTime < mr.queryTime)
    printf("\tMoon set at  %.24s, Azimuth %.2f\n", ctime(&mr.setTime), mr.setAz);

  printf("Succeeding event:\n");
  if ((!mr.hasRise || (mr.hasRise && mr.riseTime < mr.queryTime)) &&
      (!mr.hasSet || (mr.hasSet && mr.setTime < mr.queryTime)))
    printf("\tNo moon rise or set during succeeding %d hours\n", MR_WINDOW/2);
  if (mr.hasRise && mr.riseTime > mr.queryTime)
    printf("\tMoon rise at %.24s, Azimuth %.2f\n", ctime(&mr.riseTime), mr.riseAz);
  if (mr.hasSet && mr.setTime > mr.queryTime)
    printf("\tMoon set at  %.24s, Azimuth %.2f\n", ctime(&mr.setTime), mr.setAz);

  if (mr.isVisible)
    printf("Moon visible.\n");
  else
    printf("Moon not visible.\n");
}
