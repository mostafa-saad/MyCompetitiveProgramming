import java.io.*;
import java.util.Arrays;
import java.util.Comparator;
import java.util.StringTokenizer;

public class Solve_bm2 {
    FastScanner in;
    PrintWriter out;

    class Point {
        int x, y, r, id;
        int removedBy = -1;
        boolean alive = true;

        public Point(int x, int y, int r, int id) {
            this.x = x;
            this.y = y;
            this.r = r;
            this.id = id;
        }

        @Override
        public String toString() {
            return "Point{" +
                    "x=" + x +
                    ", r=" + r +
                    '}';
        }
    }

    Comparator<Point> byY = new Comparator<Point>() {
        @Override
        public int compare(Point o1, Point o2) {
            if (o1.y != o2.y) {
                return Integer.compare(o1.y, o2.y);
            }
            if (o1.x != o2.x) {
                return Integer.compare(o1.x, o2.x);
            }
            return Integer.compare(o1.id, o2.id);
        }
    };

    Comparator<Point> byX = new Comparator<Point>() {
        @Override
        public int compare(Point o1, Point o2) {
            if (o1.x != o2.x) {
                return Integer.compare(o1.x, o2.x);
            }
            if (o1.y != o2.y) {
                return Integer.compare(o1.y, o2.y);
            }
            return Integer.compare(o1.id, o2.id);
        }
    };

    Point[] filter(Point[] pts, Comparator<Point> comp, Point last, boolean firstPart, Point[] res) {
        int r =0 ;
        for (Point pp : pts) {
            boolean first = comp.compare(pp, last) < 0;
            if (first == firstPart) {
                res[r++] = pp;
            }
        }
        if (r != res.length) {
            throw new AssertionError();
        }
        return res;
    }

    final int CNT = 10;

    class Tree {
        Tree left, right;
        Point[] pts;
        int len;

        int minX, maxX, minY, maxY;

        void calcMinMax() {
            minX = Integer.MAX_VALUE;
            maxX = Integer.MIN_VALUE;
            minY = Integer.MAX_VALUE;
            maxY = Integer.MIN_VALUE;
            for (Point p : pts){
                minX = Math.min(minX, p.x);
                minY = Math.min(minY, p.y);
                maxX = Math.max(maxX, p.x);
                maxY = Math.max(maxY, p.y);
            }
        }

        void updateMinMaxFromChild() {
            minX = Math.min(left.minX, right.minX);
            maxX = Math.max(left.maxX, right.maxX);
            minY = Math.min(left.minY, right.minY);
            maxY = Math.max(left.maxY, right.maxY);
        }

        Tree(Point[] ptsByX, Point[] ptsByY) {
            len = ptsByX.length;
            boolean splitByY = (ptsByY[len - 1].y - ptsByY[0].y > ptsByX[len -1].x - ptsByX[0].x);
            for (int i = 0; i + 1 < ptsByX.length; i++) {
                if (byX.compare(ptsByX[i], ptsByX[i + 1]) >= 0) {
                    throw new AssertionError();
                }
            }
            for (int i = 0; i + 1 < ptsByY.length; i++) {
                if (byY.compare(ptsByY[i], ptsByY[i + 1]) >= 0) {
                    throw new AssertionError();
                }
            }
            if (ptsByX.length <= CNT) {
                this.pts = ptsByX;
                calcMinMax();
            } else {
                int size = ptsByX.length / 2;
                Point splitBy = splitByY ? ptsByY[size] : ptsByX[size];
                Comparator<Point> cmp = splitByY ? byY : byX;
                left = new Tree(filter(ptsByX, cmp, splitBy, true, new Point[size]),
                        filter(ptsByY, cmp, splitBy, true, new Point[size]));
                right = new Tree(filter(ptsByX, cmp, splitBy, false, new Point[ptsByX.length - size]),
                        filter(ptsByY, cmp, splitBy, false, new Point[ptsByX.length - size]));
                updateMinMaxFromChild();
            }
        }

        boolean close(Point p) {
            return intersect(minX, maxX, p.x - p.r * 2L, p.x + p.r * 2L) && intersect(minY, maxY, p.y - p.r * 2L, p.y + p.r * 2L);
        }

        int eliminateBy(Point p) {
            if (pts != null) {
                int cnt = 0;
                for (Point p2 : pts) {
                    if (!p2.alive) {
                        continue;
                    }
                    if (intersect(p, p2)) {
                        p2.alive = false;
                        p2.removedBy = p.id + 1;
                    } else {
                        cnt++;
                    }
                }
                return cnt;
            } else {
                if (!close(p)) {
                    return Integer.MAX_VALUE / 2;
                }
                int r1 = left.eliminateBy(p);
                int r2 = right.eliminateBy(p);
                int res = r1 + r2;
                if (res <= CNT) {
                    pts = new Point[res];
                    for (Point pp : left.pts) {
                        if (!pp.alive) {
                            continue;
                        }
                        res--;
                        pts[res] = pp;
                    }
                    for (Point  pp : right.pts) {
                        if (!pp.alive) {
                            continue;
                        }
                        res--;
                        pts[res] = pp;
                    }
                    return pts.length;
                }
                return Integer.MAX_VALUE / 2;
            }
        }
    }

    boolean intersect(Point a, Point b) {
        int dx = a.x - b.x, dy = a.y - b.y;
        return dx * 1L * dx + dy * 1L * dy <= (a.r + b.r) * 1L * (a.r + b.r);
    }

    boolean intersect(int x1, int x2, long y1, long y2) {
        return Math.max(x1, y1) <= Math.min(x2, y2);
    }

    void solve() {
        int n = in.nextInt();
        Point[] a = new Point[n];
        for (int i = 0; i < n; i++) {
            a[i] = new Point(in.nextInt(), in.nextInt(), in.nextInt(), i);
        }
        Arrays.sort(a, byX);
        Point[] aByY = Arrays.copyOf(a, n);
        Arrays.sort(aByY, byY);
        System.err.println("start");
        Tree t = new Tree(a, aByY);
        System.err.println("tree created");
        Arrays.sort(a, new Comparator<Point>() {
            @Override
            public int compare(Point o1, Point o2) {
                if (o1.r != o2.r) {
                    return -Integer.compare(o1.r, o2.r);
                }
                return Integer.compare(o1.id, o2.id);
            }
        });
        for (Point p : a) {
            if (!p.alive) {
                continue;
            }
            t.eliminateBy(p);
        }
        int[] res = new int[n];
        for (Point p : a) {
            res[p.id] = p.removedBy;
        }
        for (int x : res) {
            out.print(x + " ");
        }
        out.println();
    }

    void run() {
        in = new FastScanner(new File("test.in"));
        out = new PrintWriter(System.out);

        solve();

        out.close();
    }

    void runIO() {

        in = new FastScanner(System.in);
        out = new PrintWriter(System.out);

        solve();

        out.close();
    }

    class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        public FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        public FastScanner(InputStream f) {
            br = new BufferedReader(new InputStreamReader(f));
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                String s = null;
                try {
                    s = br.readLine();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                if (s == null)
                    return null;
                st = new StringTokenizer(s);
            }
            return st.nextToken();
        }

        boolean hasMoreTokens() {
            while (st == null || !st.hasMoreTokens()) {
                String s = null;
                try {
                    s = br.readLine();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                if (s == null)
                    return false;
                st = new StringTokenizer(s);
            }
            return true;
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }

        double nextDouble() {
            return Double.parseDouble(next());
        }
    }

    public static void main(String[] args) {
        new Solve_bm2().runIO();
    }
}