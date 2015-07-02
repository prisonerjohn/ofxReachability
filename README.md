ofxReachability
=====================================

Introduction
------------
A cross-platform Internet reachability addon. Register listeners on `ofxReachability::connectedEvent` and `ofxReachability::disconnectedEvent` and you're good to go.

The Apple implementation uses [Reachability](https://github.com/tonymillion/Reachability) by Tony Million. Works on Mac and iOS.

The Windows implementation is based on [this article](http://blogs.msdn.com/b/oldnewthing/archive/2010/04/19/9998139.aspx) by Raymond Chen.

Other platforms use the ping implementation, where I just ping [google.com](http://google.com) at regular intervals. Specific platform implementations are welcome!

Installation
------------
Drop the `ofxReachability` folder into `openFrameworks/addons/`.

When adding the files to your project, make sure to include the "apple" subfolder on Mac / iOS, and the "win32" subfolder on Windows.

If you're on Mac, you'll also need to add `SystemConfiguration.framework` in the linking build phase.

Compatibility
------------
Tested with openFrameworks 0.8.4 on Mac OS X 10.10 and Windows 8.1.
