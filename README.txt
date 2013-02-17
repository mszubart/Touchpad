<mszubart>: I made some changes which makes Touchpad work better for me.

First big issue:
  I have few network adapters in windows (eth, wifi, virtual machine bridges) and of course Touchpad listens on virtual one...
  This is related to windows unicorntastic api: gethostbyname finds and returns most useless one.
  My solution is even more unicorntastic. You don't want to see it.

This is original Touchpad https://github.com/dsharlet/Touchpad
