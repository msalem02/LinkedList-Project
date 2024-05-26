//Mohammed Yousef Salem - 1203022 - Section.4


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define structures for town and district
struct Town{
    char name[50];
    int population;
    struct Town* next;
    struct Town* prev;
};

struct District{
    char name[50];
    struct Town* towns;
    struct District* next;
    struct District* prev;
};

typedef struct District* List; // Define List as a pointer to District


//Function Prototypes:
void displayMenu();
void loadFromFile(List* L);
void printLoadedFile(const char* filename);
void printInformation(List L);
void radixSort(List* L);
void sortTowns(List L);
void addDistrict(List* L);
void addTown(List L);
void deleteTown(List L);
void deleteDistrict(List* L);
void calculatePopulation(List L);
void printDistrictPopulation(List L);
void changeTownPopulation(List L);
void saveToFile(List L);
void freeMemory(List* L);



int main() {
    List districts = NULL; // Initialize districts list
    int choice;

    do {
        displayMenu();      // Display the menu options
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                loadFromFile(&districts);
                break;
            case 2:
                printf("Loaded information before sorting:\n");
                printLoadedFile("C:\\Users\\Tech Zone\\CLionProjects\\LinkedListProjectOne\\districts.txt");
                break;
            case 3:
                radixSort(&districts);
                break;
            case 4:
                sortTowns(districts);
                break;
            case 5:
                printf("Sorted information:\n");
                printInformation(districts);
                break;
            case 6:
                printf("Adding a new district...\n");
                addDistrict(&districts);
                break;
            case 7:
                printf("Adding a new town...\n");
                addTown(districts);
                break;
            case 8:
                printf("Deleting a town...\n");
                deleteTown(districts);
                break;
            case 9:
                printf("Deleting a complete district...\n");
                deleteDistrict(&districts);
                break;
            case 10:
                calculatePopulation(districts);
                break;
            case 11:
                printDistrictPopulation(districts);
                break;
            case 12:
                changeTownPopulation(districts);
                break;
            case 13:
                saveToFile(districts);
                break;
            case 14:
                freeMemory(&districts);     // Free memory allocated for districts list
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while(choice != 14);
    freeMemory(&districts);        // Free memory allocated for districts list
    printf("Memory freed successfully.\n");
    return 0;
}

/*  This function displays a menu of options for the user to choose from.
    Each option corresponds to a specific action related to managing district and town information.  */
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Load input file\n");
    printf("2. Print loaded information\n");
    printf("3. Sort districts alphabetically\n");
    printf("4. Sort towns for each district based on population\n");
    printf("5. Print sorted information\n");
    printf("6. Add a new district and sort the list\n");
    printf("7. Add a new town to a certain district\n");
    printf("8. Delete a town from a specific district\n");
    printf("9. Delete a complete district\n");
    printf("10. Calculate population stats\n");
    printf("11. Print districts and their total population\n");
    printf("12. Change population of a town\n");
    printf("13. Save to output file\n");
    printf("14. Exit\n");
}


