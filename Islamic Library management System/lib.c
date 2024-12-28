#include <stdio.h>
#include <string.h>
#include <time.h> // Include for nanosleep function
#include <ctype.h>
#include <stdlib.h> // Include for system function


#define NUM_BOOKS 40
#define MAX_USERS 100
#define MAX_TRANSACTIONS 100
#define FINE_PER_DAY 10

// Define structures for Book, User, and Transaction
typedef struct {
    char title[50];
    char author[50];
    char genre[30];
    int publicationYear;
    char ISBN[20];
} Book;

typedef struct {
    char name[50];
    char contact[50];
    int borrowedBooks[NUM_BOOKS];
} User;

typedef struct {
    int userId;
    int bookId;
    char borrowDate[11];
    char returnDate[11];
} Transaction;

// Declare global arrays and counters
Book books[NUM_BOOKS];
User users[MAX_USERS];
Transaction transactions[MAX_TRANSACTIONS];
int userCount = 0;
int transactionCount = 0;

// Function prototypes
void welcomeMessage();
void displayBooks();
void mainMenu();
void searchBooks();
void advancedSearch();
void borrowBook(int userId);
int calculateFine(char borrowDate[], char returnDate[]);
void returnBook(int userId);
void registerUser();
int loginUser();
void toLowerCase(char str[]);
int countBorrowedBooks(int userId);
void displayBorrowedBooks(int userId);
void displayBookGraphic(int serialNumber, char *title, char *author);
void showProgressBar();

