#ifndef BASE_PLATFORM_H
#define BASE_PLATFORM_H

#ifdef BASE_PLATFORM_IMPLEMENTATION
internal inline void
sleep_ms(long ms)
{
  struct timespec ts;
  ts.tv_sec = ms / 1000;
  ts.tv_nsec = (ms % 1000) * 1000000L;

  while (nanosleep(&ts, &ts))
  {
    NULL;
  }
}
#endif /* BASE_PLATFORM_IMPLEMENTATION */
#endif /* BASE_PLATFORM_H */
