<mszubart>: I made some changes which makes Touchpad work better for me.

First big issue:
I have few network adapters in windows (eth, wifi, virtual machine bridges) and of course Touchpad listens on virtual one... This is related to windows unicorntastic api: gethostbyname finds and returns most useless one. My solution is even more unicorntastic. You don't want to see it.

Second big issue:
When using custom server, Touchpad forgets to what was connected after restart.  Solution: Touchpad now tries to connect to default server after resume. Default server configurable from 'Properties' menu.

This is original Touchpad https://github.com/dsharlet/Touchpad
