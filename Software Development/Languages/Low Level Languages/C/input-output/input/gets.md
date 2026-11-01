# LITERALLY DEPRECATED
# char* gets(char* s)

Dont use, it takes a buffer to write the output into but has no control on its size
leading us to a segfault waiting to happen

Other than that just a simpler getline()
