# Oro / ***bypass***

This is a very simple GameGuard bypass for RumbleFighter, an action fighting MMO. It was written in C++ using C++ 11 conventions and the win32 api.

## About

The bypass works as follows:

* Patches the GameGuard security subroutine. I've patched the subroutine rather than it's invocations, because this subroutine is used in multiple tricky contexts ie; loops inside of external threads.

* Kill communication between both the client and the daemon. The client talks with the GameGuard daemon to ensure it's health. If communication is impossible, the client will kill itself or the daemon will terminate the process.

* Kill the GameGuard daemon -> GameMon.des/GameMon64.des. If these daemons are left running after the changes above, they will terminate the client automatically because they cannot establish any communication.


It is not a complete bypass, in the sense that it will disarm GameGuard specific security checking routines, but does not include heartbeat emulation.

Because a heartbeat is not active, your client will inevitably disconnect after prolonged usage.

This bypass takes care of the following detections,

* GameGuard has been falsified (GG not properly handling errors)
* Hack detected (hacking tools, static memory modification)
* GameGuard initialization failed (GG daemon did not respond)
* Speed Hack (query tick performance counter modifications)
* Unhandeled Exception (cannot determine security status)

Pattern scanning has been included, so the bypass should be able to persist over client versions.

## Use

Simply build the project and inject the library into the RumbleFighter client. When the client window is created, the bypass will initialize itself.

> Warning: In the event Oro cannot terminate the GG daemon using the win32 TerminateProcess method, the host machine must have PSTools installed. PSTools was levereged to avoid writing a custom driver, for the sake of saving time. @ https://docs.microsoft.com/en-us/sysinternals/downloads/pskill

## Disclaimer

This project was created for eductional purposes only. I have not, and will not monetize this code for any personal gains.

---

Copyright (c) 2019 John Nolette Licensed under the MIT license.