# Change Log Smooth

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [1.6.0] - 2023-06-20
- add changelog.md
- improved performance **add()**
- add **smooth_performance.ino**
- changed type **count** to uint32_t - to extend the range.
- changed type **set_size** to uint16_t - to prevent signed/unsigned comparison.
- add parameters to **reset(int const window, int const c = 0, double const a = 0.0)** 
  to match behavior constructor.
- add missing ```cbchange = 0;``` in constructor
- minor edits readme.md


## [1.5.0] - ??


## [1.0.0] - ??
- initial version

