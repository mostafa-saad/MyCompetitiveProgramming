public class vision {

    private int OR(int[] Ns)
    {
        return grader.add_or(Ns);
    }

    private int XOR(int[] Ns)
    {
        return grader.add_xor(Ns);
    }

    private int XOR(int A, int B)
    {
        int[] gates = {A, B};
        return grader.add_xor(gates);
    }

    private int AND(int A, int B)
    {
        int[] gates = {A, B};
        return grader.add_and(gates);
    }

    private int AND_NOT(int A, int B)
    {
        return AND(A, grader.add_not(B));
    }

    private int[] diagonal(int H, int W, int N, boolean D)
    {
        int first, last, step;
        if (D)
        {
            first = N < W ? N : W * (N - W + 2) - 1;
            last = N < H ? N * W : (H - 1) * W + (N - H + 1);
            step = W - 1;
        }
        else
        {
            first = N < W ? W - 1 - N : W * (N - W + 1);
            last = N < H ? (N + 1) * W - 1 : H * W + (H - 2 - N);
            step = W + 1;
        }
        int[] cells = new int[(last == first ? 0 : (last - first) / step) + 1];
        int cur = first;
        int cnt = 0;
        while (true)
        {
            cells[cnt] = cur;
            if (cur == last)
            {
                break;
            }
            cnt++;
            cur += step;
        }
        return cells;
    }

    private void collect_diagonals(int H, int W, boolean D, int[] ors, int[] xors)
    {
        for (int i = 0; i < H + W - 1; i++)
        {
            int[] cells = diagonal(H, W, i, D);
            ors[i] = OR(cells);
            xors[i] = XOR(cells);
        }
    }

    private int find_pair(int[] ors, int[] xors, int maxDistance)
    {
        int n = maxDistance + 1;
        int[] curOrs = new int[n];
        int[] curXors = new int[n];
        int[] results = new int[Math.max(0, ors.length - maxDistance)];
        for (int i = 0; i < ors.length; i++)
        {
            curOrs[i % n] = ors[i];
            curXors[i % n] = xors[i];
            if (i >= maxDistance)
            {
                results[i - maxDistance] = AND_NOT(OR(curOrs), XOR(curXors));
            }
        }
        return OR(results);
    }

    public void construct_network(int H, int W, int K)
    {
        int diagonals = H + W - 1;
        int[] orsA = new int[diagonals];
        int[] xorsA = new int[diagonals];
        int[] orsB = new int[diagonals];
        int[] xorsB = new int[diagonals];
        collect_diagonals(H, W, true, orsA, xorsA);
        collect_diagonals(H, W, false, orsB, xorsB);
        AND_NOT(AND(find_pair(orsA, xorsA, K),
                    find_pair(orsB, xorsB, K)),
                AND(find_pair(orsA, xorsA, K - 1),
                    find_pair(orsB, xorsB, K - 1)));
    }
}