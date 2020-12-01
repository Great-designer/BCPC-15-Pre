import java.math.BigInteger;
import java.util.Scanner;
 
public class C
{
    public static void main(String[] args)
    {
        Scanner sc=new Scanner(System.in);
        String s=sc.nextLine();
        sc.close();
        BigInteger a=new BigInteger(s);
        BigInteger b=new BigInteger("2");
        BigInteger c=a.remainder(b);
        int d=c.intValue();
        BigInteger e=a.divide(b);
        BigInteger f=new BigInteger("998244352");
        BigInteger g=e.remainder(f);
        long h=g.longValue();
        long ret=1;
        long bas=6;
        for(;h!=0;h=h/2,bas=(bas*bas)%998244353)
        {
            if(h%2==1)
            {
                ret=(ret*bas)%998244353;
            }
        }
        if(d!=0)
        {
            ret=(ret*4)%998244353;
        }
        System.out.println(ret);
    }
}