void loadFromFile(List* L){

    // Open the file for reading
    FILE* file= fopen("C:\\Users\\Tech Zone\\CLionProjects\\LinkedListProjectOne\\districts.txt","r");

    // Check if the file was opened successfully
    if(file == NULL){
        printf("Error opening file...\n");
        return;
    }

    // Define an array to store each line read from the file
    char line[100];

    // Read each line from the file until the end is reached
    while(fgets(line,sizeof (line),file)){
        // Parse the line using strtok and '|' as the delimiter
        char *districtName = strtok(line, "|");
        char *townName = strtok(NULL, "|");
        char *populationStr = strtok(NULL, "|");
        int population = atoi(populationStr);

        // Initialize pointers for iterating through districts
        struct District* currentDistrict = *L;
        struct  District* prevDistrict=NULL;

        // Traverse the list to find the correct position for the new district
        while(currentDistrict !=NULL && strcmp(currentDistrict->name , districtName)<0){
            prevDistrict = currentDistrict;
            currentDistrict=currentDistrict->next;
        }


        if(currentDistrict == NULL || strcmp(currentDistrict-> name, districtName) !=0){
            // Allocate memory for the new district
            struct District* newDistrict = (struct District*)malloc(sizeof(struct District));
            strcpy(newDistrict->name,districtName);
            newDistrict-> towns= NULL;
            newDistrict -> next = currentDistrict;
            newDistrict -> prev = prevDistrict;

            // Update the pointers to insert the new district into the list
            if(prevDistrict == NULL){
                *L =newDistrict;
            }else{
                prevDistrict -> next = newDistrict;
            }


            currentDistrict=newDistrict;            // Update the current district pointer
        }

        // Allocate memory for the new town
        struct Town* newTown= (struct Town* ) malloc(sizeof (struct Town));
        strcpy(newTown->name,townName);
        newTown->population=population;
        newTown->next=NULL;
        newTown->prev=NULL;

        // Initialize pointers for iterating through towns in the current district
        struct Town* currentTown = currentDistrict->towns;

        // Check if the town list in the district is empty or if the new town should be inserted at the beginning
        if(currentTown== NULL || strcmp( currentTown->name,townName)>0){
            newTown->next =currentTown;
            if(currentTown!=NULL)
                currentTown->prev=newTown;
            currentDistrict -> towns =newTown;

        }
        else{
            // Find the correct position to insert the new town in the sorted town list
            while (currentTown -> next !=NULL && strcmp(currentTown -> next -> name,townName) <0){
                currentTown = currentTown -> next;
            }

            // Update pointers to insert the new town in the correct position
            newTown->next = currentTown->next;
            newTown ->prev =currentTown;

            if(currentTown -> next != NULL){
                currentTown ->next ->prev = newTown;
            }
            currentTown -> next =newTown;
        }
    }


    fclose(file);    // Close the file after reading is done
    printf("File loaded successfully...!\n");

}


// Function to print the contents of a file given its filename
void printLoadedFile(const char* filename) {
    FILE* file = fopen(filename, "r");     // Open the file in read mode

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening file.\n");
        return;     // Return from function if file opening fails
    }

    char line[100]; // Buffer to store each line read from the file, assuming maximum line length is 100 characters

    // Read each line from the file and print it
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);  // Print each line from the file directly
    }

    fclose(file);       // Close the file
}


// Function to print information about districts and towns
void printInformation(List L){
    struct District* currentDistrict =L;            // Initialize currentDistrict to point to the start of the list
    struct Town* currentTown;

    // Iterate through each district in the list
    while (currentDistrict!= NULL){
        currentTown = currentDistrict->towns;       // Initialize currentTown to point to the towns in the current district

        // Iterate through each town in the current district
        while(currentTown != NULL){

            // Print district name, town name, and population of the current town
            printf("%s|%s|%d\n", currentDistrict->name, currentTown->name, currentTown->population);
            currentTown = currentTown->next;        // Move to the next town in the current district
        }

        currentDistrict=currentDistrict-> next;     // Move to the next district in the list
    }
}


void radixSort(List* L){

    int maxLength=0;                    // Determine the maximum length of names in the list
    struct District* current= *L;
    while(current != NULL){
        int len= strlen(current->name);
        if(len > maxLength){
            maxLength=len;
        }
        current=current->next;
    }

    // Radix sort algorithm
    for(int pos=maxLength-1;pos>= 0;pos--){

        // Initialize an output list and count array
        struct District* output=NULL;
        int count[256]={0};                // Assuming ASCII characters

        // Count occurrences of characters at 'pos' position
        struct District* current = *L;
        while(current !=NULL){
            count[(unsigned char)current -> name[pos]]++;
            current=current -> next;
        }

        // Cumulative sum of count array
        for (int i = 1; i <256; i++) {
            count[i] += count[i-1];
        }

        // Rearrange elements based on count array
        current =*L;
        while (current !=NULL){
            struct District* next=current-> next;
            int index = (unsigned char)current->name[pos];
            count[index]--;

            // Update links in the output list
            current->next = output;
            current->prev = NULL;
            if (output != NULL) {
                output->prev = current;
            }

            output = current;
            current = next;
        }
        *L = output;                            // Update the original list pointer to point to the sorted list

    }
    printf("Sorting Successful..\n");
}


