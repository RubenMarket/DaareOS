#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_FILE "database.dat"

typedef struct {
    int id;
    char name[100];
    int age;
} User;

typedef struct {
    User *users;
    size_t size;
    size_t capacity;
} Database;

// Function to initialize the database
Database* create_database() {
    Database *db = malloc(sizeof(Database));
    db->size = 0;
    db->capacity = 10;
    db->users = malloc(db->capacity * sizeof(User));
    return db;
}

// Function to save the database to a file
void save_database(Database *db) {
    FILE *file = fopen(DB_FILE, "wb");
    if (file) {
        fwrite(&db->size, sizeof(size_t), 1, file);
        fwrite(db->users, sizeof(User), db->size, file);
        fclose(file);
    } else {
        printf("Error saving database.\n");
    }
}

// Function to load the database from a file
Database* load_database() {
    FILE *file = fopen(DB_FILE, "rb");
    Database *db = create_database();
    if (file) {
        fread(&db->size, sizeof(size_t), 1, file);
        db->users = realloc(db->users, db->size * sizeof(User));
        fread(db->users, sizeof(User), db->size, file);
        fclose(file);
    } else {
        printf("No database found, starting a new one.\n");
    }
    return db;
}

// Function to add a user to the database
void add_user(Database *db, int id, const char *name, int age) {
    if (db->size >= db->capacity) {
        db->capacity *= 2;
        db->users = realloc(db->users, db->capacity * sizeof(User));
    }
    db->users[db->size].id = id;
    strncpy(db->users[db->size].name, name, sizeof(db->users[db->size].name) - 1);
    db->users[db->size].age = age;
    db->size++;
}

// Function to find a user by ID
User* find_user_by_id(Database *db, int id) {
    for (size_t i = 0; i < db->size; i++) {
        if (db->users[i].id == id) {
            return &db->users[i];
        }
    }
    return NULL;
}

// Function to delete a user by ID
void delete_user(Database *db, int id) {
    for (size_t i = 0; i < db->size; i++) {
        if (db->users[i].id == id) {
            for (size_t j = i; j < db->size - 1; j++) {
                db->users[j] = db->users[j + 1];
            }
            db->size--;
            return;
        }
    }
    printf("User with ID %d not found.\n", id);
}

// Function to print all users in the database
void print_all_users(Database *db) {
    for (size_t i = 0; i < db->size; i++) {
        printf("ID: %d, Name: %s, Age: %d\n", db->users[i].id, db->users[i].name, db->users[i].age);
    }
}

// Free memory allocated for the database
void free_database(Database *db) {
    free(db->users);
    free(db);
}

int main() {
    // Load database from file or create a new one
    Database *db = load_database();

    // Adding users
    add_user(db, 1, "John Doe", 30);
    add_user(db, 2, "Jane Smith", 25);
    add_user(db, 3, "Sam Brown", 22);

    // Print all users
    printf("Users in the database:\n");
    print_all_users(db);

    // Save database to file
    save_database(db);

    // Find a user by ID
    User *user = find_user_by_id(db, 2);
    if (user) {
        printf("\nFound user by ID: %d, Name: %s, Age: %d\n", user->id, user->name, user->age);
    }

    // Delete a user by ID
    delete_user(db, 1);
    printf("\nAfter deleting user with ID 1:\n");
    print_all_users(db);

    // Save changes to the database
    save_database(db);

    // Free the database memory
    free_database(db);

    return 0;
}
