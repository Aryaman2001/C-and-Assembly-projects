/******************************************************************************
 * @file: functions.c
 *
 * WISC NETID - agarwal59
 * CANVAS USERNAME - ARYAMAN AGARWAL
 * WISC ID NUMBER - 9081576937
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: Aryaman Agarwal (agarwal59@wisc.edu)
 * @modified: SUBMISSION DATE
 *****************************************************************************/
#include <stdio.h>
#include "functions.h"

// Some macros that may be useful to you 
#define MAX_USERNAME_LEN    32
#define MAX_EMAIL_LEN       32
#define MAX_DOMAIN_LEN      64
#define MIN_PASSWORD_LEN    8
#define MAX_PASSWORD_LEN    16
#define NEW_LINE_CHAR       10

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0 
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 
// Examples: IsLetter, IsDigit, Length, Find...
int Adjust_Len(char arr[], size_t len) {
    int retLen = 0;
    for (int i = 0; i < len; i++) {
        if ((int)arr[i] == 0) {
            return retLen;
        }
        retLen++;        
    }
    return retLen;
}

int IsTopDomainPresent(char email[], size_t len) {
    int ret = 0;
    if ((int)email[len - 4] == 46 && (int)email[len - 3] == 101 && (int)email[len - 2] == 100 && (int)email[len - 1] == 117) {
        ret = 1;
    } else if ((int)email[len - 4] == 46 && (int)email[len - 3] == 99 && (int)email[len - 2] == 111 && (int)email[len - 1] == 109) {
        ret = 1;
    } else if ((int)email[len - 4] == 46 && (int)email[len - 3] == 110 && (int)email[len - 2] == 101 && (int)email[len - 1] == 116) {
        ret = 1;
    } 
    return ret;
}

/******************************************************************************
 * Verification functions
 *****************************************************************************/

/*
 * A username must begin with a letter [A-Z, a-z], contain 32 characters
 * or less, and  may only consist of letters, underscores, or 
 * digits [A-Z, a-z, _, 0-9]. An error message is displayed if any of 
 * these conditions are not met. Only print the first applicable error 
 * message. 
 *
 * @param user : The username string
 * @param len : Size of the username input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Username(char user[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
    dbgprintf("This line only prints if DEBUG is set to 1\n");
    len = Adjust_Len(user, len);

    int first_char = (int)user[0];
    if (first_char < 65 || first_char > 122 || (first_char > 90 && first_char < 97)) {
        printf(ERROR_01_USER_START_INVALID);
        return 0;
    }

    if (len > 32) {
        printf(ERROR_02_USER_LEN_INVALID);
        return 0;
    }

    for (int i = 1; i < len; i++) {
        int charac = (int)user[i];
        
        if ((charac != 95) && !(charac >= 48 && charac <= 57) && !(charac >= 65 && charac <= 90) && !(charac >= 97 && charac <= 122)) {
            printf(ERROR_03_USER_CHARS_INVALID);
            return 0;
        }
    }    
    
    /* END MODIFYING CODE HERE */

    printf(SUCCESS_1_USER);
    return 1;
}

/*
 * An email address has four parts:
 *      name
 *          exists
 *          must start with letter
 *          max 32 characters
 *          may contain only letters and digits
 *      @ symbol
 *          exists
 *      domain name
 *          exists
 *          max of 64 characters
 *          composed of one or more subdomains separated by .
 *          subdomain must begin with a letter
 *          subdomains may contain only letters and digits
 *      top-level domain 
 *          must be [.edu, .com, .net]
 *
 * If the email address contains one or more errors print only the first
 * applicable error from the list.
 *
 * Note this task is based on a real world problem and may not be the best 
 * order to approach writing the code.
 *
 * @param email : The email string
 * @param len : Size of the email input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Email(char email[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
    len = Adjust_Len(email, len);

    int first_char = (int)email[0];
    if (first_char == 64) {
        printf(ERROR_04_EMAIL_MISSING_NAME);
        return 0;
    }
    if (first_char < 65 || first_char > 122 || (first_char > 90 && first_char < 97)) {
        printf(ERROR_05_EMAIL_START_INVALID);
        return 0;
    }

    int name_len = 0;
    for (int i = 0; i < len; i++) {
        int charac = (int)email[i];
        if (charac == 64) {
            break;
        }
        name_len++;
    }

    if (name_len == len && IsTopDomainPresent(email, len) == 1) {
        // @ is missing but a valid top level domain is present
        name_len = len - 4;
    }


    if (name_len > 32) {
        printf(ERROR_06_EMAIL_NAME_LEN_INVALID);
        return 0;
    }

    for (int i = 1; i < name_len; i++) {
        int charac = (int)email[i];
        if (!(charac >= 48 && charac <= 57) && !(charac >= 65 && charac <= 90) && !(charac >= 97 && charac <= 122)) {
            printf(ERROR_07_EMAIL_NAME_CHARS_INVALID);
            return 0;
        }
    }

    int symbol_char = (int)email[name_len];
    if (symbol_char != 64) {
        printf(ERROR_08_EMAIL_MISSING_SYMBOL);
        return 0;
    }

    int top_domain_len = 0;
    if (IsTopDomainPresent(email, len) == 1) {
        top_domain_len = 4;
    }
    // for (int i = len - 1; i > name_len; i--) {
    //     int charac = (int)email[i];
    //     if (charac == 46) {
    //         top_domain_len++;
    //         break;
    //     }
    //     top_domain_len++;
    // }

    if (len - name_len - 1 == top_domain_len) {
        printf(ERROR_09_EMAIL_MISSING_DOMAIN);
        return 0;
    }

    if (len - name_len - 1 - top_domain_len > 64) {
        printf(ERROR_10_EMAIL_DOMAIN_LEN_INVALID);
        return 0;
    }

    int first_email_char = (int)email[name_len + 1];
    if (first_email_char < 65 || first_email_char > 122 || (first_email_char > 90 && first_email_char < 97)) {
        printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
        return 0;
    }

    // int email_domain_len = len - name_len - 1 - top_domain_len;

    for (int i = name_len + 2; i < len - top_domain_len; i++) {
        int charac = (int)email[i];
        int prev_charac = (int)email[i - 1];

        if (prev_charac == 46) {
            if (charac < 65 || charac > 122 || (charac > 90 && charac < 97)) {
                printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
                return 0;
            } else {
                continue;
            }
        }

        if (charac != 46 && !(charac >= 48 && charac <= 57) && !(charac >= 65 && charac <= 90) && !(charac >= 97 && charac <= 122)) {
            printf(ERROR_12_EMAIL_DOMAIN_CHARS_INVALID);
            return 0;
        }
    }

    if (top_domain_len != 4) {
        printf(ERROR_13_TOP_LEVEL_DOMAIN_INVALID);
        return 0;
    }   

    int dot_char = (int)email[len - top_domain_len];
    if (dot_char != 46) {
        printf(ERROR_13_TOP_LEVEL_DOMAIN_INVALID);
        return 0;
    }

    if ((int)email[len - top_domain_len + 1] == 101 && (int)email[len - top_domain_len + 2] == 100 && (int)email[len - top_domain_len + 3] == 117) {
        // do nothing
    } else if ((int)email[len - top_domain_len + 1] == 99 && (int)email[len - top_domain_len + 2] == 111 && (int)email[len - top_domain_len + 3] == 109) {
        // do nothing
    } else if ((int)email[len - top_domain_len + 1] == 110 && (int)email[len - top_domain_len + 2] == 101 && (int)email[len - top_domain_len + 3] == 116) {
        // do nothing
    } else {
        printf(ERROR_13_TOP_LEVEL_DOMAIN_INVALID);
        return 0;
    }

    /* END MODIFYING CODE HERE */
    printf(SUCCESS_2_EMAIL);
    return 1;
}

