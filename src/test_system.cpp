#include <test_system.hpp>
#include <cstdio>

// Warning: Linux-specific headers
#include <unistd.h>
#include <sys/wait.h>

using namespace TestSystem;

//--------
// Colors
//--------

#define BRED    "\033[1;31m"
#define BGREEN  "\033[1;39m"
#define BYELLOW "\033[1;33m"
#define BPURPLE "\033[1;35m"
#define BCYAN   "\033[1;36m"
#define RESET   "\033[0m"

//---------------
// Test verdicts
//---------------

constexpr size_t TIMEOUT_MILLISSECONDS = 1000U; // seconds

// Test system implementation:
TestResult TestSystem::run_test(const char* name, TestScenario test, bool inspect /* = false */)
{
    // Print the test name:
    printf("Running test %40s: ", name);
    fflush(stdout);

    // WARNING: A little bit of Linux-specific OS magic.
    // NOTE: create a child process with copied address space.
    pid_t child_pid = fork();
    if (child_pid == -1)
    {
        fprintf(stderr, "Unable to call fork()\n");
        exit(EXIT_FAILURE);
    }

    //---------------
    // Child process
    //---------------
    if (child_pid == 0)
    {
        try {
            bool result = test();
            if (result)
            {
                exit(OK);
            }
            else
            {
                exit(FAIL);
            }
        }
        catch (const std::exception& exc)
        {
            if (inspect)
            {
                printf(BPURPLE "[EXC] (exception: %s)\n" RESET, exc.what());
            }

            exit(EXCEPTION);
        }
    }

    //----------------
    // Parent process
    //----------------

    pid_t ret = 0;
    int wstatus = 0;
    for (size_t msec = 0U; msec < TIMEOUT_MILLISSECONDS; ++msec)
    {
        // Wait for child process to return:
        ret = waitpid(child_pid, &wstatus, WNOHANG);
        if (ret == -1)
        {
            fprintf(stderr, "Unable to call wait()\n");
            exit(EXIT_FAILURE);
        }

        // Exit timeout loop:
        if (ret != 0)
        {
            break;
        }

        // Sleep for 1 millisecond:
        usleep(1000U);
    }

    // Handle timeout exit:
    if (ret == 0)
    {
        printf(BPURPLE "[TIMEOUT]\n" RESET);
        kill(child_pid, SIGKILL);
        return TIMEOUT;
    }

    // Handle correct exit:
    if (WIFEXITED(wstatus))
    {
        switch (WEXITSTATUS(wstatus))
        {
            case OK:
            {
                printf(BGREEN "[OK]\n" RESET);
                return OK;
            }
            case FAIL:
            {
                printf(BRED "[FAIL]\n" RESET);
                return FAIL;
            }
            case EXCEPTION:
            {
                if (!inspect)
                {
                    printf(BPURPLE "[EXC]\n" RESET);
                }
                return EXCEPTION;
            }
            default:
            {
                fprintf(stderr, "Unexpected switch case\n");
                exit(EXIT_FAILURE);
            }
        };
    }
    // Handle error exit:
    else if (WIFSIGNALED(wstatus))
    {
        printf(BPURPLE "[ERROR] (killed by signal %d)\n" RESET, WTERMSIG(wstatus));
        return ERROR;
    }

    // This point must be unreachable:
    fprintf(stderr, "Unexpected waitpid() opeartion\n");
    exit(EXIT_FAILURE);
}