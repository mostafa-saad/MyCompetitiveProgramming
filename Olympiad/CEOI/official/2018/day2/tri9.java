// DK, poreted Mateusz Radecki solution

//import java.util.*;
import java.util.Arrays;
import java.util.*;

class vector {
    int[] data = new int[40*1000 + 15];
    public int   size = 0;

    public int at(int i) {
        return data[i];
    }

    public void set(int i, int x) {
        data[i] = x;
    }

    public int back() {
        return data[size-1];
    }

    public void push_back(int x) {
        data[size] = x;
        ++size;
    }

    public void pop_back() {
        --size;
    }

    public void push_front(int x) {
        for(int i = size; i > 0; --i) {
            data[i] = data[i-1];
        }
        data[0] = x;

        ++size;
    }

    void swap(int i, int j) {
        int tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    }

    public void reverse(int p, int q) {
        --q;
        while(p < q) {
            swap(p, q);
            ++p;
            --q;
        }
    }

    boolean is_less(int a, int b) {
        return trilib.is_clockwise(1, a, b);
    }

    Integer[] take_copy() {
        Integer[] ret = new Integer[size];
        for(int i = 0; i < size; ++i) {
            ret[i] = new Integer(data[i]);
        }

        return ret;
    }

    public void mySort() {
        Integer[] sorted = take_copy();
        Arrays.sort(sorted, new Comparator<Integer>() {
            public int compare(Integer o1, Integer o2) {
                return 1 - 2 * (trilib.is_clockwise(1, (int)o1, (int)o2) ? 1 : 0);
            }
        });
        for(int i = 0; i < size; ++i) {
            data[i] = sorted[i];
        }
    }

    public void swap_with(vector b) {
        int   r = b.size;
        int[] d = b.data;
        b.data = data;
        b.size = size;
        data = d;
        size = r;
    }
}


public class tri {
    static int n;
    static vector[] divide = new vector[2];
    static vector[] hull   = new vector[2];

    public static void main(String[] args) {
        for(int i = 0; i < 2; ++i) {
            divide[i] = new vector();
            hull[i]   = new vector();
        }

        n = trilib.get_n();

        for(int i=3; i<=n; i++) {
            divide[trilib.is_clockwise(1, 2, i) ? 1 : 0].push_back(i);
        }

        for(int h = 0; h<2; ++h) {
            divide[h].push_back(2);
            divide[h].mySort();
            for (int i=0; i < divide[h].size; i++) {
                int r = hull[h].size;
                while (r>1 && !trilib.is_clockwise(hull[h].at(r-2), hull[h].at(r-1), divide[h].at(i))) {
                    r--;
                    hull[h].pop_back();
                }
                hull[h].push_back(divide[h].at(i));
            }
            if(h > 0) {
                hull[h].reverse(0, hull[h].size);
            }
            hull[h].push_front(1); // wloz?
        }

        for(int h=0; h<2; h++) {
            hull[0].pop_back();
            while(true) {
                int out = 1;
                int r   = hull[0].size;

                if (r>1 && !trilib.is_clockwise(hull[0].at(r-2), hull[0].at(r-1), hull[1].back())) {
                    hull[0].pop_back();
                    out=0;
                }

                int d=hull[1].size;
                if (d>1 && !trilib.is_clockwise(hull[0].back(), hull[1].at(d-1), hull[1].at(d-2))) {
                    hull[1].pop_back();
                    out=0;
                }
                if (out > 0) {
                    break;
                }
            }

            for (int i=0; i<2; i++) {
                hull[i].reverse(0, hull[i].size);
            }

            hull[0].swap_with(hull[1]);
        }

        trilib.give_answer(hull[0].size + hull[1].size);
    }
};

