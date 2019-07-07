
class coins{

    int[] coin_flips(int[] b, int c) {
        int x = 0;
        for (int i = 0; i < 64; ++ i)
            x ^= b[i] * i;
        int[] flips = new int[1];
        flips[0] = c ^ x;
        return flips;
    }

    int find_coin(int[] b) {
        int x = 0;
        for (int i = 0; i < 64; ++ i)
            x ^= b[i] * i;
        return x;
    }
}