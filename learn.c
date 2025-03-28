#include <stdio.h>
#include <stdlib.h>

int main() {
    // Récupère la valeur de la variable d'environnement "PATH"
    int i;
    i = 0;
    const char *path = getenv("TOfTO");
    // Vérifie si la variable existe
    if (path != NULL) {
        printf("La variable d'environnement PATH vaut :\n%s\n", path);
    } else {
        printf("La variable d'environnement PATH n'est pas définie.\n");
    }
    
    return 0;
}