int main() {
    // Initialize books
    strcpy(books[0].title, "Bulugh al-Maram");
    strcpy(books[0].author, "Ibn Hajar al-Asqalani");
    strcpy(books[0].genre, "Hadith");
    books[0].publicationYear = 1449;
    strcpy(books[0].ISBN, "978-1-23456-789-40");

    strcpy(books[1].title, "Sahih Bukhari");
    strcpy(books[1].author, "Imam Bukhari");
    strcpy(books[1].genre, "Hadith");
    books[1].publicationYear = 846;
    strcpy(books[1].ISBN, "978-1-23456-789-1");

    strcpy(books[2].title, "Sahih Muslim");
    strcpy(books[2].author, "Imam Muslim");
    strcpy(books[2].genre, "Hadith");
    books[2].publicationYear = 875;
    strcpy(books[2].ISBN, "978-1-23456-789-2");

    strcpy(books[3].title, "Riyad-us-Saliheen");
    strcpy(books[3].author, "Imam Nawawi");
    strcpy(books[3].genre, "Hadith");
    books[3].publicationYear = 1277;
    strcpy(books[3].ISBN, "978-1-23456-789-3");

    strcpy(books[4].title, "Al-Adab Al-Mufrad");
    strcpy(books[4].author, "Imam Bukhari");
    strcpy(books[4].genre, "Hadith");
    books[4].publicationYear = 870;
    strcpy(books[4].ISBN, "978-1-23456-789-4");

    strcpy(books[5].title, "Fortress of the Muslim");
    strcpy(books[5].author, "Saeed bin Ali bin Wahf Al-Qahtani");
    strcpy(books[5].genre, "Dua");
    books[5].publicationYear = 1980;
    strcpy(books[5].ISBN, "978-1-23456-789-5");

    strcpy(books[6].title, "The Sealed Nectar");
    strcpy(books[6].author, "Safiy-ur-Rahman al-Mubarakpuri");
    strcpy(books[6].genre, "Biography");
    books[6].publicationYear = 1979;
    strcpy(books[6].ISBN, "978-1-23456-789-6");

    strcpy(books[7].title, "Fiqh-us-Sunnah");
    strcpy(books[7].author, "Sayyid Sabiq");
    strcpy(books[7].genre, "Fiqh");
    books[7].publicationYear = 1950;
    strcpy(books[7].ISBN, "978-1-23456-789-7");

    strcpy(books[8].title, "Tafsir Ibn Kathir");
    strcpy(books[8].author, "Ibn Kathir");
    strcpy(books[8].genre, "Tafsir");
    books[8].publicationYear = 1373;
    strcpy(books[8].ISBN, "978-1-23456-789-8");

    strcpy(books[9].title, "Ar-Raheeq Al-Makhtum");
    strcpy(books[9].author, "Safiy-ur-Rahman al-Mubarakpuri");
    strcpy(books[9].genre, "Biography");
    books[9].publicationYear = 1979;
    strcpy(books[9].ISBN, "978-1-23456-789-9");

    strcpy(books[10].title, "Men Around the Messenger");
    strcpy(books[10].author, "Khalid Muhammad Khalid");
    strcpy(books[10].genre, "Biography");
    books[10].publicationYear = 1960;
    strcpy(books[10].ISBN, "978-1-23456-789-10");

    strcpy(books[11].title, "Stories of the Prophets");
    strcpy(books[11].author, "Ibn Kathir");
    strcpy(books[11].genre, "Biography");
    books[11].publicationYear = 1372;
    strcpy(books[11].ISBN, "978-1-23456-789-11");

    strcpy(books[12].title, "The Fundamentals of Tawheed");
    strcpy(books[12].author, "Dr. Abu Ameenah Bilal Philips");
    strcpy(books[12].genre, "Aqidah");
    books[12].publicationYear = 1990;
    strcpy(books[12].ISBN, "978-1-23456-789-12");

    strcpy(books[13].title, "The Book of Manners");
    strcpy(books[13].author, "Fu'ad Ibn 'Abdul-'Azeez Ash-Shulhoob");
    strcpy(books[13].genre, "Manners");
    books[13].publicationYear = 2003;
    strcpy(books[13].ISBN, "978-1-23456-789-13");

    strcpy(books[14].title, "The Ideal Muslim");
    strcpy(books[14].author, "Dr. Muhammad Ali Al-Hashimi");
    strcpy(books[14].genre, "Self-Help");
    books[14].publicationYear = 2005;
    strcpy(books[14].ISBN, "978-1-23456-789-14");

    strcpy(books[15].title, "The Ideal Muslimah");
    strcpy(books[15].author, "Dr. Muhammad Ali Al-Hashimi");
    strcpy(books[15].genre, "Self-Help");
    books[15].publicationYear = 2005;
    strcpy(books[15].ISBN, "978-1-23456-789-15");

    strcpy(books[16].title, "The Rights of the Parents");
    strcpy(books[16].author, "Ibn Kathir");
    strcpy(books[16].genre, "Family");
    books[16].publicationYear = 1372;
    strcpy(books[16].ISBN, "978-1-23456-789-16");

    strcpy(books[17].title, "The Book of Zakat");
    strcpy(books[17].author, "Imam Nawawi");
    strcpy(books[17].genre, "Fiqh");
    books[17].publicationYear = 1277;
    strcpy(books[17].ISBN, "978-1-23456-789-17");

    strcpy(books[18].title, "The Book of Hajj");
    strcpy(books[18].author, "Imam Nawawi");
    strcpy(books[18].genre, "Fiqh");
    books[18].publicationYear = 1277;
    strcpy(books[18].ISBN, "978-1-23456-789-18");

    strcpy(books[19].title, "The Book of Fasting");
    strcpy(books[19].author, "Imam Nawawi");
    strcpy(books[19].genre, "Fiqh");
    books[19].publicationYear = 1277;
    strcpy(books[19].ISBN, "978-1-23456-789-19");

    strcpy(books[20].title, "Islamic Jurisprudence");
    strcpy(books[20].author, "Imam Shafi'i");
    strcpy(books[20].genre, "Religion");
    books[20].publicationYear = 820;
    strcpy(books[20].ISBN, "978-1-23456-789-20");

    strcpy(books[21].title, "The Life of the Prophet Muhammad");
    strcpy(books[21].author, "Ibn Ishaq");
    strcpy(books[21].genre, "Biography");
    books[21].publicationYear = 767;
    strcpy(books[21].ISBN, "978-1-23456-789-21");

    strcpy(books[22].title, "The History of Islam");
    strcpy(books[22].author, "Ibn Khaldun");
    strcpy(books[22].genre, "History");
    books[22].publicationYear = 1377;
    strcpy(books[22].ISBN, "978-1-23456-789-22");

    strcpy(books[23].title, "The Book of Knowledge");
    strcpy(books[23].author, "Imam Ghazali");
    strcpy(books[23].genre, "Education");
    books[23].publicationYear = 1100;
    strcpy(books[23].ISBN, "978-1-23456-789-23");

    strcpy(books[24].title, "The Book of Prayer");
    strcpy(books[24].author, "Imam Ghazali");
    strcpy(books[24].genre, "Fiqh");
    books[24].publicationYear = 1100;
    strcpy(books[24].ISBN, "978-1-23456-789-24");

    strcpy(books[25].title, "The Book of Purification");
    strcpy(books[25].author, "Imam Ghazali");
    strcpy(books[25].genre, "Fiqh");
    books[25].publicationYear = 1100;
    strcpy(books[25].ISBN, "978-1-23456-789-25");

    strcpy(books[26].title, "The Book of Charity");
    strcpy(books[26].author, "Imam Ghazali");
    strcpy(books[26].genre, "Fiqh");
    books[26].publicationYear = 1100;
    strcpy(books[26].ISBN, "978-1-23456-789-26");

    strcpy(books[27].title, "The Book of Fasting");
    strcpy(books[27].author, "Imam Ghazali");
    strcpy(books[27].genre, "Fiqh");
    books[27].publicationYear = 1100;
    strcpy(books[27].ISBN, "978-1-23456-789-27");

    strcpy(books[28].title, "The Book of Pilgrimage");
    strcpy(books[28].author, "Imam Ghazali");
    strcpy(books[28].genre, "Fiqh");
    books[28].publicationYear = 1100;
    strcpy(books[28].ISBN, "978-1-23456-789-28");

    strcpy(books[29].title, "The Book of Marriage");
    strcpy(books[29].author, "Imam Ghazali");
    strcpy(books[29].genre, "Fiqh");
    books[29].publicationYear = 1100;
    strcpy(books[29].ISBN, "978-1-23456-789-29");

    strcpy(books[30].title, "The Book of Divorce");
    strcpy(books[30].author, "Imam Ghazali");
    strcpy(books[30].genre, "Fiqh");
    books[30].publicationYear = 1100;
    strcpy(books[30].ISBN, "978-1-23456-789-30");

    strcpy(books[31].title, "The Book of Transactions");
    strcpy(books[31].author, "Imam Ghazali");
    strcpy(books[31].genre, "Fiqh");
    books[31].publicationYear = 1100;
    strcpy(books[31].ISBN, "978-1-23456-789-31");

    strcpy(books[32].title, "The Book of Inheritance");
    strcpy(books[32].author, "Imam Ghazali");
    strcpy(books[32].genre, "Fiqh");
    books[32].publicationYear = 1100;
    strcpy(books[32].ISBN, "978-1-23456-789-32");

    strcpy(books[33].title, "The Book of Jihad");
    strcpy(books[33].author, "Imam Ghazali");
    strcpy(books[33].genre, "Fiqh");
    books[33].publicationYear = 1100;
    strcpy(books[33].ISBN, "978-1-23456-789-33");

    strcpy(books[34].title, "The Book of Food");
    strcpy(books[34].author, "Imam Ghazali");
    strcpy(books[34].genre, "Fiqh");
    books[34].publicationYear = 1100;
    strcpy(books[34].ISBN, "978-1-23456-789-34");

    strcpy(books[35].title, "The Book of Drinks");
    strcpy(books[35].author, "Imam Ghazali");
    strcpy(books[35].genre, "Fiqh");
    books[35].publicationYear = 1100;
    strcpy(books[35].ISBN, "978-1-23456-789-35");

    strcpy(books[36].title, "The Book of Clothing");
    strcpy(books[36].author, "Imam Ghazali");
    strcpy(books[36].genre, "Fiqh");
    books[36].publicationYear = 1100;
    strcpy(books[36].ISBN, "978-1-23456-789-36");

    strcpy(books[37].title, "The Book of Hunting");
    strcpy(books[37].author, "Imam Ghazali");
    strcpy(books[37].genre, "Fiqh");
    books[37].publicationYear = 1100;
    strcpy(books[37].ISBN, "978-1-23456-789-37");

    strcpy(books[38].title, "The Book of Sacrifice");
    strcpy(books[38].author, "Imam Ghazali");
    strcpy(books[38].genre, "Fiqh");
    books[38].publicationYear = 1100;
    strcpy(books[38].ISBN, "978-1-23456-789-38");

    strcpy(books[39].title, "The Book of Funerals");
    strcpy(books[39].author, "Imam Ghazali");
    strcpy(books[39].genre, "Fiqh");
    books[39].publicationYear = 1100;
    strcpy(books[39].ISBN, "978-1-23456-789-39");

    welcomeMessage();
    
    int choice, userId;
    while (1) {
        mainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice); // Add this line to read the user input
        if (choice < 1 || choice > 9) {
            printf("Invalid input. Please select a number from 1 to 9.\n");
            continue;
        }
        switch (choice) { 
            case 1:
                showProgressBar(); // Show progress bar for displaying books
                displayBooks();
                break;
            case 2:
                searchBooks();
                break;
            case 3:
                advancedSearch();
                break;
            case 4:
                userId = loginUser();
                if (userId != -1) {
                    showProgressBar(); // Show progress bar for borrowing book
                    borrowBook(userId);
                }
                break;
            case 5:
                userId = loginUser();
                if (userId != -1) {
                    showProgressBar(); // Show progress bar for returning book
                    returnBook(userId);
                }
                break;
            case 6:
                showProgressBar(); // Show progress bar for registering user
                registerUser();
                break;
            case 7:
                loginUser();
                break;
            case 8:
                userId = loginUser();
                if (userId != -1) {
                    showProgressBar(); // Show progress bar for displaying borrowed books
                    displayBorrowedBooks(userId);
                }
                break;
            case 9:
                printf("Thank you for visiting the library.\n");
                return 0;
            default:
                printf("Invalid choice. Please select a number from 1 to 9.\n");
        }
    } 
    return 0;
}

