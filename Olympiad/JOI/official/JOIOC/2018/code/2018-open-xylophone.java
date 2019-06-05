public class xylophone {
  public void solve(int N) {
    int[] A = new int[N + 1];
    int sig = +1;
    int prv = xylophone_lib.query(1, 2);
    A[1] = 0;
    A[2] = prv;
    for (int i = 3; i <= N; ++i) {
      int crt = xylophone_lib.query(i - 1, i);
      if (prv + crt != xylophone_lib.query(i - 2, i)) {
        sig *= -1;
      }
      A[i] = A[i - 1] + sig * crt;
      prv = crt;
    }
    int min = 0;
    for (int i = 1; i <= N; ++i) {
      if (min > A[i]) {
        min = A[i];
      }
    }
    for (int i = 1; i <= N; ++i) {
      A[i] += 1 - min;
    }
    int pos1 = -1, posN = -1;
    for (int i = 1; i <= N; ++i) {
      if (A[i] == 1) {
        pos1 = i;
      }
      if (A[i] == N) {
        posN = i;
      }
    }
    if (pos1 > posN) {
      for (int i = 1; i <= N; ++i) {
        A[i] = N + 1 - A[i];
      }
    }
    for (int i = 1; i <= N; ++i) {
      xylophone_lib.answer(i, A[i]);
    }
  }
}

