#include <stdio.h>
#include <string.h>

#define MAX_DAYS 7
#define MAX_TASKS 3
#define MAX_LEN 100

// Structure for each day
struct Day {
    char dayName[10];
    char tasks[MAX_TASKS][MAX_LEN];
};

int main() {
    struct Day week[MAX_DAYS] = {
        {"Monday"}, {"Tuesday"}, {"Wednesday"},
        {"Thursday"}, {"Friday"}, {"Saturday"}, {"Sunday"}
    };

    int dayChoice, taskCount;

    
    printf("Enter tasks for any day of the week.\n");

    while (1) {
        printf("\nSelect a day:\n");
        for (int i = 0; i < MAX_DAYS; i++) {
            printf("%d. %s\n", i + 1, week[i].dayName);
        }
        printf("8. Exit and Show Tasks\n");
        printf("Enter your choice (1-8): ");
        scanf("%d", &dayChoice);

        if (dayChoice == 8) break;

        if (dayChoice < 1 || dayChoice > 7) {
            printf("Invalid choice. Try again.\n");
            continue;
        }

        int index = dayChoice - 1;
        printf("How many tasks for %s? (max 3): ", week[index].dayName);
        scanf("%d", &taskCount);
        getchar(); 
        if (taskCount < 1 || taskCount > MAX_TASKS) {
            printf("Invalid number of tasks.\n");
            continue;
        }

        for (int i = 0; i < taskCount; i++) {
            printf("Enter task %d: ", i + 1);
            fgets(week[index].tasks[i], MAX_LEN, stdin);
            week[index].tasks[i][strcspn(week[index].tasks[i], "\n")] = '\0'; 
        }
    }

    
    printf("\n--- Weekly Calendar ---\n");
    for (int i = 0; i < MAX_DAYS; i++) {
        printf("%s:\n", week[i].dayName);
        for (int j = 0; j < MAX_TASKS; j++) {
            if (strlen(week[i].tasks[j]) > 0) {
                printf("  - %s\n", week[i].tasks[j]);
            }
        }
    }

    return 0;
}
