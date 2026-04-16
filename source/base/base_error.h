/* base library internal error checking system */
#ifndef BASE_ERROR_H
#define BASE_ERROR_H

#define error_at(msg)                                                   \
    do {                                                                \
        write_string(STDERR_FD, Red "[ERROR] " __FILE__ ":");           \
        write_int(STDERR_FD, __LINE__);                                 \
        write_string(STDERR_FD, ":" __func__ ": " Reset);               \
        write_string(STDERR_FD, (msg));                                 \
        write_string(STDERR_FD, "\n");                                  \
    } while (0)

#define warn(msg)                                                       \
    do {                                                                \
        write_string(STDERR_FD, Yellow "[WARN] " __FILE__ ":");         \
        write_int(STDERR_FD, __LINE__);                                 \
        write_string(STDERR_FD, ":" __func__ ": " Reset);               \
        write_string(STDERR_FD, (msg));                                 \
        write_string(STDERR_FD, "\n");                                  \
    } while (0)

#define assert_msg(expr, msg)                                           \
    do {                                                                \
        if (!(expr)) {                                                  \
            write_string(STDERR_FD, Red "[ERROR] " __FILE__ ":");       \
            write_int(STDERR_FD, __LINE__);                             \
            write_string(STDERR_FD, ":" __func__ ": " Reset);           \
            write_string(STDERR_FD, (msg));                             \
            write_string(STDERR_FD, "\n");                              \
            _exit(1);                                                   \
        }                                                               \
    } while (0)

#define show                                                            \
    do {                                                                \
        write_string(STDOUT_FD, __FILE__ ":");                          \
        write_int(STDOUT_FD, __LINE__);                                 \
        write_string(STDOUT_FD, ":" __func__ "\n");                     \
    } while (0)

#define test(expr)                                                      \
    do {                                                                \
        if ((expr) != 0) {                                              \
            write_string(STDERR_FD, "[FAILED] " __FILE__ ":");          \
            write_int(STDERR_FD, __LINE__);                             \
            write_string(STDERR_FD, ":" __func__ "\n");                 \
            _exit(1);                                                   \
        }                                                               \
    } while (0)

#define verify(expr)                                                    \
    do {                                                                \
        if ((expr) != 0) {                                              \
            write_string(STDERR_FD, Red "[ERROR] " __FILE__ ":");       \
            write_int(STDERR_FD, __LINE__);                             \
            write_string(STDERR_FD, ":" __func__ "\n" Reset);           \
            _exit(1);                                                   \
        } else {                                                        \
            write_string(STDERR_FD, Green "[OK] " __FILE__ ":");        \
            write_int(STDERR_FD, __LINE__);                             \
            write_string(STDERR_FD, ":" __func__ "\n" Reset);           \
        }                                                               \
    } while (0)

#endif /* BASE_ERROR_H */