// Display a welcome message
void welcomeMessage() {
    printf("====================================\n");
    printf("=                                  =\n");
    printf("=      Welcome to the Islamic      =\n");
    printf("=         Library System           =\n");
    printf("=                                  =\n");
    printf("====================================\n\n");
}

// Display book information in a tabular format
void displayBookGraphic(int serialNumber, char *title, char *author) {
    // Print the table header
    printf("-------------------------------------------------\n");
    printf("| %-10s | %-20s | %-10s |\n", "Book ID", "Title", "Author");
    printf("-------------------------------------------------\n");
    
    // Print the book details in a tabular format
    printf("| %-10d | %-20.20s | %-10.10s |\n", serialNumber, title, author);
    
    // Print the table footer
    printf("-------------------------------------------------\n");
}

// Display all books in the library
void displayBooks() {
    printf("\nBooks available in the library:\n");
    for (int i = 0; i < NUM_BOOKS; i++) {
        displayBookGraphic(i + 1, books[i].title, books[i].author);
    }
    printf("\n");
}

// Display the main menu
void mainMenu() {
    printf("====================================\n");
    printf("=          Main Menu               =\n");
    printf("====================================\n");
    printf("1. Display Books\n");
    printf("2. Search Books\n");
    printf("3. Advanced Search\n");
    printf("4. Borrow Book\n");
    printf("5. Return Book\n");
    printf("6. Register User\n");
    printf("7. Login\n");
    printf("8. Display Borrowed Books\n");
    printf("9. Exit\n");
    printf("====================================\n");
    printf("\n");
}