// Function to sort towns within each district based on population
void sortTowns(List L){

    struct District* currentDistrict =L;
    while(currentDistrict != NULL){
        struct Town* sortedTowns= NULL; // Initialize a sorted list of towns
        struct  Town* currentTown=currentDistrict -> towns;     // Get the first town in the district

        // Iterate through each district
        while(currentTown != NULL){
            struct Town* next=currentTown ->next;       // Store the next town in the list
            struct Town* prev = NULL;
            struct Town* temp = sortedTowns;

            // Sorting towns based on population in ascending order
            while (temp != NULL && temp->population < currentTown->population) {
                prev = temp;
                temp = temp->next;
            }

            // Insert current town into the sorted list
            if(prev == NULL){
                currentTown -> next=sortedTowns;
                if(sortedTowns != NULL){
                    sortedTowns -> prev =currentTown;
                }
                sortedTowns=currentTown;
            }
            else{
                prev -> next =currentTown;
                currentTown -> next =temp;
                currentTown -> prev= prev;
                if(temp != NULL){
                    temp -> prev =currentTown;
                }
            }

            currentTown= next;      // Move to the next town in the district
        }

        // Update the district's list of towns to the sorted list
        currentDistrict->towns = sortedTowns;
        currentDistrict = currentDistrict->next;        // Move to the next district
    }
    printf("Towns sorted based on population :) \n");

}


// Function to add a new district to the list
void addDistrict (List *L){
    char name[50];

    printf("Enter new district name: ");
    getchar(); // Consume newline character from previous input
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline character from fgets input

    // Allocate memory for the new district
    struct District* newDistrict =(struct District* ) malloc(sizeof (struct District));
    strcpy( newDistrict -> name, name);     // Copy the name into the new district
    newDistrict->towns = NULL;                          // Initialize the towns list for the new district
    newDistrict->next = NULL;
    newDistrict->prev = NULL;

    // Get the current district list and initialize variables for traversal
    struct District* currentDistrict= *L;
    struct District* prevDistrict= NULL;

    // Traverse the district list to find the correct position for insertion
    while(currentDistrict != NULL && strcmp(currentDistrict -> name , name) < 0){
        prevDistrict= currentDistrict;
        currentDistrict= currentDistrict->next;
    }

    // Check if the district with the same name already exists
    if(currentDistrict == NULL || strcmp(currentDistrict -> name, name) != 0){
        newDistrict ->next = currentDistrict;
        newDistrict ->prev = prevDistrict;
        if(prevDistrict == NULL){
            *L = newDistrict;       // Update the list head if adding at the beginning
        }
        else{
            prevDistrict -> next =newDistrict;
        }
    } else{
        printf("District already exists.\n");
        free(newDistrict);       // Free memory if district already exists
    }

}


// Function to add a new town to a specific district in the list
void addTown(List L){

    char districtName[50], townName[50];
    int population;

    // Get user input for district name, town name, and population
    printf("Enter district name to add town: ");
    scanf("%s", districtName);

    printf("Enter new town name: ");
    getchar(); // Consume newline character from previous input
    fgets(townName, sizeof(townName), stdin);
    townName[strcspn(townName, "\n")] = '\0'; // Remove newline character from fgets input

    printf("Enter town population: ");
    scanf("%d", &population);


    struct District* currentDistrict = L;           // Initialize currentDistrict to the start of the district list


    // Traverse the district list to find the specified district
    while(currentDistrict != NULL && strcmp(currentDistrict -> name, districtName)){
        currentDistrict = currentDistrict -> next;
    }

    // Check if the district exists
    if(currentDistrict != NULL){

        // Allocate memory for the new town
        struct Town* newTown = (struct Town*)malloc(sizeof(struct Town));
        strcpy(newTown->name, townName);        // Copy the town name
        newTown->population = population;                   // Assign the population
        newTown->next = NULL;
        newTown->prev = NULL;

        // Get the current list of towns in the district
        struct Town* currentTown = currentDistrict->towns;

        // Insert the new town into the correct position based on alphabetical order
        if(currentTown == NULL || strcmp(currentTown -> name, townName) > 0){
            newTown->next = currentTown;
            if (currentTown != NULL) {
                currentTown->prev = newTown;
            }
            currentDistrict->towns = newTown;
        }
        else {
            while (currentTown->next != NULL && strcmp(currentTown->next->name, townName) < 0) {
                currentTown = currentTown->next;
            }
            newTown->next = currentTown->next;
            newTown->prev = currentTown;
            if (currentTown->next != NULL) {
                currentTown->next->prev = newTown;
            }
            currentTown->next = newTown;
        }
    }
    else {
        printf("District not found :( \n");
    }
}

