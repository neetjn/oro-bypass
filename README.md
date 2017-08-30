# Oro / ***bypass***

This is a very simple GameGuard bypass for RumbleFighter, an action fighting MMO. It was written in C++ using C++ 11 conventions and the win32 api.

It is not a complete bypass, in the sense that it will disarm GameGuard specific security checking routines, but does not include heartbeat emulation.

Because a heartbeat is not active, your client will inevitably dc after prolonged usage. For more extensive time to dabble or mess around, I would suggest loading this module once the client window has been initialized using manual mapping.

This bypass takes care of the following detections,

* GameGuard has been falsified (GG not properly handling errors)
* Hack detected (hacking tools, static memory modification)
* GameGuard initialization failed (GG daemon did not respond)
* Speed Hack (query tick performance counter modifications)
* Unhandeled Exception (cannot determine security status)

Pattern scanning has been included, so the bypass should be able to persist over client versions.