// Convert a string to lowercase
void toLowerCase(char str[]) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Search for books by keyword
void searchBooks() {
    char keyword[50];
    printf("\nEnter keyword to search: ");
    scanf("%s", keyword);
    toLowerCase(keyword);
    showProgressBar(); // Show progress bar before displaying search results
    printf("\n====================================\n");
    printf("=          Searched Results          =\n");
    printf("====================================\n");
    int found = 0; // Add a flag to check if any book is found
    for (int i = 0; i < NUM_BOOKS; i++) {
        char title[50], author[50], genre[30];
        strcpy(title, books[i].title);
        strcpy(author, books[i].author);
        strcpy(genre, books[i].genre);
        toLowerCase(title);
        toLowerCase(author);
        toLowerCase(genre);
        if (strstr(title, keyword) || strstr(author, keyword) || strstr(genre, keyword)) {
            printf("%d. %s by %s\n", i + 1, books[i].title, books[i].author);
            found = 1; // Set the flag if a book is found
        }
    }
    if (!found) {
        printf("No books found matching the keyword.\n");
    }
    printf("====================================\n\n");
}

// Perform an advanced search for books
void advancedSearch() {
    int choice;
    printf("\n====================================\n");
    printf("=       Advanced Search Options    =\n");
    printf("====================================\n");
    printf("1. Search by Author\n");
    printf("2. Search by Genre\n");
    printf("====================================\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Clear the newline character left by scanf
    char keyword[50];
    int found = 0; // Add a flag to check if any book is found
    switch (choice) {
        case 1:
            printf("Enter author name: ");
            fgets(keyword, sizeof(keyword), stdin);
            keyword[strcspn(keyword, "\n")] = 0; // Remove trailing newline
            toLowerCase(keyword);
            showProgressBar(); // Show progress bar before displaying search results
            printf("\n====================================\n");
            printf("=          Searched Results          =\n");
            printf("====================================\n");
            for (int i = 0; i < NUM_BOOKS; i++) {
                char author[50];
                strcpy(author, books[i].author);
                toLowerCase(author);
                if (strstr(author, keyword)) {
                    printf("%d. %s by %s\n", i + 1, books[i].title, books[i].author);
                    found = 1; // Set the flag if a book is found
                }
            }
            break;
        case 2:
            printf("Enter genre: ");
            fgets(keyword, sizeof(keyword), stdin);
            keyword[strcspn(keyword, "\n")] = 0; // Remove trailing newline
            toLowerCase(keyword);
            showProgressBar(); // Show progress bar before displaying search results
            printf("\n====================================\n");
            printf("=          Searched Results          =\n");
            printf("====================================\n");
            for (int i = 0; i < NUM_BOOKS; i++) {
                char genre[30];
                strcpy(genre, books[i].genre);
                toLowerCase(genre);
                if (strstr(genre, keyword)) {
                    printf("%d. %s by %s\n", i + 1, books[i].title, books[i].author);
                    found = 1; // Set the flag if a book is found
                }
            }
            break;
        default:
            printf("Invalid choice.\n");
    }
    if (!found) {
        printf("No books found matching the keyword.\n");
    }
    printf("====================================\n\n");
}

// Count the number of books borrowed by a user
int countBorrowedBooks(int userId) {
    int count = 0;
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i].userId == userId && strcmp(transactions[i].returnDate, "N/A") == 0) {
            count++;
        }
    }
    return count;
}

