/*
  Model solution for task Hacker
  Author: Krzystof Kiljan
  Complexity: O(n log n)
    hac.cpp translated to Java
 */

import java.io.*;
import java.util.*;

public class hac
{
    private static final int MAKS_N = 500 * 1000 + 13;

    int n, operCompNum, myCompNum;
    Vector<Integer> v = new Vector();
    Vector<Integer> sums = new Vector();
    SortedMap<Integer, Integer> curSums = new TreeMap();

    void readIn()
    {
        Scanner sc = new Scanner( System.in );

        n = sc.nextInt();
        operCompNum = n / 2;
        myCompNum = n - operCompNum;

        for(int i = 0; i < n; i++)
        {
            v.add(sc.nextInt());
        }
    }

    void duplicateV()
    {
        for(int j = 0; j < 2; j++)
            for(int i = 0; i < n; i++)
                v.add(v.get(i));
    }

    void precompSums()
    {
        int sum = 0;
        int curStart = 0;
        int end = curStart + myCompNum;

        for (int i = curStart; i < end; i++)
            sum += v.get(i);

        sums.add(sum);

        while (curStart < 2 * n)
        {
            sum -= v.get(curStart);
            curStart++;
            sum += v.get(end);
            end++;
            sums.add(sum);
        }
    }

    // cnt may be equal 1 or -1 if we want to delete the element
    void insertIntoCurSums(int key, int cnt)
    {
        if(cnt == -1)
        {
            if(curSums.get(key) == 1)
                curSums.remove(key);
            else curSums.put(key, curSums.get(key) - 1);
        }
        else
        {
            if(curSums.get(key) != null)
                curSums.put(key, curSums.get(key) + 1);
            else curSums.put(key, 1);
        }

    }

    int calcMaxAns()
    {
        int ans = -1;
        int curStart = n - myCompNum + 1;
        int end = curStart + myCompNum;


        for (int i = curStart; i < end; i++)
            insertIntoCurSums(sums.get(i), 1);

        ans = curSums.firstKey();

        while (end < 2 * n)
        {
            insertIntoCurSums(sums.get(curStart), -1);
            curStart++;
            insertIntoCurSums(sums.get(end), 1);
            end++;
            if(ans < curSums.firstKey())
                ans = curSums.firstKey();
        }

        return ans;
    }

    public static void main(String[] args)
    {
        hac h = new hac();
        h.readIn();
        h.duplicateV();
        h.precompSums();
        System.out.println(h.calcMaxAns());
    }

}
