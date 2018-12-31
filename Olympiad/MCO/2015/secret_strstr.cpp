#include <cstring>
#include <cstdio>
#define MAX_N 100000
using namespace std;
char BASE94_TEMPLATE[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-_=+[]{}\\|;:'\",./<>?";

void base94_encode(int input, char *output) {
  // Each int needs at most 5 bytes to encode
  // 2^(4*8) < 94^5
  int offset = 4;
  do {
    output[offset] = BASE94_TEMPLATE[input % 94];
    input = input / 94;
    offset = offset - 1;
  } while (input);

  // Pad with spaces
  while (offset >= 0) {
    output[offset] = ' ';
    offset = offset - 1;
  }
}

int main() {
  int N;
  int message;
  char str_message_1[2 * 5 * MAX_N + 5], str_message_2[5 * MAX_N + 5];

  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    scanf("%d", &message);
    base94_encode(message, str_message_1 + 5 * i);
  }
  memcpy(str_message_1 + 5 * N, str_message_1, 5 * N);
  str_message_1[2 * 5 * N] = 0;

  for (int i = 0; i < N; i++) {
    scanf("%d", &message);
    base94_encode(message, str_message_2 + 5 * i);
  }
  str_message_2[5 * N] = 0;

  if (strstr(str_message_1, str_message_2) != NULL) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }
}
