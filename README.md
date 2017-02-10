# pthcheck
Simple static checker for pthread monitor C code.

It uses coccinelle with some ad'hoc rules.

# Usage

'''
	spatch --sp-file pthcheck.cocci FILE
'''

The output patch matches the problematic lines. Empty patch means no
matching lines.

# Rules

The rules implemented are quite simple and target beginner code.
Advanced synchronization may trigger false positive.

It detects:
- mutex lock but no unlock
- mutex unlock but no lock
- mutex lock and unlock do not use the same mutex
- condition wait use a if inside a lock and unlock

TODO
- condition wait is not inside a lock and unlock
- condition wait do not use the same mutex as lock and unlock
- two mutex lock/unlock are intricated
- return before unlock



