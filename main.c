#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void getBanner();
void print_usage(const char *progname);

int main(int argc, char *argv[]) {
  FILE *fp;
  long prev_size = 0;
  //int change = 0;
  int interval = 1;
  char *file_path = NULL;
  char *file_mode = "r";

  if (argc < 2) {
    print_usage(argv[0]);
    return 1;
  }

  int i = 1;

  while (i < argc) {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      print_usage(argv[0]);
      return 0;
    } else if (strcmp(argv[i], "-i") == 0) {
      if (i + 1 < argc) {
        interval = atoi(argv[i + 1]);
        if (interval <= 0) {
          fprintf(stderr, "Error: interval must be a positive integer\n");
          return 1;
        }
        i += 2;
      } else {
        fprintf(stderr, "Error: -i requires an argument\n");
        return 1;
      }
    } else if (file_path == NULL) {
      file_path = argv[i];
      i++;
    } else {
      fprintf(stderr, "Unknown argument: %s\n", argv[i]);
      print_usage(argv[0]);
      return 1;
    }
  }

  fp = fopen(file_path, file_mode);

  if (fp == NULL) {
    perror("Error opening file");
    return 1;
  }

  getBanner();

  while (1) {
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    if (prev_size != size) {
      // print contents of the file
      fclose(fp);

      fp = fopen(file_path, file_mode);
      if (fp == NULL) {
        perror("Error reopening file");
        return 1;
      }

      // printf("\n\nLog change: %d \n\n", change++);

      printf("\n\n\n");

      char ch;
      while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
      }
      fflush_unlocked(stdout);

      prev_size = size;
    }

    sleep(interval);
  }

  fclose(fp);

  return 0;
}

void getBanner() {
  printf("\n"
         "        _                                \n"
         "       | |                                 \n"
         "  ___  | |__   ___   ___  _ __ __   __ ___  \n"
         " / _ \\ | '_ \\ / __| / _ \\| '__|\\ \\ / // _ \\ \n"
         "| (_) || |_) |\\__ \\|  __/| |    \\ V /|  __/ \n"
         " \\___/ |_.__/ |___/ \\___||_|     \\_/  \\___| \n"
         "                                             \n"
         "                                             \n"
         "\n!! Watch below to monitor any changes to the file !!\n\n");
}

void print_usage(const char *progname) {
  printf("Usage: %s <file-to-watch> [-i interval_seconds]\n", progname);
  printf("Options:\n");
  printf("  -i <seconds>    Poll interval in seconds (default: 1)\n");
  printf("  -h, --help      Show this help message\n");
}