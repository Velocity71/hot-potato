# hot_potato
## A keystroke forwarder used to easily control multiple computers with one keyboard, in situations where SSH would be unwieldy or impossible.
<img src="hot_potato.png"  width="200" height="200">

## What's the big idea?
In certain situations, such as editing UEFI settings, or installing a new operating system, SSH can be unwieldy or impossible to use. I would prefer not to plug in my keyboard to a different computer every time I wish to move to that one, or move to a different keyboard if each computer has a dedicated one. It can be annoying, time consuming, and boring. Enter 'hot_potato'. 'hot_potato' records your keystrokes and transmits them to HID-compatible microcontrollers, which directly input the keystrokes to that device. The end goal is to be able to use your main device normally, and then at the flick of a switch, use the same keyboard (and mouse perhaps...) on another device. But that's just the idea.
