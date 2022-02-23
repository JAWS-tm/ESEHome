package beans;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;


public class Encrypt
{
    public static String hash(String password) throws NoSuchAlgorithmException
    {

        MessageDigest md = MessageDigest.getInstance("SHA-1");
        md.update(password.getBytes());

        byte byteData[] = md.digest();
        StringBuffer sb = new StringBuffer();
        for (int i = 0; i < byteData.length; i++) {
         sb.append(Integer.toString((byteData[i] & 0xff) + 0x100, 16).substring(1));
        }
        return sb.toString();
    }
}