from libcpp.string cimport string

cdef extern from 'dynd/config.hpp' namespace 'dynd':
    char[] dynd_version_string
    char[] dynd_git_sha1

    void load(const string &)