// Borrow a book
void borrowBook(int userId) {
    int borrowedBooks = countBorrowedBooks(userId);
    if (borrowedBooks >= 3) {
        printf("You have already borrowed 3 books. Please return one or all books to borrow more.\n\n");
        return;
    }
    int bookId;
    printf("Enter book ID to borrow: ");
    scanf("%d", &bookId);
    if (bookId > 0 && bookId <= NUM_BOOKS) {
        // Check if the book is already borrowed by any user and not returned
        for (int i = 0; i < transactionCount; i++) {
            if (transactions[i].bookId == bookId - 1 && strcmp(transactions[i].returnDate, "N/A") == 0) {
                printf("This book is currently borrowed by another user and not returned yet.\n\n");
                return;
            }
        }
        // Check if the user has already borrowed this book and not returned it
        for (int i = 0; i < transactionCount; i++) {
            if (transactions[i].userId == userId && transactions[i].bookId == bookId - 1 && strcmp(transactions[i].returnDate, "N/A") == 0) {
                printf("You have already borrowed this book and not returned it yet.\n\n");
                return;
            }
        }
        transactions[transactionCount].userId = userId;
        transactions[transactionCount].bookId = bookId - 1;
        printf("Enter borrow date (YYYY-MM-DD): ");
        scanf("%s", transactions[transactionCount].borrowDate);
        strcpy(transactions[transactionCount].returnDate, "N/A");
        transactionCount++;
        printf("Book borrowed successfully.\n\n");
    } else {
        printf("Invalid book ID.\n\n");
    }
}

