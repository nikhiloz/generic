/**
 * @file system_command_demo.c
 * @brief Demonstration of executing system commands from C programs
 * @author Development Team
 * @date Created: July 2025
 *
 * This program demonstrates various ways to execute system commands from C:
 * - Using system() function
 * - Using popen() for command output capture
 * - Using execvp() family functions
 * - Proper error handling and security considerations
 *
 * Originally inspired by a command to download FFmpeg:
 * wget -O ffmpeg.tar.xz https://johnvansickle.com/ffmpeg/builds/ffmpeg-git-arm64-static.tar.xz
 */

#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

/*============================================================================
 * CONSTANTS AND CONFIGURATION
 *============================================================================*/

#define MAX_COMMAND_LENGTH 1024
#define MAX_OUTPUT_LENGTH 4096
#define FFMPEG_URL "https://johnvansickle.com/ffmpeg/builds/ffmpeg-git-arm64-static.tar.xz"
#define OUTPUT_FILENAME "ffmpeg.tar.xz"

/*============================================================================
 * FUNCTION PROTOTYPES
 *============================================================================*/

static void demonstrate_system_function(void);
static void demonstrate_popen_function(void);
static void demonstrate_exec_family(void);
static int execute_command_with_output(const char *command, char *output, size_t output_size);
static int safe_system_command(const char *command);
static void download_ffmpeg_demo(void);
static void print_security_warning(void);

/*============================================================================
 * UTILITY FUNCTIONS
 *============================================================================*/

/**
 * @brief Safely execute a system command with error checking
 * @param command The command to execute
 * @return 0 on success, -1 on failure
 */
static int safe_system_command(const char *command) {
    if (!command) {
        fprintf(stderr, "Error: NULL command provided\n");
        return -1;
    }

    printf("Executing command: %s\n", command);

    int result = system(command);

    if (result == -1) {
        fprintf(stderr, "Error: Failed to execute command: %s\n", strerror(errno));
        return -1;
    }

    // Check if the command was executed successfully
    if (WIFEXITED(result)) {
        int exit_status = WEXITSTATUS(result);
        if (exit_status == 0) {
            printf("Command executed successfully\n");
            return 0;
        } else {
            fprintf(stderr, "Command exited with status: %d\n", exit_status);
            return -1;
        }
    } else {
        fprintf(stderr, "Command terminated abnormally\n");
        return -1;
    }
}

/**
 * @brief Execute a command and capture its output
 * @param command The command to execute
 * @param output Buffer to store the command output
 * @param output_size Size of the output buffer
 * @return 0 on success, -1 on failure
 */
static int execute_command_with_output(const char *command, char *output, size_t output_size) {
    if (!command || !output || output_size == 0) {
        fprintf(stderr, "Error: Invalid parameters provided\n");
        return -1;
    }

    printf("Executing command with output capture: %s\n", command);

    FILE *pipe = popen(command, "r");
    if (!pipe) {
        fprintf(stderr, "Error: Failed to open pipe: %s\n", strerror(errno));
        return -1;
    }

    // Read command output
    size_t bytes_read = 0;
    char *current_pos = output;
    size_t remaining_space = output_size - 1; // Leave space for null terminator

    while (remaining_space > 0 && fgets(current_pos, remaining_space, pipe) != NULL) {
        size_t line_length = strlen(current_pos);
        current_pos += line_length;
        remaining_space -= line_length;
        bytes_read += line_length;
    }

    output[bytes_read] = '\0'; // Ensure null termination

    int exit_status = pclose(pipe);
    if (exit_status == -1) {
        fprintf(stderr, "Error: Failed to close pipe: %s\n", strerror(errno));
        return -1;
    }

    if (WIFEXITED(exit_status) && WEXITSTATUS(exit_status) == 0) {
        printf("Command executed successfully, captured %zu bytes of output\n", bytes_read);
        return 0;
    } else {
        fprintf(stderr, "Command failed with exit status: %d\n", WEXITSTATUS(exit_status));
        return -1;
    }
}

/**
 * @brief Print security warning about system command execution
 */
static void print_security_warning(void) {
    printf("\n============================================================\n");
    printf("                    SECURITY WARNING\n");
    printf("============================================================\n");
    printf("Executing system commands from C programs can be dangerous!\n\n");
    printf("Security considerations:\n");
    printf("1. Never pass user input directly to system() without validation\n");
    printf("2. Use absolute paths for commands when possible\n");
    printf("3. Validate and sanitize all input parameters\n");
    printf("4. Consider using execvp() family for better security\n");
    printf("5. Be aware of shell injection vulnerabilities\n");
    printf("6. Run with minimal privileges required\n");
    printf("============================================================\n\n");
}

/*============================================================================
 * DEMONSTRATION FUNCTIONS
 *============================================================================*/

/**
 * @brief Demonstrate the system() function
 */