/*
 * The following password requirements must be verified:
 *  - May use any character except spaces (i.e., "my password" is invalid)
 *  - Must contain at least 8 characters (i.e., "Password" has 8 characters 
 *    and is valid)
 *  - May have at most 16 characters (i.e., "1234567890Abcdef" has 16 
 *    characters and is valid)
 *  - Must contain at least one upper case character [A-Z]
 *  - Must contain at least one lower case character [a-z]
 *
 * @param pwd : The original password string
 * @param len : Size of the original password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Password(char pwd[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
    len = Adjust_Len(pwd, len);

    int upper = 0;
    int lower = 0;
    for (int i = 0; i < len; i++) {
        int charac = (int)pwd[i];
        if (charac == 32) {
            printf(ERROR_14_PWD_SPACES_INVALID);
            return 0;
        }

        if (charac >= 65 && charac <= 90) {
            upper = 1;
        }
        if (charac >= 97 && charac <= 122) {
            lower = 1;
        }
    }
    
    if (len < 8) {
        printf(ERROR_15_PWD_MIN_LEN_INVALID);
        return 0;
    }

    if (len > 16) {
        printf(ERROR_16_PWD_MAX_LEN_INVALID);
        return 0;
    }

    if (upper != 1) {
        printf(ERROR_17_PWD_MIN_UPPER_INVALID);
        return 0;
    }
    
    if (lower != 1) {
        printf(ERROR_18_PWD_MIN_LOWER_INVALID);
        return 0;
    }  
    /* END MODIFYING CODE HERE */

    return 1;
}
/*
 * Original Password and the Reentered Password must match
 *
 * @param pwd1 : The original password string
 * @param len1 : Size of the original password input buffer
 * @param pwd2 : The reentered password string
 * @param len2 : Size of the renetered password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Passwords_Match(char pwd1[], size_t len1, char pwd2[], size_t len2) {

    /* BEGIN MODIFYING CODE HERE */
    len1 = Adjust_Len(pwd1, len1);
    len2 = Adjust_Len(pwd2, len2);

    if (len1 != len2) {
        printf(ERROR_19_PWD_MATCH_INVALID);
        return 0;
    }

    for (int i = 0; i < len1; i++) {
        int charac1 = (int)pwd1[i];
        int charac2 = (int)pwd2[i];

        if (charac1 != charac2) {
            printf(ERROR_19_PWD_MATCH_INVALID);
            return 0;
        }
    }
    /* END MODIFYING CODE HERE */

    printf(SUCCESS_3_PASSWORDS);
    return 1;
}

/******************************************************************************
 * I/O functions
 *****************************************************************************/

/*
 * Prompts user with an input and reads response from stdin
 *
 * @param message : Prompt displayed to the user
 * @param data : char array to hold user repsonse
 * @param MAX_LENGTH : Size of user response input buffer
 */
void Get_User_Data(char *message, char *data, const int MAX_LENGTH) {
    printf("%s", message);
    fgets(data, MAX_LENGTH, stdin);
    
    /* BEGIN MODIFYING CODE HERE */  
    for (int i = 0; i < MAX_LENGTH; i++) {
        if ((int)data[i] == 10) {
            data[i] = '\0';
            break;
        }        
    }
    /* END MODIFYING CODE HERE */
    return;
}