// Calculate the fine for late return of a book
int calculateFine(char borrowDate[], char returnDate[]) {
    int borrowYear, borrowMonth, borrowDay;
    int returnYear, returnMonth, returnDay;

    sscanf(borrowDate, "%d-%d-%d", &borrowYear, &borrowMonth, &borrowDay);
    sscanf(returnDate, "%d-%d-%d", &returnYear, &returnMonth, &returnDay);

    struct tm borrow_tm = {0}, return_tm = {0};
    borrow_tm.tm_year = borrowYear - 1900;
    borrow_tm.tm_mon = borrowMonth - 1;
    borrow_tm.tm_mday = borrowDay;
    return_tm.tm_year = returnYear - 1900;
    return_tm.tm_mon = returnMonth - 1;
    return_tm.tm_mday = returnDay;

    time_t borrow_time = mktime(&borrow_tm);
    time_t return_time = mktime(&return_tm);
    double seconds = difftime(return_time, borrow_time);
    int days = seconds / (60 * 60 * 24);
    if (days > 30) {
        return (days - 30) * FINE_PER_DAY;
    }
    return 0;
}

// Return a borrowed book
void returnBook(int userId) {
    int bookId;
    printf("Enter book ID to return: ");
    scanf("%d", &bookId);
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i].userId == userId && transactions[i].bookId == bookId - 1 && strcmp(transactions[i].returnDate, "N/A") == 0) {
            printf("Enter return date (YYYY-MM-DD): ");
            scanf("%s", transactions[i].returnDate);
            int fine = calculateFine(transactions[i].borrowDate, transactions[i].returnDate);
            if (fine > 0) {
                printf("Book returned successfully. You have a fine of %d rupees.\n\n", fine);
            } else {
                printf("Book returned successfully. No fine.\n\n");
            }
            return;
        }
    }
    printf("No record found for borrowed book.\n\n");
}

// Register a new user
void registerUser() {
    printf("Enter name: ");
    getchar(); // To consume the newline character left by previous input
    fgets(users[userCount].name, sizeof(users[userCount].name), stdin);
    users[userCount].name[strcspn(users[userCount].name, "\n")] = 0; // Remove trailing newline
    printf("Enter contact details: ");
    scanf("%s", users[userCount].contact);
    userCount++;
    printf("User registered successfully.\n\n");
}

// Login a user
int loginUser() {
    char name[50];
    printf("Enter name to login: ");
    getchar(); // To consume the newline character left by previous input
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove trailing newline
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].name, name) == 0) {
            printf("Login successful.\n\n");
            return i;
        }
    }
    printf("User not found. Please register yourself first\n\n");
    return -1;
}

// Display the books borrowed by a user
void displayBorrowedBooks(int userId) {
    int borrowedCount = 0;
    printf("\nBooks borrowed by user:\n");
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i].userId == userId) {
            printf("%d. %s (Borrowed on: %s, Returned on: %s)\n", borrowedCount + 1, books[transactions[i].bookId].title, transactions[i].borrowDate, transactions[i].returnDate);
            borrowedCount++;
        }
    }
    if (borrowedCount == 0) {
        printf("No books borrowed.\n");
    }
    printf("\n");
}

// Show a progress bar
void showProgressBar() {
    printf("Loading: [");
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 100000000L; // 0.1 seconds
    for (int i = 0; i < 20; i++) {
        printf("#");
        fflush(stdout);
        nanosleep(&ts, NULL); // Sleep for 0.1 seconds
    }
    printf("]\n");
}