static void demonstrate_system_function(void) {
    printf("=== SYSTEM() FUNCTION DEMONSTRATION ===\n");
    printf("The system() function executes a command through the shell.\n\n");

    // Simple commands
    printf("1. Listing current directory contents:\n");
    safe_system_command("ls -la");

    printf("\n2. Showing current date and time:\n");
    safe_system_command("date");

    printf("\n3. Checking disk usage:\n");
    safe_system_command("df -h .");

    printf("\n4. Showing system information:\n");
    safe_system_command("uname -a");

    printf("\n");
}

/**
 * @brief Demonstrate the popen() function
 */
static void demonstrate_popen_function(void) {
    printf("=== POPEN() FUNCTION DEMONSTRATION ===\n");
    printf("The popen() function executes a command and captures its output.\n\n");

    char output[MAX_OUTPUT_LENGTH];

    // Capture command output
    printf("1. Capturing 'ls -la' output:\n");
    if (execute_command_with_output("ls -la", output, sizeof(output)) == 0) {
        printf("Output:\n%s\n", output);
    }

    printf("2. Capturing 'ps aux | head -10' output:\n");
    if (execute_command_with_output("ps aux | head -10", output, sizeof(output)) == 0) {
        printf("Output:\n%s\n", output);
    }

    printf("3. Checking if wget is available:\n");
    if (execute_command_with_output("which wget", output, sizeof(output)) == 0) {
        printf("wget found at: %s", output);
    } else {
        printf("wget not found in PATH\n");
    }

    printf("\n");
}

/**
 * @brief Demonstrate the exec family of functions
 */
static void demonstrate_exec_family(void) {
    printf("=== EXEC FAMILY DEMONSTRATION ===\n");
    printf("The exec family provides more control and security than system().\n\n");

    pid_t pid = fork();

    if (pid == -1) {
        fprintf(stderr, "Error: Fork failed: %s\n", strerror(errno));
        return;
    }

    if (pid == 0) {
        // Child process
        printf("Child process: executing 'ls -la' using execvp()\n");

        char *args[] = {"ls", "-la", NULL};
        execvp("ls", args);

        // If we reach here, execvp failed
        fprintf(stderr, "Error: execvp failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process terminated abnormally\n");
        }
    }

    printf("\n");
}

/**
 * @brief Demonstrate downloading FFmpeg (the original use case)
 */
static void download_ffmpeg_demo(void) {
    printf("=== FFMPEG DOWNLOAD DEMONSTRATION ===\n");
    printf("This demonstrates the original command from generic05.c\n");
    printf("Original command: wget -O ffmpeg.tar.xz %s\n\n", FFMPEG_URL);

    // Check if wget is available
    char output[256];
    if (execute_command_with_output("which wget", output, sizeof(output)) != 0) {
        printf("wget is not available on this system.\n");
        printf("Please install wget first:\n");
        printf("  Ubuntu/Debian: sudo apt-get install wget\n");
        printf("  CentOS/RHEL: sudo yum install wget\n");
        printf("  macOS: brew install wget\n");
        return;
    }

    printf("wget found at: %s", output);

    // Construct the download command
    char download_command[MAX_COMMAND_LENGTH];
    snprintf(download_command, sizeof(download_command),
             "wget -O %s '%s'", OUTPUT_FILENAME, FFMPEG_URL);

    printf("Would execute: %s\n", download_command);
    printf("Note: Actual download is commented out to avoid unnecessary network traffic.\n");
    printf("Uncomment the line below to perform the actual download:\n");
    printf("// safe_system_command(download_command);\n\n");

    // Uncomment the next line to actually perform the download
    // safe_system_command(download_command);

    // Show what would happen after download
    printf("After successful download, you would typically:\n");
    printf("1. Extract the archive: tar -xf %s\n", OUTPUT_FILENAME);
    printf("2. Install the binaries to /usr/local/bin/\n");
    printf("3. Update PATH if necessary\n");

    printf("\n");
}

/*============================================================================
 * MAIN FUNCTION
 *============================================================================*/

/**
 * @brief Main function - demonstrates various system command execution methods
 * @return EXIT_SUCCESS on successful execution
 */
int main(void) {
    printf("========================================================\n");
    printf("    SYSTEM COMMAND EXECUTION DEMONSTRATION\n");
    printf("========================================================\n\n");

    print_security_warning();

    demonstrate_system_function();
    demonstrate_popen_function();
    demonstrate_exec_family();
    download_ffmpeg_demo();

    printf("========================================================\n");
    printf("    DEMONSTRATION COMPLETED\n");
    printf("========================================================\n");
    printf("\nKey takeaways:\n");
    printf("1. system() is simple but can be insecure\n");
    printf("2. popen() allows output capture\n");
    printf("3. exec family provides better security and control\n");
    printf("4. Always validate input and handle errors\n");
    printf("5. Consider security implications of command execution\n");

    return EXIT_SUCCESS;
}