//Deletes a town from the specified district in a linked list.
void deleteTown(List L){
    char districtName[50], townName[50];
    printf("Enter district name to delete town from: ");
    scanf("%s", districtName);


    printf("Enter town name to delete: ");
    getchar(); // Consume newline character from previous input
    fgets(townName, sizeof(townName), stdin);
    townName[strcspn(townName, "\n")] = '\0'; // Remove newline character from fgets input

    // Traverse the linked list of districts to find the specified district
    struct District* currentDistrict = L;
    while (currentDistrict != NULL && strcmp(currentDistrict->name, districtName) != 0) {
        currentDistrict = currentDistrict->next;
    }

    // If the specified district is found
    if (currentDistrict != NULL) {

        // Traverse the linked list of towns in the district to find the specified town
        struct Town* currentTown = currentDistrict->towns;
        while (currentTown != NULL && strcmp(currentTown->name, townName) != 0) {
            currentTown = currentTown->next;
        }

        // If the specified town is found
        if (currentTown != NULL) {

            // Delete the town from the linked list
            if (currentTown->prev == NULL) {
                currentDistrict->towns = currentTown->next;
            }
            else {
                currentTown->prev->next = currentTown->next;
            }
            if (currentTown->next != NULL) {
                currentTown->next->prev = currentTown->prev;
            }
            free(currentTown);       // free the memory
            printf("Town deleted successfully.\n");
        }
        else {
            printf("Town not found in the district.\n");
        }
    }
    else {
        printf("District not found.\n");
    }

}


// Function to delete a district and its associated towns from a linked list
void deleteDistrict(List* L){
    char name[50];

    printf("Enter district name to delete: ");
    getchar(); // Consume newline character from previous input
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline character from fgets input


    // Initialize a pointer to the current district, starting from the head of the list
    struct District* currentDistrict= *L;

    // Traverse the list until the end is reached or the district with the given name is found
    while (currentDistrict != NULL && strcmp(currentDistrict->name, name) != 0) {
        currentDistrict = currentDistrict->next;        // Move to the next district
    }

    // If the district with the given name is found
    if(currentDistrict != NULL) {

        // Delete all towns associated with the district
        struct Town *currentTown = currentDistrict->towns;
        while (currentTown != NULL) {
            struct Town *temp = currentTown;          // Temporarily store the current town
            currentTown = currentTown->next;          // Move to the next town
            free(temp);                       // Free memory allocated for the current town
        }


        // Adjust pointers to remove the district from the linked list
        if (currentDistrict->prev == NULL) {
            *L = currentDistrict->next;              // If the district is the first node, update the head pointer
        } else {
            currentDistrict->prev->next = currentDistrict->next;         // Update the next pointer of the previous district
        }
        if (currentDistrict->next != NULL) {
            currentDistrict->next->prev = currentDistrict->prev;         // Update the previous pointer of the next district
        }

        // Free memory allocated for the district
        free(currentDistrict);
        printf("District and associated towns deleted successfully.\n");
    }
    else {
        printf("District not found.\n");        // If the district with the given name is not found

    }
}


// Function to calculate population
void calculatePopulation(List L){
    int totalPopulation = 0 , maxPopulation = 0 , minPopulation= INT_MAX;
    struct District* currentDistrict = L;

    // Iterate through each district
    while(currentDistrict != NULL){
        struct Town* currentTown = currentDistrict -> towns;

        // Iterate through each town in the district
        while ( currentTown != NULL){
            totalPopulation += currentTown -> population;

            // Update max population if needed
            if (currentTown -> population > maxPopulation) {
                maxPopulation = currentTown -> population;
            }

            // Update min population if needed
            if (currentTown -> population < minPopulation) {
                minPopulation = currentTown -> population;
            }

            currentTown = currentTown -> next;                  // Move to the next town in the list.

        }

        currentDistrict = currentDistrict -> next;             // Move to the next district in the list.

    }

    // Output the total, maximum, and minimum population
    printf("Total population of Palestine: %d\n", totalPopulation);
    printf("Maximum town population: %d\n", maxPopulation);
    printf("Minimum town population: %d\n", minPopulation);

}


