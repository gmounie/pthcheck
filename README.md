# pthcheck
Static checker for simple pthread monitor C code.

It uses coccinelle with some ad'hoc rules.

# Usage

'''
	spatch --sp-file pthcheck.cocci FILE
'''

The output patch matches the problematic lines. Empty patch means no
matching lines.

The matching rules (to find what is the problem) are exposed with the
debug option.

'''
	spatch --debug --sp-file pthcheck.cocci FILE
'''

# Rules

The rules implemented target simple code. More advanced
synchronization scheme may trigger false positive matching.

It matches:
- mutex lock but no unlock
- mutex unlock but no lock
- mutex lock and unlock do not use the same mutex
- condition wait use a if inside a lock and unlock
- condition wait without lock on the same mutex before
- condition wait without unlock on the same mutex after
- signal witout lock before
- signal without unlock after
- repetitive lock on the same mutex
- unlock lock around the wait with the same mutex
TODO
- create do not get a thread_t
- return before unlock

# Rational

The rules come from the most common bugs of my students. 


