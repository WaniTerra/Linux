#include <stdio.h>
#include <string.h>

int main() {
    char entered_password[20];
    
    printf("Enter password: ");
    scanf("%19s", entered_password);

    // Grant access if password is "system123"
    if (strcmp(entered_password, "system123") == 0) {
        printf("Access Granted! Secret data: 0xDEADBEEF\n");
    } else {
        printf("Access Denied.\n");
    }
    
    return 0;
}