// Function to print population of each district
void printDistrictPopulation(List L){

    struct District* currentDistrict = L;                  // Pointer to traverse the list of districts.

    // Iterate through each district
    while(currentDistrict != NULL){
        int districtPopulation = 0;
        struct Town* currentTown = currentDistrict -> towns;

        // Iterate through each town in the district
        while (currentTown != NULL){

            districtPopulation += currentTown->population;
            currentTown = currentTown->next;              // Move to the next town in the list.

        }

        // Output the population of the current district
        printf("%s District, Population = %d\n", currentDistrict->name, districtPopulation);

        currentDistrict = currentDistrict->next;         // Move to the next town in the list.

    }
}


// Function to change the population of a town in a given district
void changeTownPopulation(List L){

    // Declare variables to store input values
    char districtName[50], townName[50];
    int newPopulation;

    // Ask user to enter district and town names
    printf("Enter district name: ");
    scanf("%s", districtName);
    printf("Enter town name: ");
    scanf("%s", townName);


    struct District* currentDistrict = L;       // Initialize currentDistrict pointer to the first element in the list

    // Search for the district with the given name
    while (currentDistrict != NULL && strcmp(currentDistrict -> name, districtName) != 0) {
        currentDistrict = currentDistrict -> next;
    }

    // If district is found
    if(currentDistrict != NULL){

        // Initialize currentTown pointer to the first town in the district
        struct Town* currentTown = currentDistrict -> towns;

        // Search for the town with the given name in the district
        while (currentTown != NULL && strcmp( currentTown -> name, townName ) != 0){
            currentTown = currentTown -> next;
        }

        // If town is found
        if(currentTown != NULL){

            // Ask user to enter new population
            printf("Enter new population: ");
            scanf("%d", &newPopulation);

            currentTown -> population = newPopulation;              // Update the population of the town
            printf("Population updated successfully.\n");
        }
        else
            printf("Town not found in the district.\n");

    }

    else
        printf("District not found.\n");

}


// Function to save district and town data to a file
void saveToFile(List L) {

    // Open a file in write mode
    FILE* file = fopen("C:\\Users\\Tech Zone\\CLionProjects\\LinkedListProjectOne\\sorted_districts.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct District* currentDistrict = L;       // Initialize currentDistrict pointer to the first district in the list

    // Loop through each district and write its data to the file
    while (currentDistrict != NULL) {
        int districtPopulation = 0;
        struct Town* currentTown = currentDistrict -> towns;

        // Calculate district population
        while (currentTown != NULL) {
            districtPopulation += currentTown -> population;
            currentTown = currentTown -> next;
        }

        // Write district name and population to file
        fprintf(file, "%s District, Population = %d\n", currentDistrict -> name, districtPopulation);

        // Write town names and populations to file
        currentTown = currentDistrict -> towns;
        while (currentTown != NULL) {
            fprintf(file, "%s, %d\n", currentTown -> name, currentTown -> population);
            currentTown = currentTown -> next;
        }

        fprintf(file, "\n");  // Add a newline after each district's data
        currentDistrict = currentDistrict -> next;
    }

    fclose(file);       // Close the file after writing all data
    printf("Data saved to The File successfully.\n");
}


// Function to free memory allocated for districts and towns
void freeMemory(List* L){

    struct District* currentDistrict = *L;      // Initialize currentDistrict pointer to the first district in the list

    // Loop through each district and free its memory
    while(currentDistrict != NULL){
        struct Town* currentTown = currentDistrict -> towns;

        // Loop through each town in the district and free its memory
        while (currentTown != NULL) {
            struct Town* temp = currentTown;
            currentTown = currentTown->next;
            free(temp);
        }

        // Free memory allocated for the current district
        struct District* temp = currentDistrict;
        currentDistrict = currentDistrict->next;
        free(temp);

    }

    *L = NULL;      // Set the list pointer to NULL after freeing all memory

}