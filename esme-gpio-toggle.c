#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_GPIO 26
#define GPIO_CHIP_PATH "/dev/gpiochip0"

static void usage(const char *progname)
{
    fprintf(stderr,
            "Usage : %s [--gpio <GPIO_ID>]\n"
            "    Sans argument, la GPIO par defaut est %d.\n",
            progname, DEFAULT_GPIO);
}

int main(int argc, char *argv[])
{
    int gpio = DEFAULT_GPIO;
    struct gpiod_chip *chip;
    struct gpiod_line *line;
    int ret;
    int value = 0;  // valeur initiale peu importe

    /* --- Parsing des arguments --- */
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "--gpio")) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Erreur : --gpio nécessite un argument.\n");
                usage(argv[0]);
                return EXIT_FAILURE;
            }
            gpio = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            usage(argv[0]);
            return EXIT_SUCCESS;
        } else {
            fprintf(stderr, "Argument inconnu : %s\n", argv[i]);
            usage(argv[0]);
            return EXIT_FAILURE;
        }
    }

    /* --- Ouverture du chip GPIO --- */
    chip = gpiod_chip_open(GPIO_CHIP_PATH);
    if (!chip) {
        perror("gpiod_chip_open");
        return EXIT_FAILURE;
    }

    /* --- Récupération de la ligne --- */
    line = gpiod_chip_get_line(chip, gpio);
    if (!line) {
        perror("gpiod_chip_get_line");
        gpiod_chip_close(chip);
        return EXIT_FAILURE;
    }

    /* --- Demande de la ligne en sortie --- */
    ret = gpiod_line_request_output(line, "esme-gpio-toggle", value);
    if (ret < 0) {
        perror("gpiod_line_request_output");
        gpiod_line_release(line);
        gpiod_chip_close(chip);
        return EXIT_FAILURE;
    }

    /* --- Boucle infinie : toggle toutes les secondes --- */
    while (1) {
        value = !value;                           // inverse la valeur
        ret = gpiod_line_set_value(line, value);  // écrit sur la GPIO
        if (ret < 0) {
            perror("gpiod_line_set_value");
            break;
        }
        sleep(1);  // 1 seconde
    }

    /* --- Nettoyage (si on sort de la boucle) --- */
    gpiod_line_set_value(line, 0);
    gpiod_line_release(line);
    gpiod_chip_close(chip);

    return EXIT_SUCCESS;
}
 
