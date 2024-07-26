#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "movie.h"

// Function to check if a string contains only alphabetic characters
int is_alpha_string(const char *str) {
    while (*str) {
        if (!isalpha(*str)) {
            return 0; // Not an alphabetic string
        }
        str++;
    }
    return 1; // Is an alphabetic string
}

// Function to check if an email contains at least one uppercase letter, one lowercase letter, and one special character
int is_valid_email(const char *email) {
    int has_upper = 0, has_lower = 0, has_special = 0;
    while (*email) {
        if (isupper(*email)) {
            has_upper = 1;
        } else if (islower(*email)) {
            has_lower = 1;
        } else if (ispunct(*email)) {
            has_special = 1;
        }
        email++;
    }
    return has_upper && has_lower && has_special;
}

// TICKET BOOKING FUNCTION
void movie_book_ticket(unsigned int *total_tickets_sold, unsigned int total_tickets) {
    char movie_name[3][20] = {"AVENGERS", "ENDGAME", "INTERSTELLAR"};
    int BASE_PRICE[3][3] = {
        {250, 350, 450}, // AVENGERS: Silver: 250, Gold: 350, Recliner: 450
        {500, 600, 700}, // ENDGAME: Silver: 500, Gold: 600, Recliner: 700
        {650, 750, 850}  // INTERSTELLAR: Silver: 650, Gold: 750, Recliner: 850
    };
    char user_CHOICE[20];
    unsigned int TICKETS = 0;
    int CATEGORY = 0;
    char *CATEGORY_NAME[3] = {"SILVER", "GOLD", "RECLINER"};
    int MOVIE_PRICE;

    printf("1. AVENGERS - Silver: 250, Gold: 350, Recliner: 450\n");
    printf("2. ENDGAME - Silver: 500, Gold: 600, Recliner: 700\n");
    printf("3. INTERSTELLAR - Silver: 650, Gold: 750, Recliner: 850\n");
    printf("\nEnter the movie name: ");
    scanf("%s", user_CHOICE);

    // Convert user input to uppercase to handle case sensitivity
    for (int i = 0; user_CHOICE[i]; i++) {
        user_CHOICE[i] = toupper(user_CHOICE[i]);
    }

    // Validate that the movie name contains only alphabetic characters
    if (!is_alpha_string(user_CHOICE)) {
        printf("Invalid movie name. Please enter a valid movie name.\n");
        return;
    }

    printf("\nNO OF TICKETS YOU WANT TO BOOK: ");
    while (scanf("%u", &TICKETS) != 1) {
        while (getchar() != '\n'); // Clear invalid input from buffer
        printf("Invalid input. Please enter a number: ");
    }

    if (*total_tickets_sold + TICKETS > total_tickets) {
        printf("Not enough tickets available. Only %u tickets remaining.\n", total_tickets - *total_tickets_sold);
        return;
    }

    printf("Choose category:\n1. Silver\n2. Gold\n3. Recliner\n");
    printf("Enter your choice: ");
    while (scanf("%d", &CATEGORY) != 1 || CATEGORY < 1 || CATEGORY > 3) {
        while (getchar() != '\n'); // Clear invalid input from buffer
        printf("Invalid input. Please enter a number between 1 and 3: ");
    }

    int found = 0;
    // PRICE CALCULATING USING FOR LOOP
    for (int i = 0; i < 3; i++) {
        if (strcmp(movie_name[i], user_CHOICE) == 0) {
            printf("%s IS AVAILABLE FOR BOOKING.\n", user_CHOICE);
            found = 1;
            MOVIE_PRICE = TICKETS * BASE_PRICE[i][CATEGORY - 1];
            printf("\nTOTAL PRICE: %d\n", MOVIE_PRICE);
            break;
        }
    }

    if (!found) {
        printf("%s IS NOT AVAILABLE FOR BOOKING.\n", user_CHOICE);
        printf("PLEASE SELECT OTHERS\n");
        return;
    }

    // Allocate memory for customer using malloc
    struct Customer *customer = (struct Customer *)malloc(sizeof(struct Customer));
    if (customer == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    printf("\nEnter your name: ");
    scanf("%s", customer->name);

    // Validate email input
    do {
        printf("Enter your email: ");
        scanf("%s", customer->email);
        if (!is_valid_email(customer->email)) {
            printf("Invalid email. Please enter an email with at least one uppercase letter, one lowercase letter, and one special character.\n");
        }
    } while (!is_valid_email(customer->email));

    customer->tickets = TICKETS;
    strcpy(customer->movie, user_CHOICE);

    *total_tickets_sold += TICKETS;

    // Displaying customer details
    printf("\nBooking Details:\n");
    printf("Name: %s\n", customer->name);
    printf("Email: %s\n", customer->email);
    printf("Movie: %s\n", customer->movie);
    printf("Tickets: %u\n", customer->tickets);
    printf("Category: %s\n", CATEGORY_NAME[CATEGORY - 1]);
    printf("Total Price: %d\n", MOVIE_PRICE);
    printf("Remaining Tickets: %u\n", total_tickets - *total_tickets_sold);

    // Free allocated memory
    free(customer);
}