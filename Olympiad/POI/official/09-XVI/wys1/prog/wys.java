/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wyspy na trojkatnej sieci (WYS)                           *
 *   Plik:     wys.java                                                  *
 *   Autor:    Jakub Lacki                                               *
 *   Opis:     Rozwiazanie wzorcowe.                                     *
 *                                                                       *
 *************************************************************************/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.util.TreeSet;
import java.util.HashMap;


public class wys{
    static String przew(String s)
    {
	return s.substring(1)+s.charAt(0);
    }
    static String wspak(String s)
    {
	String ret = new String();
	for(int i=s.length()-1; i>=0; i--)
	    ret = ret + s.charAt(i);
	return ret;
    }
    static String next(String s)
    {
	if(s.charAt(1) == 'a')
	    return "" + (char)(s.charAt(0)-1) + (char)(s.charAt(2)-1) + s.substring(3);
	else
	    return "" + (char)(s.charAt(0)-1) + 'e' + (char)(s.charAt(1)-1) + s.substring(2);
    }
    static String poprawnyKod(String s)
    {
	String ret, akt;
	akt = s;
	ret = new String("z");
	for(int i=0; i<s.length(); i++)
	{
	    if(akt.compareTo(ret) < 0) ret = akt;
	    akt = przew(akt);
	}
	akt = wspak(akt);
	for(int i=0; i<s.length(); i++)
	{
	    if(akt.compareTo(ret)< 0) ret = akt;
	    akt = przew(akt);
	}
	return ret;
    }
    static TreeSet<String> specjalnyPrzypadek()
    {
	TreeSet<String> ret = new TreeSet<String>();
	ret.add("aadecddcddde");
	ret.add("aaececdcddde");
	ret.add("aaedceccddde");
	ret.add("aaeddcebddde");
	ret.add("cdddcddd");
	return ret;
    }

    static TreeSet<String> generuj(String obieg)
    {
	TreeSet<String> ret = new TreeSet<String>();
	if(obieg.charAt(0)== 'a' && obieg.charAt(1) == 'a')
	    return specjalnyPrzypadek();
	else
	{
	    int n = obieg.length()-1;
	    if(obieg.charAt(0) == 'a')
		obieg = przew(obieg);
	    ret.add(poprawnyKod(next(obieg)));
	    obieg = przew(obieg);
	    for(int i=0; i<n; i++)
	    {
		if(obieg.charAt(0) != 'a')
		    ret.add(poprawnyKod(next(obieg)));
		obieg = przew(obieg);
	    }
	    return ret;
	}
    }
    private static HashMap wyniki;

    static void generuj_wszystko()
    {
	wyniki = new HashMap();
	for(int i=1; i<=10; i++)
	    wyniki.put(i, new TreeSet<String>());
	((TreeSet<String>)wyniki.get(1)).add("eee");
	for(int i=1; i<10; i++)
	{
	    for(String st : ((TreeSet<String>)wyniki.get(i)))
	    {
		((TreeSet<String>)wyniki.get(i+1)).addAll(generuj(st));
	    }
	}
    }
    public static void main(String[] args) throws java.io.IOException {
	BufferedReader bufReader = new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer tokenizer = new StringTokenizer(bufReader.readLine());
	generuj_wszystko();
	int t = Integer.parseInt(tokenizer.nextToken());
	for(int i=0; i<t; i++)
	{
	    tokenizer = new StringTokenizer(bufReader.readLine());
	    char typ = tokenizer.nextToken().charAt(0);
	    if(typ == 'N')
	    {
		int k = Integer.parseInt(tokenizer.nextToken());
		System.out.println(((TreeSet<String>)wyniki.get(k)).size());
		int p = 0;
		for(String s : ((TreeSet<String>)wyniki.get(k)))
		{
		    if(p!=0) System.out.print(' ');
		    p = 1;
		    System.out.print(s);
		}
		System.out.println();
	    }
	    else if(typ == 'K')
	    {
		TreeSet<String> wyn = generuj(tokenizer.nextToken());
		System.out.println(wyn.size());
		int p = 0;
		for(String s : wyn)
		{
		    if(p!=0) System.out.print(' ');
		    p = 1;
		    System.out.print(s);
		}
		System.out.println();
	    }
	}
    }
}
